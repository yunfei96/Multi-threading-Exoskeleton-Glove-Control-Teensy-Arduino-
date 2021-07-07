static void comm_thread(void* arg) 
{
   int state = 0; //data strucutre: mode, thumb compression, thumb rotatry force, ...., wrist compression 
   //0,0,0,0,0,0,0,0,0,
   //0,100,0,-2000,-2000,-2000,-2000,0,0,
   String readString;
   while(1)
   { 
      struct comm_msg msg{false,'x','x','x','x'};
      xQueueReceive(com_Queue, &msg, portMAX_DELAY);
      if(msg.flag == true)
      {
        if (BT.available())
        {
          char in = BT.read();
          Serial.print(in);
          readString += in;
          state = 1;
        }
        else if(state == 1)
        {
          int end;
          int i = 0;
          while((end=readString.indexOf(","))!=-1)
          {
            String num = readString.substring(0,end);
            readString= readString.substring(end+1,readString.length());
            Serial.println(num); 
            input[i] = num.toFloat();
            i = i+1;
          }
          readString = "";
          state = 0;
        }
      
      }
      else
      {
          BT.print(msg.slip);
          BT.print('\t');
          BT.print(msg.thumbc);
          BT.print('\t');
          BT.print(msg.indexc);
          BT.println('\t');
      }
       
        
    }
    
}
