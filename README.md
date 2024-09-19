# DIY-Arudino-Midi-SamplePad
이 페이지는 아두이노 레오나르도 보드와 피에조 센서를 이용해 샘플링 드럼패드를 직접 제작하고 개발하는 과정을 서술합니다
<br>

# 만들게 된 계기
  * 기성품 드럼 샘플링 패드들이 전부 50만원대 이상으로 매우 비싸다
  * 그닥 기능도 없는거같은데 어이가 없어서.
    
# 사용된 부품

  * **아두이노 레오나르도** (혹은 ATmega32U4 칩을 사용하며 아날로그 인풋이 6개 이상 가지고 있는 모든 마이크로 컨트롤러) x1
  * **16x2 LCD** (I2C모듈 포함) x1
  * **피에조 센서** x6
  * 1M옴 저항 x6
  * 배선재 
  * 빵판 (권장)


# 회로도 설명
<img width="921" alt="스크린샷 2024-09-04 오후 4 43 47" src="https://github.com/user-attachments/assets/0a7a9a24-aed9-49de-82eb-794e2dbea027">

<br>
<br>


> 본 가이드는 ATmega32u4칩을 내장한 아두이노 레오나르도 기준으로 서술합니다

* 아두이노 우노같은 일반적인 ATmega328P칩셋은 시리얼 신호만 출력하기에 미디 신호를 받으려면 시리얼 신호를 미디로 변환해주는 별도의 프로그램이 필요합니다. 가능하면 레오나르도같이 ATmega32u4칩셋을 사용하는 보드를 사용하세요.
* 회로도 잘못만들어서 LCD 그라운드가 연결되어있지 않습니다.. 참고하여 4개의 핀들 모두 잘 연결해주세요

# 작동 원리
* 아두이노가 피에조 센서의 측정값을 정수로 입력
* 센서 측정값이 threshold 값보다 크고, 이전 음표보다 debounceTime만큼 지났는지 체크하여 중복 입력 방지
* MIDIUSB 라이브러리를 이용하여 미디 값을 전송
* LCD에 패드 번호 (핀번호와 일치함)와 음표 값을 표시 (ex. Pad: 1, Note: C1)

# 하드웨어 제작
<img width="835" alt="스크린샷 2024-09-19 오전 11 21 48" src="https://github.com/user-attachments/assets/2893f7f2-48ca-4ddd-b5a9-06f9cc863f2b">
<br>

* 3D프린트된 베이스에 아크릴 상판을 덮는 형식으로 제작했습니다. 제작하기 위해선 최소 240x190x200mm 사이즈로 출력이 가능한 3D 프린터와 아크릴을 자를 레이저 커팅기가 필요합니다.
<br>

<img width="864" alt="스크린샷 2024-09-19 오전 11 41 54" src="https://github.com/user-attachments/assets/0bba72f2-c880-44b9-8d35-f3410bd8ad21">
<br>

* 각자 패드는 이미지와 같은 방진 구조를 가지고 있습니다. 다른 디자인으로 제작해도 좋지만 진동이 너무 잘 전달되게 되면 피에조 센서에 간섭이 생겨서 다른 노트들이 입력되는 현상이 생길수 있습니다.
<br>

# 제작 과정
![IMG_3290](https://github.com/user-attachments/assets/78b708df-55dd-4f11-9b95-edbfdbdd1e5b)
![IMG_3289](https://github.com/user-attachments/assets/2b2c0797-d0ba-465f-bb8e-bd1281366209)
![IMG_3254](https://github.com/user-attachments/assets/93aeac07-f2e5-4606-8a13-ee8931913922)
![IMG_3288](https://github.com/user-attachments/assets/c7b56019-dcee-4eae-b95d-d96318c8f057)

