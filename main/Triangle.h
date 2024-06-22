#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GameObject.h"

class Triangle : public GameObject {
public:
  Triangle(int x, int y, int width, int height, uint16_t color)
    : GameObject(x, y, width, height, color) {}

  void draw(TFT &screen) override {
    int x0 = x, y0 = y;
    int x1 = x0+width/2, y1 = y0+height;
    int x2 = x0-width/2, y2 = y1;
    screen.fillTriangle(x0,y0,x1,y1,x2,y2,color);
  }
};

#endif // TRIANGLE_H