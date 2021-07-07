void setup_motor_encoder()
{
  //thumb rotary
  pinMode(TR_pwmPin, OUTPUT);
  pinMode(TR_dirPin, OUTPUT);
  pinMode(TR_encAPin, INPUT);
  pinMode(TR_encBPin, INPUT);
  pinMode(TR_encAPin, INPUT_PULLUP);
  pinMode(TR_encBPin, INPUT_PULLUP);
  pinMode(TR_potPin, INPUT);

  //thumb
  pinMode(T_pwmPin, OUTPUT);
  pinMode(T_dirPin, OUTPUT);
  pinMode(T_encAPin, INPUT);
  pinMode(T_encBPin, INPUT);
  pinMode(T_encAPin, INPUT_PULLUP);
  pinMode(T_encBPin, INPUT_PULLUP);
  pinMode(T_potPin, INPUT);
  
  //index 
  pinMode(I_pwmPin, OUTPUT);
  pinMode(I_dirPin, OUTPUT);
  pinMode(I_encAPin, INPUT);
  pinMode(I_encBPin, INPUT);
  pinMode(I_encAPin, INPUT_PULLUP);
  pinMode(I_encBPin, INPUT_PULLUP);
  pinMode(I_potPin, INPUT);

  //middle
  pinMode(M_pwmPin, OUTPUT);
  pinMode(M_dirPin, OUTPUT);
  pinMode(M_encAPin, INPUT);
  pinMode(M_encBPin, INPUT);
  pinMode(M_encAPin, INPUT_PULLUP);
  pinMode(M_encBPin, INPUT_PULLUP);
  pinMode(M_potPin, INPUT);

  //Ring
  pinMode(R_pwmPin, OUTPUT);
  pinMode(R_dirPin, OUTPUT);
  pinMode(R_encAPin, INPUT);
  pinMode(R_encBPin, INPUT);
  pinMode(R_encAPin, INPUT_PULLUP);
  pinMode(R_encBPin, INPUT_PULLUP);
  pinMode(R_potPin, INPUT);
  
  //Pinky 
  pinMode(P_pwmPin, OUTPUT);
  pinMode(P_dirPin, OUTPUT);
  pinMode(P_encAPin, INPUT);
  pinMode(P_encBPin, INPUT);
  pinMode(P_encAPin, INPUT_PULLUP);
  pinMode(P_encBPin, INPUT_PULLUP);
  pinMode(P_potPin, INPUT);

  //Wrist
  pinMode(W_pwmPin, OUTPUT);
  pinMode(W_dirPin, OUTPUT);
  pinMode(W_encAPin, INPUT);
  pinMode(W_encBPin, INPUT);
  pinMode(W_encAPin, INPUT_PULLUP);
  pinMode(W_encBPin, INPUT_PULLUP);
  pinMode(W_potPin, INPUT);
  
  //
  pinMode(fsr_i, INPUT);
  pinMode(fsr_t, INPUT);
}

void setup_interrupt()
{
  //----------------------------encoder external interrupt---------------------------
  attachInterrupt(digitalPinToInterrupt(TR_encAPin), update_tr_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(TR_encBPin), update_tr_encoder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(T_encAPin), update_thumb_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(T_encBPin), update_thumb_encoder, CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(I_encAPin), update_index_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(I_encBPin), update_index_encoder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(M_encAPin), update_middle_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(M_encBPin), update_middle_encoder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(R_encAPin), update_ring_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(R_encBPin), update_ring_encoder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(P_encAPin), update_pinky_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(P_encBPin), update_pinky_encoder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(W_encAPin), update_wrist_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(W_encBPin), update_wrist_encoder, CHANGE);
}



  
