//
//  food.cpp
//  emptyExample
//
//  Created by lampros on 4/9/14.
//
//

#include "food.h"


Food::Food(){
    size=80;
    xPos = rand()%((ofGetWindowWidth()*2) - (int) size ) + size/2;//rand(size/2, width - size/2);
    yPos = rand()%(ofGetWindowHeight() - (int) size) + size+2;//rand(scoreHeight + size/2, height - size/2);
    
}

// Display
void Food::display(){
    ofSetColor(255, 255, 255);
    ofFill();
    ofRectRounded(xPos, yPos, size, size, 5);
}


void Food::reset(){
    
    // rand()%(max - min) +min
    xPos = rand()%((ofGetWindowWidth()*2) - (int) size ) + size/2;//rand(size/2, width - size/2);
    yPos = rand()%(ofGetWindowHeight() - (int) size);//rand(scoreHeight + size/2, height - size/2);

}
