#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "TFT.h"

class GameObject {
public:
  int x, y, width, height;
  uint16_t color;

  GameObject(int x, int y, int width, int height, uint16_t color)
    : x(x), y(y), width(width), height(height), color(color) {}

  virtual void draw(TFT &screen) = 0;  // Rein virtuelle Methode
  int getX() {return x;}
  int getY() {return y;}
  int getWidth() {return width;}
  int getHeigth() {return height;};

};

#endif // GAMEOBJECT_H
