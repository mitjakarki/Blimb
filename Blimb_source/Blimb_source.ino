///////////////////////////////////////////////////////////////////////////
////       BLIMB 1.0
////         ****
////      Kärki Mitja
////    Mustaniemi Janne
////         ****
////  University of Oulu
////  Embedded systems project
////         2016      
////         **** 
//// This arduino code is a part of the University of Oulu course "Embedded systems project", course code 521423S
//// The code handles incoming bluetooth data and writes it to four servos. It also features debugging mode via an SSD1306 OLED display (disabled by default).
////
////
//////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <Servo.h>
#include <SSD1306_text.h>

Servo s_mount;        // set servo objects
Servo s_shoulder;
Servo s_arm;
Servo s_clamp;

///SSD1306_text oled;    // You'll need to add the SSD1306 library to your arduino IDE and uncomment this line if you want to use debug mode.
                         // Also, see line "#define OLED 0"  about 30 lines below this  

// Serial input data from mobile app
char com_in[11] = "090090090-";  // The initial value for all servos is 90 degrees and the clamp servo is open.

// Variables that hold servo position values
uint8_t pos_planar;
uint8_t pos_shoulder;
uint8_t pos_arm;

uint8_t pos_planar_old = 90;
uint8_t pos_shoulder_old = 90;
uint8_t pos_arm_old = 90;
uint8_t pos_clamp_old = 90;


uint8_t clamp_stop = 0;     //  read button in clamp. Initialised to not pressed (0)
bool clamp_shut = false;// - or + from serial

const uint8_t clamp_pin = 4;     //sensor pin


// OLED prints for debugging
char str1[16] = "mount:         ";
char str2[16] = "shoulder:      ";
char str3[16] = "arm:           ";
char str4[16] = "clamp:         ";

#define OLED 0      // set to 1 to enable debugging mode.

//Clamp angles
#define clamp_open_pos 90
#define clamp_shut_pos 180

void setup() {
  Serial.begin(9600);     // start serial connection with bluetooth module
  
  pinMode(clamp_pin, INPUT_PULLUP);

  delay(2000);

  //initialize servos
  s_mount.attach(3); 
  s_mount.write(90);
  delay(500);
  s_shoulder.attach(5);
  s_shoulder.write(170);
  delay(500);
  s_arm.attach(6);
  s_arm.write(180);
  delay(500);
  s_clamp.attach(9);
  s_clamp.write(clamp_open_pos);
  delay(500);

#if OLED == 1
  oled.init();
  oled.clear();

  // Write OLED prints
  oled.setCursor(0, 0);
  oled.write(str1);
  oled.setCursor(2, 0);
  oled.write(str2);
  oled.setCursor(4, 0);
  oled.write(str3);
  oled.setCursor(6, 0);
  oled.write(str4);

#endif
}

void loop() {
 
  
  readSerial();
  

#if OLED == 1
  // Update angles on OLED
  oled.setCursor(2, 60);
  oled.write(com_in[0]);
  oled.write(com_in[1]);
  oled.write(com_in[2]);
  oled.setCursor(4, 60);
  oled.write(com_in[3]);
  oled.write(com_in[4]);
  oled.write(com_in[5]);
  oled.setCursor(0, 60);
  oled.write(com_in[6]);
  oled.write(com_in[7]);
  oled.write(com_in[8]);
  oled.setCursor(6, 60);
  oled.write(com_in[9]);
#endif

  ParseSignal();
  
  servosWrite();

  delay(15);      //main delay
  
}

void ParseSignal() {
  uint8_t temp_shoulder = ConvertAngle(com_in[0], com_in[1], com_in[2]);
  uint8_t temp_arm =  ConvertAngle(com_in[3], com_in[4], com_in[5]);
  uint8_t temp_planar = ConvertAngle(com_in[6], com_in[7], com_in[8]);
  
  if(temp_shoulder <= 120) {        // ignores invalid values (errors) from signal
    pos_shoulder = temp_shoulder;
  }
  
  if(temp_arm <= 150) {
    pos_arm = temp_arm;
  }

  if(temp_planar <= 180) {
    pos_planar = temp_planar;
  }
  
}

int ConvertAngle (char a, char b, char c) {
  int h = (a - 48) * 100;
  int t = (b - 48) * 10;
  int o = c;
  int i = h + t + o;

  return i - 48;
}


void servosWrite() {
  
  clamp_stop = !(digitalRead(clamp_pin));   // check if sensor in the clamp is pressed
  

  if (clamp_shut == true && clamp_stop == 0 && (pos_clamp_old < clamp_shut_pos)) {  // if BT says shut clamp, there is nothing (detected) in the clamp and clamp is not fully shut
    pos_clamp_old++;                                                                // then shut clamp 
    s_clamp.write(pos_clamp_old);
  }
  if(clamp_shut == false && pos_clamp_old > clamp_open_pos) {
    pos_clamp_old--; // open clamp
    s_clamp.write(pos_clamp_old);
    }
  
  /* The servo angles are written to servos in one angle increments */
  
  if (pos_planar != pos_planar_old) {           
    if (pos_planar_old < pos_planar) {
      pos_planar_old++;
    }
    else {
      pos_planar_old--;
    }
    s_mount.write(180 - pos_planar_old);        // The additions and substractions in the servo write functions are to correct arm alignment
  }

  if (pos_shoulder != pos_shoulder_old) {
    if (pos_shoulder_old < pos_shoulder) {
      pos_shoulder_old++;
    }
    else {
      pos_shoulder_old--;
    }
    s_shoulder.write(pos_shoulder_old+75);
  }

  if (pos_arm != pos_arm_old) {
    if (pos_arm_old < pos_arm) {
      pos_arm_old++;
    }
    else {
      pos_arm_old--;
    }
    s_arm.write(198 - pos_arm_old); 
  }

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
  oled.setCursor(0, 100);
  oled.write(mountc);

  oled.setCursor(2, 100);
  oled.write(shoulderc);

  oled.setCursor(4, 100);
  oled.write(armc);
#endif
}


void readSerial(){
  
    uint8_t i = 0;
    while (Serial.available()) {
    char a = Serial.read();
    int o = a - 48;
    
    if (o >= 0 && o <= 9 || a == '+' || a == '-') {
      com_in[i] = a;
      i++;
    }
      
    
    if (a == '-') {
      clamp_shut = false;
      break;
    }

    if (a == '+') {
      clamp_shut = true;
      break;
    }
    delay(1);
}

}
