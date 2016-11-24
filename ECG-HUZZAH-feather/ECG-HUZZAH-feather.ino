//L2 FDV - Projet Ingénierie 2016/2017 - ECG wireless
//Nina Guérin - Julien Pichon - Simon Fradet 

/*
 *  Ce code permets de connecter le module wifi HUZZAH Feather ESP8266 à un routeur wifi (un téléphone en partage de connexion par exemple) et à un ordinateur connecté au même routeur wifi
 *  This cod epermit to connect wifi modul HUZZAH Feather ESP8266 to a wifi box (such as a smartphone sharing data) et to a computer connected to the same wifi box
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>

// Appel des module nécéssaire à l'éxécution
// Call the needed modul to execute

ESP8266WiFiMulti WiFiMulti;
int connected2 =0;
WiFiClient client;
const uint16_t port = 1000;
const char * host = "adresse_IP"; // insérer ici l'adresse IP de l'ordinateur auquel vous allez vous connecter / insert here your computer IP adress
char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "S: 1 2 3 4 1254 1245 1234";       // a string to send back
unsigned int localPort = 2390;      // local port to listen on
int packetNumber=0;
unsigned int time0=micros();
unsigned int time1=micros();
int samplingDelay = 50000; //20ms =50 hz
int counter =0;
int received;

WiFiUDP Udp;

void setup() {
  pinMode(0,OUTPUT);
    Serial.begin(9600);
    delay(10);
// initialize device
    Serial.println("Initializing I2C devices...");
    // Connection du module au réseau wifi choisi. NB: l'ordinateur doit aussi être connecté à ce réseau
    //Connect the modul to choosen wifi network. NB: computer must be connect to the same network
     WiFiMulti.addAP("nom_wifi", "mot_de_passe"); // insérer ici le nom et le mot de passe du réseau auquel vous souhaiter connecté le module / insert here name and password of the network

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(50);
    Udp.begin(localPort);
    delay(50);
}

//Cette boucle récupère les données du port série d'Arduino puis le module wifi HUZZAH les envoie en wifi
//This loop get datas from arduino's serial port and wifi modul HUZZAH send it by wifi
void loop() {
    if (Serial.available()>0) 
    {
    String toto = Serial.readStringUntil(13);
    int received = toto.toInt();
    Serial.print(Serial.available());
    time1=micros();
    unsigned int time2=time1-time0;
    if(time2>=1)
         {
         char msg[30];
         Udp.beginPacket(host,2390);
         digitalWrite(0,LOW);
         if(packetNumber<255) packetNumber ++;
         else packetNumber=0;
         sprintf(msg, "%d", received);
           Serial.println(msg);
           Udp.write(msg);
           Udp.endPacket();
         time0=micros();
         delay(5);
         }
    }
}

