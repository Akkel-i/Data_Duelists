/*******************************************************************
Spotify parts:
    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow

Other code by Heikki Hietala and respective part websites
 *******************************************************************/

// ----------------------------
// Standard Libraries
// ----------------------------


#include <GxEPD.h>
//#include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w
#include <GxGDEW075T8/GxGDEW075T8.h>      // 7.5" b/w
//#include <GxGDEW075T7/GxGDEW075T7.h>      // 7.5" b/w 800x480

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

//fonts
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

const char* maxfontmono1 = "FreeMonoBold24pt7b";
const GFXfont* maxfmono = &FreeMonoBold24pt7b;
const char* midfontmono2 = "FreeMonoBold18pt7b";
const GFXfont* midfmono = &FreeMonoBold18pt7b;
const char* smallfontmono3 = "FreeMonoBold12pt7b";
const GFXfont* smallfmono = &FreeMonoBold12pt7b;
const char* tinyfontmono4 = "FreeMonoBold9pt7b";
const GFXfont* tinyfmono = &FreeMonoBold9pt7b;

//ottaa kuvan mukaan
//#include "img_01.h"

// constructor for AVR Arduino, copy from GxEPD_Example else
GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 17, /*RST=*/ 16); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4); // default selection of (9), 7




void setup()
{
  /******************************* START EPAPER SETUP ***************************************/
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
  display.println("Yattaaa!!!!");
  display.setCursor(60, 90);
  //print_face(); saa piirrettyä naaman
  //display.update();
  
   //uint16_t x = (display.width() - 64) / 2;
  //uint16_t y = 5;
  //display.drawExampleBitmap(gImage_img_01, x, y, 64, 180, GxEPD_BLACK);
//  display.drawBitmap(0, 0, img_01.h, 250, 122, EPD_BLACK);
  //display.update();

  display.drawExampleBitmap(img_01, x, y, 64, 180, GxEPD_BLACK);
  display.update();
  
  Serial.begin(115200);



}


void loop()
{

}

void print_face() {
  display.println(
  ".------\ /------.\n"
   "|       -       |\n"
   "|               |\n"
   "|               |\n"
   "|               |\n"
"_______________________\n"
"===========.===========\n"
  "/ ~~~~~     ~~~~~ \\\n"
 "/|     |     |\\\n"
" W   ---  / \\  ---   W\n"
 "\\      |o o|      /\n"
  "|                 |\n"
  "\\    #########    /\n"
   "\\  ## ----- ##  /\n"
    "\\##         ##/\n"
     "\\_____v_____/\n"
  );
}
