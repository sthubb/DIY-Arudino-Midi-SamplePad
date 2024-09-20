#include <MIDIUSB.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int threshold = 500;  // Minimum value to trigger a note
const int debounceTime = 50; // Debounce time in milliseconds
const int noiseDelayTime = 2000;  // Delay for initial noise stabilization (2 seconds)

// Pin assignments for piezo sensors
const int piezoPins[6] = {A0, A1, A2, A3, A4, A5};
// MIDI note assignments
const int midiNotes[6] = {42, 44, 46, 36, 38, 37};  // C1, D1, C#1, F#1, G#1, A#1
// MIDI note names
const char* noteNames[6] = {"C1", "D1", "C#1", "F#1", "G#1", "A#1"};

// Store the last trigger time to debounce pads
unsigned long lastTriggerTime[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // Initialize Serial communication for serial monitor output
  Serial.begin(9600);

  for (int i = 0; i < 6; i++) {
    pinMode(piezoPins[i], INPUT);
  }

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Display a startup message
  lcd.setCursor(0, 0);
  lcd.print("Drum Pad Ready!");
  
  // Wait for noise stabilization
  delay(noiseDelayTime);
}

void loop() {
  for (int i = 0; i < 6; i++) {
    int sensorValue = analogRead(piezoPins[i]);

    // Trigger only if value is above threshold and debounce time has passed
    if (sensorValue > threshold && millis() - lastTriggerTime[i] > debounceTime) {
      sendMIDI(midiNotes[i]);
      displayPadInfo(i); // Display pad number and MIDI note on LCD
      printPadInfoToSerial(i); // Print pad info to Serial Monitor
      lastTriggerTime[i] = millis();
    }
  }
}

// Function to send MIDI note
void sendMIDI(byte note) {
  midiEventPacket_t noteOn = {0x09, 0x90, note, 127};  // 127 velocity, note ON
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();

  midiEventPacket_t noteOff = {0x08, 0x80, note, 0};   // note OFF
  delay(10);  // Short delay for note off
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}

// Function to display the pad number and MIDI note on the LCD
void displayPadInfo(int padIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pad: ");
  lcd.print(padIndex + 1);  // Display pad number (1 to 6)
  
  lcd.setCursor(0, 1);
  lcd.print("Note: ");
  lcd.print(noteNames[padIndex]);  // Display MIDI note name (C1, D1, etc.)
}

// Function to print pad info to Serial Monitor
void printPadInfoToSerial(int padIndex) {
  Serial.print("Pad: ");
  Serial.print(padIndex + 1);  // Print pad number (1 to 6)
  Serial.print(" | Note: ");
  Serial.println(noteNames[padIndex]);  // Print MIDI note name (C1, D1, etc.)
}