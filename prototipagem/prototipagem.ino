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
  if (conteudo.substring(1) == "D8 4B 12 22")
  {
    microservo9g.write(-90);
    digitalWrite(led_liberado, HIGH);
    Serial.println("Cartao1 - Acesso liberado !");
    Serial.println();
    delay(3000);
    microservo9g.write(90);
    digitalWrite(led_liberado, LOW);
  }
  if (conteudo.substring(1) == "87 4B DC 8A")
  {
    Serial.println("Cartao2 - Acesso negado !!");
    Serial.println();
    // Pisca o led vermelho
    for (int i= 1; i<5 ; i++)
    {
      digitalWrite(led_negado, HIGH);
      delay(200);
      digitalWrite(led_negado, LOW);
      delay(200);
    }
  }
  delay(1000);
}
