#include <WiFi.h> //Biblioteca conexão Wifi

const char* ssid = "CJ"; //Rede
const char* password = "12345678"; // Senha da Rede



void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    
    Serial.print("Connecting to "); 
    Serial.println(ssid);

    WiFi.begin(ssid, password); //Comando para conectar na rede

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.println("Wifi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); //Endereço da conexão
}

void loop(){
  conecta_rede ();
}

void conecta_rede (){
  digitalWrite(2, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
  delay(2000);
}

