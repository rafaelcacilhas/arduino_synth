enum WaveTypes { SQUARE, SINE, SAW, TRIANGLE};

bool soundEnabled = true;
const int buzzerPin = 13;
const int lowPin = 8;
const int highPin = 9;

float rootFrequency = 440.0;
WaveTypes waveType = SQUARE;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(lowPin, INPUT);
  pinMode(highPin, INPUT);
  
  Serial.begin(9600);
}

void handlePause(){
  if (Serial.available()) {
      char cmd = Serial.read();
      if(cmd == 's') {
        soundEnabled = false;
        noTone(buzzerPin);
        Serial.println("Sound stopped!");
      } else if (cmd == 'p') {
        soundEnabled = true;
        Serial.println("Sound playing!");
      }
  }
}

void loop(){
  handlePause();
  if (soundEnabled) {

    if( digitalRead(lowPin)== HIGH && digitalRead(highPin)== HIGH   ){
      tone(buzzerPin, 3*rootFrequency);
    } 
    else if( digitalRead(lowPin)== HIGH  ){
      tone(buzzerPin, rootFrequency);
    } 
    else if(digitalRead(highPin) == HIGH){
      tone(buzzerPin, 2*rootFrequency);
    }
    else {
      noTone(buzzerPin);
    }
  }
  
}
