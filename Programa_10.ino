#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

int rele = 4;
int n = 0;
void seguranca();

char st[20];


void setup() {
  pinMode(rele, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o card: ");
  Serial.println();
}

void loop() {

 // seguranca();
  
  if(mfrc522.PICC_IsNewCardPresent()){
    if(mfrc522.PICC_ReadCardSerial()){
      //Serial.print("UID da tag: ");
      String conteudo= "";
      byte letra;

      for(byte i=0; i<mfrc522.uid.size; i++){
       // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       // Serial.print(mfrc522.uid.uidByte[i], HEX);
        conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      
      if (conteudo.substring(1) == "64 60 01 67"){
        if(digitalRead(rele) == LOW){
          delay(1000);
          digitalWrite(rele, HIGH);
          Serial.println("Carro Liberado!");
          delay(10000);
          digitalWrite(rele, LOW);
        }
      }
      else{
        digitalWrite(rele, LOW);
        Serial.println("Carro Bloqueado!");
      }
    }
  }
  else if (! mfrc522.PICC_IsNewCardPresent()){
    if(digitalRead(rele) == HIGH){
      digitalWrite(rele, LOW);
      Serial.print("Carro Bloqueado!\n");
    }
  }
  delay(250);
}

