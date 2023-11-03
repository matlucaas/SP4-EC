#include <ArduinoJson.h>    // Lib to format JSON Document
#include "EspMQTTClient.h"  // Lib to comunicate MQTT from ESP

// Define os pinos do LED RGB
const int pinoR = 10;  // Pino para o LED vermelho
const int pinoG = 11; // Pino para o LED verde
const int pinoB = 9; // Pino para o LED azul
const int pinoBotao = 12; // Pino para o botão
int buttonState = 0;
int verificarBotao = 0;
const int buzzer = 7;
unsigned long tempoInicio; // Tempo desde que o programa começou usando a função millis()
unsigned long tempoFoco = 30000; // Tempo de duração do foco - 30 segundos
unsigned long tempoDescanso = 10000; // Tempo de duração do descanso inicial - 10 segundos;
unsigned long intervaloTotal = tempoFoco + tempoDescanso; // Soma do tempo do ciclo
int indiceDescanso = 0;
char  apertaBotaoJson[100];
float valorBotaoPressionado = 0;

EspMQTTClient client
(
  "WiFI",                //nome da sua rede Wi-Fi
  "2153818aa",           //senha da sua rede Wi-Fi
  "mqtt.tago.io",       //Endereço do servidor MQTT
  "Default",            //User é sempre default pois vamos usar token
  "2fd007b0-7978-4d12-8444-1e4bb3013479",              // Código do Token
  "SPRINT4",              //Nome do device
  1883                  //Porta de comunicação padrao
);

void setup() {
  Serial.begin(9600);
  pinMode(pinoR, OUTPUT);
  pinMode(pinoG, OUTPUT);
  pinMode(pinoB, OUTPUT);
  pinMode(pinoBotao, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  Serial.println("Conectando WiFi");
  while(!client.isWifiConnected()){
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("Conectado!");

  Serial.println("Conectando com o broker MQTT");
  while(!client.isMqttConnected()){
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("Conectado!");
}

void onConnectionEstablished()
{}

void azul(){
  analogWrite(pinoR,220);
  analogWrite(pinoG,220);
  analogWrite(pinoB,255);
}

void loop() {
  
  tempoInicio = millis();
  buttonState = digitalRead(pinoBotao);
  
  if (tempoInicio % intervaloTotal < tempoFoco){
    // Tempo de duração da etapa de foco
    if(verificarBotao >= 1){
      // Envia os dados para a nuvem
      valorBotaoPressionado += 1;
      StaticJsonDocument<300> documentoJson;
      documentoJson["variable"] = "valorBotaoPressionado";
      documentoJson["value"] = valorBotaoPressionado;
      serializeJson(documentoJson, apertaBotaoJson);
      Serial.println("Enviando dados do botão");
      Serial.println(apertaBotaoJson);
      
      client.publish("topicoSPRINT4", apertaBotaoJson);
      client.loop(); 
      Serial.print("Dados enviados para a nuvem.");
      indiceDescanso += 1;
    }
    
    verificarBotao = 0;
    digitalWrite(pinoR, HIGH); 
    digitalWrite(pinoG, HIGH); 
    digitalWrite(pinoB, HIGH);
    noTone(buzzer);
  }
  
  else{
    // Tempo de duração da etapa de descanso
    
    if(indiceDescanso == 3){
      while(1){ 
        digitalWrite(pinoR, HIGH); 
        digitalWrite(pinoG, LOW); 
        digitalWrite(pinoB, LOW);
        delay(1000);
        digitalWrite(pinoR, LOW); 
        digitalWrite(pinoG, LOW); 
        digitalWrite(pinoB, LOW);
        delay(1000);
      }
    }
    
    if (buttonState == LOW) {
      // Botão pressionado durante o descanso, definir a cor do LED como azul
      verificarBotao += 1;
      Serial.println(tempoInicio);
    }
    
    if (verificarBotao == 0){ // Caso o botão não seja pressionado, emite um alerta sonoro e visual para apertar o botão, para que assim seja contabilizado que o usuário está em foco
      digitalWrite(pinoR, HIGH); 
      digitalWrite(pinoG, LOW); 
      digitalWrite(pinoB, LOW);
      tone(buzzer, 1500);
    }else if(verificarBotao >= 1){ // Caso o botão seja pressionado, ir para o modo de descanso
      azul();
      noTone(buzzer);
    }
  }
  delay(1);
}
