/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

// include TFT and SPI libraries
#include <TFT.h>
#include <SPI.h>

#include "Game.h"
#include "GameObject.h"
#include "Block.h"
#include "Player.h"
#include "Sunshine.h"

// pin definition for Arduino UNO
#define cs 10
#define dc 9
#define rst 8

const int SW_pin = 2;  // Taster-Pin
const int X_pin = A0;  // X-Ausgang
const int Y_pin = A1;  // Y-Ausgang

#define SENSITIVITY_STEPS 128
#define MAX_SPEED 5  
#define TRESHOLD 64

// Color definitions
#define BLACK 0x0000
#define RED 0x001F
#define BLUE 0xF800
#define GREEN 0x07E0
#define YELLOW 0x07FF
#define MAGENTA 0xF81F
#define CYAN 0xFFFC
#define WHITE 0xFFFF


// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);
Game game(TFTscreen);
Player* player;

Sunshine* sun;

Triangle* tri;
Block* block0;
Block* block1;
Block* block2;


void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  //initialize the library
  TFTscreen.begin();

  TFTscreen.fillScreen(WHITE);  // Bildschirm mit weißer Farbe füllen
  TFTscreen.setTextColor(BLACK);  // Textfarbe auf Schwarz setzen
  TFTscreen.setTextSize(2);  // Textgröße setzen
  TFTscreen.setCursor(40, 60);  // Textcursor positionieren
  TFTscreen.println("Round 1");  // "Game Over" Nachricht schreiben

  delay(3000);
  TFTscreen.fillScreen(WHITE);

  sun = new Sunshine(20, 20, 10);
  game.setSun(sun);

  player = new Player(10, 100, 10, 15, MAGENTA);
  game.setPlayer(player);
  game.populateChunks();
  int current =0;

  game.currentChunk=current;
  game.gameObjects=game.chunks[current];

  TFTscreen.fillScreen(WHITE);
}

void loop() {
  int speedX = calculateSpeedX();
  Serial.print("Speed: ");
  Serial.println(speedX);

  int isJumping = checkJumping();
  Serial.print("Jump: ");
  Serial.println(isJumping);

  game.updatePlayer(-speedX, isJumping);
  game.render();

  delay(50);  // Kleiner Delay, um das Flackern zu reduzieren
}

int calculateSpeedX() {
  int joystickX = analogRead(X_pin);
  if (joystickX < 512 + TRESHOLD && joystickX > 512 - TRESHOLD) return 0;
  int speed = map(joystickX, 0, 1023, -MAX_SPEED, MAX_SPEED);
  return speed;
}

int checkJumping() {
  int joystickY = analogRead(Y_pin);
  if (joystickY < 512 + TRESHOLD) return 0;
  return 1;
}

