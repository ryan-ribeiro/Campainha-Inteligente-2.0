#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "DFRobot_DF2301Q.h"

const char* ssid = "WiFi network name/SSID";
const char* password = "password";

const char* serverName = "https://api.callmebot.com/whatsapp.php?phone=";

unsigned long timerDelay = 5000;
unsigned long lastTime = 0;

const int buzzerPin = 9;  // Pino digital conectado ao buzzer
const int tempoBase = 500;  // Tempo base de 1 batida em milissegundos

DFRobot_DF2301Q asr; // Instância da biblioteca DFRobot, referente ao sensor de detecção de voz offline SEN0539-EN
uint8_t CMDID;       // Variável para armazenar os bits dos comandos interpretados pelo sensor de voz

void tocarCampainha() {
  const int Csharp6 = 1109;
  const int A4 = 440;

  const int duracaoCsharp6 = tempoBase / 2;
  const int duracaoA4 = tempoBase;

  tone(buzzerPin, Csharp6, duracaoCsharp6);
  delay(duracaoCsharp6 + 50);

  tone(buzzerPin, A4, duracaoA4);
  delay(duracaoA4 + 50);
}

void tocarAcessoNegado() {
  tone(buzzerPin, 3000, tempoBase);
  delay(100);
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Conectado à rede WiFi com endereço IP: ");
  Serial.println(WiFi.localIP());

  while (!(asr.begin())) {
    Serial.println("Comunicação I2C falhou, tentando novamente em alguns segundos.");
    delay(3000);
  }
  Serial.println("Begin ok!");
    /**
   * @brief Set voice volume
   * @param voc - Volume value(1~7)
   */
  asr.setVolume(4);

  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  asr.setMuteMode(0);

  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  asr.setWakeTime(20);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    CMDID = asr.getCMDID(); // Lê os comandos CMDID a partir do módulo de reconhecimento de voz offline
  } else {
    Serial.println("WiFi desconectado");
    setup();
  }

  if (CMDID == 141) { // Verifique se o comando CMDID está correto
    if ((millis() - lastTime) > timerDelay) { 
      asr.playByCMDID(141);  // Módulo confirma em áudio aos visitantes ter entendido o comando
      RequisicaoHttpPOST();  // Envia mensagem ao remetente cadastrado
      tocarCampainha();
      lastTime = millis();
    }
  } else {
    tocarAcessoNegado();
  }
}

void RequisicaoHttpPOST() {
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure();  // Necessário para ignorar verificação de certificado SSL
  http.begin(client, serverName);

  http.addHeader("Content-Type", "application/json");
  String body = "{\"phone\":\"{{phone}}\",\"text\":\"Alguém está na porta!\"},\"apikey\":\"{{apikey}}\"}";

  Serial.println(body);

  int httpResponseCode = http.POST(body);

  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("Resposta do servidor:");
    Serial.println(payload);
  } else {
    Serial.print("Erro na solicitação HTTP: ");
    Serial.println(httpResponseCode);
  }

  http.end();
} 