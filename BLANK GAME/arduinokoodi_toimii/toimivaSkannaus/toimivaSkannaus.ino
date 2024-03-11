/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-rfid-nfc
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5  // ESP32 pin GPIO5 
#define RST_PIN 27 // ESP32 pin GPIO27 

MFRC522 rfid(SS_PIN, RST_PIN);

String Scanned_value_NFC;
String NFC1 = "";
String NFC2 = "";
String convertedNFC1;
String convertedNFC2;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  //Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

void loop() {

  Scanned_value_NFC = "";
  // lukee nfc funktiolla ja tallentaa arvoon
  Scanned_value_NFC = read_NFC();
  //Serial.println("skannattu tagi on: " + Scanned_value_NFC);
  if (Scanned_value_NFC.length() == 0) {
    //Serial.println("Arvoa ei löydy, laita NFC tagi");
  } else if (NFC1.length() == 0 && Scanned_value_NFC != NFC1 ) {
      NFC1 = Scanned_value_NFC;
      //Serial.println("Saved to NFC1");
    } else if (Scanned_value_NFC != NFC2) {
      // If NFC1 is not empty, assign it to NFC2
      NFC2 = Scanned_value_NFC;
      //Serial.println("Saved to NFC2");
  }


  //Serial.println("NFC1 arvo on: " + NFC1);
  //Serial.println("NFC2 arvo on: " + NFC2);
  //Serial.println();

  // testiä vaa toimiiks toi UID arvon muutos numeroihin
    if (NFC1.length() != 0 && NFC2.length() != 0) {
      //Serial.println("funktio mikä muuttaa UID meidän arvoiksi: ");
        convertedNFC1 = convertUID(NFC1);
        convertedNFC2 = convertUID(NFC2);
        // NÄMÄ ON NE NUMEROT
        Serial.println(convertedNFC1);
        Serial.println(convertedNFC2);
        //Serial.println();
    }

    //
  


 //delay(1000);
 }

// FUNKTIOT


// tämä funktio hakee NFC lukialla NFC laitteen UID tiedon ja return se
String read_NFC() {
  String UID = "" ;

    //Serial.println("Trying to read...");

  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      //Serial.print("RFID/NFC Tag Type: ");
      //Serial.println(rfid.PICC_GetTypeName(piccType));


      // print UID in Serial Monitor in the hex format ja UID muuttuja on nyt meidän NFC tagin arvo
      //Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        //Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        String hexValue = String(rfid.uid.uidByte[i], HEX);
        //Serial.print(hexValue);
        UID += hexValue;
      }
      //Serial.println();

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }

    return UID;
}

// muuttaa 0-9 a-f joksikin numeroksi
String convertUID(const String& uid) {
    String result = "";

    for (int i = 0; i < uid.length(); i++) {
        char c = uid[i];
        int value = 0;

        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        } else {
            // Handle invalid characters here (if needed)
            // For now, we'll set the value to 0 for any invalid character
        }
        value = constrain(value, 0, 9);
        //Serial.println(value);
        result += String(value);
    }

    return result;
}
