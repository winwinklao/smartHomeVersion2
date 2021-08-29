#include <analogWrite.h>
#include <IRremote.h>
int RECV_PIN = 23;
int led1 = 4;
#define code1  16753245  // ค่าปุ่มกดที่ 1
#define code2  16736925  // ค่าปุ่มกดที่ 2
#define code3  16769565  // ค่าปุ่มกดที่ 3
#define code4  16720605  // ค่าปุ่มกดที่ 4
#define code5  16712445  // ค่าปุ่มกดที่ 5
#define code6  16761405  // ค่าปุ่มกดที่ 6
#define code7  16769055  // ค่าปุ่มกดที่ 7
#define code8  16754775  // ค่าปุ่มกดที่ 8
#define code9  16748655  // ค่าปุ่มกดที่ 9
IRrecv irrecv(RECV_PIN);
decode_results results;

int RGBPin[] = { 0, 2, 32 };
int i = 0;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(RGBPin[0], OUTPUT);
  pinMode(RGBPin[1], OUTPUT);
  pinMode(RGBPin[2], OUTPUT);
}

void SetRGB(int r, int g, int b) {
  analogWrite(RGBPin[0], r);
  analogWrite(RGBPin[1], g);
  analogWrite(RGBPin[2], b);
}

void RGBOFF(int r, int g, int b){
  analogWrite(RGBPin[0], r);
  analogWrite(RGBPin[1], g);
  analogWrite(RGBPin[2], b);
}

void loop() {
  if(i == 1){
      if(i == 1){
       Serial.println("Red");
       SetRGB(255, 0, 0); // Red
       delay(500);
      }
      if (irrecv.decode(&results)){
         if(results.value == code8){
            Serial.println("LED RGB OFF");
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
          if (results.value == code9){
            Serial.println("LED RGB OFF");
            // กำหนด LED ดับ
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
         irrecv.resume();
       }
      if(i == 1){
       Serial.println("Green");
       SetRGB(0, 255, 0); // Green
       delay(500);
      }
      if (irrecv.decode(&results)){
         if(results.value == code8){
            Serial.println("LED RGB OFF");
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
          if (results.value == code9){
            Serial.println("LED RGB OFF");
            // กำหนด LED ดับ
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
         irrecv.resume(); 
       }
      if(i == 1){
       Serial.println("Blue");
       SetRGB(0, 0, 255); // Blue
       delay(500);
      }
      if (irrecv.decode(&results)){
         if(results.value == code8){
            Serial.println("LED RGB OFF");
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
          if (results.value == code9){
            Serial.println("LED RGB OFF");
            // กำหนด LED ดับ
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
         irrecv.resume();
       }
      if(i == 1){
       Serial.println("Yellow");
       SetRGB(255, 255, 0); // Yellow
       delay(500);
      }
      if (irrecv.decode(&results)){
         if(results.value == code8){
            Serial.println("LED RGB OFF");
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
          if (results.value == code9){
            Serial.println("LED RGB OFF");
            // กำหนด LED ดับ
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
         irrecv.resume(); 
       }
      if(i == 1){
       Serial.println("Sky blue");
       SetRGB(0, 255, 255); // Sky blue
       delay(500);
      }
      if (irrecv.decode(&results)){
         if(results.value == code8){
            Serial.println("LED RGB OFF");
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
          if (results.value == code9){
            Serial.println("LED RGB OFF");
            // กำหนด LED ดับ
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
         irrecv.resume(); 
       }
      if(i == 1){
       Serial.println("Pink");
       SetRGB(255, 0, 255); // Pink
       delay(500);
      }
      if (irrecv.decode(&results)){
         if(results.value == code8){
            Serial.println("LED RGB OFF");
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
          if (results.value == code9){
            Serial.println("LED RGB OFF");
            // กำหนด LED ดับ
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
         irrecv.resume(); 
       }
      if(i == 1){
       Serial.println("White");
       SetRGB(255, 255, 255); // White
       delay(500);
      }
       if (irrecv.decode(&results)){
         if(results.value == code8){
            Serial.println("LED RGB OFF");
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
          if (results.value == code9){
            Serial.println("LED RGB OFF");
            // กำหนด LED ดับ
            i = 0;
            RGBOFF(0, 0, 0);
            delay(500);
          }
         irrecv.resume(); 
       }
  }
  else{
    if (irrecv.decode(&results)){
      Serial.print("รหัสปุ่มกด: ");
      Serial.println(results.value);
      if (results.value == code1){ 
        Serial.println("LED ON");
        digitalWrite(led1, HIGH);
      }
      if (results.value == code2){
        Serial.println("LED OFF");
        digitalWrite(led1, LOW);
      }
      if (results.value == code3){
        Serial.println("LED RED ON");
        // กำหนด LED สีแดง
        analogWrite(RGBPin[0], 255);
        analogWrite(RGBPin[1], 0);
        analogWrite(RGBPin[2], 0);
        delay(500);
      }
      if (results.value == code4){
        Serial.println("LED GREEN ON");
        // กำหนด LED สีเขียว
        analogWrite(RGBPin[0], 0);
        analogWrite(RGBPin[1], 255);
        analogWrite(RGBPin[2], 0);
        delay(500);
      }
      if (results.value == code5){
        Serial.println("LED PINK ON");
        // กำหนด LED สีชมพู
        analogWrite(RGBPin[0], 255);
        analogWrite(RGBPin[1], 0);
        analogWrite(RGBPin[2], 120);
        delay(500);
      }
      if (results.value == code6){
        Serial.println("LED BLUE ON");
        // กำหนด LED สีน้ำเงิน
        analogWrite(RGBPin[0], 0);
        analogWrite(RGBPin[1], 0);
        analogWrite(RGBPin[2], 255);
        delay(500);
      }
      if (results.value == code7){
        Serial.println("LED PURPLE ON");
        // กำหนด LED สีม่วง
        analogWrite(RGBPin[0], 160);
        analogWrite(RGBPin[1], 2);
        analogWrite(RGBPin[2], 255);
        delay(500);
      }
      if (results.value == code8){
        Serial.println("LED RGB ON");
        i = 1;
      }
      if (results.value == code9){
        Serial.println("LED COLOR OFF");
        // กำหนด LED ดับ
        i = 0;
        analogWrite(RGBPin[0], 0);
        analogWrite(RGBPin[1], 0);
        analogWrite(RGBPin[2], 0);
        delay(500);
      }
      irrecv.resume(); // Receive the next value
    }
  }
} 
