#include "essClient.h"

//--------------------------------------------------------------
void essClient::setup(){
    ofSetFrameRate(15);
    ofSetFullscreen(true);
	sms.setVerbose(true);
	sms.setupHardware();
	sms.setValueMode(OFX_SM_SCALED);
	sms.setSmoothPct(0.90);
	
	ofSetVerticalSync(true);
	ofSetCircleResolution(64);
    
    UDPSend.Create();
    UDPSend.Connect(clientIP.c_str(),port);
    UDPSend.SetNonBlocking(true);
    
    UDPReceive.Create();
    UDPReceive.Bind(port);
    UDPReceive.SetNonBlocking(true);
    
    

}

//--------------------------------------------------------------
void essClient::update(){
	sms.readMotion();
    
	ofPoint smoothed = sms.getSmoothedXYZ();
    
    
    float h = smoothed.x/smoothed.y;
    float angle = atan(h);
    
    if (smoothed.x < -sensitivity && abs(smoothed.x)>abs(smoothed.y) ){
        direction = 2;
        sendDirection();
    }
    if(smoothed.x > sensitivity && abs(smoothed.x)>abs(smoothed.y)){
        direction = 1;
        sendDirection();
    }
    if(smoothed.y > sensitivity && abs(smoothed.y)>abs(smoothed.x)){
        direction = 4;
        sendDirection();
    }
    if(smoothed.y < -sensitivity && abs(smoothed.y)>abs(smoothed.x)){
        direction = 3;
        sendDirection();
    }

}

//--------------------------------------------------------------
void essClient::drawSnakeBlock(int xPos, int yPos, int snake, int i){
    xPos = xPos - ofGetWindowWidth();
    if(snake == 1){
        if(i == 0){
            ofSetColor(255, 0, 0);
        }else{
            ofSetColor(255, 0, 0,150);
        }
    }else{
        if(i == 0){
            ofSetColor(0, 255, 0);
        }else{
            ofSetColor(0, 255, 0,150);
        }
    }
    ofFill();
    ofRectRounded(xPos,yPos, snakeBlockSize, snakeBlockSize, 10);
}

//--------------------------------------------------------------
void essClient::drawFood(int xPos, int yPos){
    xPos = xPos - ofGetWindowWidth();
    ofSetColor(255, 255, 255);
    ofFill();
    ofRectRounded(xPos, yPos, foodSize, foodSize, 5);
}

//--------------------------------------------------------------
void essClient::draw(){
    ofBackground(0, 0, 0);
    char udpMessage[1000];
    UDPReceive.Receive(udpMessage,1000);
    raw = udpMessage;

    vector<string> input = ofSplitString(raw, "%");
        
    if(input.size() > 2){
        for(int i = 0; i != input.size(); i++) {
            if(i == 0){
                string inputTemp = input[i];
                vector<string> food = ofSplitString(inputTemp, ",");
                string xTemp = food[0];
                string yTemp = food[1];
                int xPos = ofToInt(xTemp);
                int yPos = ofToInt(yTemp);
                drawFood(xPos, yPos);
            }else{
                string tempInput = input[i];
                vector<string> snakeBlock = ofSplitString(tempInput, ";");
                for(int ii = 0; ii != snakeBlock.size(); ii++) {
                    string tempSnakeBlock = snakeBlock[ii];
                    vector<string> block = ofSplitString(tempSnakeBlock, ",");
                    string xTemp = block[0];
                    string yTemp = block[1];
                    int xPos = ofToInt(xTemp);
                    int yPos = ofToInt(yTemp);
                    drawSnakeBlock(xPos, yPos, i, ii);
                }
            }
        }
    }
}

//--------------------------------------------------------------
void essClient::keyPressed(int key){
    
    if (key == OF_KEY_LEFT){
        direction = 1;
        sendDirection();
    }
    if (key == OF_KEY_RIGHT){
        direction = 2;
        sendDirection();
    }
    if (key == OF_KEY_UP){
        direction = 3;
        sendDirection();
    }
    if (key == OF_KEY_DOWN){
        direction = 4;
        sendDirection();
    }
}

void essClient::sendDirection(){
    string output = ofToString(direction);
    UDPSend.Send(output.c_str(), output.length());
}

//--------------------------------------------------------------
void essClient::keyReleased(int key){
}

//--------------------------------------------------------------
void essClient::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void essClient::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void essClient::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void essClient::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void essClient::windowResized(int w, int h){

}

//--------------------------------------------------------------
void essClient::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void essClient::dragEvent(ofDragInfo dragInfo){ 

}