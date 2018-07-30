/*Esp8266 | Arduino 
 — — — — — — — — -
     RX | 3 
     TX | 2 
    GND | GND (same)
    VCC | 3.3v (same) 
  CH_PD | None(3.3v) (same) 
 GPIO 0 | None (same) 
 GPIO 2 | None (same)
 RST    | None
 
 */


#include <SoftwareSerial.h> 
#include <FirebaseArduino.h>

#define RX 2 //2
#define TX 3 //3



//SoftwareSerial esp8266(2, 3); 

String AP = "Walankaa";       // CHANGE ME
String PASS = "tokyoghoul"; // CHANGE ME
String API = "1FSWU8DT4B6K4V67";   // CHANGE ME
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 

// Set these to run example.
#define FIREBASE_HOST "console.firebase.google.com/u/0/project/bus-service-69ffe/database/bus-service-69ffe/data"
#define FIREBASE_AUTH "f8yJgdidYle098kDLilZoxLLgfJZ0agN0274NT6T"

SoftwareSerial esp8266(RX,TX); 
 
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("pushbutton", 0);
  Firebase.set("sunlight", 0);
  Firebase.set("redlight", 0);
  Firebase.set("cooldown", 0);
  Firebase.set("brrr", 0);
}
void loop() {

   Firebase.setInt("pushbutton", 123);
  String valSensor;
 valSensor = "Rashed";
 String getData = "GET /update?api_key="+ API +"&"+ field +"=" + valSensor;
sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}
int getSensorData(){
  return random(1000); // Replace with 
}
void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
