#define button1 A0
#define button2 A1

#include <EEPROM.h>
#include <MicroView.h>

unsigned char count;  // a "char" is 8-bits = one byte It makes the numbers go from 0 to 255

void setup() {


pinMode(button1,INPUT_PULLUP);  // Use INPUT_PULLUP instead of a digitalwrite(#,HIGH); to more accurately describe intent.
pinMode(button2,INPUT_PULLUP);

count = EEPROM.read(0); //read what was saved at spot 0 and make it equal to count
  
  uView.begin();
  uView.clear(PAGE);		// clear page
  uView.print("Hello Liz!");
  uView.display();
  delay(2000);
  uView.setCursor(0,0);
  uView.print("Let's knit");
  uView.display();
  delay(2000);
  uView.setCursor(0,0);
  uView.print("Ur on row ");
  uView.display();
}

void loop() {

static boolean pressed1 = false;
static long int presstime1 = 0L;
static boolean longpress1 = false;

static boolean pressed2 = false;
static long int presstime2 = 0L;
static boolean longpress2 = false;

static boolean changed = true;  // default with true to force the first display of the count value. Otherwise it won't display until the count is changed by the first button press.

if (digitalRead(button1) == 0)
{
  if (!pressed1)
  {
     pressed1 = true;
     presstime1 = millis();
     count++; //add one to the count
     changed = true;  // Take note that the count has changed to update the display
     EEPROM.write(0,count); //save it
  }
  else
  if (!longpress1 && (millis() > (presstime1 + 3000)))
  {
    longpress1 = true;
    count = 0; //reset
    changed = true;  // Take note that the count has changed to update the display
    EEPROM.write(0,count); //save it
  }
}
else
{
  if (pressed1 && (millis() > presstime1 + 1))
  {
    pressed1 = false;    
    longpress1 = false;
  }
}

  
if (digitalRead(button2) == 0)
{
  if (!pressed2)
  {
     pressed2 = true;
     presstime2 = millis();
     count--;
     changed = true;  // Take note that the count has changed to update the display
     EEPROM.write(0,count);
  }
  else
  if (!longpress2 && (millis() > (presstime2 + 3000)))
  {
    longpress2 = true;
    count = 0;
    changed = true;  // Take note that the count has changed to update the display
    EEPROM.write(0,count);
  }
}
else
{
  if (pressed2 && (millis() > presstime2 + 1))
  {
    pressed2 = false;    
    longpress2 = false;
  }
}
  
if (changed)  // Only clear the display and show the count if it the changed flag is true. Allows removal of orphaned char(s) without flickering.
{
  uView.setCursor(0,10);
  uView.print("   ");
  uView.display();

  uView.setCursor(0,10);
  uView.print(count);
  uView.display();
  changed = false;  // Reset changed flag to avoid the display flickering.
}
  
}
