#pragma once

#include "ofMain.h"
#include "snake.h"
#include "food.h"
#include "ofxSuddenMotion.h"
#include "ofxUDPManager.h"
#include "ofSoundPlayer.h"
#include "ofxSpeech.h"
#include "ofTrueTypeFont.h"



class essServer : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        int checkCannibalism(vector<snake> snakes);
    
        string clientIP     = "132.229.130.208";
        int port            = 11999;
        snake snake1, snake2;
        Food food;
        ofxSuddenMotion sms;
        ofxUDPManager UDPReceive;
        ofxUDPManager UDPSend;
        vector<snake> snakes;
        ofxSpeechSynthesizer    synthesizer;
        bool pause;
    
        ofTrueTypeFont myfont, myFontB;
};

