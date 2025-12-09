#pragma once

#define soundPin 13
#define X A0
#define Y A1
#define K 8
#define Fbutton 7
#define E 6
#define D 5
#define C 4
#define B 3
#define A 2


float A3_note = 220.0;
float B3_note = 246.94;

float C4_note = 261.63;
float D4_note = 293.66;
float E4_note = 329.63;
float F4_note = 349.23;
float G4_note = 392.0;
float A4_note = 440.0;
float B4_note = 493.88;

float C5_note = 523.25;
float D5_note = 487.33;
float E5_note = 659.25;
float F5_note = 698.46;
float G5_note = 783.99;
float A5_note = 880.0;
float B5_note = 987.77;

void printInputs(float xRead, float yRead);

bool analogIsLeft();
bool analogIsRight();
bool analogIsDown();
bool analogIsUp();
