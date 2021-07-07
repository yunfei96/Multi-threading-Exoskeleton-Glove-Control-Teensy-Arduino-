#ifndef PINOUT
#define PINOUT

//---------------Pin setting--------------
//thumb rotary sea
int TR_pwmPin = 15;
int TR_dirPin  = 16;
#define TR_encAPin 38
#define TR_encBPin 37

//thumb sea
int T_pwmPin = 2;
int T_dirPin = 3;
#define T_encAPin 25
#define T_encBPin 26

//index sea
int I_pwmPin = 4;
int I_dirPin = 5;
#define I_encAPin 27
#define I_encBPin 28

//middle sea
int M_pwmPin = 6;
int M_dirPin = 7;
#define M_encAPin 29
#define M_encBPin 30

//ring sea
int R_pwmPin = 8;
int R_dirPin = 9;
#define R_encAPin 31
#define R_encBPin 32

//pinky sea
int P_pwmPin = 10;
int P_dirPin = 11;
#define P_encAPin 36
#define P_encBPin 35

//wrist sea
int W_pwmPin = 12;
int W_dirPin = 24;
#define W_encAPin 34
#define W_encBPin 33

//pot
#define TR_potPin 23
#define T_potPin 22
#define I_potPin 21
#define M_potPin 20
#define R_potPin 19
#define P_potPin 14
#define W_potPin 17

#define fsr_i 40
#define fsr_t 39
#endif
