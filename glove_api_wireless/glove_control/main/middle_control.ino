static void middle_control_thread(void* arg) 
{
  int mode = 0;
  int limit_angle = 35; //degree
  double angle = 0;
  double start_distance = 0;
  int enc=0;
  float current_spring_compression = 0;
  float desired_spring_compression = 0; 
  int first_enter = 0;
  int safety = 0;
  while(1)
  { 
    int pot = 0;
    xQueueReceive(middle_pot_Queue, &pot, portMAX_DELAY);
    mode = input[0]; //mode = 0, position control; mode = 1, calibration; mode = 2, force control; mode = 3 safty mode
    //calculate the angle of pot
    angle = (pot-700)*0.028125 + 2.92;
    Serial.println(current_spring_compression);

    //send to comm thread
//    struct comm_msg msg{false, 'm', angle, current_spring_compression};
//    BaseType_t xHigherPriorityTaskWoken_eq = pdFALSE;
//    xQueueSend( com_Queue, &msg, &xHigherPriorityTaskWoken_eq);
    
    //safety factor, if exceed angle, set to orignal position 
    
    if (angle >= limit_angle) 
    {
      
      if(input[4] < middle_encoderValue && mode == 0)
        setpoint_m = input[4];
      else
      {
        if (first_enter == 0)
        {
          safety = middle_encoderValue;
          first_enter = 1;
        }
        setpoint_m = safety;
      }
    }
    else if(mode == 0)
        setpoint_m = input[4];

    else if(mode == 1)
    {
      start_distance = tan(angle*PI/180.0)*23;
      enc = middle_encoderValue;
    }
    else if( mode == 2)
    {
      desired_spring_compression = input[4];
      //------------------calculate the difference
      double encoder_distance = (middle_encoderValue-enc)*0.004386 + start_distance;
      current_spring_compression = encoder_distance - tan(angle*PI/180.0)*23;
      double spring_difference = desired_spring_compression - current_spring_compression;
      //Serial.println(angle);
      //Serial.println(current_spring_compression);
      if(abs(spring_difference) > 0.5)
      {
        int sp = middle_encoderValue + spring_difference/0.004386; //set point = current dis + desired dis
        if (sp < 0)
          setpoint_m = 0;
        else
          setpoint_m = sp;
      }
    }
  }
  
}
