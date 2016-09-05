float xmin = 500;
float xmax = 500;
float xcenter = 536;
float xdeadzone = 1;
float xsensitivity = 0.01;

float ymin = 500;
float ymax = 500;
float ycenter = 502;
float ydeadzone = 1;
float ysensitivity = 0.01;

void initXY() {
  xcenter = analogRead(xpin);
  ycenter = analogRead(ypin);
}

void ReadXY() {
  int xvalue = analogRead(xpin);
  int xmove=0;
  if(xvalue > xmax) xmax = xvalue;
  if(xvalue < xmin) xmin = xvalue;
  //if (xvalue > xcenter + xdeadzone) xmove=((xvalue-xcenter)/(xmax-xcenter))*xsensitivity;
  //if (xvalue < xcenter - xdeadzone) xmove=(1-(xvalue-xmin)/(xcenter-xmin))*xsensitivity*-1;

  if (xvalue > xcenter + xdeadzone) xmove=(xvalue-xcenter)*xsensitivity;
  if (xvalue < xcenter - xdeadzone) xmove=(xvalue-xcenter)*xsensitivity;
  
  int yvalue = analogRead(ypin);
  int ymove=0;
  //if (yvalue > ycenter + ydeadzone) ymove=((yvalue-ycenter-ydeadzone)/(ymax-ycenter-ydeadzone))*ysensitivity;
  //if (yvalue < ycenter - ydeadzone) ymove=(1-(yvalue-ymin)/(ycenter-ydeadzone-ymin))*ysensitivity*-1;

  if (yvalue > ycenter + ydeadzone) ymove=(yvalue-ycenter)*ysensitivity;
  if (yvalue < ycenter - ydeadzone) ymove=(yvalue-ycenter)*ysensitivity;
  
  if(debug!=0){
    Serial.print("Joystick x=");
    Serial.print(xvalue);
    Serial.print(" , y=");
    Serial.println(yvalue);
    Serial.print("Move x=");
    Serial.print(xmove);
    Serial.print(" , y=");
    Serial.println(ymove);
  }

  //if(xmove>0){xmove=5;} 
  //if(xmove<0){xmove=-5;} 
  //if(ymove>0){ymove=5;} 
  //if(ymove<0){ymove=-5;} 
   
  if(xmove!=0 || ymove!=0) {
    mode = newmode;
    if(keyState == 0){
      Queue(0, ActionKeys,  mode,1,0);
      keyState = 1;
    }
     // Does this need a Move 0,0,0 too?
    Queue(0, ActionMouse, mode,xmove,ymove);
    //Queue(0, ActionKeys,  mode,0,0);
    //Queue(15, ActionMouse, mode,-xmove,-ymove);
    Queue(0, ActionMouse, mode,0,0);
  } else {
     if(keyState == 1){
       Queue(0, ActionKeys,  mode,0,0);
       keyState = 0;
     }
  }
  //Queue(100, ActionReadXY, 0,0,0);
}

