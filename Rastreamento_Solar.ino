#include <WiFi.h> //Biblioteca conexão Wifi
#include <ThingSpeak.h> //Biblioteca conexão ThingSpeak

const char* ssid = "CJ"; //Rede
const char* password = "12345678"; // Senha da Rede
const long channel = 3366372; //Canal utilizado
const char *WRITE_API = "W7ZQLMMVG5GXUQF0"; //Senha de acesso API

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

    ThingSpeak.begin(client); //Incializa o ThingSpeak
}

void loop(){
  conecta_rede ();
  int estado_led;
  estado_led = digitalRead(2);
  Serial.print("LED = ");
  Serial.println(estado_led);
  delay(1000);
 
  conecta_nuvem ();
}

void conecta_rede (){
  digitalWrite(2, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
  delay(2000);
}

void conecta_nuvem(){

}

