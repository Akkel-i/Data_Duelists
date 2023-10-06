/*
 * liitäntäkaaviot: https://esp32io.com/tutorials/esp32-rfid-nfc
 */

#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <string>

#define SS_PIN  5  // ESP32 pin GPIO5 
#define RST_PIN 27 // ESP32 pin GPIO27 
#define EEPROM_SIZE 1024

String Scanned_value_NFC;
String NFC1;
String NFC2;
String muutettu_arvo;
bool playersCreated = false;

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  
  // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}



// hahmon luonti
class CreatePlayer {
public:
  // Constructor to initialize the variables
  CreatePlayer(String nameValue, int strValue, int defValue, int agiValue, int conValue) {
    name = nameValue;
    str = strValue;
    def = defValue;
    agi = agiValue;
    con = conValue;
  }
    String getName() {
    return name;
  }
  int getStr() {
    return str;
  }
  int getDef() {
    return def;
  }
  int getAgi() {
    return agi;
  }
  int getCon() {
    return con;
  }
private:
  String name;
  int str;
  int def;
  int agi;
  int con;
};



void loop() { 
  //NFC1 = "";
  //NFC2 = "";
  Scanned_value_NFC = "";
  // lukee nfc funktiolla ja tallentaa arvoon
  Scanned_value_NFC = read_NFC();
  Serial.println("skannattu tagi on: " + Scanned_value_NFC);
  if (Scanned_value_NFC.length() == 0) {
    Serial.println("Arvoa ei löydy, laita NFC tagi");
  } else if (NFC1.length() == 0 && Scanned_value_NFC != NFC1 ) {
      NFC1 = Scanned_value_NFC;
      Serial.println("Saved to NFC1");
    } else if (Scanned_value_NFC != NFC2) {
      // If NFC1 is not empty, assign it to NFC2
      NFC2 = Scanned_value_NFC;
      Serial.println("Saved to NFC2");
  }


  Serial.println("NFC1 arvo on: " + NFC1);
  Serial.println("NFC2 arvo on: " + NFC2);
  Serial.println();

  // testiä vaa toimiiks toi UID arvon muutos numeroihin
    if (!NFC1.length() == 0) {
      Serial.println("funktio mikä muuttaa UID meidän arvoiksi: ");
      for (int i = 0; i < NFC1.length(); i++) {
        Serial.print(" " + UID_value(String(NFC1[i])));
      }
      Serial.println();
    }

  /* testiä toimiiko muistiin tallentaminen ja lukeminen
   *  if (NFC1.length() != 0) {
   * saveToMemory(NFC1);
   * }
   * Serial.print("Muistista luettu arvo on: ");
   * Serial.print(getFromMemory());
   */

  if ( playersCreated == false) {
  // str, def, agi, con. Tällä kutsulla tekee 
  CreatePlayer player1("Jonas", 10, 42, 10, 5);
  CreatePlayer player2("Aku", 10, 42, 10, 5);
  playersCreated = true;
    // statseja haetaan komennolla: player1.getDef()
    Serial.println("hahmot luotu ja ");
    Serial.print("player1 deffa on: " +  String(player1.getDef()) + " ja player2 constitution on: " +  String(player2.getCon()));
  }
  
  delay(2000); // odottaa 2 sekuntia
}








// FUNKTIOT ALHAALLA


// tämä funktio hakee NFC lukialla NFC laitteen UID tiedon ja return se
String read_NFC() {
  String UID = "" ;
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      // print UID in Serial Monitor in the hex format ja UID muuttuja on nyt meidän NFC tagin arvo
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        String hexValue = String(rfid.uid.uidByte[i], HEX);
        Serial.print(hexValue);
        UID += hexValue;
      }
      Serial.println();

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
  return UID;
}






// muuttaa 0-9 a-f joksikin numeroksi
int UID_value(String x) {
  if (x == "0") {
    return 1;
  } else if ( x == "1") {
    return 2;
  } else if ( x == "2") {
    return 3;
  } else if ( x == "3") {
    return 4;
  } else if ( x == "4") {
    return 5;
  } else if ( x == "5") {
    return 6;
  } else if ( x == "6") {
    return 7;
  } else if ( x == "7") {
    return 8;
  } else if ( x == "8") {
    return 9;
  } else if ( x == "9") {
    return 0;
  } else if ( x == "a") {
    return -1;
  } else if ( x == "b") {
    return -2;
  } else if ( x == "c") {
    return -3;
  } else if ( x == "d") {
    return -4;
  } else if ( x == "e") {
    return -5;
  } else if ( x == "f") {
    return -6;
  }
};

// tallentaa esp32 muistiin muuttujan, pitäis pystyy tallentaa myös array, eli sit vaa laittaa array sisään
void saveToMemory(String toBeSaved) {
  EEPROM.put(0, toBeSaved);
  EEPROM.commit();
};

// hakee esp32 muistista arvon, jos haluut käyttää niin muista loop
String getFromMemory() {
  String savedThing;
  EEPROM.get(0, savedThing);
  return savedThing;
};
