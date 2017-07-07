/***********************
 UDOO cabinet NeoMatrix LED Markee
 2017
 http://www.udoo.org
 Creative Common License
************************/

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif
#include "Definitions.h"
#include "Shape.h"

// Control PIN
#define PIN 9

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(48, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

// --------------------------------------------  
// Set the color of animation (see Definitions.h)
const uint16_t colors[] = { matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
// Set the brightness (max 50)
int brigh = 40;
// Delay between animation
int wait = 200;
// ---------------------------------------------

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(brigh);
  randomSeed(analogRead(0));
}

// Variable to print text
int x = matrix.width();
int pass = 0;

void loop() {
  // Set the color of text (see Definitions.h)
  //scrivi("le bragiuole", MAGENTA);
  // Text change color
  //scriviColor("Ciao");
  pacman();
  space();
  UDOOAnimation();
  battito();
  /*switch(random(0, 5)){
    case 0: 
    pacman();
    break;
    case 1: 
    space();
    break;
    case 2:
    UDOOAnimation();
    break;
    case 3:
    battito();
    break;
    default:
    scrivi("La droga!", GREEN);
    break;
  }*/
}

void sprite(const uint8_t* x, unsigned long y, int w){
  byte red = (y & 0xFF0000) >> 16;
  byte green = ( y & 0x00FF00) >> 8;
  byte blue = (y & 0x0000FF);  
  matrix.drawBitmap(0,0, x, 8, 8, matrix.Color(red, green, blue));
  matrix.show();
  delay(w);
  matrix.fillScreen(0);
}

void spriteWpos(const uint8_t* x, unsigned long y, int pos){
  byte red = (y & 0xFF0000) >> 16;
  byte green = ( y & 0x00FF00) >> 8;
  byte blue = (y & 0x0000FF);
  matrix.drawBitmap(pos, 0, x, 8, 8, matrix.Color(red, green, blue));
}

void spriteWHpos(const uint8_t* x, unsigned long y, int posX, int posY){
  byte red = (y & 0xFF0000) >> 16;
  byte green = ( y & 0x00FF00) >> 8;
  byte blue = (y & 0x0000FF);
  matrix.drawBitmap(posX, posY, x, 8, 8, matrix.Color(red, green, blue));
}

void showWaitAndClear(int w){
  matrix.show();
  delay(w);
  matrix.fillScreen(0);
}

void showWait(int w){
  matrix.show();
  delay(w);
}

void showClear(){
  matrix.fillScreen(0);
}


void scrivi(String z, unsigned long y) {
  int len = z.length();
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  byte red = (y & 0xFF0000) >> 16;
  byte green = ( y & 0x00FF00) >> 8;
  byte blue = (y & 0x0000FF);
  matrix.print(z);
  if(--x < -len*6) {
    x = matrix.width();
  }
  matrix.setTextColor(matrix.Color(red,green,blue));
  matrix.show();
  delay(100);
}

void scriviColor(String y) {
  int len = y.length();
  matrix.fillScreen(0);
  matrix.setCursor(x, 0); 
  matrix.print(y);
  //matrix.print(F("Scrivi"));
  if(--x < -len*6) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(100);
}

 // ---Animation---
 void heart() {
   sprite(cuore1,RED,wait);
   sprite(cuore1,PINK,wait);
   sprite(cuore1,BLUE,wait);
   sprite(cuore1,MAGENTA,wait);
 }

 void space(){
  int posX = 0;
  for (posX = -8; posX < 39; posX++) {
    switch(posX % 8) {
      case 0:
        spriteWpos(navicella1, RED, posX);
        break;
      case 1:
        spriteWpos(navicella2, RED, posX);
        break;
      case 2:
        spriteWpos(navicella3, RED, posX);
        break;
      case 3:
        spriteWpos(navicella4, RED, posX);
        break;
      case 4:
        spriteWpos(navicella5, RED, posX);
        break;
      default:
        spriteWpos(navicella1, RED, posX);
        break;
    }
    showWaitAndClear(50);
  }

  for (posX = 39; posX >=19; posX--){
     spriteWpos(navicella1, RED, posX);
     showWaitAndClear(50);
  }
  spriteWpos(navicella2, RED, posX);
  showWaitAndClear(50);
  spriteWpos(navicella3, RED, posX);
  showWaitAndClear(50);
  spriteWpos(navicella4, RED, posX);
  showWaitAndClear(50);

  int posY = 0;
  for (posY; posY < 4; posY++){
    spriteWHpos(navicella5, RED, posX, posY);
    showWaitAndClear(50);
  }

  spriteWHpos(navicella5, RED, posX, posY);
  matrix.show();

  long randNumber;
  for(int i = 0; i< 20; i++){
    randNumber = random(47);
    if(randNumber != 23){
      for(int starPos = 0; starPos <= 7; starPos++){
        matrix.drawPixel(int(randNumber), starPos, WHITE);
        spriteWHpos(navicella5, RED, posX, posY);
        matrix.show();
        delay(10);
        showClear();
      }
    }
  }
   
  int alienY =  -13;
  for (alienY; alienY < 0; alienY++) {
    spriteWHpos(navicella5, RED, posX, posY);
    spriteWHpos(alienoa1, BLUE, 3, alienY);
    spriteWHpos(alienob1, DARKORANGE, 19, alienY);
    spriteWHpos(alienoc1, VIOLET, 36, alienY);
    showWaitAndClear(60);
  }
  for (int count = 0; count < 10; count++){
    if (count % 2 ) {
      spriteWHpos(alienoa1, BLUE, 3, alienY);       
      //spriteWHpos(alienob1, DARKORANGE, 19, alienY);
      spriteWHpos(alienoboom, WHITE, 19, alienY);
      spriteWHpos(alienoc1, VIOLET, 36, alienY);
    } else {
      spriteWHpos(alienoa2, BLUE, 3, alienY);       
      //spriteWHpos(alienob2, DARKORANGE, 19, alienY);
      spriteWHpos(alienoboom1, WHITE, 19, alienY);
      spriteWHpos(alienoc2, VIOLET, 36 , alienY);
    }
    showWaitAndClear(150);
  } 
 }

void pacman() {
  pacmanR();
  pacmanL();
  pacmanExit();
}

void pacmanR(){
  for (int pos = - 30; pos < 56; pos++) {
    if (abs(pos) % 5) {
      if((abs(pos) % 5 ) == 4 || (abs(pos) % 5 ) == 1){
        spriteWpos(pacmanMezzo, YELLOW, pos + 20);
        spriteWpos(gost1, GOLD, pos + 9);
        spriteWpos(gost1, RED, pos);
      } else {
        spriteWpos(pacmanAperto, YELLOW, pos + 20);
        spriteWpos(gost2, GOLD, pos + 9);
        spriteWpos(gost2, RED, pos);
      }
    } else {
      spriteWpos(pacmanChiuso, YELLOW, pos + 20);
      spriteWpos(gost1, GOLD, pos + 9);
      spriteWpos(gost1, RED, pos);
    }
    showWaitAndClear(50);
  }
}

void pacmanL(){
  for (int pos = 54; pos > -30; pos--) {
    if (abs(pos) % 5) {
      if((abs(pos) % 5 ) == 4 || (abs(pos) % 5 ) == 1){
        spriteWpos(pacmanMezzoL, YELLOW, pos + 20);
        spriteWpos(gost1, DARKBLUE, pos + 9);
        spriteWpos(gost1, DARKBLUE, pos);
      } else {
        spriteWpos(pacmanApertoL, YELLOW, pos + 20);
        spriteWpos(gost2, DARKBLUE, pos + 9);
        spriteWpos(gost2, DARKBLUE, pos);
      }
    } else {
      spriteWpos(pacmanChiusoL, YELLOW, pos + 20);
      spriteWpos(gost1, DARKBLUE, pos + 9);
      spriteWpos(gost1, DARKBLUE, pos);
    }
    showWaitAndClear(50);
  }
}

void pacmanEyes(){
  for (int pos = - 15; pos < 45; pos++) {
    spriteWpos(gost3, WHITE, pos + 9);
    spriteWpos(gost3, WHITE, pos);
    showWaitAndClear(25);
  }
}

void pacmanExit(){
  for (int pos = - 30; pos < 20; pos++) {
    int color;
    if (abs(pos) % 4){
      color = WHITE;
    } else {
      color = DARKBLUE;
    }
    if (abs(pos) % 5) {
      if((abs(pos) % 5 ) == 4 || (abs(pos) % 5 ) == 1){
        spriteWpos(gost1, color, pos + 20);
        spriteWpos(gost1, color, pos + 9);
        spriteWpos(pacmanMezzo, YELLOW, pos);
      } else {
        spriteWpos(gost2, color, pos + 20);
        spriteWpos(gost2, color, pos + 9);
        spriteWpos(pacmanAperto, YELLOW, pos);
      }
    } else {
      spriteWpos(gost1, color, pos + 20);
      spriteWpos(gost1, color, pos + 9);
      spriteWpos(pacmanChiuso, YELLOW, pos);
    }
    showWaitAndClear(50);
  }
  for (int pos = 20; pos > -30; pos--) {
    if (abs(pos) % 5) {
      if((abs(pos) % 5 ) == 4 || (abs(pos) % 5 ) == 1){
        spriteWpos(gost1, RED, pos + 20);
        spriteWpos(gost1, GOLD, pos + 9);
        spriteWpos(pacmanMezzoL, YELLOW, pos);
      } else {
        spriteWpos(gost2, RED, pos + 20);
        spriteWpos(gost2, GOLD, pos + 9);
        spriteWpos(pacmanApertoL, YELLOW, pos);
      }
    } else {
      spriteWpos(gost1, RED, pos + 20);
      spriteWpos(gost1, GOLD, pos + 9);
      spriteWpos(pacmanChiusoL, YELLOW, pos);
    }
    showWaitAndClear(50  );
  }
}
 
void battito() {
   sprite(cuore1,RED,400);
   sprite(cuore2,RED,200);
   sprite(cuore3,RED,100);
   sprite(cuore2,RED,200);
   sprite(cuore1,RED,400);   
   sprite(cuore2,RED,200);
   sprite(cuore3,RED,100);
   sprite(cuore2,RED,200);
}

void UDOOAnimation(){
  for(int i = -30; i< 48; i++){
    spriteWpos(U,MAGENTA, 0 + i);
    spriteWpos(D,MAGENTA, 9 + i);
    spriteWpos(O,MAGENTA, 18 + i);
    spriteWpos(O,MAGENTA, 27 + i);
    
    showWaitAndClear(50);  
  }
  delay(500);  
  for(int i = 48; i >= 6 ; i --){
    spriteWpos(U,MAGENTA, i );
    showWaitAndClear(0);
  }
  delay(500);
  for(int i = 48; i >= 15; i --){
    spriteWpos(U,MAGENTA, 6);
    spriteWpos(D,MAGENTA, i);
    showWaitAndClear(0);
  }
  delay(500);
  for(int i = 48; i >= 24; i --){
    spriteWpos(U,MAGENTA, 6);
    spriteWpos(D,MAGENTA, 15);
    spriteWpos(O,MAGENTA, i);
    showWaitAndClear(0);
  }
  delay(500);
  for(int i = 48; i >= 33; i --){
    spriteWpos(U,MAGENTA, 6);
    spriteWpos(D,MAGENTA, 15);
    spriteWpos(O,MAGENTA, 24);
    spriteWpos(O,MAGENTA, i);
    showWaitAndClear(0);
  }
  delay(500);
  for(int i = 0; i< 39; i++){
    spriteWpos(U,MAGENTA, 6 + i);
    spriteWpos(D,MAGENTA, 15 + i);
    spriteWpos(O,MAGENTA, 24 + i);
    spriteWpos(O,MAGENTA, 33 + i);
    
    showWaitAndClear(50);  
  }

  for(int count = 0; count <= 2; count ++){
    for(int i = -30; i< 48; i++){
      spriteWpos(U,MAGENTA, 0 + i);
      spriteWpos(D,MAGENTA, 9 + i);
      spriteWpos(O,MAGENTA, 18 + i);
      spriteWpos(O,MAGENTA, 27 + i);
      
      showWaitAndClear(50);  
    }
  }
}

void UDOO(){
    spriteWpos(U,MAGENTA, 0);
    spriteWpos(D,MAGENTA, 9);
    spriteWpos(O,MAGENTA, 18);
    spriteWpos(O,MAGENTA, 27);
    showWaitAndClear(50);
}
