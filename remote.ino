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
int R = 0;
int G = 2;
int B = 32;
int s = 0;
void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led1, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);    
  pinMode(B, OUTPUT);
  digitalWrite(led1, LOW);
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("รหัสปุ่มกด: ");
    Serial.println(results.value);
    if (results.value == code1) { // ถ้าค่าที่ส่งมาตรงกับ ค่าในตัวแปร code1 ให้ทำใน ปีกกา if
      Serial.println("LED ON");
      digitalWrite(led1, HIGH);
    }
    if (results.value == code2) { // ถ้าค่าที่ส่งมาตรงกับ ค่าในตัวแปร code2 ให้ทำใน ปีกกา if
      Serial.println("LED OFF");
      digitalWrite(led1, LOW);
    }
    if (results.value == code3) {
      Serial.println("LED RED ON");
      // กำหนด LED สีแดง
      //s = 0;
      analogWrite(R, 255);
      analogWrite(G, 0);
      analogWrite(B, 0);
      delay(500);
    }
    if (results.value == code4) {
      Serial.println("LED GREEN ON");
      // กำหนด LED สีเขียว
      //s = 0;
      analogWrite(R, 0);
      analogWrite(G, 255);
      analogWrite(B, 0);
      delay(500);
    }
    if (results.value == code5) {
      Serial.println("LED PINK ON");
      // กำหนด LED สีชมพู
      //s = 0;
      analogWrite(R, 255);
      analogWrite(G, 0);
      analogWrite(B, 120);
      delay(500);
    }
    if (results.value == code6) {
      Serial.println("LED BLUE ON");
      // กำหนด LED สีน้ำเงิน
      //s = 0;
      analogWrite(R, 0);
      analogWrite(G, 0);
      analogWrite(B, 255);
      delay(500);
    }
    if (results.value == code7) {
      Serial.println("LED PURPLE ON");
      // กำหนด LED สีม่วง
      //s = 0;
      analogWrite(R, 160);
      analogWrite(G, 2);
      analogWrite(B, 255);
      delay(500);
    }
    if (results.value == code8) {
      Serial.println("LED RGB ON");
      s = 1;
      while(s == 1){
        if (irrecv.decode(&results)) {
          if (results.value == code9) {
            Serial.println("LED OFF");
            // กำหนด LED ดับ
            s = 0;
            //break;
          }
          irrecv.resume(); // Receive the next value
        }
        ch(s);
        
      }
    }
    if (results.value == code9) {
      Serial.println("LED OFF");
      // กำหนด LED ดับ
      s = 0;
      ch(s);
    }
    irrecv.resume(); // Receive the next value
  }
}

void ch(int i){
  if(i == 1){
      analogWrite(R, 255);
      analogWrite(G, 0);
      analogWrite(B, 0);
      delay(500);
      // กำหนด LED สีเขียว
      analogWrite(R, 0);
      analogWrite(G, 255);
      analogWrite(B, 0);
      delay(500);
      // กำหนด LED สีน้ำเงิน
      analogWrite(R, 0);
      analogWrite(G, 0);
      analogWrite(B, 255);
      delay(500);
  }
  else if(i == 0){
      analogWrite(R, 0);
      analogWrite(G, 0);
      analogWrite(B, 0);
      delay(500);
  }
}
