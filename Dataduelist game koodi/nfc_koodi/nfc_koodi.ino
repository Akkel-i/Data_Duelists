 /*
 * liitäntäkaaviot: https://esp32io.com/tutorials/esp32-rfid-nfc
 */

#include <SPI.h>
#include <MFRC522.h>
#include <string.h>


#define SS_PIN  5  // ESP32 pin GPIO5 
#define RST_PIN 27 // ESP32 pin GPIO27 


String Scanned_value_NFC;
String NFC1 = "";
String NFC2 = "";
String convertedNFC1;
String convertedNFC2;
int arrayNFC1[4];
int arrayNFC2[4];


MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522


  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");


}


void loop() { 







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
    if (NFC1.length() != 0 && NFC2.length() != 0) {
      Serial.println("funktio mikä muuttaa UID meidän arvoiksi: ");
        convertedNFC1 = convertUID(NFC1);
        convertedNFC2 = convertUID(NFC2);
        Serial.println(convertedNFC1 + " " + convertedNFC2);
        Serial.println();
    }



  //tekee UID numero-arvoista array(4) jossa statsit 0-9 arvoilla
    createStats(convertedNFC1, arrayNFC1);
    createStats(convertedNFC2, arrayNFC2);




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





/*  convertUID() käytetään näin:
    String NFC1 = "fa167765";
    String converted = convertUID(NFC1); */
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
        Serial.println(value);
        result += String(value);
    }

    return result;
}

// päivittää NFC:n numerot arrayhin jota voi käyttää sitten statseihin. Laita sisään string UID ja array johon haluat tulokset päivittyvät
void createStats(const String& input, int resultArray[4]) {
    // Make sure the input length is even to group numbers in pairs
    if (input.length() % 2 == 0) {
        for (int i = 0; i < input.length(); i += 2) {
            String numberPair = input.substring(i, i + 2);
            int num1 = numberPair.substring(0, 1).toInt();
            int num2 = numberPair.substring(1).toInt();
            resultArray[i / 2] = num1 + num2;
        }
    } else {
        // Handle the case when the input length is not even (if needed)
        // You can set the resultArray to an error state here if required
    }
}
