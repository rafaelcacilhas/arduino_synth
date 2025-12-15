#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "musicalNotes.h" // A3_note to B5_note
#include "hardware.h"
#define soundPin 13

Adafruit_MCP4725 dac;

float phase = 0.0;
unsigned long lastTime = 0;

float rootFrequency = C4_note; 
float currentNote = C4_note;
bool lastNoteBtnState = HIGH;

int waveType = SINE_WAVE;
int currentWaveType = SINE_WAVE;
bool lastWaveBtnState = HIGH;

float volume = 1.0;
float fadeRate = 0.95;
bool mutePressed = false;
bool volumeOn = true;
bool lastVolBtnState = HIGH;

void setup(){
  for (int i=0; i < 9; i++) pinMode(i,INPUT_PULLUP);
  pinMode(X, INPUT);
  pinMode(Y, INPUT); 
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  noTone(soundPin);

  
  Serial.begin(9600);
  dac.begin(0x60);
}

int getWaveValue(int index, int waveType){
    switch(waveType){
      case SQUARE_WAVE:
        return pgm_read_word(&squareTable[index]);
        break;
      case SINE_WAVE:
        return pgm_read_word(&sineTable[index]);
        break;
      case SAW_WAVE:
        return pgm_read_word(&sawTable[index]);
        break;
      default:
        return 0;
        break;
    } 
}

float getRootFrequency(){
    if (!digitalRead(Abutton)) return C5_note*2;
    if (!digitalRead(Bbutton)) return C4_note/2;
    if     (analogIsUp() && analogIsLeft() )return C5_note*2;
    else if(analogIsUp() && analogIsRight() ) return D4_note;
    else if(analogIsDown() && analogIsRight() )return F4_note;
    else if(analogIsDown() && analogIsLeft() )return A4_note; 
    else if(analogIsUp() ) return C4_note/2;
    else if(analogIsDown() )return G4_note;
    else if(analogIsLeft() )return B4_note;
    else if(analogIsRight() ) return E4_note;

    return rootFrequency;
}

int changeWaveType(int currentType){
  if(currentType == SQUARE_WAVE) return SINE_WAVE;
  if(currentType == SINE_WAVE) return SAW_WAVE;
  if(currentType == SAW_WAVE) return SQUARE_WAVE;
  return 0;  
}

void loop(){
  unsigned long now = micros();  
  if (now - lastTime >= 100) {
    
    lastTime = now;
    rootFrequency = getRootFrequency();
    int index = (int)phase & 0xFF;      // 0-255
    uint16_t dacValue = getWaveValue(index, waveType); // getWaveValue(index, waveType)

    bool currentMute = !digitalRead(Ebutton);
    if (currentMute )                       volume = max(0.0, volume * fadeRate);
    else if (!currentMute && volume < 1.0)  volume = min(1.0, volume / fadeRate);

    if (!digitalRead(Fbutton)) waveType = changeWaveType(waveType);

    dac.setVoltage(dacValue, false);
        
    phase += (256.0 * rootFrequency) / 10000.0;
    if (phase >= 256.0) phase -= 256.0;

    printOutputs(dacValue);
  }
}


bool analogIsUp() {
  return analogRead(Y) > 750;
}

bool analogIsDown() {
  return analogRead(Y) < 250;
}

bool analogIsLeft() {
  return analogRead(X) < 250;
}

bool analogIsRight() {
  return analogRead(X) > 750;
}


void printInputs(float xRead, float yRead){
  Serial.print("X val: ");
  Serial.println("Y val: ");
  Serial.print(xRead);
  Serial.print("   ");
  Serial.println(yRead);

  if      (!digitalRead(K))       Serial.println("K");
  else if (!digitalRead(Fbutton)) Serial.println("F");
  else if (!digitalRead(Ebutton))       Serial.println("E");
  else if (!digitalRead(Dbutton))       Serial.println("D");
  else if (!digitalRead(Cbutton))       Serial.println("C");
  else if (!digitalRead(Bbutton))       Serial.println("B");
  else if (!digitalRead(Abutton))       Serial.println("A");
}

void printOutputs(float dacTeoreticalValue){
    float dacMeasuredValue = analogRead(A0);    
    float opampValue = analogRead(A1);   
    float opampInput = analogRead(A2);   
    float amplitude = 10.0;
    
//    Serial.print("Teorico:");
//    Serial.print(amplitude*dacTeoreticalValue/DacMaxValue);
//    Serial.print(",");
    Serial.print("DAC:");
    Serial.println(dacMeasuredValue);
//    Serial.print(",");
//    Serial.print("OpampInput:");
//    Serial.print(amplitude*opampInput/OutMaxValue);
//    Serial.print(",");
//    Serial.print("OpAmp:");
//    Serial.println(amplitude*opampValue/350.0); 
}
