////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// Fast Adressable Bitbang LED Library
/// Copyright (c)2015, 2017 Dan Truong
///
/// This is the simplest exmple to use the library.
///
/// This example is for an Arduino Uno board with a LED strip connected to
/// port D6. Targetting any other board requires you to change something.
/// The program sends an array of pixels to display on the strip.
/// "strip" represents the hardware: LED types and port configuration,
/// "pixels" represents the data sent to the LEDs: a series of colors.
///
/// Wiring:
///
/// The LED strip DI (data input) line should be on port D6 (Digital pin 6 on
/// Arduino Uno). If you need to change the port, change all declarations below
/// from, for example from "ws2812b<D,6> myWs2812" to "ws2812b<B,4> myWs2812"
/// if you wanted to use port B4.
/// The LED power (GND) and (+5V) should be connected on the Arduino Uno's GND
/// and +5V.
///
/// Visual results:
///
/// If the hardware you use matches this program you will see the LEDs blink
/// repeatedly red, green, blue, white, in that order.
///
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <FAB_LED.h>
#include <string.h>

// Declare the LED protocol and the port
ws2812b<D,6>  strip;

// How many pixels to control
const uint8_t numPixels = 16;

// How bright the LEDs will be (max 255)
const uint8_t maxBrightness = 16;

// The pixel array to display
grb  pixels[numPixels] = {};

using namespace std; 
////////////////////////////////////////////////////////////////////////////////
// Sets the array to specified color
////////////////////////////////////////////////////////////////////////////////
void FillPixels(char r, char g, char b)
{
  for(int i = 0; i < numPixels; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}

////////////////////////////////////////////////////////////////////////////////
// This method is automatically called once when the board boots.
////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  // Turn off the LEDs
  Serial.println("start;");
  strip.clear(2 * numPixels);
}

String s;

////////////////////////////////////////////////////////////////////////////////
/// @brief This method is automatically called repeatedly after setup() has run.
/// It is the main loop.
////////////////////////////////////////////////////////////////////////////////
void loop()
{
  if (Serial.available() > 0) {
    s = Serial.readStringUntil(';');
  }
  
  SerialHandler();

}

void SerialHandler()
{
  char newString[50];
  strcpy(newString, s.c_str());
  for(int i = 0; i != 50; i++)
  {
    if(newString[i] == 1)
    {
      newString[i] = 0;
    }
  }
  if(newString[0] == 'F')   //"FFFFBBBLLLRRR"
  {
   Set_front(newString[1],newString[2],newString[3]);
   Set_back(newString[4],newString[5],newString[6]);
   Set_left(newString[7],newString[8],newString[9]);
   Set_right(newString[10],newString[11],newString[12]);
   Serial.print("R;");
  }
  else if (newString[0] == 'S') //"F(POS)RGB"
  {
    Set_pixel(newString[1],newString[2],newString[3],newString[4]);
    Serial.print("R;");
  }
  else if (newString[0] == 'T') //"T"
  {
    Send_newPixel();
    Serial.print("R;");
  }
  else if (newString[0] == 'C') //"T"
  {
    clearPixels();
    Serial.print("R;");
  }
  else if(newString[0] == 'P')
  {
    Serial.print("pong;");
  }
  for(int i = 0; i != 50; i++)
  {
    s[i] = '\0';  
    newString[i] = '\0'; 
  }
}

void Set_pixel(int pos,char r,char g,char b)
{
    pixels[pos].r = r;
    pixels[pos].g = g;
    pixels[pos].b = b;
}

void Send_newPixel()
{
  strip.sendPixels(numPixels, pixels);
}

void led_errror()
{
  FillPixels(255,0,0);
}
void clearPixels(void)
{
  for(int i = 0; i != numPixels; i++)
  {
    pixels[i].r = 0;
    pixels[i].g = 0;
    pixels[i].b = 0;
  }
}
void Set_left(char r,char g,char b)
{
  for(int i = 0; i != 4; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}
void Set_front(char r,char g,char b)
{
  for(int i = 4; i != 8; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}
void Set_right(char r,char g,char b)
{
  for(int i = 8; i != 12; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}
void Set_back(char r,char g,char b)
{
  for(int i = 12; i != 16; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}
