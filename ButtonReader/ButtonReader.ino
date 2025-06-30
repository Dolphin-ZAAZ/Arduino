bool prevButton1 = false;
bool prevButton2 = false;
bool prevButton3 = false;
bool prevButton4 = false;
bool prevButton5 = false;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); //Power
  pinMode(2, INPUT); //5
  pinMode(3, INPUT_PULLUP); //4
  pinMode(4, INPUT_PULLUP); //3
  pinMode(5, INPUT_PULLUP); //2
  pinMode(6, INPUT_PULLUP); //1
  pinMode(7, INPUT); //Analogue Click
  pinMode(8, OUTPUT); //Passive Buzzer
}

void loop() {
  bool isOn = false;

  int analogueX = analogRead(A4);
  int analogueY = analogRead(A5);
  int analogueClick = digitalRead(7);

  int petentiometerValue = analogRead(A3);

  int soundSensorAnalogue = analogRead(A2);
  int soundSensorDigital = digitalRead(9);

  int button1 = digitalRead(6);
  int button2 = digitalRead(5);
  int button3 = digitalRead(4);
  int button4 = digitalRead(3);
  int button5 = digitalRead(2);

  Serial.println(button5);

  prevButton5 = button5;

  if (button5 == 1) {
    if (button5 != prevButton5) {
      isOn = !isOn;
    }
  }

  // if (isOn) {
  //   digitalWrite(13, HIGH);
  // } else {
  //   digitalWrite(13, LOW);
  // }
}
