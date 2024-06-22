#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include "Liste.h" // Verwende die angepasste LinkedList-Klasse

#include "Player.h"
#include "Triangle.h"
#include "Block.h"
#include "Sunshine.h"

// Color definitions
#define BLACK       0x0000  // Schwarz
#define RED         0xF800  // Rot
#define BLUE        0x001F  // Blau
#define GREEN       0x07E0  // Grün
#define YELLOW      0xFFE0  // Gelb
#define MAGENTA     0xF81F  // Magenta
#define CYAN        0x07FF  // Cyan
#define WHITE       0xFFFF  // Weiß
#define ORANGE      0xFD20  // Orange
#define PURPLE      0x780F  // Lila
#define PINK        0xF81F  // Rosa
#define LIME        0x07E0  // Limette
#define BROWN       0xA145  // Braun
#define GREY        0x8410  // Grau
#define DARKGREY    0x4208  // Dunkelgrau
#define LIGHTGREY   0xC618  // Hellgrau
#define NAVY        0x000F  // Marineblau

// (y,x)
// (0,0) .  . . . . .  . . . . (159,0)
//   .                            .
//   .                            .
//   .                            .
// (0,127)                     (159,127)
extern TFT screen;  // TFT-Bildschirm als extern deklarieren

class Game {
public:
  int maxChunks = 6;
  int currentChunk = 0;
  int rounds = 1;
  LinkedList<GameObject*> gameObjects;
  LinkedList<GameObject*> chunks[6];
  Player* player;
  Triangle* tri;
  Block* block;
  Sunshine* sun;


  Game(TFT &tft) : screen(tft) {}

  void addObject(GameObject* obj) {
    gameObjects.add(obj);
  }

  void setPlayer(Player* p) {
    player = p;
    addObject(p);
  }

  void setTriangle(Triangle* t) {
    tri = t;
    addObject(t);
  }

  void setBlock(Block* b) {
    block = b;
    addObject(b);
  }

  void setSun(Sunshine* s) {
    sun = s;
  }

 
  
  void updatePlayer(int speedX, int isJumping)
  {
    if (player == nullptr) return;
    player->fall();
    if(isJumping) player->jump();

      player->restoreBackground(screen);  // Hintergrund des Spielers wiederherstellen
      player->move(speedX);  // Spieler bewegen
      manageCollisions();
      if(player->y > 120 - player->height) die();
      if(player->x>=159 && currentChunk == maxChunks-1) 
      {
        screen.background(WHITE);
        currentChunk ++;
        win();
      }
      if(player->x>=159 && currentChunk < maxChunks-1) 
      {
        screen.background(WHITE);
        currentChunk ++;
        gameObjects=chunks[currentChunk];
        player->x=0;
        render();
        
      }
      if(player->x < 0 && currentChunk > 0)
      {
        player->x=158;
        screen.background(WHITE);
        currentChunk --;
        gameObjects=chunks[currentChunk];
        render();
      }
      
      player->update(gameObjects);  // Position des Spielers aktualisieren
      
      player->draw(screen);  // Spieler an der neuen Position zeichnen
    
  }

  void populateChunks() {
    chunks[0].add(new Block(0, 120, 160, 8, GREEN));     
    chunks[0].add(new Triangle(40, 110, 10, 10, BLACK));
    chunks[0].add(new Block(90,110,10,10,BLACK));
    chunks[0].add(new Block(100,100,20,20,BLACK));
    chunks[0].add(new Block(120,110,10,10,BLACK));

    chunks[1].add(new Block(0, 120, 160, 8, GREEN));    
    chunks[1].add(new Block(0, 80, 115, 10, BLACK));
    chunks[1].add(new Block(130, 105, 40, 15, BROWN));       
    chunks[1].add(new Block(45, 40, 80, 10, GREY));
    chunks[1].add(new Block(140, 40, 40, 10, GREY));
    chunks[1].add(new Block(0, 55, 15, 10, BROWN));

    chunks[2].add(new Block(0, 105, 30, 15, BROWN));
    chunks[2].add(new Block(0, 40, 50, 10, GREY));
    chunks[2].add(new Block(50, 40, 10, 80, GREY));
    chunks[2].add(new Block(90, 80, 30, 10, GREY));
    chunks[2].add(new Block(140, 80, 20, 10, GREY));

    
    chunks[3].add(new Block(0, 80, 20, 10, GREY));
    chunks[3].add(new Block(40, 70, 10, 10, GREY));
    chunks[3].add(new Block(85, 60, 10, 10, GREY));
    chunks[3].add(new Block(135, 50, 10, 10, GREY));
    
    chunks[4].add(new Block(0, 120, 30, 8, GREEN)); 
    chunks[4].add(new Block(50, 120, 25, 8, GREEN)); 
    chunks[4].add(new Block(120, 110, 40, 8, GREEN));

    chunks[5].add(new Block(0, 110, 20, 8, GREEN)); 
    chunks[5].add(new Block(40, 90, 10, 10, PURPLE)); 
    chunks[5].add(new Block(70, 70, 10, 10, PURPLE)); 
    chunks[5].add(new Block(90, 50, 10, 10, PURPLE)); 
    chunks[5].add(new Block(150, 30, 10, 10, PURPLE)); 
    chunks[5].add(new Block(60, 110, 20, 10, PURPLE)); 
    chunks[5].add(new Block(100, 110, 10, 10, PURPLE));
    chunks[5].add(new Block(130, 80, 10, 10, PURPLE));
    chunks[5].add(new Block(150, 100, 10, 10, PURPLE)); 
}

  void render() {
    sun->draw(screen);
    Node<GameObject*>* current = gameObjects.getFirst(); // Erhalte einen Zeiger auf das erste Element der Liste
    while (current != nullptr) {
      current->data->draw(screen); // Zeichne das aktuelle Element
      current = gameObjects.getNext(); // Gehe zum nächsten Element
    }
  }

  void manageCollisions()
  {
    Node<GameObject*>* currentNode = gameObjects.getFirst();

    while(currentNode!=nullptr){
      GameObject* obj = currentNode->data;
      if (player->isOverlapLeft(*obj) && player->speedX > 0) {
          // Die neue Position überlappt mit einem anderen GameObject, also breche die Bewegung ab
        player->speedX= 0;
        player->x= obj->x - player->width;
      }
      if (player->isOverlapBottom(*obj) && player->speedY > 0) {
          // Die neue Position überlappt mit einem anderen GameObject, also breche die Bewegung ab
        player->speedY= 0;
        player->y= obj->y - player->height;
        player->canJump=true;
      }
      if (player->isOverlapTop(*obj) && player->speedY < 0) {
          // Die neue Position überlappt mit einem anderen GameObject, also breche die Bewegung ab
        player->speedY= 0;
        player->y= obj->y + player->height;
      }
      if (player->isOverlapRight(*obj) && player->speedX < 0) {
          // Die neue Position überlappt mit einem anderen GameObject, also breche die Bewegung ab
        player->speedX= 0;
        player->x= obj->x + obj->width;
      }
      currentNode = gameObjects.getNext();
    }
  }

void die() {
    screen.fillScreen(WHITE);  // Bildschirm mit weißer Farbe füllen
    screen.setTextColor(BLACK);  // Textfarbe auf Schwarz setzen
    screen.setTextSize(2);  // Textgröße setzen
    screen.setCursor(30, 60);  // Textcursor positionieren
    screen.println("Game Over");  // "Game Over" Nachricht schreiben
    delay(3000);  // 5 Sekunden warten

    char buffer[48];

    if(rounds==9) {
      rounds=1;
      screen.fillScreen(WHITE);  // Bildschirm mit weißer Farbe füllen
      screen.setTextSize(2);
      screen.setCursor(40, 60);  // Textcursor positionieren
      screen.println("You lost");  // "Game Over" Nachricht schreiben
      
    }
    else {
      rounds++;
      sprintf(buffer,"Round %d",rounds);
      screen.fillScreen(WHITE);  // Bildschirm mit weißer Farbe füllen
      screen.setCursor(40, 60);  // Textcursor positionieren
      screen.println(buffer);  // "Game Over" Nachricht schreiben

    }

      
    delay(3000);

    // Spiel zurücksetzen
    screen.fillScreen(WHITE);  // Bildschirm mit weißer Farbe füllen
    currentChunk = 0;
    gameObjects = chunks[currentChunk];
    player->y = 100;
    player->x = 10;

}

void win() {
    screen.fillScreen(WHITE);
    screen.setTextColor(BLACK);
    screen.setTextSize(2);  // Textgröße setzen
    screen.setCursor(40, 60);  // Textcursor positionieren
    screen.println("You won"); 

    delay(3000);

    char buffer2[48];
    
    if(rounds==1) sprintf(buffer2,"%d round",rounds);
    else sprintf(buffer2,"%d rounds",rounds);

    screen.fillScreen(WHITE);
    screen.setCursor(40, 50);
    screen.println("Won in");
    screen.setCursor(30, 80);  // Textcursor positionieren
    screen.println(buffer2);
    
    delay(3000);

    screen.fillScreen(WHITE);  // Bildschirm mit weißer Farbe füllen
    currentChunk = 0;
    gameObjects = chunks[currentChunk];
    player->y = 100;
    player->x = 10;
    rounds = 1;
    screen.setCursor(40, 60);  // Textcursor positionieren
    screen.println("Round 1");  
    screen.fillScreen(WHITE);

}

private:
  TFT &screen; // Referenz auf den TFT-Bildschirm
};

#endif // GAME_H
