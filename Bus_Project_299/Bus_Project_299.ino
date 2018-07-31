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
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) */
 
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h> 

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

//Wifi pin ESP8266
#define RX 2 
#define TX 3

// LCD Config
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 14, d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//Config ESP8266 Wifi Module
String AP = "Walankaa";       // CHANGE ME
String PASS = "tokyoghoul"; // CHANGE ME
String API = "FDW7ERYQ1EM9EXRZ";   // CHANGE ME
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";    //Thingspeak Filed Name
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;

int uid_counter=0;
String passenger_list[20];


SoftwareSerial esp8266(RX,TX); 

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  esp8266.begin(9600);       ///wifi serial
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  
  Serial.println(F("Write personal data on a MIFARE PICC "));
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Bus Status!");
}

void loop() {

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
  
  /*Dump card Info*/
  Serial.print(F("Card UID:"));    //Dump UID
  byte uid;
  byte suid;
  String sid;
  String full_id="";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     uid = mfrc522.uid.uidByte[i];
     Serial.print("(");
     Serial.print(uid);
     Serial.print(")");
     sid = String(uid); //Conver UID to string for complete UID
     full_id =full_id + sid;
   
  }
  
  /*unsigned long final_uid=full_id.toInt();
  Serial.print("\nUID:");
  Serial.print(final_uid);
  Serial.print("\nScanned UID:");
  Serial.print(full_id);*/
  
  for(int i=0;i<=uid_counter;i++){
      
      if (full_id==passenger_list[i]){
        Serial.println("Checked  In!!!!");
       
        break;
      }
      else if(full_id!=passenger_list[i] && (i==uid_counter || uid_counter==0)){
        //Serial.print(full_id);
        Serial.print("Check In");
        passenger_list[uid_counter] = full_id;
        uid_counter++;
        break;
        }  
  }
   
   Serial.print("\n Current Passenger:");
   Serial.println(uid_counter);
   for(int i=0;i<uid_counter;i++){
      Serial.print("Passenger[");
      Serial.print(i);
      Serial.print("]:");
      Serial.println(passenger_list[i]);

   }

  
  

  
  

  
 
   
  //Serial.print(F(" PICC type: "));   // Dump PICC type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  //Serial.println(mfrc522.PICC_GetTypeName(piccType));

  /* Sector with keys: 3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63(DO NOT TOUCH)*/
  MFRC522::StatusCode status;

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

  
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  String n;
  String b;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Name: ");
  //Serial.print(F("Name: "));
  
  n = readData(12,key);
 // Serial.print(n);
  lcd.print(n);

 
  lcd.setCursor(0,1);
  lcd.print("Balance: ");
  //Serial.print(F("Balance: "));
  b = readData(16,key);
  int balance;
  balance = b.toInt();  //convert balance to int
  //Serial.print(balance);
  lcd.print(balance);
  
  
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
