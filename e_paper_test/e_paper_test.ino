#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <Fonts/FreeMonoBold9pt7b.h> 
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>// this font is referred to below with the name maxfontmono1

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>

const char* maxfontmono1 = "FreeMonoBold24pt7b"; // << see? maxfontmono1
const GFXfont* maxfmono = &FreeMonoBold24pt7b;
const char* midfontmono2 = "FreeMonoBold18pt7b";
const GFXfont* midfmono = &FreeMonoBold18pt7b;
const char* smallfontmono3 = "FreeMonoBold12pt7b";
const GFXfont* smallfmono = &FreeMonoBold12pt7b;
const char* tinyfontmono4 = "FreeMonoBold9pt7b";
const GFXfont* tinyfmono = &FreeMonoBold9pt7b;

const char* maxfontsans1 = "FreeSans24pt7b";
const GFXfont* maxfsans = &FreeSans24pt7b;
const char* midfontsans2 = "FreeSans18pt7b";
const GFXfont* midfsans = &FreeSans18pt7b;
const char* smallfontsans3 = "FreeSans12pt7b";
const GFXfont* smallfsans = &FreeSans12pt7b;
const char* tinyfontsans4 = "FreeSans9pt7b";
const GFXfont* tinyfsans = &FreeSans9pt7b;

const char* maxfontsansbold1 = "FreeSansBold24pt7b";
const GFXfont* maxfsansbold = &FreeSansBold24pt7b;
const char* midfontsansbold2 = "FreeSansBold18pt7b";
const GFXfont* midfsansbold = &FreeSansBold18pt7b;
const char* smallfontsansbold3 = "FreeSansBold12pt7b";
const GFXfont* smallfsansbold = &FreeSansBold12pt7b;
const char* tinyfontsansbold4 = "FreeSansBold9pt7b";
const GFXfont* tinyfsansbold = &FreeSansBold9pt7b;

const char* maxfontsansboldOblique1 = "FreeSansBoldOblique24pt7b";
const GFXfont* maxfsansboldOblique = &FreeSansBoldOblique24pt7b;
const char* midfontsansboldOblique2 = "FreeSansBoldOblique18pt7b";
const GFXfont* midfsansboldOblique = &FreeSansBoldOblique18pt7b;
const char* smallfontsansboldOblique3 = "FreeSansBoldOblique12pt7b";
const GFXfont* smallfsansboldOblique = &FreeSansBoldOblique12pt7b;
const char* tinyfontsansboldOblique4 = "FreeSansBoldOblique9pt7b";
const GFXfont* tinyfsansboldOblique = &FreeSansBoldOblique9pt7b;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
