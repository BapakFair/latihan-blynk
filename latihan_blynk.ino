#define BLYNK_TEMPLATE_ID "TMPL6rlxVsMXD"
#define BLYNK_TEMPLATE_NAME "sinau iot"
#define BLYNK_AUTH_TOKEN "B9WJ1OVOk6zIuv0qtcxR5oeVgzZO36VX"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Kopi Rahayu";//Enter your WIFI name
char pass[] = "indonesia123";//Enter your WIFI password

// int buzzer = D4;
int smokeA0 = A0;
int smokeD0 = D0;
int led = D3;
// int ledPutih = D1;

int sensorThres = 100;

BLYNK_WRITE(V1) {
  digitalWrite(D3, param.asInt());
}

void setup() {
  // pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  // pinMode(smokeD0, INPUT);
  pinMode(led, OUTPUT);
  // pinMode(ledPutih, OUTPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  Serial.begin(115200);
}

void loop() {
  int analogSensor = analogRead(smokeA0);
  int digitalSensor = digitalRead(smokeD0);

  Serial.print("Pin Analog 0: ");
  Serial.println(analogSensor);
  
  Blynk.virtualWrite(V0, analogSensor);

  Serial.print("Pin digital 0: ");
  Serial.println(digitalSensor);

 // Untuk cek nilai threshold

 if (analogSensor > sensorThres)
 {
    tone(buzzer, 1000, 200);
    Serial.print("Message: Terdeteksi Asap! ");
    digitalWrite(led, HIGH);
    delay(200);
 }
 else
 {
   noTone(buzzer);
   digitalWrite(led, LOW);
 }
 delay(1000);
 Blynk.run();

}