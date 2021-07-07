static void sensor_thread(void* arg) 
{
  //sensor
  int i = 0;
  
  int sum_tr_value = 0;
  int sum_thumb_value = 0;
  int sum_index_value = 0;
  int sum_middle_value = 0;
  int sum_ring_value = 0;
  int sum_pinky_value = 0;
  int sum_wrist_value = 0;
  int sum_fsr_index = 0;
  int sum_fsr_thumb = 0;
  int old_thumb = 0;
  int old_index = 0;
  while(1)
  {
    char flag = 'f';
    xQueueReceive(sensor_trigger_Queue, &flag, portMAX_DELAY);
    if (i<5)
    {
       sum_tr_value = sum_tr_value + analogRead(TR_potPin);
       sum_thumb_value = sum_thumb_value + analogRead(T_potPin);
       sum_index_value = sum_index_value + analogRead(I_potPin);
       sum_middle_value = sum_middle_value + analogRead(M_potPin);
       sum_ring_value = sum_ring_value + analogRead(R_potPin);
       sum_pinky_value = sum_pinky_value + analogRead(P_potPin);
       sum_wrist_value = sum_wrist_value + analogRead(W_potPin);
       i++;
    }
    else
    {
       i=0;
       int tr_value = sum_tr_value/5;
       int thumb_value = sum_thumb_value/5;
       int index_value = sum_index_value/5;
       int middle_value = sum_middle_value/5;
       int ring_value = sum_ring_value/5;
       int pinky_value = sum_pinky_value/5;
       int wrist_value = sum_wrist_value/5;
       int index = analogRead(fsr_i);
       int thumb = analogRead(fsr_t);
       
       //Serial.println(index);
       
       //Serial.println(thumb);
       TickType_t xHigherPriorityTaskWoken_eq = pdFALSE;
       xQueueSend( tr_pot_Queue, &tr_value, xHigherPriorityTaskWoken_eq);
       xQueueSend( t_pot_Queue, &thumb_value, xHigherPriorityTaskWoken_eq);
       xQueueSend( index_pot_Queue, &index_value, xHigherPriorityTaskWoken_eq);
       xQueueSend( middle_pot_Queue, &middle_value, xHigherPriorityTaskWoken_eq);
       xQueueSend( ring_pot_Queue, &ring_value, xHigherPriorityTaskWoken_eq);
       xQueueSend( pinky_pot_Queue, &pinky_value, xHigherPriorityTaskWoken_eq);
       xQueueSend( wrist_pot_Queue, &wrist_value, xHigherPriorityTaskWoken_eq);

       sum_tr_value = 0;
       sum_thumb_value = 0;
       sum_index_value = 0;
       sum_middle_value = 0;
       sum_ring_value = 0;
       sum_pinky_value = 0;
       sum_wrist_value = 0;

       struct comm_msg msg{false, 'f', 'n','n','n'};
       if ((old_thumb - thumb) > 200 or (old_index - index) > 200 )
          msg.slip = 's';
       else 
          msg.slip = 'n';
  
       old_thumb = thumb;
       old_index = index;

       if ( thumb < 3900 )
          msg.thumbc = 'c';
       else
          msg.thumbc = 'n';

       if ( index < 3900 )
          msg.indexc = 'c';
       else
          msg.indexc = 'n';
       
       if (input[8] == 1)
          xQueueSend(com_Queue, &msg, xHigherPriorityTaskWoken_eq);
       sum_fsr_index = 0;
       sum_fsr_thumb = 0;
       
    }
    
   }
    
}
