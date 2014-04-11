//
//  snake.cpp
//  emptyExample
//
//  Created by lampros on 4/9/14.
//
//

#include "snake.h"
#include "food.h"



// constructor
snake::snake(){
    snakeLength = 1;
    size = 40;
    direction = 2;
    
    
    xPos.insert(xPos.begin(), rand() % (ofGetWindowWidth()*2) +size);
    yPos.insert(yPos.begin(), rand() % ( (int) -size/2 + ofGetWindowHeight()) + size/2);
    eatSound.loadSound("eat.wav");
    badSound.loadSound("bad.wav");
}


void snake::move(){
    
    // Every element of the snake takes the position of its
    // predecessor
    for(int i = snakeLength - 1; i > 0; i-- ){
        xPos[i]= xPos[i - 1];
        yPos[i]=yPos[i - 1];
    }
    
    // Head of the snake
    switch(direction){
        case 1:  // Turn Left
            xPos[0] = xPos[0] - size;
            break;
            
        case 2:  // Turn Right
            xPos[0] = xPos[0] + size;
            break;
            
        case 3: // Go Up
            yPos[0] = yPos[0] - size;
            break;
            
        case 4: // Go Down
            yPos[0] = yPos[0] + size;
            break;
            
    }
    
    // When passes the out from the window appear on the other side of it
    xPos[0]=((int) xPos[0] + (ofGetWindowWidth()*2)) % (ofGetWindowWidth()*2);
    yPos[0] = ((int) yPos[0]+ ofGetWindowHeight() )%ofGetWindowHeight();
    
    // Check if it bite itself
    if( eatSelf())
        reset();
    
}


void snake::display(){
    // Display every rect of the snake
    for(int i = 0; i <snakeLength; i++){
        //fill(255, 0, 0,map(i - 1 , 0 , snakeLength-1, 255, 100));
        if (i != 0) {
          ofSetColor(snakeColor, 150);
        }else
            ofSetColor(snakeColor);
        ofFill();
        ofRectRounded(xPos[i],yPos[i], size, size, 10);
    }
}


void snake::grow(){
    // Add a new rect at the tail of the snake
    xPos.push_back( snakeLength-1 + size);
    yPos.push_back( snakeLength-1 + size);
    snakeLength++;
}

bool snake::eatSelf(){
    
    // Check if it ate itself
    for(int i = 1; i < snakeLength; i++){
        if( ofDist(xPos[0], yPos[0], xPos[i], yPos[i]) < size){
            return true;
            badSound.play();
        }
    }
    
    return false;
}

void snake::reset(){
    
    float x = xPos[0];
    float y = yPos[0];
    snakeLength=1;
    xPos.clear();
    yPos.clear();
    xPos.insert(xPos.begin(),x);
    yPos.insert(yPos.begin(),y);
    score=0;
    
}

void snake::eat(Food &myFood ){

    if( ofDist(myFood.xPos + myFood.size/2, myFood.yPos + myFood.size/2, xPos[0]+size/2, yPos[0]+size/2) < myFood.size/2 + size/2){
        myFood.reset();
        grow();
        eatSound.play();
        score++;
        if(score>highScore)
            highScore=score;
        
    }
}

string snake::snakeDataToString(snake &mySnake, Food &myFood){
    
    
    ostringstream oss("");
    
    oss << myFood.xPos;
    oss << ",";
    oss << myFood.yPos;
    oss << "%";
    
    
    for (int temp = 0; temp < snakeLength; temp++){
        oss << xPos[temp];
        oss << "," ;
        oss << yPos[temp];
        if(temp != snakeLength -1)
            oss << ";" ;
        else
            oss << "%";
        
        
    }
    for (int temp = 0; temp < mySnake.snakeLength; temp++){
        oss << mySnake.xPos[temp];
        oss << "," ;
        oss << mySnake.yPos[temp];
        if(temp != mySnake.snakeLength -1)
            oss << ";" ;
        else
            oss << "\n";
        
        
    }
    
    
    
    return oss.str();
    
}

void snake::setColor(int red, int green, int blue){
    
    snakeColor.r = red;
    snakeColor.g=green;
    snakeColor.b = blue;
    
}

