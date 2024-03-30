const int stepPin1 = 2;
const int dirPin1 = 5;

const int stepPin2 = 3;
const int dirPin2 = 6;

// Define variables for controlling rotation speed
const unsigned long targetRotationTime = 60000; // Target rotation time in milliseconds (1 minute)
const int stepsPerRevolution = 200; // Number of steps per full revolution
unsigned long stepDelay = targetRotationTime / stepsPerRevolution; // Calculate delay between steps

void setup(void) {
    pinMode(stepPin1, OUTPUT);
    pinMode(dirPin1, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(dirPin2, OUTPUT);
    // We'll send debugging information via the Serial monitor
    Serial.begin(9600);
}

void loop(void) {
    // Set the direction of rotation
    digitalWrite(dirPin1, LOW); // or LOW for opposite direction
    digitalWrite(dirPin2, LOW); // or LOW for opposite direction
    
    // Generate steps to move the stepper motor
    for (int i = 0; i < 800; i++) {
        digitalWrite(stepPin1, HIGH);
        digitalWrite(stepPin2, HIGH);
        delay(18); // Ensure a minimum pulse width (adjust as needed)
        digitalWrite(stepPin1, LOW);
        digitalWrite(stepPin2, LOW);
        delay(20); // Adjust this delay for the desired rotation speed
    }
// delay(1000);
    // Optional: Send debugging information via Serial
    Serial.println("Completed 360 degrees rotation in 1 minute");
}
