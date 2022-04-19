 #include "SPI.h"
#include "MFRC522.h"

#define RST_PIN D0
#define SS_PIN D1
#define OUTPUT_A D2   //ช่องส่งสัญญาณของรถไฟขบวน A
#define OUTPUT_B D3   //ช่องส่งสัญญาณของรถไฟขบวน B

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    pinMode(OUTPUT_A, OUTPUT);
    pinMode(OUTPUT_B, OUTPUT);
}

void loop() {

  //อ่านค่าจาก Tag RFID 
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;
   
   Serial.print(F("PICC type: "));  
   MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
   Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  
  //แสดงหมายเลขจาก Tag RFID
  Serial.print("Tap card key: ");
  Serial.println(strID);

  // โค้ดส่วนควบคุม OUTPUT โดยเอาค่าจากตัวแปร strID มาเทียบ
  
  //เงื่อนไขเมื่อรถขบวน A วิ่งผ่าน RFID 
  if (strID.indexOf("67:69:02:33") >= 0) { 
    digitalWrite(OUTPUT_A, HIGH); //ส่งสัญญาณว่ามีรถไฟขบวน A ผ่าน
    digitalWrite(OUTPUT_B, LOW);  //ส่งสัญญาณว่าไม่มีรถไฟขบวน A
    Serial.println("OUTPUT_A HIGH");
    delay(1000);
    digitalWrite(OUTPUT_A, LOW); //ส่งสัญญาณว่าไม่มีรถไฟขบวน A
    digitalWrite(OUTPUT_B, LOW); //ส่งสัญญาณว่าไม่มีรถไฟขบวน B
  } 
  
  //เงื่อนไขเมื่อรถขบวน B วิ่งผ่าน RFID 
  else if (strID.indexOf("D3:CF:48:73") >= 0) { 
    digitalWrite(OUTPUT_A, LOW);  //ส่งสัญญาณว่าไม่มีรถไฟขบวน B
    digitalWrite(OUTPUT_B, HIGH); //ส่งสัญญาณว่ามีรถไฟขบวน B ผ่าน
    Serial.println("OUTPUT_B HIGH");
    delay(1000);
    digitalWrite(OUTPUT_A, LOW); //ส่งสัญญาณว่าไม่มีรถไฟขบวน A
    digitalWrite(OUTPUT_B, LOW); //ส่งสัญญาณว่าไม่มีรถไฟขบวน B
  } 

  //เงื่อนไขเมื่อไม่มีรถไฟวิ่งผ่าน RFID 
  else {
    digitalWrite(OUTPUT_A, LOW); //ส่งสัญญาณว่าไม่มีรถไฟขบวน A
    digitalWrite(OUTPUT_B, LOW); //ส่งสัญญาณว่าไม่มีรถไฟขบวน B
    Serial.println("NO OUTPUT");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
