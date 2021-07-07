void motorTimer() 
{
  //---------------send queue from IRS--------------------------------
  BaseType_t xHigherPriorityTaskWoken_eq = pdFALSE;
  int dis = 0;
  xQueueSendFromISR( motor_Queue, &dis, &xHigherPriorityTaskWoken_eq);

}

void comTimer() 
{
  //Serial.println("enter timer");
  //---------------send queue from IRS--------------------------------
  BaseType_t xHigherPriorityTaskWoken_eq = pdFALSE;
  struct comm_msg msg{true, 'x','x','x','x'};
  xQueueSendFromISR( com_Queue, &msg, &xHigherPriorityTaskWoken_eq);
  
}

void senTimer() 
{
  //Serial.println("enter timer");
  //---------------send queue from IRS--------------------------------
  BaseType_t xHigherPriorityTaskWoken_eq = pdFALSE;
  char flag = 'f';
  xQueueSendFromISR( sensor_trigger_Queue, &flag, &xHigherPriorityTaskWoken_eq);
  
}

void update_tr_encoder(){
  int MSB = digitalRead(TR_encAPin); //MSB = most significant bit
  int LSB = digitalRead(TR_encBPin); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (tr_lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) tr_encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) tr_encoderValue --;

  tr_lastEncoded = encoded; //store this value for next time
}

void update_thumb_encoder(){
  int MSB = digitalRead(T_encAPin); //MSB = most significant bit
  int LSB = digitalRead(T_encBPin); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (t_lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) t_encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) t_encoderValue --;

  t_lastEncoded = encoded; //store this value for next time
}

void update_index_encoder(){
  int MSB = digitalRead(I_encAPin); //MSB = most significant bit
  int LSB = digitalRead(I_encBPin); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (index_lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) index_encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) index_encoderValue --;

  index_lastEncoded = encoded; //store this value for next time
}

void update_middle_encoder(){
  int MSB = digitalRead(M_encAPin); //MSB = most significant bit
  int LSB = digitalRead(M_encBPin); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (middle_lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) middle_encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) middle_encoderValue --;

  middle_lastEncoded = encoded; //store this value for next time
}

void update_ring_encoder(){
  int MSB = digitalRead(R_encAPin); //MSB = most significant bit
  int LSB = digitalRead(R_encBPin); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (ring_lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) ring_encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) ring_encoderValue --;

  ring_lastEncoded = encoded; //store this value for next time
}

void update_pinky_encoder(){
  int MSB = digitalRead(P_encAPin); //MSB = most significant bit
  int LSB = digitalRead(P_encBPin); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (pinky_lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) pinky_encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) pinky_encoderValue --;

  pinky_lastEncoded = encoded; //store this value for next time
}

void update_wrist_encoder(){
  int MSB = digitalRead(W_encAPin); //MSB = most significant bit
  int LSB = digitalRead(W_encBPin); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (wrist_lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) wrist_encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) wrist_encoderValue --;

  wrist_lastEncoded = encoded; //store this value for next time
}
