#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 5
#define RST_PIN 9
#define LED 2 //connect the relay to number 3 pin
#define BUZZER 3 // connect the buzzer to 2 pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
#define IR 4
#define pump 6
int timer=0;
int offtime = 10000;
int x = 0;
bool ir_val =0;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(IR, INPUT);
  pinMode(pump, OUTPUT);
  Serial.println("Put your card to the reader for scanning ...");
  Serial.println();

}
void loop() 
{
  ir_val = digitalRead(IR);
  if(ir_val == LOW && timer<=offtime){
    timer++;
    delay(475);
  }else{
    timer = 0;
  }
  if(timer == 0 || timer>1){
    digitalWrite(pump, HIGH);
  }else{
    digitalWrite(pump, LOW);
  }
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "F3 7E F5 45") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(LED, HIGH);
    delay(ACCESS_DELAY);
    digitalWrite(LED, LOW);
    
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(BUZZER, HIGH);
    delay(DENIED_DELAY);
    digitalWrite(BUZZER, LOW);
    delay(2000);
  }
  

  
}
