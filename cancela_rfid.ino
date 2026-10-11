#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Definição de Pinos
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 6
#define BUTTON_PIN 2

MFRC522 rfid(SS_PIN, RST_PIN);
Servo cancela;

// Lista de Cartões Autorizados (UIDs numéricos)
const long cartoesAutorizados[] = {1243044925, 2023456789};
const int numCartoes = sizeof(cartoesAutorizados) / sizeof(cartoesAutorizados[0]);

bool cancelaAberta = false;
int posicaoDoServo = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  
  cancela.attach(SERVO_PIN);
  cancela.write(0); // Garante cancela fechada no início
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Sistema de Cancela RFID Inicializado.");
}

void loop() {
  // 1. Verificação do Botão de Acionamento Manual
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Acionamento Manual Detectado!");
    abrirCancela();
  }

  // 2. Verificação de Leitura do Cartão RFID
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Converter UID do cartão lido para valor numérico
  long uidLido = 0;
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidLido = (uidLido << 8) | rfid.uid.uidByte[i];
  }

  Serial.print("Cartao Lido UID: ");
  Serial.println(uidLido);

  // Validar se o UID pertence à lista de autorizados
  bool autorizado = false;
  for (int i = 0; i < numCartoes; i++) {
    if (uidLido == cartoesAutorizados[i]) {
      autorizado = true;
      break;
    }
  }

  if (autorizado) {
    Serial.println("Acesso Permitido!");
    abrirCancela();
  } else {
    Serial.println("Acesso Negado!");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Função para abrir a cancela de forma suave (0º a 90º)
void abrirCancela() {
  if (!cancelaAberta) {
    for (posicaoDoServo = 0; posicaoDoServo <= 90; posicaoDoServo++) {
      cancela.write(posicaoDoServo);
      delay(15);
    }
    cancelaAberta = true;
    delay(5000); // Permanece aberta por 5 segundos
    fecharCancela();
  }
}

// Função para fechar a cancela de forma suave (90º a 0º)
void fecharCancela() {
  if (cancelaAberta) {
    for (posicaoDoServo = 90; posicaoDoServo >= 0; posicaoDoServo--) {
      cancela.write(posicaoDoServo);
      delay(15);
    }
    cancelaAberta = false;
  }
}
