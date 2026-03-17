#define LGFX_AUTODETECT
#include <LovyanGFX.hpp>
#include "walk.h"
#include "background.h"
#include "background2.h"

static LGFX lcd;
static LGFX_Sprite sprites[2];
static LGFX_Sprite warrior;
static LGFX_Sprite rightbutt;
static LGFX_Sprite block;
static LGFX_Sprite roadBlock;
static LGFX_Sprite planter;
static LGFX_Sprite barrel;
//======================================declarations=======================================
static uint32_t lcd_width ;
static uint32_t lcd_height;

static int_fast16_t sprite_height;

bool rightleft = true;
bool RIGHT = true;
bool LEFT  = false;
bool UP    = false;
bool DOWN  = false;
unsigned long lastFrameTime = 0;
const int frameDelay = 100;  // 100ms between frames
//=======================================methods=============================================
void checkCollision(){
  if(wY<0 + warriorHeight/3) {wY = 0 + warriorHeight/3;}
  if(wY>lcd_height - warriorHeight/2) {wY = lcd_height - warriorHeight/2;}
  if(wX<0 + warriorWidth/3){ wX = 0 + warriorWidth/3;}
  if(wX>lcd_width - warriorWidth/3) {wX = lcd_width - warriorWidth/3;}
}

void checkTouch(uint16_t tX, uint16_t tY){
  if(tX>290 && tX<320 && tY>160 && tY<190){ // right
    RIGHT = true;
    LEFT  = false;
    UP    = false;
    DOWN  = false;
    unsigned long currentTime = millis();
    if (currentTime - lastFrameTime >= frameDelay) {
      lastFrameTime = currentTime;
      if(w >= 35 || w <=27) w = 27;
      w++;
      drawFrame(w);
      warrior.pushImage(0, 0, warriorWidth,  warriorHeight, knight);
    }
    wX++;
  }
  if(tX>230 && tX<260 && tY>160 && tY<190){ // left
    RIGHT = false;
    LEFT  = true;
    UP    = false;
    DOWN  = false;
    unsigned long currentTime = millis();
    if (currentTime - lastFrameTime >= frameDelay) {
      lastFrameTime = currentTime;
      if(w >= 17 || w <=9) w = 9;
      w++;
      drawFrame(w);
    }
    wX--;
    warrior.pushImage(0, 0, warriorWidth,  warriorHeight, knight);
  }
  if(tX>260 && tX<290 && tY>130 && tY<160){ // up
    RIGHT = false;
    LEFT  = false;
    UP    = true;
    DOWN  = false;
    unsigned long currentTime = millis();
    if (currentTime - lastFrameTime >= frameDelay) {
      lastFrameTime = currentTime;
      if(w >= 8 || w <=0) w = 0;
      w++;
      drawFrame(w);
    }
    wY--;
    warrior.pushImage(0, 0, warriorWidth,  warriorHeight, knight);
  }
  if(tX>260 && tX<290 && tY>190 && tY<220){ // down
    RIGHT = false;
    LEFT  = false;
    UP    = false;
    DOWN  = true;
    unsigned long currentTime = millis();
    if (currentTime - lastFrameTime >= frameDelay) {
      lastFrameTime = currentTime;
      if(w >= 26 || w <=18) w = 18;
      w++;
      drawFrame(w);
    }
    wY++;
    warrior.pushImage(0, 0, warriorWidth,  warriorHeight, knight);
  }
}

//================================================== setup =============================
void setup(void) {
  Serial.begin(115200);
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

  rightbutt.createSprite(30, 30);
  rightbutt.drawTriangle(0, 0, 0, 30, 30, 15, TFT_SKYBLUE); // right

  block.createSprite(30, 30);
  block.drawRect(0, 0, 30, 30, TFT_ORANGE);

  roadBlock.createSprite(block2W, block2H);
  roadBlock.setSwapBytes(true);
  drawBlock2(1);
  roadBlock.pushImage(0, 0, block2W,  block2H, blocks2);

  planter.createSprite(block2W, blockH-4);
  planter.setSwapBytes(true);
  drawBlock2(4);
  planter.pushImage(0, 0, block2W,  blockH-4, blocks2);

  barrel.createSprite(block2W, block2H);
  barrel.setSwapBytes(true);
  drawBlock2(4);
  barrel.pushImage(0, 0, block2W,  block2H, blocks2);
  lcd.startWrite();

  wX = warriorWidth/3;
  wY = lcd_height/2 - 25;
}
//=======================================loop===============================================
void loop(void) {
  uint16_t tX, tY;
  bool touched = lcd.getTouch(&tX, &tY);
  if( touched ) {
    checkTouch(tX, tY);
  } else {
    if(RIGHT) drawFrame(27);
    if(LEFT) drawFrame(9);
    if(UP) drawFrame(0);
    if(DOWN) drawFrame(18);
    warrior.pushImage(0, 0, warriorWidth,  warriorHeight, knight);
  }

  static uint8_t flip = 0;
  for (int_fast16_t y = 0; y < lcd_height; y += sprite_height) {
    flip = flip ? 0 : 1;
    sprites[flip].fillScreen(TFT_BROWN); // background 
    rightbutt.pushRotateZoom(&sprites[flip], 300, 180 - y, 0, 1, 1, 0); // right butt
    rightbutt.pushRotateZoom(&sprites[flip], 240, 180 - y, 180, 1, 1, 0); // left butt
    rightbutt.pushRotateZoom(&sprites[flip], 270, 210 - y, 90, 1, 1, 0); // down butt
    rightbutt.pushRotateZoom(&sprites[flip], 270, 150 - y, 270, 1, 1, 0); // up butt

    planter.pushRotateZoom(&sprites[flip], 20, 200 - y, 0, 1, 1, 0); // planter q3
    barrel.pushRotateZoom(&sprites[flip], 200, 40 - y, 0, 1, 1, 0); // planter q1

    for(int b = 0; b <= 4; b++){
      roadBlock.pushRotateZoom(&sprites[flip], lcd_width/2, (block2H * b) - y, 0, 1, 1, 0); // x axis
    }
    for(int b = 0; b <= 6; b++){
      roadBlock.pushRotateZoom(&sprites[flip], block2H * b, lcd_height/2 - y, 90, 1, 1, 0); // y axis
    }

    warrior.pushRotateZoom(&sprites[flip], wX, wY - y, 0, 1, 1, 0); // warrior

    planter.pushRotateZoom(&sprites[flip], 20, 40 - y, 0, 1, 1, 0); // planter q2

    block.pushRotateZoom(&sprites[flip], lcd_width/2, lcd_height/2 - y, 0, 1, 1, 0); // collision block

    sprites[flip].pushSprite(&lcd, 0, y);
  }
  lcd.display();

  checkCollision();
}

