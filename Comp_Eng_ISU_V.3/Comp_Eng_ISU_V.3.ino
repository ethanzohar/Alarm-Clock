//2D array used to hold all the pins of each of the six seven segment displays
int clocks[6][7] = {{24, 25, 46, 45, 44, 23, 22}, {28, 29, 49, 48, 47, 27, 26}, {31, 32, 52, 51, 50, 30, 53}, {35, 36, 4, 3, 2, 34, 33}, {38, 39, 7, 6, 5, 37, 8} , {42, 43, 11, 10, 9, 41, 40}};

//an array used to hold the six different values that will be displayed on the seven segment displays
int currentTime[6];

//changes the delay of the second counter
int timeDelay = 1000;

//variables used to keep track of the time
int second01 = 0;
int second10 = 0;
int minute01 = 8;
int minute10 = 0;
int hour01 = 0;
int hour10 = 0;

//variables used to keep track of the time of the alarm
int alarmTime0001 = 0;
int alarmTime0010 = 0;
int alarmTime0100 = 0;
int alarmTime1000 = 0;

//varibles used to declare the pins of the buttons
int alarmButton = A1;
int minuteButton = A2;
int hourButton = A3;

//variable used to declare the pin of the switch
int alarmSwitch = A4;

//variables for the led pins
int ledRed = A8;
int ledGreen = A9;

//varibale used to declare the pin of the buzzer
int buzzerPin = 12;

//variables used to detect a HIGH or LOW signal from the buttons
int snooze;
int minuteCounter;
int hourCounter;

//variable used to detect a HIGH or LOW signal from the switch
int alarmOn;

//booleans used to check if the alarm is being set or not
boolean alarmToggle = false;
boolean alarmSet = false;
boolean alarmStart = false;

void setup() {
  //for loop used to set all the pins in the clocks array as OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(clocks[0][i], OUTPUT);
    pinMode(clocks[1][i], OUTPUT);
    pinMode(clocks[2][i], OUTPUT);
    pinMode(clocks[3][i], OUTPUT);
    pinMode(clocks[4][i], OUTPUT);
    pinMode(clocks[5][i], OUTPUT);
  }
  //declares the buzzerPin as an OUTPUT
  pinMode(buzzerPin, OUTPUT);

  //declares all the button pins as an INPUT
  pinMode(alarmButton, INPUT);
  pinMode(minuteButton, INPUT);
  pinMode(hourButton, INPUT);

  //declares the led pins as OUTPUT
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  // declares the switch pin as an INPUT
  pinMode(alarmSwitch, INPUT);

  //Starts the serial monitor
  Serial.begin(9600);
}
void alarm() {
  if (alarmTime0001 == minute01 && alarmTime0010 == minute10 && alarmTime0100 == hour01 && alarmTime1000 == hour10 && alarmOn == true && alarmSet == false && alarmStart == true) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    alarmStart = false;
    digitalWrite(buzzerPin, LOW);
  }
}
//Function used to check when a time value has maxed out and changes it accordingly
void timeTrack() {
  if (second01 >= 9) {
    second10++;
    second01 = -1;
  }
  if (second10 == 6) {
    minute01++;
    second10 = 0;
  }
  if (minute01 == 10) {
    minute10++;
    minute01 = 0;
  }
  if (minute10 == 6) {
    hour01++;
    minute10 = 0;
  }
  if (hour01 == 10) {
    hour10++;
    hour01 = 0;
  }
  if (hour10 == 2 && hour01 == 4) {
    hour01 = 0;
    hour10 = 0;
  }
  if (alarmTime0100 == 10) {
    alarmTime1000++;
    alarmTime0100 = 0;
  }
  if (alarmTime0001 == 10) {
    alarmTime0010++;
    alarmTime0001 = 0;
  }
  if (alarmTime1000 == 2 && alarmTime0100 == 4) {
    alarmTime1000 = 0;
    alarmTime0100 = 0;
  }
  if (alarmTime0010 == 6) {
    alarmTime0010 = 0;
  }
  //Adds a value of 1 to second01 each second
  second01++;
  delay(timeDelay);
}
//Function used to draw the proper number that corrisponds to the proper time on each of the displays
void displays() {
  for (int i = 0; i < 6; i++) {
    if (currentTime[i] == 0) {
      zero(clocks[i]);
    } else if (currentTime[i] == 1) {
      one(clocks[i]);
    } else if (currentTime[i] == 2) {
      two(clocks[i]);
    } else if (currentTime[i] == 3) {
      three(clocks[i]);
    } else if (currentTime[i] == 4) {
      four(clocks[i]);
    } else if (currentTime[i] == 5) {
      five(clocks[i]);
    } else if (currentTime[i] == 6) {
      six(clocks[i]);
    } else if (currentTime[i] == 7) {
      seven(clocks[i]);
    } else if (currentTime[i] == 8) {
      eight(clocks[i]);
    } else if (currentTime[i] == 9) {
      nine(clocks[i]);
    }
  }
}
//Function used to check the button inputs, change the clock time, and set the alarm
void buttonInputs() {
  if (minuteCounter == 0) {
    if (alarmSet == false) {
      minute01++;
    } else if (alarmSet == true) {
      alarmTime0001++;
    }
  }
  if (hourCounter == 0) {
    if (alarmSet == false) {
      hour01++;
    } else if (alarmSet == true) {
      alarmTime0100++;
    }
  }
  if (snooze == 0) {
    alarmStart = true;
    if (alarmSet == false && alarmToggle == false) {
      alarmSet = true;
      alarmToggle = true;
    } else if (alarmSet == true && alarmToggle == false) {
      alarmSet = false;
      alarmToggle = true;
    }
  } else if (snooze == 1) {
    alarmToggle = false;
  }
}
//Sets the led to green or red based on if the alarm is on or being set
void led() {
  if (alarmSet == true) {
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 255);
  } else if (alarmOn == true) {
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 0);
  } else {
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 0);
  }
}
//function to draw the number zero
void zero(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], HIGH);
  digitalWrite(i[4], HIGH);
  digitalWrite(i[5], HIGH);
  digitalWrite(i[6], LOW);
}
//function to draw the number one
void one(int i []) {
  digitalWrite(i[0], LOW);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], LOW);
  digitalWrite(i[4], LOW);
  digitalWrite(i[5], LOW);
  digitalWrite(i[6], LOW);
}
//function to draw the number two
void two(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], LOW);
  digitalWrite(i[3], HIGH);
  digitalWrite(i[4], HIGH);
  digitalWrite(i[5], LOW);
  digitalWrite(i[6], HIGH);
}
//function to draw the number three
void three(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], HIGH);
  digitalWrite(i[4], LOW);
  digitalWrite(i[5], LOW);
  digitalWrite(i[6], HIGH);
}
//function to draw the number four
void four(int i []) {
  digitalWrite(i[0], LOW);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], LOW);
  digitalWrite(i[4], LOW);
  digitalWrite(i[5], HIGH);
  digitalWrite(i[6], HIGH);
}
//function to draw the number five
void five(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], LOW);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], HIGH);
  digitalWrite(i[4], LOW);
  digitalWrite(i[5], HIGH);
  digitalWrite(i[6], HIGH);
}
//function to draw the number six
void six(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], LOW);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], HIGH);
  digitalWrite(i[4], HIGH);
  digitalWrite(i[5], HIGH);
  digitalWrite(i[6], HIGH);
}
//function to draw the number seven
void seven(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], LOW);
  digitalWrite(i[4], LOW);
  digitalWrite(i[5], LOW);
  digitalWrite(i[6], LOW);
}
//function to draw the number eight
void eight(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], HIGH);
  digitalWrite(i[4], HIGH);
  digitalWrite(i[5], HIGH);
  digitalWrite(i[6], HIGH);
}
//function to draw the number nine
void nine(int i []) {
  digitalWrite(i[0], HIGH);
  digitalWrite(i[1], HIGH);
  digitalWrite(i[2], HIGH);
  digitalWrite(i[3], HIGH);
  digitalWrite(i[4], LOW);
  digitalWrite(i[5], HIGH);
  digitalWrite(i[6], HIGH);
}
//main loop for the program
void loop() {
  //variables set to detecting inputs from the buttons
  snooze = digitalRead(alarmButton);
  minuteCounter = digitalRead(minuteButton);
  hourCounter = digitalRead(hourButton);

  //variable set to detecting input from the switch
  alarmOn = digitalRead(alarmSwitch);

  Serial.println(snooze);
  Serial.println(minuteCounter);
  Serial.println(hourCounter);
  Serial.println(alarmOn);
  Serial.println();

  //calling the functions into the main loop
  alarm();
  timeTrack();
  displays();
  buttonInputs();
  led();

  //sets the currentTime array to be either the real time or the time shown on the alarm
  if (alarmSet == false) {
    currentTime[0] = hour10;
    currentTime[1] = hour01;
    currentTime[2] = minute10;
    currentTime[3] = minute01;
    currentTime[4] = second10;
    currentTime[5] = second01;
  } else if (alarmSet == true) {
    currentTime[0] = alarmTime1000;
    currentTime[1] = alarmTime0100;
    currentTime[2] = alarmTime0010;
    currentTime[3] = alarmTime0001;
    currentTime[4] = 0;
    currentTime[5] = 0;
  }
}

