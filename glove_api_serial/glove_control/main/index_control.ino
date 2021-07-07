static void index_control_thread(void* arg) 
{
  int mode = 0;
  int limit_angle = 29; //degree
  double angle = 0;
  double start_distance = 0;
  float current_spring_compression = 0;
  float desired_spring_compression = 0; 
  int enc=0;
  int first_enter = 0;
  int safety = 0;
  while(1)
  { 
    int pot = 0;
    xQueueReceive(index_pot_Queue, &pot, portMAX_DELAY);
    mode = input[0]; //mode = 0, position control; mode = 1, calibration; mode = 2, force control;
    //calculate the angle of pot
    angle = (pot-470)*0.02340 + 2.92;
    //Serial.println(index_encoderValue);
    //safety factor, if exceed angle, set to orignal position 

    //send to comm thread
//    struct comm_msg msg{false, 'i', angle, current_spring_compression};
//    BaseType_t xHigherPriorityTaskWoken_eq = pdFALSE;
//    xQueueSend( com_Queue, &msg, &xHigherPriorityTaskWoken_eq);
    
    if (angle >= limit_angle)
    {
      if(input[3] < index_encoderValue && mode == 0)
        setpoint_i = input[3];
      else
      {
        if (first_enter == 0)
        {
          safety = index_encoderValue;
          first_enter = 1;
        }
        setpoint_i = safety;
      }
    }
    
    else if(mode == 0)
        setpoint_i = input[3];
    
    else if(mode == 1)
    {
        start_distance = tan(angle*PI/180.0)*28;
        enc = index_encoderValue;
    }
      
      
    else if( mode == 2)
    {
      desired_spring_compression = input[3];
      //------------------calculate the difference
      double encoder_distance = (index_encoderValue-enc)*0.004386 + start_distance;
      current_spring_compression = encoder_distance - tan(angle*PI/180.0)*28;
      double spring_difference = desired_spring_compression - current_spring_compression;
      //Serial.println(angle);
      //Serial.println(current_spring_compression);
      if(abs(spring_difference) > 0.5)
      {
        int sp = index_encoderValue + spring_difference/0.004386; //set point = current dis + desired dis
        if (sp < 0)
          setpoint_i = 0;
        else
          setpoint_i = sp;
        //Serial.println(index_encoderValue);
      }
    }
    
  }
    
}
