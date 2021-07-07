static void wrist_control_thread(void* arg) 
{
  int limit_angle_lb = 80; //lower bound
  int limit_angle_ub = 375; //upper bound
  double angle = 0;
  double start_distance = 0;
  
  float current_spring_compression = 0;
  float desired_spring_compression = 0; 
  
  while(1)
  {
    desired_spring_compression = input[7];
    int pot = 0;
    xQueueReceive(wrist_pot_Queue, &pot, portMAX_DELAY);
    
    //current angle
    angle = pot; 
    //Serial.println(angle);
    //Serial.println(desired_spring_compression);
    //-----------------initial position and limit control -------------------------
    if(desired_spring_compression == 0)
    {
      setpoint_w = 0;
      //start_distance = tan((angle-5)*PI/180.0)*28;
    }
    else if(angle <= limit_angle_lb || angle >= limit_angle_ub)
    {
       setpoint_w = wrist_encoderValue;
    }
    else
    {
      setpoint_w = -desired_spring_compression/0.001666667; 
      //------------------calculate the difference
//      double encoder_distance = wrist_encoderValue*0.001666667 + start_distance;
//      current_spring_compression = abs(encoder_distance - tan(angle*PI/180.0)*32);
//      double spring_difference = desired_spring_compression - current_spring_compression;
//      //Serial.println(current_spring_compression);
//      if(abs(spring_difference) > 0.2)
//        setpoint_w = wrist_encoderValue + spring_difference/0.001666667; //set point = current dis + desired dis
    }
   
  }
}
