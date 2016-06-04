/* Cherry MX Custom Keypad Example Program
 * By: Dan Watson 
 * syncchannel.blogspot.com
 * 5/29/2016
 * 
 * This example program has the following behavior for the keys:
 *  -- They send w, a, s, and d respectively
 *  -- Software debouncing (5ms)
 *  -- Characters are only sent once when the key is depressed
 *  -- Only one key can be pressed at a time
 *  -- The backlight pulses, but goes to full brightness on a press
 *  
 *  All key behavior is completely customizable by modifying this program.
 *  
 *  See this reference to learn the various keyboard and mouse commands available:
 *  https://www.arduino.cc/en/Reference/MouseKeyboard
 */

// You need to include this in some versions of the IDE
//#include <Keyboard.h>

// Define I/O connections on board
#define SW1 9
#define SW2 10
#define SW3 5
#define SW4 13
#define BACKLIGHT 6

// Counter for updating the backlight
uint16_t backlightCounter = 0;

void setup()
{
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(BACKLIGHT, OUTPUT);
  
  Keyboard.begin();
}

void loop()
{
  // Check the first key. If it is pressed, wait 5ms
  if (digitalRead(SW1) == LOW)
  {
    delay(5);

    // Check again (debouncing). If still pressed, send key
    if (digitalRead(SW1) == LOW)
    {
      // Backlight to full brightness during press
      analogWrite(BACKLIGHT,200);
      backlightCounter = 201;

      // Send key
      Keyboard.print('w');

      // Sit here while key is still pressed, sending charatcer only once
      while(digitalRead(SW1) == LOW) { }
    }
  }


  // Check second key
  else if (digitalRead(SW2) == LOW)
  {
    delay(5);
    if (digitalRead(SW2) == LOW)
    {
      analogWrite(BACKLIGHT,200);
      backlightCounter = 201;
      Keyboard.print('a');
      while(digitalRead(SW2) == LOW) { }
    }
  }

  // Check third key
  else if (digitalRead(SW3) == LOW)
  {
    delay(5);
    if (digitalRead(SW3) == LOW)
    {
      analogWrite(BACKLIGHT,200);
      backlightCounter = 201;
      Keyboard.print('s');
      while(digitalRead(SW3) == LOW) { }
    }
  }

  // Check fourth key
  else if (digitalRead(SW4) == LOW)
  {
    delay(5);
    if (digitalRead(SW4) == LOW)
    {
      analogWrite(BACKLIGHT,200);
      backlightCounter = 0;
      Keyboard.print('d');
      while(digitalRead(SW4) == LOW) { }
    }
  }

  // If no keys were pressed, update the backlight
  else {
    backlightCounter++;

    // This if/else creates a pulsing effect instead of ramp from min to max
    if (backlightCounter < 32768)
      analogWrite(BACKLIGHT,map(backlightCounter,0,32767,0,175));
    else
      analogWrite(BACKLIGHT,map(backlightCounter,32768,65535,175,0));
  }
}
