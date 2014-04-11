//
//  food.h
//  emptyExample
//
//  Created by lampros on 4/9/14.
//
//

#ifndef emptyExample_food_h
#define emptyExample_food_h
#include "ofMain.h"
#include "ofGraphics.h"


class Food{
public:
    float xPos, yPos;
    float size;
    
    
public:
    //constructor
    
    Food();
    
    // Display
    void display();
    
    void reset();
};



#endif
