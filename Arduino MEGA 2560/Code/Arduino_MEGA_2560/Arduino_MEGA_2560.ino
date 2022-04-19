#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

modbusDevice regBank;
modbusSlave slave;

//ตัวแปรเก็บค่าสถานะ ปุ่มกดที่จอทัชสกรีน
byte buttonManual;
byte buttonAuto;


//ตัวแปรเก็บค่าสถานะ Digital INPUT จากบอร์ด ESP8266 ที่อ่านค่าจาก RFID
byte input_1_A;  byte input_1_B;
byte input_2_A;  byte input_2_B;
byte input_3_A;  byte input_3_B;
byte input_4_A;  byte input_4_B;
byte input_5_A;  byte input_5_B;
byte input_6_A;  byte input_6_B;
byte input_7_A;  byte input_7_B;
byte input_8_A;  byte input_8_B;
byte input_9_A;  byte input_9_B;
byte input_10_A; byte input_10_B;
byte input_11_A; byte input_11_B;
byte input_12_A; byte input_12_B;;
byte input_13_A; byte input_13_B;;
byte input_14_A; byte input_14_B;;
byte input_15_A; byte input_15_B;;

//ตัวแปรเก็บค่าสถานะ Digital OUTPUT ควบคุม RELAY
byte DO1;  byte DO2;  byte DO3;  byte DO4;  byte DO5;  byte DO6;
byte DO7;  byte DO8;  byte DO9;  byte DO10; byte DO11; byte DO12;
byte DO13; byte DO14; byte DO15; byte DO16; byte DO17; byte DO18;
byte DO19; byte DO20; byte DO21; byte DO22; byte DO23; byte DO24;
byte DO25; byte DO26; byte DO27; byte DO28; byte DO29; byte DO30;
byte DO31; byte DO32;

//ตัวแปรสถานะค่า Digital OUTPUT
byte DO33; byte DO34; byte DO35; byte DO36;




/************  Motor **************/
// Motor A connections
#define enA  2
#define in1  3
#define in2  4
// Motor B connections
#define in3  5
#define in4  6
#define enB  7


/********** Speed control potentiometers ******/
#define VolumeControl_1  A14
#define VolumeControl_2  A15

/***** Motor Speed Values - Start at zero *****/
int MotorSpeed1 = 0;
int MotorSpeed2 = 0;





/****************************  Timer *************************/
unsigned long startMillis;  //เวลาเริ่มต้น
unsigned long currentMillis; // เวลา ณ ปัจุบัน
const unsigned long period = 5000;  //เวลาที่รถหยุดรอ
unsigned long startMillis2;  //เวลาเริ่มต้น
unsigned long currentMillis2; //เวลา ณ ปัจุบัน
const unsigned long period2 = 900;  //เวลาที่ก่อนที่จะสั่งให้รถหยุด
boolean startmil = false; //สถานะเริ่มนับเวลา
boolean startmil2 = false; //สถานะเริ่มนับเวลา
boolean findrf = false; 
boolean findrf2 = false;
boolean trainrun = false; //สถานะรถไฟวิ่ง
boolean train_go = false; //สถานะก่อนที่รถไฟจะหยุด
/*************************************************************/




void setup() {

  //Serial.begin(9600);

  regBank.setId(1);

  //Add Analog Input registers 30001-30018 to the register bank
  regBank.add(30002);
  regBank.add(30003);
  regBank.add(30004);
  regBank.add(30005);
  regBank.add(30006);
  regBank.add(30007);
  regBank.add(30008);
  regBank.add(30009);
  regBank.add(30010);
  regBank.add(30011);
  regBank.add(30012);
  regBank.add(30013);
  regBank.add(30014);
  regBank.add(30015);
  regBank.add(30016);
  regBank.add(30017);
  regBank.add(30018);


  //Add Digital Output registers
  regBank.add(2);
  regBank.add(3);
  regBank.add(4);
  regBank.add(5);
  regBank.add(6);


  regBank.add(22);
  regBank.add(23);
  regBank.add(24);
  regBank.add(25);
  regBank.add(26);
  regBank.add(27);
  regBank.add(28);
  regBank.add(29);
  regBank.add(30);
  regBank.add(31);
  regBank.add(32);
  regBank.add(33);
  regBank.add(34);
  regBank.add(35);
  regBank.add(36);
  regBank.add(37);

  regBank.add(38);
  regBank.add(39);
  regBank.add(40);
  regBank.add(41);
  regBank.add(42);
  regBank.add(43);
  regBank.add(44);
  regBank.add(45);
  regBank.add(46);
  regBank.add(47);
  regBank.add(48);
  regBank.add(49);
  regBank.add(50);
  regBank.add(51);
  regBank.add(52);
  regBank.add(53);

  regBank.add(54);
  regBank.add(55);
  regBank.add(56);
  regBank.add(57);


  slave._device = &regBank;
  slave.setBaud(19200);

  //หมายเลข INPUT อ้างอิงจากหมายเลขในแผนที่รางรถไฟ
  /****************  Input 1 ******************/
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  /****************  Input 2 ******************/
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  /****************  Input 3 ******************/
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  /****************  Input 4 ******************/
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  /****************  Input 5 ******************/
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  /****************  Input 6 ******************/
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  /****************  Input 7 ******************/
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  /****************  Input 8 ******************/
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  /****************  Input 9 ******************/
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  /****************  Input 10 ******************/
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  /****************  Input 11 ******************/
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  /****************  Input 12 ******************/
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  /****************  Input 13 ******************/
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  /****************  Input 14 ******************/
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  /****************  Input 15 ******************/
  pinMode(52, INPUT);
  pinMode(53, INPUT);

  /**** สวิตซ์ควบคุมทิศทางรถไฟ *****/
  pinMode(48, INPUT);
  pinMode(49, INPUT);
  pinMode(50, INPUT);
  pinMode(51, INPUT);

  /***** รีเลย์ 16 ช่อง 2 ชุด *******/
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);


  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  startMillis = millis();  //initial start time
}

void loop() {

  buttonManual = regBank.get(2);
  buttonAuto = regBank.get(3);

  //เงื่อนไขเมื่อไม่ได้กดปุ่มเลือกรูปแบบการควบคุม
  if (buttonManual <= 0 && buttonAuto <= 0) {
    //System stopped working
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  //เงื่อนไขเมื่อมรการกดปุ่มเลือกรูปแบบการควบคุมพร้อมกัน 2 ปุ่ม
  else if (buttonManual >= 1 && buttonAuto >= 1) {
    //System stopped working
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  //เงื่อนไขเมื่อกดปุ่ม Manual
  else if (buttonManual >= 1) { //
    manualControl();
    TrainControl();
    SpeedControl();
  }

  //เงื่อนไขเมื่อกดปุ่ม Auto
  else if (buttonAuto >= 1) {
    byte mode1 = regBank.get(4);
    byte mode2 = regBank.get(5);
    byte mode3 = regBank.get(6);

    //เงื่อนไขเมื่อกดปุ่มเลือกดโหมดการทำงานพร้อมกันมากกว่า 1 โหมด
    if ((mode1 >= 1 && mode2 >= 1) || (mode1 >= 1 && mode3 >= 1) || (mode2 >= 1 && mode3 >= 1)) {
      //System stopped working
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }

    //เงื่อนไขเมื่อเลือกกดปุ่มโหมดที่ 1
    else if (mode1 >= 1) {
      autoControl_1();
      SpeedControl();
    }

    //เงื่อนไขเมื่อเลือกกดปุ่มโหมดที่ 2
    else if (mode2 >= 1) {
      autoControl_2();
      SpeedControl();
    }

    //เงื่อนไขเมื่อเลือกกดปุ่มโหมดที่ 3
    else if (mode3 >= 1) {
      autoControl_3();
      SpeedControl();
    }

    //เงื่อนไขเมื่อไม่มีการกดปุ่มเลือกโหมดการทำงาน
    else if (mode1 <= 0 && mode2 <= 0 && mode3 <= 0) {
      //System stopped working
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
  }


  //เงื่อนไขเมื่อรับสัญญาณ INPUT จาก RFID แล้วมาเก็บค่าในตัวแปรประจำแหน่งและส่งค่าไปเก็บที่ register bank
  //เพื่อให้ตัว master อ่านค่าจาก address ของ register bank แสดงออกไปยังหน้าจอ
  //ถ้าไม่มีรถวิ่งผ่านให้ส่งค่าเป็น 0
  //ถ้ามีรถไฟขบวน A วิ่งผ่านให้ส่งค่าเป็น 1
  //ถ้ามีรถไฟขบวน B วิ่งผ่านให้ส่งค่าเป้น 2

  /****************  Input 1 ******************/
  input_1_A = digitalRead(A0);
  input_1_B = digitalRead(A1);
  if (input_1_A == 0 && input_1_B == 0)regBank.set(30002, 0);
  else if (input_1_A == 1)regBank.set(30002, 1);
  else if (input_1_B <= 1)regBank.set(30002, 2);


  /****************  Input 2 ******************/
  input_2_A = digitalRead(A2);
  input_2_B = digitalRead(A3);
  if (input_2_A == 0 && input_2_B == 0)regBank.set(30003, 0);
  else if (input_2_A == 1)regBank.set(30003, 1);
  else if (input_2_B <= 1)regBank.set(30003, 2);


  /****************  Input 3 ******************/
  input_3_A = digitalRead(A4);
  input_3_B = digitalRead(A5);
  if (input_3_A == 0 && input_3_B == 0)regBank.set(30004, 0);
  else if (input_3_A == 1)regBank.set(30004, 1);
  else if (input_3_B <= 1)regBank.set(30004, 2);


  /****************  Input 4 ******************/
  input_4_A = digitalRead(A6);
  input_4_B = digitalRead(A7);
  if (input_4_A == 0 && input_4_B == 0)regBank.set(30005, 0);
  else if (input_4_A == 1)regBank.set(30005, 1);
  else if (input_4_B <= 1)regBank.set(30005, 2);


  /****************  Input 5 ******************/
  input_5_A = digitalRead(A8);
  input_5_B = digitalRead(A9);
  if (input_5_A == 0 && input_5_B == 0)regBank.set(30006, 0);
  else if (input_5_A == 1)regBank.set(30006, 1);
  else if (input_5_B <= 1)regBank.set(30006, 2);


  /****************  Input 6 ******************/
  input_6_A = digitalRead(A10);
  input_6_B = digitalRead(A11);
  if (input_6_A == 0 && input_6_B == 0)regBank.set(30007, 0);
  else if (input_6_A == 1)regBank.set(30007, 1);
  else if (input_6_B <= 1)regBank.set(30007, 2);


  /****************  Input 7 ******************/
  input_7_A = digitalRead(A12);
  input_7_B = digitalRead(A13);
  if (input_7_A == 0 && input_7_B == 0)regBank.set(30008, 0);
  else if (input_7_A == 1)regBank.set(30008, 1);
  else if (input_7_B <= 1)regBank.set(30008, 2);


  /****************  Input 8 ******************/
  input_8_A = digitalRead(8);
  input_8_B = digitalRead(9);
  if (input_8_A == 0 && input_8_B == 0)regBank.set(30009, 0);
  else if (input_8_A == 1)regBank.set(30009, 1);
  else if (input_8_B <= 1)regBank.set(30009, 2);


  /****************  Input 9 ******************/
  input_9_A = digitalRead(10);
  input_9_B = digitalRead(11);
  if (input_9_A == 0 && input_9_B == 0)regBank.set(30010, 0);
  else if (input_9_A == 1)regBank.set(30010, 1);
  else if (input_9_B <= 1)regBank.set(30010, 2);


  /****************  Input 10 ******************/
  input_10_A = digitalRead(12);
  input_10_B = digitalRead(13);
  if (input_10_A == 0 && input_10_B == 0)regBank.set(30011, 0);
  else if (input_10_A == 1)regBank.set(30011, 1);
  else if (input_10_B <= 1)regBank.set(30011, 2);


  /****************  Input 11 ******************/
  input_11_A = digitalRead(14);
  input_11_B = digitalRead(15);
  if (input_11_A == 0 && input_11_B == 0)regBank.set(30012, 0);
  else if (input_11_A == 1)regBank.set(30012, 1);
  else if (input_11_B <= 1)regBank.set(30012, 2);


  /****************  Input 12 ******************/
  input_12_A = digitalRead(16);
  input_12_B = digitalRead(17);
  if (input_12_A == 0 && input_12_B == 0)regBank.set(30013, 0);
  else if (input_12_A == 1)regBank.set(30013, 1);
  else if (input_12_B <= 1)regBank.set(30013, 2);


  /****************  Input 13 ******************/
  input_13_A = digitalRead(18);
  input_13_B = digitalRead(19);
  if (input_13_A == 0 && input_13_B == 0)regBank.set(30014, 0);
  else if (input_13_A == 1)regBank.set(30014, 1);
  else if (input_13_B <= 1)regBank.set(30014, 2);


  /****************  Input 14 ******************/
  input_14_A = digitalRead(20);
  input_14_B = digitalRead(21);
  if (input_14_A == 0 && input_14_B == 0)regBank.set(30015, 0);
  else if (input_14_A == 1)regBank.set(30015, 1);
  else if (input_14_B <= 1)regBank.set(30015, 2);


  /****************  Input 15 ******************/
  input_15_A = digitalRead(52);
  input_15_B = digitalRead(53);
  if (input_15_A == 0 && input_15_B == 0)regBank.set(30016, 0);
  else if (input_15_A == 1)regBank.set(30016, 1);
  else if (input_15_B <= 1)regBank.set(30016, 2);


  slave.run();
}


//ฟังก์ชั่นการควบคุมอัตโนมัติ โหมดที่ 1
void autoControl_1() {  

/************************** เงื่อนไขเช็คการหยุดรถไฟให้จอดตามเวลาที่กำหนด *********************************/

  if (trainrun == false) {
    //Serial.println("run");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (trainrun == true) {

    if (train_go == true) {
      findrf = true;

      //Serial.println("stop");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    else {
      //Serial.println("run");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    if (startmil2 == false) {
      startMillis2 = millis();
      startmil2 = true;
    }
    currentMillis2 = millis();
    if (currentMillis2 - startMillis2 >= period2) { //test whether the period has elapsed
      train_go = true;
      startMillis2 = currentMillis2;  //IMPORTANT to save the start time of the current LED state.
    }
  }
  if (findrf == true) {
    if (startmil == false) {
      startMillis = millis();
      startmil = true;
    }
    currentMillis = millis();
    if (currentMillis - startMillis >= period)  //test whether the period has elapsed
    {
      trainrun = false;
      startmil = false;
      findrf = false;
      train_go = false;
      startmil2 = false;
      startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
    }
  }
/************************************************************************************************/

  /****************  Input 1 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 1
  if (input_1_A == 1) {
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 1
  else if (input_1_B == 1) {
    digitalWrite(22, HIGH);
    digitalWrite(23, HIGH);
  }

  /****************  Input 2 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 2
  if (input_2_A == 1) {
    digitalWrite(39, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 2
  else if (input_2_B == 1) {
    digitalWrite(39 , HIGH);
  }

  /****************  Input 3 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 3
  if (input_3_A == 1) {
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 3
  else if (input_3_B == 1) {
    digitalWrite(32, HIGH);
    digitalWrite(33, HIGH);
  }

  /****************  Input 4 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 4
  if (input_4_A == 1) {
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);

  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 4
  else if (input_4_B == 1) {
    digitalWrite(30, HIGH);
    digitalWrite(31, HIGH);
  }

  /****************  Input 5 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 5
  if (input_5_A == 1) {
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 5
  else if (input_5_B == 1) {
    digitalWrite(28, HIGH);
    digitalWrite(29, HIGH);
  }

  /****************  Input 6 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 6
  if (input_6_A == 1) {
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    trainrun = true;
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 6
  else if (input_6_B == 1) {
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
    trainrun = true;
  }


  /****************  Input 7 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 7
  if (input_7_A == 1) {
    digitalWrite(24, LOW);
    digitalWrite(25, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 7
  else if (input_7_B == 1) {
    digitalWrite(24, HIGH);
    digitalWrite(25, HIGH);
  }
}



//ฟังก์ชั่นการควบคุมอัตโนมัติ โหมดที่ 2
void autoControl_2() { 

/************************** เงื่อนไขเช็คการหยุดรถไฟให้จอดตามเวลาที่กำหนด *********************************/

  if (trainrun == false) {
    //Serial.println("run");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (trainrun == true) {

    if (train_go == true) {
      findrf = true;

      //Serial.println("stop");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    else {
      //Serial.println("run");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    if (startmil2 == false) {
      startMillis2 = millis();
      startmil2 = true;
    }
    currentMillis2 = millis();
    if (currentMillis2 - startMillis2 >= period2)  //test whether the period has elapsed
    {
      train_go = true;
      startMillis2 = currentMillis2;  //IMPORTANT to save the start time of the current LED state.
    }

  }

  if (findrf == true) {

    if (startmil == false) {
      startMillis = millis();
      startmil = true;
    }
    currentMillis = millis();
    if (currentMillis - startMillis >= period)  //test whether the period has elapsed
    {
      trainrun = false;
      startmil = false;
      findrf = false;
      train_go = false;
      startmil2 = false;
      startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
    }
  }  
/************************************************************************************************/
  

  /****************  Input 1 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 1
  if (input_1_A == 1) {
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    digitalWrite(37, LOW);
    digitalWrite(42, LOW);
  }
  else if (input_1_B == 1) {
    //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 1
    digitalWrite(22, HIGH);
    digitalWrite(23, HIGH);
    digitalWrite(36, LOW);
    digitalWrite(41, LOW);
  }

  /****************  Input 3 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 3
  if (input_3_A == 1) {
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 3
  else if (input_3_B == 1) {
    digitalWrite(32, HIGH);
    digitalWrite(33, HIGH);
  }

  /****************  Input 4 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 4
  if (input_4_A == 1) {
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 4
  else if (input_4_B == 1) {
    digitalWrite(30, HIGH);
    digitalWrite(31, HIGH);
  }

  /****************  Input 5 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 5
  if (input_5_A == 1) {
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);
    digitalWrite(37, HIGH);
    digitalWrite(42, HIGH);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 5
  else if (input_5_B == 1) {
    digitalWrite(25, HIGH);
    digitalWrite(27, HIGH);
    digitalWrite(28, HIGH);
    digitalWrite(29, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(41, HIGH);
  }

  /****************  Input 8 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 8
  if (input_8_A == 1) {
    trainrun = true;
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 8
  else if (input_8_B == 1) {
    trainrun = true;
  }


  /****************  Input 10 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 10
  if (input_10_A == 1) {
    trainrun = true;
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 10
  else if (input_10_B == 1) {
    trainrun = true;
  }
}



//ฟังก์ชั่นการควบคุมอัตโนมัติ โหมดที่ 3
void autoControl_3() {    

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  /****************  Input 1 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 1
  if (input_1_A == 1) {
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
  }
  //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 1
  else if (input_1_B == 1) {
    digitalWrite(22, HIGH);
    digitalWrite(23, HIGH);
  }

  /****************  Input 2 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 2
  if (input_2_A == 1) {
    digitalWrite(39, HIGH);
  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 2
  else if (input_2_B == 1) {
    digitalWrite(39 , HIGH);
  }


  /****************  Input 3 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 3
  if (input_3_A == 1) {
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 3
  else if (input_3_B == 1) {
    digitalWrite(32, HIGH);
    digitalWrite(33, HIGH);
  }

  /****************  Input 4 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 4
  if (input_4_A == 1) {
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);

  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 4
  else if (input_4_B == 1) {
    digitalWrite(30, HIGH);
    digitalWrite(31, HIGH);
  }

  /****************  Input 5 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 5
  if (input_5_A == 1) {
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);
    digitalWrite(38, HIGH);

  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 5
  else if (input_5_B == 1) {
    digitalWrite(28, HIGH);
    digitalWrite(29, HIGH);
    digitalWrite(38, HIGH);
  }

  /****************  Input 12 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 12
  if (input_12_A == 1) {
    digitalWrite(35, HIGH);
    digitalWrite(34, LOW);
    digitalWrite(40, LOW);

  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 12
  else if (input_12_B == 1) {
    digitalWrite(40, HIGH);
    digitalWrite(34, LOW);
    digitalWrite(35, LOW);

  }


  /****************  Input 13 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 13
  if (input_13_A == 1) {
    digitalWrite(35, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 13
  else if (input_13_B == 1) {
    digitalWrite(35, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }


  /****************  Input 14 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 14
  if (input_14_A == 1) {
    digitalWrite(40, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 14
  else if (input_14_B == 1) {
    digitalWrite(40, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }


  /****************  Input 15 ******************/
  //เมื่อรถไฟขบวน A ผ่านตำแหน่งที่ 15
  if (input_15_A == 1) {
    digitalWrite(34, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
   //เมื่อรถไฟขบวน B ผ่านตำแหน่งที่ 15
  else if (input_15_B == 1) {
    digitalWrite(34, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

//ฟังกชั่น์ควบคุมไฟบอกสัญญาณและประแจรถไฟ
//โดยการอ่านค่า ปุ่มกดที่จอทัชสกรีนมาควบคุมผ่านรีเลย์
//หมายเลข register bank ที่กำหนดจะตรงกับหมายเลข pin ของ Arduino MEGA 2560 เพื่อให้ง่ายต่อการพัฒนา

void manualControl() {

  /***************** Output 1 ******************/
  DO1 = regBank.get(22);
  if (DO1 <= 0 && digitalRead(22) == HIGH)digitalWrite(22, LOW);
  if (DO1 >= 1 && digitalRead(22) == LOW) digitalWrite(22, HIGH);

  /***************** Output 2 ******************/
  DO2 = regBank.get(23);
  if (DO2 <= 0 && digitalRead(23) == HIGH)digitalWrite(23, LOW);
  if (DO2 >= 1 && digitalRead(23) == LOW) digitalWrite(23, HIGH);

  /***************** Output 3 ******************/
  DO3 = regBank.get(24);
  if (DO3 <= 0 && digitalRead(24) == HIGH)digitalWrite(24, LOW);
  if (DO3 >= 1 && digitalRead(24) == LOW)digitalWrite(24, HIGH);

  /***************** Output 4 ******************/
  DO4 = regBank.get(25);
  if (DO4 <= 0 && digitalRead(25) == HIGH)digitalWrite(25, LOW);
  if (DO4 >= 1 && digitalRead(25) == LOW) digitalWrite(25, HIGH);

  /***************** Output 5 ******************/
  DO5 = regBank.get(26);
  if (DO5 <= 0 && digitalRead(26) == HIGH)digitalWrite(26, LOW);
  if (DO5 >= 1 && digitalRead(26) == LOW) digitalWrite(26, HIGH);

  /***************** Output 6 ******************/
  DO6 = regBank.get(27);
  if (DO6 <= 0 && digitalRead(27) == HIGH)digitalWrite(27, LOW);
  if (DO6 >= 1 && digitalRead(27) == LOW) digitalWrite(27, HIGH);

  /***************** Output 7 ******************/
  DO7 = regBank.get(28);
  if (DO7 <= 0 && digitalRead(28) == HIGH)digitalWrite(28, LOW);
  if (DO7 >= 1 && digitalRead(28) == LOW) digitalWrite(28, HIGH);

  /***************** Output 8 ******************/
  DO8 = regBank.get(29);
  if (DO8 <= 0 && digitalRead(29) == HIGH)digitalWrite(29, LOW);
  if (DO8 >= 1 && digitalRead(29) == LOW) digitalWrite(29, HIGH);

  /***************** Output 9 ******************/
  DO9 = regBank.get(30);
  if (DO9 <= 0 && digitalRead(30) == HIGH)digitalWrite(30, LOW);
  if (DO9 >= 1 && digitalRead(30) == LOW) digitalWrite(30, HIGH);

  /***************** Output 10 ******************/
  DO10 = regBank.get(31);
  if (DO10 <= 0 && digitalRead(31) == HIGH)digitalWrite(31, LOW);
  if (DO10 >= 1 && digitalRead(31) == LOW) digitalWrite(31, HIGH);

  /***************** Output 11 ******************/
  DO11 = regBank.get(32);
  if (DO11 <= 0 && digitalRead(32) == HIGH)digitalWrite(32, LOW);
  if (DO11 >= 1 && digitalRead(32) == LOW) digitalWrite(32, HIGH);

  /***************** Output 12 ******************/
  DO12 = regBank.get(33);
  if (DO12 <= 0 && digitalRead(33) == HIGH)digitalWrite(33, LOW);
  if (DO12 >= 1 && digitalRead(33) == LOW) digitalWrite(33, HIGH);

  /***************** Output 13 ******************/
  DO13 = regBank.get(34);
  if (DO13 <= 0 && digitalRead(34) == HIGH)digitalWrite(34, LOW);
  if (DO13 >= 1 && digitalRead(34) == LOW) digitalWrite(34, HIGH);

  /***************** Output 14 ******************/
  DO14 = regBank.get(35);
  if (DO14 <= 0 && digitalRead(35) == HIGH)digitalWrite(35, LOW);
  if (DO14 >= 1 && digitalRead(35) == LOW)digitalWrite(35, HIGH);

  /***************** Output 15 ******************/
  DO15 = regBank.get(36);
  if (DO15 <= 0 && digitalRead(36) == HIGH)digitalWrite(36, LOW);
  if (DO15 >= 1 && digitalRead(36) == LOW)digitalWrite (36, HIGH);

  /***************** Output 16 ******************/
  DO16 = regBank.get(37);
  if (DO16 <= 0 && digitalRead(37) == HIGH)digitalWrite(37, LOW);
  if (DO16 >= 1 && digitalRead(37) == LOW) digitalWrite(37, HIGH);

  /***************** Output 17 ******************/
  DO17 = regBank.get(38);
  if (DO17 <= 0 && digitalRead(38) == HIGH)digitalWrite(38, LOW);
  if (DO17 >= 1 && digitalRead(38) == LOW) digitalWrite(38, HIGH);

  /***************** Output 18 ******************/
  DO18 = regBank.get(39);
  if (DO18 <= 0 && digitalRead(39) == HIGH)digitalWrite(39, LOW);
  if (DO18 >= 1 && digitalRead(39) == LOW) digitalWrite(39, HIGH);

  /***************** Output 19 ******************/
  DO19 = regBank.get(40);
  if (DO19 <= 0 && digitalRead(40) == HIGH)digitalWrite(40, LOW);
  if (DO19 >= 1 && digitalRead(40) == LOW) digitalWrite(40, HIGH);

  /***************** Output 20 ******************/
  DO20 = regBank.get(41);
  if (DO20 <= 0 && digitalRead(41) == HIGH)digitalWrite(41, LOW);
  if (DO20 >= 1 && digitalRead(41) == LOW) digitalWrite(41, HIGH);

  /***************** Output 21 ******************/
  DO21 = regBank.get(42);
  if (DO21 <= 0 && digitalRead(42) == HIGH)digitalWrite(42, LOW);
  if (DO21 >= 1 && digitalRead(42) == LOW) digitalWrite(42, HIGH);

  /***************** Output 22 ******************/
  DO22 = regBank.get(43);
  if (DO22 <= 0 && digitalRead(43) == HIGH)digitalWrite(43, LOW);
  if (DO22 >= 1 && digitalRead(43) == LOW) digitalWrite(43, HIGH);

  /***************** Output 23 ******************/
  DO23 = regBank.get(44);
  if (DO23 <= 0 && digitalRead(44) == HIGH)digitalWrite(44, LOW);
  if (DO23 >= 1 && digitalRead(44) == LOW) digitalWrite(44, HIGH);

  /***************** Output 24 ******************/
  DO24 = regBank.get(45);
  if (DO24 <= 0 && digitalRead(45) == HIGH)digitalWrite(45, LOW);
  if (DO24 >= 1 && digitalRead(45) == LOW) digitalWrite(45, HIGH);

  /***************** Output 25 ******************/
  DO25 = regBank.get(46);
  if (DO25 <= 0 && digitalRead(46) == HIGH)digitalWrite(46, LOW);
  if (DO25 >= 1 && digitalRead(46) == LOW) digitalWrite(46, HIGH);

  /***************** Output 26 ******************/
  DO26 = regBank.get(47);
  if (DO26 <= 0 && digitalRead(47) == HIGH)digitalWrite(47, LOW);
  if (DO26 >= 1 && digitalRead(47) == LOW) digitalWrite(47, HIGH);

}


//ฟังชั่นการควบคุมความเร็วรถไฟ
void SpeedControl() {

  /***************** SPEED INPUT ***************/

  // Read the values from the potentiometers
  MotorSpeed1 = analogRead(VolumeControl_1);  //อ่านค่าจากตัวต้านทานปรับค่าได้มาเก็บไว้ในตัวแปร
  MotorSpeed2 = analogRead(VolumeControl_2);  //อ่านค่าจากตัวต้านทานปรับค่าได้มาเก็บไว้ในตัวแปร

  // Convert to range of 0-255
  MotorSpeed1 = map(MotorSpeed1, 0, 1023, 0, 255); //นำค่าที่เก็บไว้ในตัวแปรมาแปลงเป็นสัญญาณดิจิทัล
  MotorSpeed2 = map(MotorSpeed2, 0, 1023, 0, 255); //นำค่าที่เก็บไว้ในตัวแปรมาแปลงเป็นสัญญาณดิจิทัล

  // Adjust to prevent "buzzing" at very low speed
  if (MotorSpeed1 < 8)MotorSpeed1 = 0;
  if (MotorSpeed2 < 8)MotorSpeed2 = 0;

  // Set the motor speeds
  analogWrite(enA, MotorSpeed1);
  analogWrite(enB, MotorSpeed2);

  //ส่งอ่านที่อ่านได้จากตัวต้านทานปรับค่าได้ไปเก็บไว้ใน register bank เพื่อให้แสดงผลไปยังจอทัชสกรีน
  regBank.set(30017, MotorSpeed1);
  regBank.set(30018, MotorSpeed2);


  //Serial.print("Speed_1 = ");
  //Serial.print(MotorSpeed1);
  //Serial.print("  ");
  //Serial.print("Speed_2 = ");
  //Serial.println(MotorSpeed2);

}

//ฟังก์ชั่นควบคุมทิศทางการวิ่งของรถไฟ
void TrainControl() {

  /********** train A  Forward/Backward ********/

  DO33 = regBank.get(54);
  //เมื่อกดปุ่ม Forward ราง A
  if (DO33 <= 0) {     
    //รถไฟวิ่งไปข้างหน้า
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  //เมื่อกดปุ่ม Backward ราง A
  else if (DO33 >= 1) {    
    //รถไฟวิ่งกลับหลัง
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  /********* train B  Forward/Backward  *********/

  DO34 = regBank.get(55);
  //เมื่อกดปุ่ม Forward ราง B
  if (DO34 <= 0  ) {
    //รถไฟวิ่งไปข้างหน้า
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
   //เมื่อกดปุ่ม Backward ราง B
  else if (DO34 >= 1 ) {
    //รถไฟวิ่งกลับหลัง
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  byte sw1_f  = digitalRead(48);
  byte sw1_b  = digitalRead(49);
}
