#define xpin A0
#define ypin A1
#define zpin A2
#define debugpin A5

float xmin = 514;
float xmax = 585;
float xcenter = 536;
float xdeadzone = 5;
float xsensitivity = 5;

float ymin = 455;
float ymax = 540;
float ycenter = 502;
float ydeadzone = 5;
float ysensitivity = 5;

float zmin = 416;
float zmax = 597;
float zcenter = 465;
float zdeadzone = 3;
float zsensitivity = 2;

int mode = 20; // 10,11=Rotate , 20,21=Translate/Zoom

int debug = 0;
void setup() {
  pinMode(13, OUTPUT);
  pinMode(debugpin,INPUT_PULLUP);
  delay(1000);
  int sensorVal = digitalRead(debugpin);
  if (sensorVal==LOW){
    debug = 1;
    Serial.begin(9600);

  } else {
    Mouse.begin();
    Keyboard.begin();  
  }
}

void loop() {
  int xvalue = analogRead(xpin);
  int xmove=0;
  if (xvalue > xcenter + xdeadzone) xmove=((xvalue-xcenter-xdeadzone)/(xmax-xcenter-xdeadzone))*xsensitivity;
  if (xvalue < xcenter - xdeadzone) xmove=(1-(xvalue-xmin)/(xcenter-xdeadzone-xmin))*xsensitivity*-1;

  int yvalue = analogRead(ypin);
  int ymove=0;
  if (yvalue > ycenter + ydeadzone) ymove=((yvalue-ycenter-ydeadzone)/(ymax-ycenter-ydeadzone))*ysensitivity;
  if (yvalue < ycenter - ydeadzone) ymove=(1-(yvalue-ymin)/(ycenter-ydeadzone-ymin))*ysensitivity*-1;
  
  int zvalue = analogRead(zpin);
  int zmove=0;
  //if (zvalue > zcenter + zdeadzone) zmove=((zvalue-zcenter-zdeadzone)/(zmax-zcenter-zdeadzone))*zsensitivity;
  //if (zvalue < zcenter - zdeadzone) zmove=(1-(zvalue-zmin)/(zcenter-zdeadzone-zmin))*zsensitivity*-1;

  if (debug==0){
    if(xmove!=0 || ymove!=0 || zmove!=0) {
      digitalWrite(13, HIGH);
      if(mode==10){
        Keyboard.press(KEY_LEFT_SHIFT);
        Mouse.press(MOUSE_MIDDLE);
        delay(10);
        mode=11;
      }
      if(mode==11){
        Mouse.move(-xmove, ymove, 0);
      }
      if(mode==20){
        Keyboard.press(KEY_LEFT_SHIFT);
        Mouse.press(MOUSE_MIDDLE);
        delay(10);
        mode=21;
      }
      if(mode==21){
        Mouse.move(-xmove, ymove, zmove);
      }      
    } else {
      digitalWrite(13, LOW);
      if(mode==11){
        Mouse.release(MOUSE_MIDDLE);
        Keyboard.release(KEY_LEFT_SHIFT);
        mode=10;
      }
      if(mode==21){
        Mouse.release(MOUSE_MIDDLE);
        Keyboard.release(KEY_LEFT_SHIFT);
        mode=20;
      }
    }
  } else {
      Serial.print("x = " );
      Serial.print(xvalue);
      Serial.print(" / " );
      Serial.print(xmove);
      Serial.print(" , y = " );
      Serial.print(yvalue);
      Serial.print(" / " );
      Serial.print(ymove);
      Serial.print(" , z = " );
      Serial.print(zvalue);
      Serial.print(" / " );
      Serial.print(zmove);
      Serial.println("." );
      
      //Serial.print("\t Output = ");
      //Serial.println(xmove);
  }

  delay(100);

}
