 /*
 * liitäntäkaaviot: https://esp32io.com/tutorials/esp32-rfid-nfc
 */

#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <string>
#include <GxEPD.h>
#include <GxGDEW075T8/GxGDEW075T8.h>      // 7.5" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
//fonts
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <ezButton.h>

#define SS_PIN  5  // ESP32 pin GPIO5 
#define RST_PIN 27 // ESP32 pin GPIO27 
#define EEPROM_SIZE 1024

const char* maxfontmono1 = "FreeMonoBold24pt7b";
const GFXfont* maxfmono = &FreeMonoBold24pt7b;
const char* midfontmono2 = "FreeMonoBold18pt7b";
const GFXfont* midfmono = &FreeMonoBold18pt7b;
const char* smallfontmono3 = "FreeMonoBold12pt7b";
const GFXfont* smallfmono = &FreeMonoBold12pt7b;
const char* tinyfontmono4 = "FreeMonoBold9pt7b";
const GFXfont* tinyfmono = &FreeMonoBold9pt7b;

GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 17, /*RST=*/ 16); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4); // default selection of (9), 7

String Scanned_value_NFC;
String NFC1 = "";
String NFC2 = "";
String convertedNFC1;
String convertedNFC2;
int arrayNFC1[4];
int arrayNFC2[4];
bool playersCreated = false;
bool gameWon = false;

const int buttonPin = 13; // Pin connected to the button
ezButton button(buttonPin);


MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522


  button.setDebounceTime(50); // set debounce time to 100 milliseconds 
  
  // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");

    display.init();
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(smallfmono);
/************************************ END EPAPER SETUP ****************************/
  display.setCursor(30, 30);
  display.println("YAY ^^");
  display.println();
  display.setCursor(60, 70);
  display.setFont(smallfmono);
  display.println("Yattaaa!!");
  display.setCursor(60, 90);
  //print_face(); saa piirrettyä naaman

  display.setCursor(140, 200);
  display.setFont(maxfmono);
  display.println("DATA DUELIST");

  display.setCursor(300, 300);
  display.setFont(smallfmono);
  display.println("with UFC");

  display.update();
}



// hahmon luonti
class CreatePlayer {
public:
  // Constructor to initialize the variables
  CreatePlayer(String nameValue, int strValue, int defValue, int agiValue, int conValue, int winValue, int lossValue) {
    name = nameValue;
    str = strValue;
    def = defValue;
    agi = agiValue;
    con = conValue;
    wins = winValue;
    losses = lossValue;
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
  int getWins() {
    return wins;
  }
  int getLosses() {
    return losses;
  }
    void addWins() {
    wins++;
  }
  void addLosses() {
    losses++;
  }
private:
  String name;
  int str;
  int def;
  int agi;
  int con;
  int wins;
  int losses;
};



void loop() { 

  button.loop(); // MUST call the loop() function first

  int btnState = button.getState();
  Serial.println(btnState);
  
  if(btnState == 0){
    Serial.println("The button is pressed");
    NFC1 = "";
    NFC2 = "";
    gameWon = false;
  };
  // TOIMIIIII!!!!!



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

  /* testiä toimiiko muistiin tallentaminen ja lukeminen (pitäis toimii, ainakin simuloiden)
   *  if (NFC1.length() != 0) {
   * saveToMemory(NFC1);
   * }
   * Serial.println("Muistista luettu arvo on: ");
   * Serial.println(getFromMemory());
   */

  //tekee UID numero-arvoista array(4) jossa statsit 0-9 arvoilla
    createStats(convertedNFC1, arrayNFC1);
    createStats(convertedNFC2, arrayNFC2);

/*     näillä voi käydä läpi arrayn sisällöt
    for (int i = 0; i < 4; i++) {
    Serial.print("Result[" + String(i) + "]: ");
    Serial.println(arrayNFC1[i]);
    }
    for (int i = 0; i < 4; i++) {
        Serial.print("Result[" + String(i) + "]: ");
        Serial.println(arrayNFC2[i]);
    } */






  // str, def, agi, con, voitot, häviöt. Tällä kutsulla tekee  (array kutsut pitäisi toimia ihan oikein, simulaatiossa)
  //CreatePlayer player1("Jonas", 10, 42, 10, 5, 0, 0 );
  CreatePlayer player1("Jonas", arrayNFC1[0], arrayNFC1[1], arrayNFC1[2], arrayNFC1[3], 0, 0 );
  //CreatePlayer player2("Aku", 10, 42, 10, 5, 0, 0 );
  CreatePlayer player2("Aku", arrayNFC2[0], arrayNFC2[1], arrayNFC2[2], arrayNFC2[3], 0, 0 );

    // statseja haetaan komennolla: player1.getDef()
    Serial.println("hahmot luotu ja ");
    Serial.println("player1 deffa on: " +  String(player1.getDef()) + " ja player2 constitution on: " +  String(player2.getCon()) + " Pelaajan1 nimi on: " + player1.getName());
  

    //tästä alkaa battle
    if (NFC1.length() != 0 && NFC2.length() != 0) {
    int hp1 = player1.getCon() + 50;
    int hp2 = player2.getCon() + 50;
    int str1 = player1.getStr();
    int str2 = player2.getStr();
    int def1 = player1.getDef();
    int def2 = player2.getDef();
    int agi1 = player1.getAgi();
    int agi2 = player2.getAgi();
    int atk1 = str1 - def2;
    int atk2 = str2 - def1;
    
    if (atk1 < 0){
        atk1 = 1;
    };
    if (atk2 < 0){
        atk2 = 1;
    };
    Serial.println();
    Serial.println("=== Hahmo 1 ===");
    Serial.println("---------------");
    Serial.println("HP on: " + String(hp1));
    Serial.println("---------------");
    Serial.println("Strengi on: " + String(str1));
    Serial.println("---------------");
    Serial.println("Deffa on: " + String(def1));
    Serial.println("---------------");
    Serial.println("Agi on: " + String(agi1));
    Serial.println("---------------");
    Serial.println();
    Serial.println();
    Serial.println("=== Hahmo 2 ===");
    Serial.println("---------------");
    Serial.println("HP on: " + String(hp2));
    Serial.println("---------------");
    Serial.println("Strengi on: " + String(str2));
    Serial.println("---------------");
    Serial.println("Deffa on: " + String(def2));
    Serial.println("---------------");
    Serial.println("Agi on: " + String(agi2));
    Serial.println("---------------");
    Serial.flush();

    //hahmojen statsi printti


  //Serial.print(player1.getStr() - player2.getDef());
  while (gameWon == false) {
      int hit1 = random(1,7);
      int hit2 = random(1,7);
      
    //kattoo onko jommankumman critti true, eli tekee crit dmg, ja joka kierros kattoo uudelleen.
    //bool crit1 = (random(0,19) > player1.getAgi());
    //Serial.println(crit1);
    //bool crit2 = random(0,19) > player2.getAgi();
    //Serial.println(crit2);

    // ykköspelaajan hyökkäys crit tai ilman
    if (random(1,21) <= agi1) {          // pitäis ottaa random luku 0-20 ja verrata sitä hahmon agi, eli critti chance
        hp2 = hp2 - ((hit1 + atk1) * 1.5);
        Serial.println("pelaaja 1 crittas!" + String((hit1 + atk1) * 1.5) + " damage");
    } else  {   
      hp2 = hp2 - (hit1 + atk1);
        Serial.println("pelaaja 1 normi hyökkäys!" + String(atk1 + hit1) + " damage");
    }

    // kakkospelaajan hyökkäys crit tai ilman
    if (random(1,21) <= agi2) {          // pitäis ottaa random luku 0-20 ja verrata sitä hahmon agi, eli critti chance
        hp1 = hp1 - ((hit2 + atk2) * 1.5);
            Serial.println("pelaaja 2 crittas! " + String((hit2 + atk2) * 1.5) + " damage");
    } else {
      hp1 = hp1 - (hit2 + atk2);
            Serial.println("pelaaja 2 normi hyökkäys!" + String(hit2 + atk2) + " damage");
    }  

    Serial.println("pelaajan 1 hp on: " + String(hp1));
    Serial.println("pelaajan 2 hp on: " + String(hp2));


    if (hp1 <= 0) {
    Serial.println("player2 win");
    gameWon = true;

    display.setCursor(350, 350);
    display.setFont(smallfmono);
    display.println("player2 win");
    display.update();
    }
    else if  (hp2 <= 0) {
    Serial.println("player1 win");
    gameWon = true;

    display.setCursor(350, 350);
    display.setFont(smallfmono);
    display.println("player1 win");
    display.update();
    };


  };

  };



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
