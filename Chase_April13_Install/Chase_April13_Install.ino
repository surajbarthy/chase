const int stepPin1 = 2;  // Outer Shaft
const int dirPin1 = 5;   // Outer Shaft

const int stepPin2 = 3;  // Inner Shaft
const int dirPin2 = 6;   // Inner Shaft

unsigned long lastStepTime1 = 0;  // Last step time for stepper motor 1
unsigned long lastStepTime2 = 0;  // Last step time for stepper motor 2

// DON'T USE
// one hour
// const float stepDelay1 = 4500 / 60;        // Delay for stepper motor 1 in milliseconds
// const float stepDelay2 = 4500;   // Delay for stepper motor 2 in milliseconds

// 30 minutes
const float stepDelay1 = 2250 / 30;  // Delay for stepper motor 1 in milliseconds
const float stepDelay2 = 2250;       // Delay for stepper motor 2 in milliseconds

// test
// const float stepDelay1 = 60 / 60;  // Delay for stepper motor 1 in milliseconds
// const float stepDelay2 = 60 / 3;   // Delay for stepper motor 2 in milliseconds

// reset timer
const float resetStepDelay1 = 10;  // Delay for stepper motor 1 in milliseconds
const float resetStepDelay2 = 10;       // Delay for stepper motor 2 in milliseconds

int stepsCount2 = 0;   // Counter to track steps of stepper motor 2
int stepsToTake1 = 0;  // Number of steps stepper motor 1 needs to take

// Button Constants
const int buttonPin = 7;

// Button Variables
int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int flag = 0;

unsigned long lastPressTime = 0;
unsigned long doublePressTime = 500;  // Time window for double press detection
int pressCount = 0;

enum PressState {
  WAITING,
  SINGLE_PRESS,
  DOUBLE_PRESS
};

PressState pressState = WAITING;

void setup() {
  pinMode(stepPin1, OUTPUT);  // Outer Shaft
  pinMode(dirPin1, OUTPUT);   // Outer Shaft
  pinMode(stepPin2, OUTPUT);  // Inner Shaft
  pinMode(dirPin2, OUTPUT);   // Inner Shaft

  // Button
  pinMode(buttonPin, INPUT_PULLUP);

  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        unsigned long currentTime = millis();

        if (pressState == WAITING) {
          pressState = SINGLE_PRESS;
          lastPressTime = currentTime;
        } else if (pressState == SINGLE_PRESS && (currentTime - lastPressTime) < doublePressTime) {
          pressState = DOUBLE_PRESS;
        }
      }
    }
  }

  lastButtonState = reading;

  unsigned long currentTime = millis();  // Get the current time

  // Handle press states
  if (pressState == SINGLE_PRESS && (currentTime - lastPressTime) >= doublePressTime) {
    // Single press detected
    Serial.println("Single Press - Toggle dirPin2");
    toggleDirPin2();
    pressState = WAITING;
  } else if (pressState == DOUBLE_PRESS) {
    // Double press detected
    Serial.println("Double Press - Toggle dirPin1");
    toggleDirPin1();
    pressState = WAITING;
  }

  // Step motor 2 continuously
  if (currentTime - lastStepTime2 >= stepDelay2) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(10);  // Pulse width for stepper motor 2
    digitalWrite(stepPin2, LOW);
    lastStepTime2 = currentTime;  // Update last step time for stepper motor 2
    stepsCount2++;                // Increment steps count for stepper motor 2

    // If stepper motor 2 reaches a multiple of 200 steps, set steps to take for stepper motor 1
    if (stepsCount2 % 800 == 0) {
      stepsToTake1 = 800;
      Serial.println(millis());
    }
  }

  // Step motor 1 if steps to take are greater than 0
  if (stepsToTake1 > 0 && currentTime - lastStepTime1 >= stepDelay1) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(10);  // Pulse width for stepper motor 1
    digitalWrite(stepPin1, LOW);
    lastStepTime1 = currentTime;  // Update last step time for stepper motor 1
    stepsToTake1--;               // Decrement steps to take for stepper motor 1
  }
}

void toggleDirPin2() {
  if (flag == 0) {
    Serial.print("LOW");

    // move back 100 steps
    digitalWrite(dirPin2, HIGH);     // Set direction for stepper motor 2
    for (int i = 0; i < 800; i++) {  // Step motor 2 for 100 steps
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(50);  // Pulse width for stepper motor 2
      digitalWrite(stepPin2, LOW);
      delay(resetStepDelay2);  // Delay for stepper motor 2

      int reading = digitalRead(buttonPin);
      if (reading)
        break;
    }
    // stepsCount2=0;
    flag = 1;
  } else {
    Serial.print("HIGH");
    digitalWrite(dirPin2, LOW);
    // for (int i = 0; i < 100; i++) {  // Step motor 2 for 100 steps
    //   digitalWrite(stepPin2, HIGH);
    //   delayMicroseconds(50);  // Pulse width for stepper motor 2
    //   digitalWrite(stepPin2, LOW);
    //   delay(stepDelay2);  // Delay for stepper motor 2
    // }
    stepsCount2 = 0;
    flag = 0;
  }
}

void toggleDirPin1() {
  static bool dir1Flag = false;

  if (dir1Flag == false) {
    Serial.print("LOW");

    // move back 100 steps
    digitalWrite(dirPin1, HIGH);     // Set direction for stepper motor 1
    for (int i = 0; i < 800; i++) {  // Step motor 1 for 100 steps
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(50);  // Pulse width for stepper motor 1
      digitalWrite(stepPin1, LOW);
      delay(resetStepDelay1);  // Delay for stepper motor 1
 
      int reading = digitalRead(buttonPin);
      if (reading)
        break;
    }
    dir1Flag = true;
  } else {
    Serial.print("HIGH");
    digitalWrite(dirPin1, LOW);
    // for (int i = 0; i < 100; i++) {  // Step motor 1 for 100 steps
    //   digitalWrite(stepPin1, HIGH);
    //   delayMicroseconds(50);  // Pulse width for stepper motor 1
    //   digitalWrite(stepPin1, LOW);
    //   delay(stepDelay1);  // Delay for stepper motor 1
    // }
    dir1Flag = false;
  }
}
