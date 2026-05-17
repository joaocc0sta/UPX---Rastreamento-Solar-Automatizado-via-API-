#include <Wire.h> //Comunicação I2C
#include <WiFi.h> //Biblioteca conexão Wifi
#include <ThingSpeak.h> //Biblioteca conexão ThingSpeak
#include <Adafruit_INA219.h> //Biblioteca do módulo sensor ina219

const char* ssid = "CJ"; //Rede
const char* password = "12345678"; // Senha da Rede
const long channel = 3366372; //Canal utilizado
const char *WRITE_API = "W7ZQLMMVG5GXUQF0"; //Senha de acesso API

WiFiClient client;
Adafruit_INA219 ina219;

void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    
    Serial.print("Connecting to "); 
    Serial.println(ssid);

    WiFi.mode(WIFI_STA); //Coloca o ESP32 em modo estação

    WiFi.begin(ssid, password); //Comando para conectar na rede

    while (WiFi.status() != WL_CONNECTED){ //Teste de conexão Wifi
        delay(500);
        Serial.print(".");
    }

    Serial.println("Wifi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); //Endereço da conexão

   ThingSpeak.begin(client); //Incializa o ThingSpeak

   	uint32_t currentFrequency; /*definição de um ponteiro currentFrequency */
    if (! ina219.begin())
	{ 
		Serial.println("Falha ao encontrar o INA219"); 
		while (1) { delay(10); 
	} 
}
}

void loop(){
  controle_placa();
 
  //conecta_nuvem ();
}

void controle_placa(){ //Função que ler os dados coletados pelo sensor INA219

  float tensao_nominal = 0; 
  float corrente_nominal = 0;
  float potencia_W = 0;

    //Comandos para coletar tensão, corrente e potência
    tensao_nominal = ina219.getBusVoltage_V(); 
    corrente_nominal = ina219.getCurrent_mA();
    potencia_W = tensao_nominal*corrente_nominal;

    //Mostra os dados lidos no monitor serial
    Serial.print("Tensao: ");
    Serial.print(tensao_nominal);
    Serial.println("V");
    Serial.print("Corrente: ");
    Serial.print(corrente_nominal);
    Serial.println("mA");
    Serial.print("Potência: ");
    Serial.print(potencia_W);
    Serial.println("mW");

//Envio dos dados para o ThingSpeak
ThingSpeak.setField(1, tensao_nominal);
ThingSpeak.setField(2, corrente_nominal);
ThingSpeak.setField(3, potencia_W);

ThingSpeak.writeFields(channel, WRITE_API);

  Serial.println("Dado enviado ao ThingSpeak!");

  delay(20000); 
}


