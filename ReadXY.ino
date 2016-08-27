float xmin = 514;
float xmax = 585;
float xcenter = 536;
float xdeadzone = 1;
float xsensitivity = 1;

float ymin = 455;
float ymax = 540;
float ycenter = 502;
float ydeadzone = 1;
float ysensitivity = 1;

void initXY() {
  xcenter = analogRead(xpin);
  ycenter = analogRead(ypin);
}

void ReadXY() {
  int xvalue = analogRead(xpin);
  int xmove=0;
  //if (xvalue > xcenter + xdeadzone) xmove=((xvalue-xcenter-xdeadzone)/(xmax-xcenter-xdeadzone))*xsensitivity;
  //if (xvalue < xcenter - xdeadzone) xmove=(1-(xvalue-xmin)/(xcenter-xdeadzone-xmin))*xsensitivity*-1;

  if (xvalue > xcenter + xdeadzone) xmove=(xvalue-xcenter)*xsensitivity;
  if (xvalue < xcenter - xdeadzone) xmove=(xvalue-xcenter)*xsensitivity;
  
  int yvalue = analogRead(ypin);
  int ymove=0;
  //if (yvalue > ycenter + ydeadzone) ymove=((yvalue-ycenter-ydeadzone)/(ymax-ycenter-ydeadzone))*ysensitivity;
  //if (yvalue < ycenter - ydeadzone) ymove=(1-(yvalue-ymin)/(ycenter-ydeadzone-ymin))*ysensitivity*-1;

  if (yvalue > ycenter + ydeadzone) ymove=(yvalue-ycenter)*ysensitivity;
  if (yvalue < ycenter - ydeadzone) ymove=(yvalue-ycenter)*ysensitivity;
  
//  if(debug!=0){
//    Serial.print("Joystick x=");
//    Serial.print(xvalue);
//    Serial.print(" , y=");
//    Serial.println(yvalue);
//  }

  if(xmove>0){xmove=5;} 
  if(xmove<0){xmove=-5;} 
  if(ymove>0){ymove=5;} 
  if(ymove<0){ymove=-5;} 
   
  if(xmove!=0 || ymove!=0) {
    mode = newmode;
    Queue(0, ActionKeys,  mode,1,0); // Does this need a Move 0,0,0 too?
    Queue(0, ActionMouse, mode,xmove,ymove);
    Queue(0, ActionKeys,  mode,0,0);
    Queue(15, ActionMouse, mode,-xmove,-ymove);
    Queue(20, ActionMouse, mode,0,0);
  }
  //Queue(100, ActionReadXY, 0,0,0);
}

