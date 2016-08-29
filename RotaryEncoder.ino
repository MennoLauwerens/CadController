int SwitchLastVal = HIGH;
int SwitchRepeat = 0;

long oldPosition  = -999;
long newPosition;

void ReadRESwitch(){
  int SwitchState = digitalRead(ReSwitchpin);
//  if(debug!=0){
//    Serial.print("SwitchState=");
//    Serial.println(SwitchState);
//  }
  if(SwitchState == SwitchLastVal) {
    if(++SwitchRepeat>5) SwitchRepeat=5;
    if(SwitchRepeat==2 && SwitchState==LOW ) {
      if(mode == Translate) {
        newmode = Rotate;
      } else {
        newmode = Translate;
      }
    }
  } else {
    SwitchLastVal = SwitchState;
    SwitchRepeat = 0;
  }
  ReadRE();
}

void ReadRE(){
  newPosition = myEnc.read();
  if(debug!=0){
    Serial.print("newPosition=");
    Serial.println(newPosition);
  }
  if (newPosition > oldPosition +3) {
    Mouse.move(0, 0, -1);
    oldPosition = newPosition;
  }
  if (newPosition < oldPosition -3) {
    Mouse.move(0, 0, 1);
    oldPosition = newPosition;
  } 
}

