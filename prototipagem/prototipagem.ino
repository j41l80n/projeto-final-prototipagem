#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h> 

Servo microservo9g;

// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 

#define SS_PIN 10
#define RST_PIN 9

void setup() {
  // define que o servo esta ligado a porta digital 3
  microservo9g.attach(3);
  // move o servo para a posicao inicial
  microservo9g.write(90);
  // inicia a serial
  Serial.begin(9600);
  // inicia  SPI bus
  SPI.begin();
  // inicia MFRC522
  mfrc522.PCD_Init(); 
  // Mensagens iniciais no serial monitor
  //  Serial.println("Aproxime o seu cartao do leitor...");
  //  Serial.println();
}

void loop() {
  
}
