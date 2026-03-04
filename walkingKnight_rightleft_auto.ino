#define LGFX_AUTODETECT
#include <LovyanGFX.hpp>
#include "walk.h"

static LGFX lcd;

static uint32_t lcd_width ;
static uint32_t lcd_height;

static LGFX_Sprite sprites[2];
static LGFX_Sprite warrior;
static int_fast16_t sprite_height;
unsigned short knight[4096];

bool rightleft = true;
unsigned long lastFrameTime = 0;
const int frameDelay = 100;  // 100ms between frames

void drawFrame(int frameIndex) { //, int walkingLR, int walkingUD) {
  int frameX = (frameIndex % framesPerRow) * warriorWidth;   // Calculate position in sprite sheet
  int frameY = (frameIndex / framesPerRow) * warriorHeight;
  int arryIndex = 0;
  for (int y = 0; y < warriorHeight; y++) {
    for (int x = 0; x < warriorWidth; x++) {
      int sheetIndex = (frameY + y) * sheetWidth + (frameX + x);
      //warrior.drawPixel(x, y, walking[sheetIndex]);
      knight[arryIndex] = walking[sheetIndex];
      arryIndex++;
    }
  }
}

void setup(void) {
  lcd.init();
  lcd.setRotation(3);
  lcd.setBrightness(255);

  lcd_width = lcd.width();
  lcd_height = lcd.height();

  uint32_t div = 2;
  for (;;) {
    sprite_height = (lcd_height + div - 1) / div;
    bool fail = false;
    for (std::uint32_t i = 0; !fail && i < 2; ++i)
    {
      sprites[i].setColorDepth(lcd.getColorDepth());
      sprites[i].setFont(&fonts::Font2);
      fail = !sprites[i].createSprite(lcd_width, sprite_height);
    }
    if (!fail) break;
    for (std::uint32_t i = 0; i < 2; ++i)
    {
      sprites[i].deleteSprite();
    }
    ++div;
  }

  warrior.createSprite(warriorWidth, warriorHeight);
  warrior.setSwapBytes(true);
  drawFrame(9);
  warrior.pushImage(0, 0, warriorWidth,  warriorHeight, knight);

  lcd.startWrite();
}

int_fast16_t x = 320;
int_fast16_t w = 18;

void loop(void) {
  static uint8_t flip = 0;
  unsigned long currentTime = millis();
  if (currentTime - lastFrameTime >= frameDelay) {
    lastFrameTime = currentTime;
    drawFrame(w);
    warrior.pushImage(0, 0, warriorWidth,  warriorHeight, knight);
    w++;
    if(rightleft){
      if(w>=18) w = 9;
    } else {
      if(w>=36) w = 27;
    }
  }

  for (int_fast16_t y = 0; y < lcd_height; y += sprite_height) {
    flip = flip ? 0 : 1;
    sprites[flip].fillScreen(TFT_BROWN);
    warrior.pushRotateZoom(&sprites[flip], x, (lcd_height/2) - y, 0, 1, 1, 0);
    sprites[flip].pushSprite(&lcd, 0, y);
  }
  lcd.display();

  if(rightleft){
    x--;
    if(x<0){
      w = 27;
      rightleft = false;
    }  
  } else {
    x++;
    if(x>320){
      w = 9;
      rightleft = true;
    }
  }
}

//int walk_up[9][4096];     //{0, 1, 2, 3, 4, 5, 6, 7, 8};
//int walk_left[9][4096];   //{9, 10, 11, 12, 13, 14, 15, 16, 17};
//int walk_down[9][4096];   //{18, 19, 20, 21, 22, 23, 24, 25, 26};
//int walk_right[9][4096];  //{27, 28, 29, 30, 31, 32, 33, 34, 35};