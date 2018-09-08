#include "DisplayManager.h"
#include <math.h>

#define COLOR_NONE Color(20, 20, 20)
#define JOYSTICK_COLOR Color(200, 200, 0)
#define SELECTED_COLOR Color(0, 200, 200)



DisplayManager::DisplayManager(Adafruit_WS2801 newStrip, Board* newBoard)
{
	strip = newStrip;
	board = newBoard;
}

void DisplayManager::DisplayBoard(int joystick_location, int selected_location)
{
  clearBoard();

  for (int i = 0; i < LINES_AMOUNT; i ++)
  {
    displayLine(i);
  }

  if ((LOCATION_ROAD_MIN <= joystick_location) &&
            (joystick_location <= LOCATION_ROAD_MAX))
  {
    displayLed(joystick_location, 0 /*led index*/ , JOYSTICK_COLOR);
  }

  if ((LOCATION_ROAD_MIN <= selected_location) &&
            (selected_location < LOCATION_ROAD_MAX))
  {
    displayLed(selected_location, 0 /*led index*/ , SELECTED_COLOR);
  }

  if (LOCATION_FINISHED == joystick_location)
  {
    strip.setPixelColor(120, JOYSTICK_COLOR);
  }

  if (LOCATION_FINISHED == selected_location)
  {
    strip.setPixelColor(120, SELECTED_COLOR);
  }

  if (LOCATION_DEADPOOL_1 == joystick_location)
  {
    strip.setPixelColor(128, JOYSTICK_COLOR);
  }

  if (LOCATION_DEADPOOL_1 == selected_location)
  {
    strip.setPixelColor(128, SELECTED_COLOR);
  }

  if (LOCATION_DEADPOOL_2 == joystick_location)
  {
    strip.setPixelColor(128 + 4, JOYSTICK_COLOR);
  }

  if (LOCATION_DEADPOOL_2 == selected_location)
  {
    strip.setPixelColor(128 + 4, SELECTED_COLOR);
  }

  strip.show();   // write all the pixels out
}

void DisplayManager::clearBoard()
{
    for (int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, COLOR_NONE);
    }
}

void DisplayManager::displayLine(int lineIndex)
{
    Line line = board->GetLine(lineIndex);

    if (line.player == PLAYER_NONE)
    {
      return;
    }

    int firstLedIndex = PIXELS_PER_LINE * lineIndex;
    /*if (IS_DISPLAY_BINARY)
    {
      displayLineBinary(line, firstLedIndex);
    }
    else
    {*/
      displayLineCumulative(line, lineIndex);
    //}
}

void DisplayManager::displayLineBinary(Line line, int lineIndex)
{
  
}

void DisplayManager::displayLineCumulative(Line line, int lineIndex)
{
  int overflows = floor(line.pieces / PIXELS_PER_LINE);
  int remainder = line.pieces % (PIXELS_PER_LINE - 1);

  // First LED is for the cursor
  int i;
  for (i = 1; i < PIXELS_PER_LINE; i++)
  {
    uint32_t color = COLOR_NONE;

    if (i <= remainder) {
      color = GetPlayerColors(line.player, overflows);
      //DEBUG("Displaying player led ");
      //DEBUG("Line index: ");
      //DEBUG(lineIndex);
    } else if (overflows > 0) {
      color = GetPlayerColors(line.player, overflows - 1);
      //DEBUG("Displaying overflow led");
    }

    int ledIndexInLine = i;
    displayLed(lineIndex, ledIndexInLine, color);
    
  }
  //DEBUG("\n");
}

void DisplayManager::displayLed(int lineIndex, int ledIndex, uint32_t color)
{
  strip.setPixelColor((PIXELS_PER_LINE * lineIndex) + ledIndex, color);
}
