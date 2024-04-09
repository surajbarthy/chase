const int stepPin1 = 2;  // Outer Shaft
const int dirPin1 = 5;   // Outer Shaft

const int stepPin2 = 3;  // Inner Shaft
const int dirPin2 = 6;   // Inner Shaft

unsigned long lastStepTime1 = 0;  // Last step time for stepper motor 1
unsigned long lastStepTime2 = 0;  // Last step time for stepper motor 2
const int stepDelay1 = 60 / 60;        // Delay for stepper motor 1 in milliseconds
const int stepDelay2 = 60;   // Delay for stepper motor 2 in milliseconds

int stepsCount2 = 0;  // Counter to track steps of stepper motor 2
int stepsToTake1 = 0; // Number of steps stepper motor 1 needs to take

void setup() {
  pinMode(stepPin1, OUTPUT);  // Outer Shaft
  pinMode(dirPin1, OUTPUT);   // Outer Shaft
  pinMode(stepPin2, OUTPUT);  // Inner Shaft
  pinMode(dirPin2, OUTPUT);   // Inner Shaft
  
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();  // Get the current time

  // Step motor 2 continuously
  if (currentTime - lastStepTime2 >= stepDelay2) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(10);  // Pulse width for stepper motor 2
    digitalWrite(stepPin2, LOW);
    lastStepTime2 = currentTime;  // Update last step time for stepper motor 2
    stepsCount2++;  // Increment steps count for stepper motor 2
    
    
    
    // If stepper motor 2 reaches a multiple of 200 steps, set steps to take for stepper motor 1
    if (stepsCount2 % 800 == 0) {
      // Serial.println("AAA");
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
    stepsToTake1--;  // Decrement steps to take for stepper motor 1
    // Serial.print("step1");
    // Serial.println(stepsCount2);
  }
}
