////////////////////////////////////////////////
////       BLIMB 0.3
////         ****
////      Kärki Mitja
////    Mustaniemi Janne
////         ****
////         2016
////////////////////////////////////////////////

#include <Servo.h>
#include <SSD1306_text.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(11,10); // BT_RX=D11, BT_TX=D10

Servo s_mount;
Servo s_shoulder;
Servo s_arm;
Servo s_clamp;  

SSD1306_text oled;

// Serial input data from mobile app
char com_in[11];

// Variables that hold servo position values
uint8_t pos_planar;
uint8_t pos_shoulder;
uint8_t pos_arm;
uint8_t pos_clamp;
uint8_t pos_planar_old = 90;
uint8_t pos_shoulder_old = 90;
uint8_t pos_arm_old = 90;
bool clamp_shut = false;
uint8_t clamp_sensor = 8;     //sensor in the clamp
int clamp_temp = 0;

// OLED prints
char str1[16] = "mount:         ";
char str2[16] = "shoulder:      ";
char str3[16] = "arm:           ";
char str4[16] = "clamp:         ";

#define OLED 0

#define clamp_open_pos 90


void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(clamp_sensor, INPUT_PULLUP);

  delay(2000);
  
  s_mount.attach(3);
  delay(100);
  s_shoulder.attach(5);
  delay(100);
  s_arm.attach(6);
  delay(100);
  s_clamp.attach(9);

  pos_clamp = clamp_open_pos;

#if OLED == 1
  oled.init();
  oled.clear();
  
  // Write OLED prints
  oled.setCursor(0,0);
  oled.write(str1);
  oled.setCursor(2,0);
  oled.write(str2);
  oled.setCursor(4,0);
  oled.write(str3);
  oled.setCursor(6,0);
  oled.write(str4);
  
#endif
}

void loop(){

  uint8_t i = 0;
  while(BTSerial.available()) {
    char a = BTSerial.read();
    int o = a-48;
    
    if(o >= 0 && o <= 9 || a == '+' || a == '-') {
      com_in[i] = a;
    }

    i++;
    
    if(a == '-') {
      clamp_shut = false;
      break;
    }
    
    if(a == '+') {
      clamp_shut = true;
      break;
    }
    
    Serial.println(com_in);
  }

#if OLED == 1
  // Update angles on OLED
  oled.setCursor(2,60);
  oled.write(com_in[0]);
  oled.write(com_in[1]);
  oled.write(com_in[2]);
  oled.setCursor(4,60);
  oled.write(com_in[3]);
  oled.write(com_in[4]);
  oled.write(com_in[5]);
  oled.setCursor(0,60);
  oled.write(com_in[6]);
  oled.write(com_in[7]);
  oled.write(com_in[8]);
  oled.setCursor(6,60);
  oled.write(com_in[9]);
#endif

  ParseSignal();
  clampSensor();
  //tähän väliin liian suurien kulmien tarkistus
  servosWrite();
  
  delay(20);
  //delay(100);
}

void ParseSignal() {
  
  pos_shoulder = ConvertAngle(com_in[0], com_in[1], com_in[2]);
  pos_arm = ConvertAngle(com_in[3], com_in[4], com_in[5]);
  pos_planar = ConvertAngle(com_in[6], com_in[7], com_in[8]);
  //clamp_shut = com_in[9];
}

int ConvertAngle (char a, char b, char c) {
  int h = (a-48)*100;
  int t = (b-48)*10;
  int o = c;
  int i = h+t+o;

  return i-48;
}

void servosWrite() {

  if(clamp_shut == true) {
    if(clamp_temp == 0){
      pos_clamp++;
      s_clamp.write(pos_clamp);
    }
  } else {
    if(clamp_temp != 0) {
      pos_clamp = clamp_temp;
    }
    clamp_temp = 0;
    if(pos_clamp <= clamp_open_pos) {
      pos_clamp--;
      s_clamp.write(pos_clamp);
    }
  }

  if(pos_planar != pos_planar_old) {
    if(pos_planar_old < pos_planar) {
      pos_planar_old++;
    }
    else {
      pos_planar_old--;
    }
  }

  if(pos_shoulder != pos_shoulder_old) {
    if(pos_shoulder_old < pos_shoulder) {
      pos_shoulder_old++;
    }
    else {
      pos_shoulder_old--;
    }
  }

  if(pos_arm != pos_arm_old) {
    if(pos_arm_old < pos_arm) {
      pos_arm_old++;
    }
    else {
      pos_arm_old--;
    }
  }
  
  s_mount.write(pos_planar_old);
  s_shoulder.write(pos_shoulder_old);
  s_arm.write(pos_arm_old);
  
  String mount_str = String(pos_planar_old);
  char mountc[3];
  mount_str.toCharArray(mountc, 3);
    
  String shoulder_str = String(pos_shoulder_old);
  char shoulderc[3];
  shoulder_str.toCharArray(shoulderc, 3);

  String arm_str = String(pos_arm_old);
  char armc[3];
  arm_str.toCharArray(armc, 3);
  
#if OLED == 1
  oled.setCursor(0,100);
  oled.write(mountc);

  oled.setCursor(2,100);
  oled.write(shoulderc);
  
  oled.setCursor(4,100);
  oled.write(armc);
#endif
  
  Serial.println(pos_planar);
  Serial.println(pos_shoulder);
  Serial.println(pos_arm);

}

void clampSensor() {
  
  //if buttons/sensor activates in clamp, an object has been grabbed. -> stop clamp servo
  if (clamp_sensor == 0) {    //if clamp_sensor == 0 -> button is pressed
    clamp_temp = pos_clamp;   // store the clamp angle value when button is pressed
  }
  if (clamp_sensor == 1) {    // button not pressed
    clamp_temp = 0; 
  }
}
