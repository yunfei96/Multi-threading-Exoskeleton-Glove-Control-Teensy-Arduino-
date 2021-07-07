static void tr_control_thread(void* arg) 
{
  int mode =0;
  int limit_angle = 95; //degree
  int enc = 0;
  double angle = 0;
  double start_angle = 0;
  
  float current_spring_compression = 0;
  float desired_spring_compression = 0; 
  while(1)
  { 
    int pot = 0;
    xQueueReceive(tr_pot_Queue, &pot, portMAX_DELAY);
    mode = input[0]; //mode = 0, position control; mode = 1, calibration; mode = 2, force control; mode = 3 safty mode
    //calculate the angle of pot
    angle = round(pot*0.081*10)/10.0;
    //Serial.println(angle);
    //safety factor, if exceed angle, set to orignal position 
    if (angle >= limit_angle) 
    {
      if(input[2] < tr_encoderValue && mode == 0)
        setpoint_tr = input[2];
      else
        setpoint_tr = tr_encoderValue;
    }
    
    else if(mode == 0)
        setpoint_tr = input[2];
    
    else if(mode == 1)
    {
       start_angle = angle;
       enc = tr_encoderValue;
    }
      
      
    else if( mode == 2)
    {
      desired_spring_compression = input[2];
      //------------------calculate the difference
      double motor_angle = start_angle + (tr_encoderValue-enc)/33.3; 
      current_spring_compression = angle - motor_angle; 
      double spring_difference = desired_spring_compression - current_spring_compression;
      //Serial.println(current_spring_compression);
      if(abs(spring_difference) > 5)
      {
        int sp = tr_encoderValue - spring_difference*33.3; //set point = current angle + desired angle
        if (sp > 0)
          setpoint_tr = 0;
        else
          setpoint_tr = sp;
      }
    }
  }
}
