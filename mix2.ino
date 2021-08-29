#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire) ;

#define SS_PIN 5         //RFID
#define RST_PIN 25

#define servodoor 12     //SERVO

#include <Wire.h>
#include "DHT.h"         //DHT11
#define DHTPIN 13  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
float temp = 0;
float humidity = 0;

int ledRed = 15;         //Soil Moisture
int soilPin = 33;
int val_SM = 0;
int stateValNUM = 0;
String stateVal[2] = {"Pls. Water!", "Nice:)"};

#define period_t1 200
unsigned long time_1 = 0;
#define period_t2 1000
unsigned long time_2 = 0;

int stateOLED = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN); 
Servo myServo; 
 
void setup() 
{
  Serial.begin(115200);  
  SPI.begin();
  dht.begin();      
  
  pinMode(ledRed,OUTPUT); // led Soil Moisture

  // RFID
  mfrc522.PCD_Init();   
  Serial.println("Put your card to the reader...");
  Serial.println();

  // SERVO
  myServo.attach(servodoor);  //servo pin
  myServo.write(110);        //set position door

  // DISPLAY
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed")) ;
  }
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() 
{
  
  if(millis() - time_1 > period_t1) {     //200
    time_1 = millis();
    RFID();
    readSoil();
    readDHT11();
    stateOLED++;
    if(stateOLED > 3) {
      stateOLED = 0 ;
    }
  }

  if(millis() - time_2 > period_t2) {    //1000
    time_2 = millis();
    drawScreen();
  }
}

void readSoil(void) {
    // soil moisture
    val_SM = analogRead(soilPin);
    Serial.print("value = ");
    Serial.println(val_SM);
    if(val_SM < 2000) {
      digitalWrite(ledRed, LOW);
      stateValNUM = 1 ;
    }
    else {
      digitalWrite(ledRed, HIGH);
      delay(500);
      digitalWrite(ledRed, LOW);
      delay(500);
      stateValNUM = 0 ;
    }
}

void readDHT11(void) {
    humidity = dht.readHumidity();  
    temp = dht.readTemperature();  
 
    if (isnan(humidity) || isnan(temp)){
      Serial.println("Failed to read from DHT sensor!");
      return; 
    }
  
    Serial.print("Humidity: ");
    Serial.print(humidity); 
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);  
    Serial.println(" *C ");
}

void RFID(void) {
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
    if (content.substring(1) == "71 D7 EA 2E","F6 73 4B 73") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Authorized access");
      Serial.println();
      myServo.write(0);   //open
      delay(5000);
      myServo.write(110); //close
    }
    else 
    {
      Serial.println(" Access denied");
      myServo.write(110);
    }
}

void drawScreen(void) {
 display.clearDisplay();
 display.setTextSize(2);
 display.setTextColor(WHITE);
 
 //checkstate

 if(stateOLED == 0) {
    display.setCursor(0, 0);
    display.printf("SM: %d", val_SM);
    display.setCursor(0, 18);
    display.print(stateVal[stateValNUM]);
    
 } else if(stateOLED == 1) {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.printf("Temperature");
    display.setTextSize(2);
    display.setCursor(15, 15);
    display.printf("%.2f *C", temp);
    
 } else if(stateOLED == 2) {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.printf("Humidity");
    display.setTextSize(2);
    display.setCursor(15, 15);
    display.printf("%.2f PCT", humidity);
    
 }
 display.display();
}
