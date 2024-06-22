#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
  int speedX;  // Geschwindigkeit in der X-Richtung
  int speedY = 0;
  int previousX, previousY;  // vorherige Position
  bool canJump = true;

  Player(int x, int y, int width, int height, uint16_t color)
    : GameObject(x, y, width, height, color), speedX(0), previousX(x), previousY(y) {}

  void move(int speed) {
    speedX = speed;
  }

  void fall()
  {
    speedY +=3;
    if(speedY > 2) speedY = 6;
  }

  void jump()
  {
    if(canJump) speedY = -12;
    canJump = false;
  }

  void update(LinkedList<GameObject*>& gameObjects) {
    Serial.print("x: ");
    Serial.println(x);
    Serial.print("y: ");
    Serial.println(y);
    previousX = x;
    previousY = y;
    x += speedX;
    y += speedY;
    if(x<-1) x=-1;
    if(y<-1 ) y= -1;
    if(y> 128 - height ) y= 128- height;
  }

  void setBack()
  {
    x = previousX;
    y = previousY;
  }

  void restoreBackground(TFT &screen) {
    screen.fillRect(x, y, width, height, 0xFFFF);  // Annahme: Hintergrund ist schwarz
  }

  void draw(TFT &screen) override {
    screen.fillRect(x, y, width, height, color);
  }

  bool isOverlap(GameObject& other) {
  if(x+width <=other.x && x>=other.x+other.width && y+height <= other.y && y>other.y+other.height){
    return true;
  }
    else return false;
  }

bool isOverlapLeft(GameObject& other) {
    return (x + width >= other.x && previousX + width <= other.x &&
            y < other.y + other.height && y + height > other.y);
}

bool isOverlapTop(GameObject& other) {
    return (y <= other.y + other.height && previousY >= other.y + other.height &&
            x < other.x + other.width && x + width > other.x);
}

bool isOverlapRight(GameObject& other) {
    return (x <= other.x + other.width && previousX >= other.x + other.width &&
            y < other.y + other.height && y + height > other.y);
}

bool isOverlapBottom(GameObject& other) {
    return (y + height >= other.y && previousY + height <= other.y &&
            x < other.x + other.width && x + width > other.x);
}
};

#endif // PLAYER_H
