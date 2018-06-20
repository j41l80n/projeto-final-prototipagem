#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

Servo microservo9g;
MFRC522 mfrc522(SS_PIN, RST_PIN);

int ledVermelho = 4;
int ledAzul = 2;
int pos = 0;
String conteudo = "";

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  // inicia a serial
  Serial.begin(9600);
  // inicia  SPI bus
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("UID da tag :");

  byte letra;
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println(conteudo);
  Serial.print("Identificador de Usuario: ");
  conteudo.toUpperCase();

  if (conteudo != "ED 78 03 CA")
  {
    Serial.println(conteudo);
    usuarioPermitido();
  }
  else {
    digitalWrite(ledVermelho, HIGH);
  }
  conteudo = "";
  delay(2000);
  digitalWrite(ledVermelho, LOW);
}

void usuarioPermitido() {
  microservo9g.attach(6);
  microservo9g.write(0);
  digitalWrite(ledAzul, HIGH);
  for (pos = microservo9g.read(); pos < 180; pos += 1) {
    microservo9g.write(pos);
    delay(20);
  }
  digitalWrite(ledAzul, LOW);
  microservo9g.detach();
}
