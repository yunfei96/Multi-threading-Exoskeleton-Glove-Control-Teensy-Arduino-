static void ring_control_thread(void* arg) 
{
  int mode = 0;
  int limit_angle = 30; //degree
  double angle = 0;
  double start_distance = 0;
  
  float current_spring_compression = 0;
  float desired_spring_compression = 0; 

  int first_enter = 0;
  int safety = 0;
  int enc = 0;
  while(1)
  {
    int pot = 0;
    xQueueReceive(ring_pot_Queue, &pot, portMAX_DELAY);
    mode = input[0]; //mode = 0, position control; mode = 1, calibration; mode = 2, force control; mode = 3 safty mode
    //calculate the angle of pot
    angle = (pot-550)*0.023529 + 5.23;
    //Serial.println(angle);
    //safety factor, if exceed angle, set to orignal position 
    if (angle >= limit_angle) 
    {
      if(input[5] < ring_encoderValue && mode == 0)
        setpoint_r = input[5];
      else
      {
        if (first_enter == 0)
        {
          safety = ring_encoderValue;
          first_enter = 1;
        }
        setpoint_r = safety;
      }
    }
    
    else if(mode == 0)
        setpoint_r = input[5];
  
    else if(mode == 1)
    {
      start_distance = tan(angle*PI/180.0)*32.5;
      enc = ring_encoderValue;
    }
    else if( mode == 2)
    {
      desired_spring_compression = input[5];
      //------------------calculate the difference
      double encoder_distance = (ring_encoderValue-enc)*0.004386 + start_distance;
      current_spring_compression = encoder_distance - tan(angle*PI/180.0)*32.5;
      double spring_difference = desired_spring_compression - current_spring_compression;
      //Serial.println(angle);
      //Serial.println(current_spring_compression);
      if(abs(spring_difference) > 0.5)
      {
        int sp = ring_encoderValue + spring_difference/0.004386; //set point = current dis + desired dis
        if(sp < 0)
          setpoint_r = 0;
        else
          setpoint_r = sp;
      }
    }
  }
}
