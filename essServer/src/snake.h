//
//  snake.h
//  emptyExample
//
//  Created by lampros on 4/9/14.
//
//



#ifndef emptyExample_snake_h
#define emptyExample_snake_h

#include <vector>
#include "ofMain.h"
#include "ofGraphics.h"
#include "food.h"


class  Food;

class snake {
public:
    // Snake variables
    int snakeLength;
    float size;
    int direction;
    std::vector<float> xPos, yPos;
    int vel=10;
    int score = 0;
    int highScore = 0;
    ofColor snakeColor;
    ofSoundPlayer eatSound, badSound;
    
    
    snake();    // constructor
    void move();
    void display();
    void grow();
    bool eatSelf();
    void reset();
    void eat(Food &myFood);
    void setColor(int red, int green, int blue);
    string snakeDataToString(snake &mySnake, Food &myFood);
    void eatOther(snake mySnake);
    
};


#endif
