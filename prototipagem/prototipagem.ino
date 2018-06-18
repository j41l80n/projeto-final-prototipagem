#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

Servo microservo9g;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

int pos = 0;

void setup() {
  mfrc522.PCD_Init(); // Inicia MFRC522
  // define que o servo esta ligado a porta digital 6
  microservo9g.attach(6);
  // move o servo para a posicao inicial
  microservo9g.write(0);
  // inicia a serial
  Serial.begin(9600);
  // inicia  SPI bus
  SPI.begin();
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
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
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  //usuario cadastrado
  if (conteudo.substring(1) == "ED 78 03 CA")
  {
    for (pos = microservo9g.read(); pos < 180; pos += 1) {
      microservo9g.write(pos);
      delay(20);
    }
    microservo9g.detach();
  }
  //usuario nao cadastrado
  if (conteudo.substring(1) == "BD 9B 06 7D")
  {
   
    

  }
  delay(500);
}
