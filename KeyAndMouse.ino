//keydef[] = {10 , -1 , 1 , -2 , MOUSE_LEFT , -1 , 2 , -2 , MOUSE_LEFT , -3 , KEY_LEFT_CTRL }
// Press/release keys
// PressRelease : 1=Press , 0=Release
// RotTrans     : 1=Rotate , 2=Translate
int keyState = 0;

void DoKeys(int RotTrans, int PressRelease) {
  int keymouse;
  int finished = 0;
  for(int i=1;i <= keydef[0]; i++){
    if(keydef[i]==-1 && keydef[i+1]==RotTrans) {
      //Keyboard.write('c');
      for(int j=i+2; j <= keydef[0]; j++){
        //Keyboard.write('d');
        if(keydef[j] == -2) { keymouse = -2; }
        if(keydef[j] == -3) { keymouse = -3; }
        if(keydef[j] == -1) {
          finished=1;
          break;
        }
          if(keydef[j] > 0 && keymouse == -3 && PressRelease == 1) { Keyboard.press(keydef[j]);   }
        if(debug==0) {
          if(keydef[j] > 0 && keymouse == -2 && PressRelease == 1) { Mouse.press(keydef[j]);      }
          if(keydef[j] > 0 && keymouse == -3 && PressRelease == 0) { Keyboard.release(keydef[j]); }
          if(keydef[j] > 0 && keymouse == -2 && PressRelease == 0) { Mouse.release(keydef[j]);    }
          
        } else { 
          if(keydef[j] > 0 && keymouse == -3 && PressRelease == 1) { Serial.print("KeyPress     : ");Serial.println(keydef[j]);}
          else if(keydef[j] > 0 && keymouse == -2 && PressRelease == 1) { Serial.print("MousePress   : ");Serial.println(keydef[j]);}
          else if(keydef[j] > 0 && keymouse == -3 && PressRelease == 0) { Serial.print("KeyRelease   : ");Serial.println(keydef[j]);}
          else if(keydef[j] > 0 && keymouse == -2 && PressRelease == 0) { Serial.print("MouseRelease : ");Serial.println(keydef[j]);}
          else {
            Serial.print("keydef[j]=");Serial.print(keydef[j]);
            Serial.print(", keymouse=");Serial.print(keymouse);
            Serial.print(", PressRelease=");Serial.print(PressRelease);
          }
        }
      }
      break;
    }
  }
}

void DoMouseXY(int x, int y) {
  if(debug==0) {
    //delay(5);
    Mouse.move(x, y, 0);
    delay(5);
    //Mouse.move(x, y, 0);
    //delay(5);
  } else {
    Serial.print("MouseMove   : ");Serial.print(x);Serial.print(",");Serial.println(y);
  }
}

