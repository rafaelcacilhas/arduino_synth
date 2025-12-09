#include "musicalNotes.h" // A3_note to B5_note
#include "joystick.h"
#define soundPin 13

void setup(){
  for (int i=0; i < 9; i++) pinMode(i,INPUT_PULLUP);
  pinMode(X, INPUT);
  pinMode(Y, INPUT); 
  noTone(soundPin);
  
  Serial.begin(9600);
}


void loop(){
  float xRead = analogRead(X)*1.0/1024; // Left = 0; Middle = 0.5; Right = 1.0;
  float yRead = analogRead(Y)*1.0/1024; // Down = 0; Middle = 0.5; Up = 1.0;
  printInputs(xRead,yRead);

  if (!digitalRead(E)) {
    noTone(13);
  }

  if( analogIsUp() && analogIsLeft() ) {
    tone(soundPin,C5_note); 
  }
  else if(analogIsUp() && analogIsRight() ){
    tone(soundPin,D4_note);
  }
  else if(analogIsDown() && analogIsRight() ){
    tone(soundPin,F4_note);
  }
  else if(analogIsDown() && analogIsLeft() ){
    tone(soundPin,A4_note);
  }    
  else if(analogIsRight() ){
    tone(soundPin,E4_note);
  }
  else if(analogIsDown() && analogIsRight() ){
    tone(soundPin,F4_note);
  }
  else if(analogIsUp() ){
    tone(soundPin,C4_note);
  }
  else if(analogIsDown() ){
    tone(soundPin,G4_note);
  }
  else if(analogIsLeft() ){
    tone(soundPin,B4_note);
  }
  else if(analogIsRight() ){
    tone(soundPin,E4_note);
  }
  
   
  delay(100);

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

  if      (!digitalRead(K)) Serial.println("K");
  else if (!digitalRead(Fbutton)) Serial.println("F");
  else if (!digitalRead(E)) Serial.println("E");
  else if (!digitalRead(D)) Serial.println("D");
  else if (!digitalRead(C)) Serial.println("C");
  else if (!digitalRead(B)) Serial.println("B");
  else if (!digitalRead(A)) Serial.println("A");
  
}
