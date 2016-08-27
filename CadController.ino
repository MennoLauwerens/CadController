//#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#define xpin A0
#define ypin A1
//#define zpin A2
#define ReSwitchpin A2
#define debugpin A5

#define encoder0PinClk 3 //clk
#define encoder0PinDta 2 //dta


Encoder myEnc( encoder0PinClk, encoder0PinDta );

#define Rotate 1
#define Translate 2
float zmin = 416;
float zmax = 597;
float zcenter = 465;
float zdeadzone = 3;
float zsensitivity = 2;

// Definities per programma per mode keys(mouse&kb) bij een move
// N , -1 , mode , -2 , MOUSEKEY [,MOUSEKEY] , -3, KBKEY [, KBKEY]

// 3D Builder
int keydef1[] = {10 , -1 , 1 , -2 , MOUSE_LEFT , -1 , 2 , -2 , MOUSE_LEFT , -3 , KEY_LEFT_CTRL };

int keydef[] = {10 , -1 , 1 , -2 , MOUSE_LEFT , -1 , 2 , -2 , MOUSE_LEFT , -3 , KEY_LEFT_CTRL };

//int mode = Rotate;
int newmode = Rotate;
int mode = newmode;
 
int debug = 0;

//Queue---------------------
#define MaxQueueLength 25
#define ActionReadXY 1
#define ActionKeys 2
#define ActionMouse 3
#define ActionRESwitch 4

unsigned long QueueTime[MaxQueueLength];
int QueueModule[MaxQueueLength];
int QueueAction[MaxQueueLength];
int QueueData1[MaxQueueLength];
int QueueData2[MaxQueueLength];
int QueueLength = 0;
int QueueChanged = false;
//--------------------------


// Add event to comandqueue
void Queue(int delayms, int module, int action,int data1 = 0,int data2 = 0) {
  QueueTime[QueueLength] = millis() + delayms;
  QueueModule[QueueLength] = module;
  QueueAction[QueueLength] = action;
  QueueData1[QueueLength] = data1;
  QueueData2[QueueLength] = data2;
  QueueLength++;
  QueueChanged=true;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(debugpin,INPUT_PULLUP);
  pinMode(ReSwitchpin, INPUT_PULLUP);

  
  //Check for Debug mode
  delay(500);
  int sensorVal = digitalRead(debugpin);
  if (sensorVal==LOW){
    debug = 1;
    Serial.begin(9600);
    while (!Serial) ;
    Serial.println("Debugging ON");
  } else {
    Mouse.begin();
    Keyboard.begin();  
  }
  initXY();
  Queue(1000,ActionReadXY,0,0,0);
  Queue(800,ActionRESwitch,0,0,0);
  
}

void loop() {
 if (QueueChanged) {
    //Serial.print("QueueLength: ");
    //Serial.println(QueueLength);
    //DumpQueue();
    QueueChanged=false;
  }
  if(QueueLength==0) {Queue(0, ActionReadXY, 0,0,0);Queue(0,ActionRESwitch,0,0,0);} 
  for (int i=0;i < QueueLength;i++) {

    if (QueueTime[i] <= millis()) {
      int QModule = QueueModule[i];
      int QAction = QueueAction[i];
      int QData1 = QueueData1[i];
      int QData2 = QueueData2[i];
      for (int j=i;j < QueueLength;j++) {
        QueueTime[j] = QueueTime[j+1];
        QueueModule[j] = QueueModule[j+1];
        QueueAction[j] = QueueAction[j+1];        
        QueueData1[j] = QueueData1[j+1];
        QueueData2[j] = QueueData2[j+1];
      }
      QueueLength--;
      QueueChanged=true; 
      switch (QModule) {
        case 0:
          // do nothing for debugging
          break;
        case ActionReadXY:
          ReadXY();
          break;
        case ActionKeys:
          Serial.println("ActionKeys");
          DoKeys(QAction, QData1);
          break;   
        case ActionMouse:
          DoMouseXY(QData1,QData2);
          break;
        case ActionRESwitch:
          ReadRESwitch();
          break;
      }
      break;
    }
  }
  delay(10);

}



// Removel all scheduled events for one type
void QueueRemove(int module){
  //Serial.print("Remove:");
  //Serial.println(module);
  //DumpQueue();
  int i = 0;
  for (int j=0;j < QueueLength;j++){
    if (QueueModule[j] != module) {
      QueueTime[i] = QueueTime[j];
      QueueModule[i] = QueueModule[j];
      QueueAction[i] = QueueAction[j];
      QueueData1[i] = QueueData1[j];
      QueueData2[i] = QueueData2[j];
      i++;
    }   
  }
  QueueLength = i;
  QueueChanged=true;
  //DumpQueue();
}

void DumpQueue(){    
  Serial.println("DumpQueue:");
  for (int i=0;i < QueueLength;i++){
    Serial.print(i);
    Serial.print(" - ");
    Serial.print(QueueTime[i]);
    Serial.print(" - ");
    Serial.print(QueueModule[i]);
    Serial.print(" - ");
    Serial.print(QueueAction[i]);
    Serial.print(" - ");
    Serial.print(QueueData1[i]);
    Serial.print(" - ");
    Serial.print(QueueData2[i]);
    Serial.println(".");
  }  
}
