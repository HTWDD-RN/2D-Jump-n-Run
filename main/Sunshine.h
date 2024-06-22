#ifndef SUNSHINE_H
#define SUNSHINE_H

//eine glückliche Welt braucht Sonnenlicht :)

#define YELLOW 0x07FF

#include "GameObject.h"

class Sunshine : public GameObject {
public:
  Sunshine(int x, int y, int width)
    : GameObject(x, y, width, 0, YELLOW) {}

  void draw(TFT &screen) override {
    screen.fillCircle(x, y, width, YELLOW);

  }
};



#endif //SUNSHINE_H