#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"

class Block : public GameObject {
public:
  Block(int x, int y, int width, int height, uint16_t color)
    : GameObject(x, y, width, height, color) {}

  void draw(TFT &screen) override {
    screen.fillRect(x,y,width,height,color);
  }
  
};

#endif // BLOCK_H
