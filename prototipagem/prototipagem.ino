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

void setup() {
    mfrc522.PCD_Init(); // Inicia MFRC522
  // define que o servo esta ligado a porta digital 6
  microservo9g.attach(6);
  // move o servo para a posicao inicial
  microservo9g.write(0);
  //definie o pino como saida
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  // inicia a serial
  Serial.begin(9600);
  // inicia  SPI bus
  SPI.begin();
  Serial.print("Identificador de Usuario: ");
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

  //mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo = "";
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
  // usuario cadastrado
  if (conteudo.substring(1) == "ED 78 03 CA")
  {
    digitalWrite(ledAzul, HIGH);
    for (pos = microservo9g.read(); pos < 180; pos += 1) {
      microservo9g.write(pos);
      delay(20);
    }
    delay(2000);
    digitalWrite(ledVermelho, LOW);
    microservo9g.detach();
  }
  
  //  digitalWrite(ledVermelho, HIGH);
  //  digitalWrite(ledAzul, HIGH);
  delay(500);
}

void usuarioPermitido(){

  
  }
