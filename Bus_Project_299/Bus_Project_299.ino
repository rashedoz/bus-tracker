/*
 * Write personal data of a MIFARE RFID card using a RFID-RC522 reader
 * Uses MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT. 
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * Hardware required:
 * Arduino
 * PCD (Proximity Coupling Device): NXP MFRC522 Contactless Reader IC
 * PICC (Proximity Integrated Circuit Card): A card or tag using the ISO 14443A interface, eg Mifare or NTAG203.
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */

/*Esp8266 | Arduino 
 — — — — — — — — -
     RX | 3 
     TX | 2 
    GND | GND (same)
    VCC | 3.3v (same) 
  CH_PD | none (same) 
 GPIO 0 | None (same) 
 GPIO 2 | None (same)
 RST    | None
 
 */
 /* The circuit:
 * LCD RS pin to digital pin 6
 * LCD Enable pin to digital pin 7
 * LCD D4 pin to digital pin 14 (A0)
 * LCD D5 pin to digital pin 15
 * LCD D6 pin to digital pin 16
 * LCD D7 pin to digital pin 17
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) */

 /* GPS | Arduinoo
  *  TX | 5
  *  RX | 4
  *  VCC | 3.3V
 */
 
 
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h> 

//RFID
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

//Wifi pin ESP8266
#define RX 2 //2
#define TX 3 //3

//GPS Pins
static const int RXPin = 5, TXPin = 4;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;  // The TinyGPS++ object


// LCD Config
const int rs = 6, en = 7, d4 = 14, d5 = 15, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance


/*            ****Config ESP8266 Wifi Module****            */

String AP = "Walankaa";       // CHANGE ME
String PASS = "tokyoghoul"; // CHANGE ME
String API = "RPI7NWXKPYQXEUTR";   // CHANGE Write API Of Channel
String HOST = "api.thingspeak.com";
String PORT = "80";
String field1 = "field1";   //lattitude
String field2 = "field2";   //longitude
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 

int sendCounter=1;


//Passenger List
int uid_counter=0;
String passenger_list[20];


SoftwareSerial esp8266(RX,TX);  //Wifi Module Serial
SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device

    void setup() {
                Serial.begin(9600);        // Initialize serial communications with the PC
                
                SPI.begin();               // Init SPI bus
                mfrc522.PCD_Init();        // Init MFRC522 card
                ss.begin(GPSBaud);         //GPS 
                
                lcd.print("Starting System");
             
                
                Serial.println(F(" Bus System Ready! "));
                
                // set up the LCD's number of columns and rows:
                lcd.begin(16, 2);
                lcd.setCursor(0,0);
                lcd.print("Bus Status!");
  
    }

      void loop() {

                  lcd.setCursor(0,0);
                  lcd.print("Passenger:");
                  lcd.print(uid_counter);

                    /*Get Gps Data in variable*/
                    double longitude;
                    double lattitude;
                    double *l;
                    double *ltt;
                    l = &longitude;
                    ltt = &lattitude;
                    getGPS(l,ltt); //Get GPS Location

                    

                    if(sendCounter%100==0){
                      
                          ss.end();       //temporarily close gps serial
                          esp8266.begin(9600);       ///wifi serial
                          
                          lcd.clear();
                          lcd.print("Sending GPS");

                          Serial.print("Longitude:");
                          Serial.print(longitude,6);
                          Serial.print("Lattitude:");
                          Serial.println(lattitude,6);
                          
                        //Setup Wifi Module
                        sendCommand("AT",5,"OK");
                        sendCommand("AT+CWMODE=1",5,"OK");
                        sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
  
                          
                          Serial.print("SendCounter:");
                          Serial.println(sendCounter);
                          sendData(lattitude,longitude);
                          lcd.print("Sent");
                          lcd.clear();
 
                          esp8266.end();              //end wifi serial
                          ss.begin(GPSBaud);         //GPS begin again
                      }
                      
                  sendCounter++;
                  
                  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
                  MFRC522::MIFARE_Key key;
                  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
                
                  // Look for new cards
                  if ( ! mfrc522.PICC_IsNewCardPresent()) {
                    return;
                  }
                
                  // Select one of the cards
                  if ( ! mfrc522.PICC_ReadCardSerial()) {
                    return;
                  }
                  
                  /*Dump card Info and Convert UID to String*/
                  Serial.print(F("Card UID:"));    //Dump UID
                  byte uid;
                  byte suid;
                  String sid;
                  String full_id="";
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                     //Serial.print(mfrc522.uid.uidByte[i], HEX);
                     uid = mfrc522.uid.uidByte[i];
                     //Serial.print("(");
                     Serial.print(uid);
                    // Serial.print(")");
                     sid = String(uid); //Conver UID to string for complete UID
                     full_id =full_id + sid;
                   
                  }
                  
                  /*unsigned long final_uid=full_id.toInt();
                  Serial.print("\nUID:");
                  Serial.print(final_uid);
                  Serial.print("\nScanned UID:");
                  Serial.print(full_id);*/
                
                 
                
                  
                  /*Card Info*/
                  //Serial.print(F(" PICC type: "));   // Dump PICC type
                  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
                  //Serial.println(mfrc522.PICC_GetTypeName(piccType));
                
                  /* Sector with keys: 3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63(DO NOT TOUCH)*/
                  MFRC522::StatusCode status;
                
                 /*                          *******Write Data and Balance to RFID*************          */
                 
                  /* Sector with keys: 3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63(DO NOT TOUCH)/
                  Serial.println(F("Type Your name, ending with #")); //Store Passenger Name
                  writeData(12,13,key); //write name   */
                  
                  /* UNCOMMENT FOR READINGH SECTOR
                  Serial.println("Enter sector to print");
                  int sectorToRead=Serial.parseInt(); //Serial Read sector to read
                  Serial.println(sectorToRead);   
                  dumpSector(sectorToRead,key); */
                  
                  /* Sector with keys: 3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63(DO NOT TOUCH)/
                  //Enter User Balance
                  Serial.println("Enter Balace: ");
                  writeData(16,17,key); //Enter Balance */
                
                  
                  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      // see all blocks in hex
                  
                
                  /*          ********************Read Name and Balance from RFID Card***************       */
                  
                  String n;
                  String b;
                  
                  Serial.print(F(" Name: "));
                  
                  n = readData(12,key);
                  Serial.print(n);
                
                  Serial.print(F(" Balance: "));
                  b = readData(16,key);
                  int balance;
                  balance = b.toInt();  //convert balance to int
                  Serial.print(balance);
                  
                
                  
                
                  /*lcd.setCursor(0,1);
                  lcd.print("Passenger:");
                  lcd.print(uid_counter);*/
                
                                                           /*Check IN and Check Out of RFID */                                    
                  for(int i=0;i<=uid_counter;i++){
                      if (full_id==passenger_list[i]){
                        Serial.println("  Checked  Out");
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Checked  Out!!");
                        lcd.setCursor(0,1);
                        lcd.print(n);
                        lcd.setCursor(8,1);
                        lcd.print(":");
                        lcd.print(balance);
                        delay(900);
                        lcd.clear();
                        passenger_list[i] = passenger_list[uid_counter-1];
                        passenger_list[uid_counter-1] = "";
                        uid_counter--;
                        
                        break;
                      }
                      else if(full_id!=passenger_list[i] && (i==uid_counter || uid_counter==0)){
                        //Serial.print(full_id);
                        Serial.print("  Check In");
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Checked In!!");
                        lcd.setCursor(0,1);
                        lcd.print(n);
                        lcd.setCursor(8,1);
                        lcd.print(":");
                        lcd.print(balance);
                        delay(900);
                        lcd.clear();
                        passenger_list[uid_counter] = full_id;
                        uid_counter++;
                        break;
                        }  
                  }
                
                 //Print Current Passenger List
                   Serial.print("\n Current Passenger:");
                   Serial.println(uid_counter);
                   for(int i=0;i<uid_counter;i++){
                      Serial.print("Passenger[");
                      Serial.print(i);
                      Serial.print("]:");
                      Serial.println(passenger_list[i]);
                
                   }
                  Serial.print("\n");
                
                  
                  
                  
                  //Serial.println(" ");
                  mfrc522.PICC_HaltA(); // Halt PICC
                  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
                
      }











/*Write Data to RFID Sector*/

void writeData(int b1, int b2,MFRC522::MIFARE_Key key){ 
        key=key;
        byte buffer[34];
        byte block;
        MFRC522::StatusCode status;
        byte len;
      
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial

        len = Serial.readBytesUntil('#', (char *) buffer, 30) ; // read   from serial
        for (byte i = len; i < 30; i++) buffer[i] = ' ';     // pad with spaces
      
        block = b1;  //block to write 1,4
        
        //Serial.println(F("Authenticating using key A..."));
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
          Serial.print(F("PCD_Authenticate() failed: "));
          Serial.println(mfrc522.GetStatusCodeName(status));
          return;
        }
        else Serial.println(F("PCD_Authenticate() success: "));
      
        // Write block
        status = mfrc522.MIFARE_Write(block, buffer, 16);
        if (status != MFRC522::STATUS_OK) {
          Serial.print(F("MIFARE_Write() failed: "));
          Serial.println(mfrc522.GetStatusCodeName(status));
          return;
        }
        else Serial.println(F("MIFARE_Write() success: "));
      
        block = b2; //2,5
        //Serial.println(F("Authenticating using key A..."));
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
          Serial.print(F("PCD_Authenticate() failed: "));
          Serial.println(mfrc522.GetStatusCodeName(status));
          return;
        }
      
        // Write block
        status = mfrc522.MIFARE_Write(block, &buffer[16], 16);
        if (status != MFRC522::STATUS_OK) {
          Serial.print(F("MIFARE_Write() failed: "));
          Serial.println(mfrc522.GetStatusCodeName(status));
          return;
        }
        else Serial.println(F("MIFARE_Write() success:"));
   }



  /*Dump Sector Data*/
  void dumpSector(int sector,MFRC522::MIFARE_Key key){
    
    // Dump the sector data
    Serial.println(F("Current data in sector:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();
    
    }



    
   /*Read Data*/
   String readData(int block,MFRC522::MIFARE_Key key){
      
          String s="";
          String sfull="";
          
          byte buffer1[18];
          byte len = 18;
           MFRC522::StatusCode status;
           
          //------------------------------------------- GET FIRST NAME
          status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
          if (status != MFRC522::STATUS_OK) {
            Serial.print(F("Authentication failed: "));
            Serial.println(mfrc522.GetStatusCodeName(status));
            return;
          }
        
          status = mfrc522.MIFARE_Read(block, buffer1, &len);
          if (status != MFRC522::STATUS_OK) {
            Serial.print(F("Reading failed: "));
            Serial.println(mfrc522.GetStatusCodeName(status));
            return;
          }
        
          //PRINT FIRST NAME
          for (uint8_t i = 0; i < 16; i++)
          {
            if (buffer1[i] != 32)
            {
              //Serial.write(buffer1[i]);
              s = char(buffer1[i]);
              sfull = sfull + s;
            }
          }
        //Serial.print(" ");
        return sfull;
    }


/*    ***Send GPS Data to ThingsSpeak***   */
void sendData(double lattitude,double longitude){
    
     String getData = "GET /update?api_key="+ API +"&"+ field1 +"=" + lattitude +"&"+ field2 +"=" + longitude;
     sendCommand("AT+CIPMUX=1",5,"OK");
     sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
     sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
     esp8266.println(getData);delay(1500);countTrueCommand++;
     sendCommand("AT+CIPCLOSE=0",5,"OK");
}

/*    ***Send Command to Wifi Module***   */
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
        Serial.println("Ok");
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

  /* ***** GET GPS Location ******* */
 void getGPS(double *longitude,double *lattitude){
  
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      *lattitude = gps.location.lat();
      *longitude = gps.location.lng(); 
    }
  }
 }
