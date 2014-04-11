#pragma once

#include "ofMain.h"
#include "ofxSuddenMotion.h"
#include "ofxTCPClient.h"
#include "ofxUDPManager.h"
#include <string>

class essClient : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void drawFood(int xPos, int yPos);
        void drawSnakeBlock(int xPos, int yPos, int snake, int i);
        void sendDirection();

        ofxSuddenMotion sms;
        ofxUDPManager UDPSend;
        ofxUDPManager UDPReceive;

        string clientIP     = "132.229.130.208";
        int port            = 11999;

        int sensitivity     = 6;
        int foodSize        = 80;
        int snakeBlockSize  = 40;
        int direction       = 1;
        string raw;
};
