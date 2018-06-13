#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

Servo microservo9g;
//#define SS_PIN 10;
//#define RST_PIN 9;

int pos = 0;

void setup() {
  // define que o servo esta ligado a porta digital 6
  microservo9g.attach(6);
  // move o servo para a posicao inicial
  microservo9g.write(0);
  // inicia a serial
  Serial.begin(9600);
  // inicia  SPI bus
  SPI.begin();


}

void loop() {
  Serial.print("microservo9g1: "+microservo9g.read());
  for (pos = microservo9g.read(); pos < 180; pos += 1) {
    microservo9g.write(pos);
    delay(20);
  }
  microservo9g.detach(); 
}
