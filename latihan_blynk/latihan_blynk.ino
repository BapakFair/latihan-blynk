#define BLYNK_TEMPLATE_ID "TMPL6rlxVsMXD"
#define BLYNK_TEMPLATE_NAME "sinau iot"
#define BLYNK_AUTH_TOKEN "B9WJ1OVOk6zIuv0qtcxR5oeVgzZO36VX"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Ruang Kerja";//Enter your WIFI name
char pass[] = "Indonesia45";//Enter your WIFI password

int smokeA0 = A0;
int smokeD0 = D0;
int led_biru = D2;
int led_putih = D3;
int led_merah = D4;
int buzzer = D5;

int sensorThres = 100;

BLYNK_WRITE(V2) {
  digitalWrite(D2, param.asInt());
}

BLYNK_WRITE(V3) {
  digitalWrite(D3, param.asInt());
}

BLYNK_WRITE(V4) {
  digitalWrite(D4, param.asInt());
}

BLYNK_WRITE(V5) {
  digitalWrite(D0, param.asInt());
}

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(led_biru, OUTPUT);
  pinMode(led_putih, OUTPUT);
  pinMode(led_merah, OUTPUT);

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
    digitalWrite(led_biru, HIGH);
    delay(200);
 }
 else
 {
   noTone(buzzer);
   digitalWrite(led_biru, LOW);
 }
 delay(1000);
 Blynk.run();

}