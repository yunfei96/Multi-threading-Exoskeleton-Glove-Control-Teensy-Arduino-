#include <FreeRTOS_TEENSY4.h>
#include <PID_v1.h>
#include "pinout.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(0,1);
//-------------------------------set up varibles---------------------------------------
//queue
QueueHandle_t com_Queue;
QueueHandle_t motor_Queue;
QueueHandle_t tr_pot_Queue;
QueueHandle_t t_pot_Queue;
QueueHandle_t index_pot_Queue;
QueueHandle_t middle_pot_Queue;
QueueHandle_t ring_pot_Queue;
QueueHandle_t pinky_pot_Queue;
QueueHandle_t wrist_pot_Queue;
QueueHandle_t sensor_trigger_Queue;

//thread
portBASE_TYPE thread0;
portBASE_TYPE thread1;
portBASE_TYPE thread2;
portBASE_TYPE thread3;
portBASE_TYPE thread4;
portBASE_TYPE thread5;
portBASE_TYPE thread6;
portBASE_TYPE thread7;
portBASE_TYPE thread8;
portBASE_TYPE thread9;
//timer
IntervalTimer Timer_0;
IntervalTimer Timer_1;
IntervalTimer Timer_2;

//comunication, desired compression
float input[9] = {0,0,0,0,0,0,0,0,0}; //input from serial

//encoder 
volatile int tr_encoderValue = 0;
volatile int tr_lastEncoded = 0;
volatile int t_encoderValue = 0;
volatile int t_lastEncoded = 0;
volatile int index_encoderValue = 0;
volatile int index_lastEncoded = 0;
volatile int middle_encoderValue = 0;
volatile int middle_lastEncoded = 0;
volatile int ring_encoderValue = 0;
volatile int ring_lastEncoded = 0;
volatile int pinky_encoderValue = 0;
volatile int pinky_lastEncoded = 0;
volatile int wrist_encoderValue = 0;
volatile int wrist_lastEncoded = 0;
//
struct comm_msg {
  bool flag;
  char id;
  char slip;
  char indexc;
  char thumbc;
} ;

//sea control
double kp = 3.5 , ki = 1 , kd = 0.01;             // modify for optimal performance
double input_tr = 0, output_tr = 0, setpoint_tr = 0;
double input_t = 0, output_t = 0, setpoint_t = 0;
double input_i = 0, output_i = 0, setpoint_i = 0;
double input_m = 0, output_m = 0, setpoint_m = 0;
double input_p = 0, output_p = 0, setpoint_p = 0;
double input_r = 0, output_r = 0, setpoint_r = 0;
double input_w = 0, output_w = 0, setpoint_w = 0;
PID t_pid(&input_t, &output_t, &setpoint_t, kp, ki, kd, DIRECT); 
PID tr_pid(&input_tr, &output_tr, &setpoint_tr, kp, ki, kd, DIRECT); 
PID index_pid(&input_i, &output_i, &setpoint_i, kp, ki, kd, DIRECT); 
PID middle_pid(&input_m, &output_m, &setpoint_m, kp, ki, kd, DIRECT);  
PID ring_pid(&input_r, &output_r, &setpoint_r, kp, ki, kd, DIRECT);  
PID pinky_pid(&input_p, &output_p, &setpoint_p, kp, ki, kd, DIRECT); 
PID wrist_pid(&input_w, &output_w, &setpoint_w, kp, ki, kd, DIRECT);   

//------------------------helper----------------------
void pwmOut(int out, int pwm_pin, int dir_pin) {                               
  if (out > 0) {                         // if REV > encoderValue motor move in forward direction.    
    analogWrite(pwm_pin, out);         // Enabling motor enable pin to reach the desire angle
    forward(dir_pin);                           // calling motor to move forward
  }
  else {
    analogWrite(pwm_pin, abs(out));          // if REV < encoderValue motor move in forward direction.                      
    reverse(dir_pin);                            // calling motor to move reverse
  }
}
void forward (int dir_pin) {
  digitalWrite(dir_pin, LOW);  
  
}
void reverse (int dir_pin) {
  digitalWrite(dir_pin, HIGH); 
}


void setup() {
  BT.begin(9600);
  analogReadResolution(12);
  //---------------------------------set up timer(micro seconds 1,000,000)---------------------------------------
  Timer_0.begin(comTimer, 2000); //500Hz 
  Timer_1.begin(motorTimer, 10000); //100Hz
  Timer_2.begin(senTimer, 20000); //50Hz -> 10Hz
  //---------------------------------set up gpio----------------------------------------
  setup_motor_encoder();
  //---------------------------------set up external interrupt--------------------------
  setup_interrupt();
  
  //thumb rotary
  tr_pid.SetMode(AUTOMATIC);   //set PID in Auto mode
  tr_pid.SetSampleTime(10);  // refresh rate of PID controller, 10HZ
  tr_pid.SetOutputLimits(-250, 250); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  //thumb
  t_pid.SetMode(AUTOMATIC);   //set PID in Auto mode
  t_pid.SetSampleTime(10);  // refresh rate of PID controller, 10HZ
  t_pid.SetOutputLimits(-250, 250); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  // index pid 
  index_pid.SetMode(AUTOMATIC);   //set PID in Auto mode
  index_pid.SetSampleTime(10);  // refresh rate of PID controller, 10HZ
  index_pid.SetOutputLimits(-250, 250); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  // mid pid 
  middle_pid.SetMode(AUTOMATIC);   //set PID in Auto mode
  middle_pid.SetSampleTime(10);  // refresh rate of PID controller, 10HZ
  middle_pid.SetOutputLimits(-250, 250); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  //ring
  ring_pid.SetMode(AUTOMATIC);   //set PID in Auto mode
  ring_pid.SetSampleTime(10);  // refresh rate of PID controller, 10HZ
  ring_pid.SetOutputLimits(-250, 250); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  // index pid 
  pinky_pid.SetMode(AUTOMATIC);   //set PID in Auto mode
  pinky_pid.SetSampleTime(10);  // refresh rate of PID controller, 10HZ
  pinky_pid.SetOutputLimits(-250, 250); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  // mid pid 
  wrist_pid.SetMode(AUTOMATIC);   //set PID in Auto mode
  wrist_pid.SetSampleTime(10);  // refresh rate of PID controller, 10HZ
  wrist_pid.SetOutputLimits(-250, 250); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  
  //--------------------------------create queue---------------------------------------- 
  motor_Queue = xQueueCreate(5, sizeof(int) );
  com_Queue = xQueueCreate(5, sizeof(comm_msg) );
  sensor_trigger_Queue = xQueueCreate(5, sizeof(char) );
  tr_pot_Queue = xQueueCreate(5, sizeof(int) );
  t_pot_Queue = xQueueCreate(5, sizeof(int) );
  index_pot_Queue = xQueueCreate(5, sizeof(int) );
  middle_pot_Queue = xQueueCreate(5, sizeof(int) );
  ring_pot_Queue = xQueueCreate(5, sizeof(int) );
  pinky_pot_Queue = xQueueCreate(5, sizeof(int) );
  wrist_pot_Queue = xQueueCreate(5, sizeof(int) );
  //---------------------------------create threads------------------------------------
  thread0 = xTaskCreate(comm_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread1 = xTaskCreate(motor_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread2 = xTaskCreate(tr_control_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread3 = xTaskCreate(thumb_control_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread4 = xTaskCreate(index_control_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread5 = xTaskCreate(middle_control_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread6 = xTaskCreate(ring_control_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread7 = xTaskCreate(pinky_control_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread8 = xTaskCreate(wrist_control_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  thread9 = xTaskCreate(sensor_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  //---------------------------------freertos check-------------------------------------
  Serial.println("Start RTOS");
 
  if (thread0 != pdPASS || thread1 != pdPASS || thread2 != pdPASS || thread3 != pdPASS || thread4 != pdPASS || thread5 != pdPASS || thread6 != pdPASS || thread7 != pdPASS || thread8 != pdPASS || thread9 != pdPASS) 
  {
    Serial.println(F("Creation problem"));
    while(1);
  }
  // start scheduler
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while(1);
  //----------------------------------end setup------------------------------------------
}

void loop() {
  //empty main loop
}
