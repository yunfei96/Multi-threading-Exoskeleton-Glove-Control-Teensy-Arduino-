static void motor_thread(void* arg) 
{
  
  while(1)
  {
    int pos = 0;
    xQueueReceive(motor_Queue, &pos, portMAX_DELAY);

    input_tr = tr_encoderValue;
    input_t = t_encoderValue;
    input_i = index_encoderValue;
    input_m = middle_encoderValue;
    input_r = ring_encoderValue;
    input_p = pinky_encoderValue;
    input_w = wrist_encoderValue;
    
    t_pid.Compute();                 // calculate thumb output
    if(abs(output_t) < 60)
      output_t = 0;
    pwmOut(output_t, T_pwmPin, T_dirPin);

    tr_pid.Compute();                 // calculate thumb rotatry output
    if(abs(output_tr) < 60)
      output_tr = 0;
    pwmOut(-output_tr, TR_pwmPin, TR_dirPin);

    
    index_pid.Compute();                 // calculate index output
    
    if(abs(output_i) < 60)
      output_i = 0;
    pwmOut(output_i, I_pwmPin, I_dirPin);

    middle_pid.Compute();                 // calculate middle output
    if(abs(output_m) < 60)
      output_m = 0;
    pwmOut(output_m, M_pwmPin, M_dirPin);

    ring_pid.Compute();                 // calculate ring output
    if(abs(output_r) < 60)
      output_r = 0;
    pwmOut(output_r, R_pwmPin, R_dirPin);

    pinky_pid.Compute();                 // calculate pinky output
    if(abs(output_p) < 60)
      output_p = 0;
    pwmOut(output_p, P_pwmPin, P_dirPin);

    wrist_pid.Compute();                 // calculate wrist output
    if(abs(output_w) < 60)
      output_w = 0;
    pwmOut(output_w, W_pwmPin, W_dirPin);

    
    
    
    
  }
    
}
