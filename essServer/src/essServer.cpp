#include "essServer.h"

#define SMS_THRES 6

//--------------------------------------------------------------
void essServer::setup(){
    ofSetFrameRate(15);
    ofSetFullscreen(true);
    ofBackground(0, 0, 0);
    
    
    sms.setVerbose(true);
	sms.setupHardware();
	sms.setValueMode(OFX_SM_SCALED);
	sms.setSmoothPct(0.90);
    
    
    UDPSend.Create();
    UDPSend.Connect(clientIP.c_str(),port);
    UDPSend.SetNonBlocking(true);
    
    UDPReceive.Create();
    UDPReceive.Bind(port);
    UDPReceive.SetNonBlocking(true);

    snake1.setColor(255,0,0);
    snake2.setColor(0, 225, 0);
    
    snakes.insert(snakes.begin(), snake1);
    snakes.push_back(snake2);
    pause = true;
    
    synthesizer.listVoices();
    synthesizer.initSynthesizer("Zarvox");
    synthesizer.speakPhrase("Welcome to Extended Space Snakes by \n Sam Verkoelen \n and \n George Lampropoulos!\n Press enter to begin");
    myfont.loadFont("Planetx.ttf", 48);
    myFontB.loadFont("alphbeta.ttf", 32);
}

//--------------------------------------------------------------
void essServer::update(){
    if(!pause){
        snake1.eat(food);
        snake1.move();
        snake2.eat(food);
        snake2.move();
    
        vector<snake> tempSnakes;
        tempSnakes.insert(tempSnakes.begin(), snake1);
        tempSnakes.push_back(snake2);
        int lecter = checkCannibalism(tempSnakes);
        if(lecter >= 0)
            switch (lecter) {
                case 0:
                    snake1.reset();
                    snake1.badSound.play();
                    break;
                case 1:
                    snake2.reset();
                    snake2.badSound.play();
                    break;
                default:
                    break;
            }
        sms.readMotion();
        ofPoint smoothed = sms.getSmoothedXYZ();
        
        float h = smoothed.x/smoothed.y;
        float angle = atan(h);
    
        if (abs(smoothed.x)>abs(smoothed.y) ){
            if (smoothed.x <-SMS_THRES){
                if (snake1.direction != 2) {
                    snake1.direction = 1;
                }
            }else if(smoothed.x > SMS_THRES){
                    if (snake1.direction != 1) {
                        snake1.direction = 2;
                    }
            }
        }else{
            if (smoothed.y > SMS_THRES) {
                if (snake1.direction != 4) {
                    snake1.direction = 3;
                }
            }else if (smoothed.y < -SMS_THRES){
                if (snake1.direction != 3) {
                    snake1.direction = 4;
                }
            }
        }

        string dataToSend = snake1.snakeDataToString(snake2, food) ;
        UDPSend.Send(dataToSend.c_str(),1000);
        char udpMessage[4];
        UDPReceive.Receive(udpMessage, 4);
        string message = udpMessage;
        if(ofToInt(message)==1||ofToInt(message)==2||ofToInt(message)==3||ofToInt(message)==4)
            switch(ofToInt(message)){
                case 1:
                    if(snake2.direction!= 2)
                        snake2.direction = 1;
                    break;
                case 2:
                    if(snake2.direction!= 1)
                        snake2.direction = 2;
                    break;
                case 3:
                    if(snake2.direction!= 4)
                        snake2.direction = 3;
                    break;
                case 4:
                    if(snake2.direction!= 3)
                        snake2.direction = 4;
                    break;
            }
    
        //Check if winner
        if(snake1.snakeLength == 10){
            synthesizer.speakPhrase("Red Player Wins");
            snake1.reset();
            snake2.reset();
        }else if(snake2.snakeLength==10){
            synthesizer.speakPhrase("Green Player Wins");
            snake1.reset();
            snake2.reset();
        }
    }
}

//--------------------------------------------------------------
void essServer::draw(){
    ofSetHexColor(0x7dff23);
    myfont.drawString("Extended Space Snakes", 200,150);
    myFontB.drawString("By Sam and George", 450,300);
    if(!pause){
    ofBackground(0, 0, 0);
    
    food.display();
    snake1.display();
    snake2.display();
    }
}

//--------------------------------------------------------------
void essServer::keyPressed(int key){
    
    if (key == OF_KEY_LEFT){
        if(snake1.direction != 2){
            snake1.direction = 1;
        }
    }
    if (key == OF_KEY_RIGHT){
        if (snake1.direction != 1) {
            
            snake1.direction = 2;
        }
    }
    if (key == OF_KEY_UP){
        if (snake1.direction != 4) {
            
            snake1.direction = 3;
        }
    }
    if (key == OF_KEY_DOWN){
        if (snake1.direction != 3) {
            
            snake1.direction = 4;
        }
    }
    
    if (key == ' '){
        snake1.grow();
    }

    if (key == 'p'){
        snake2.grow();
    }

    if(key == OF_KEY_RETURN){
        if (!pause) {
            pause = true;
        }else
            pause = false;
        
    }

}
//--------------------------------------------------------------
void essServer::keyReleased(int key){

}

//--------------------------------------------------------------
void essServer::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void essServer::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void essServer::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void essServer::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void essServer::windowResized(int w, int h){

}

//--------------------------------------------------------------
void essServer::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void essServer::dragEvent(ofDragInfo dragInfo){

}


//--------------------------------------------------------------
int essServer::checkCannibalism(vector <snake> snakes ){
    int ret = -1;
    for(int i = 0 ; i< snakes.size(); i++ ){
       
        for ( int j = 0; j< snakes.size(); j++){
           if(j != i){
               
               for (int k=0 ; k < snakes[j].xPos.size(); k++) {
                   float x1 = snakes[i].xPos[0] + snakes[i].size/2;
                   float y1 = snakes[i].yPos[0] + snakes[i].size/2;
                   float x2 = snakes[j].xPos[k] + snakes[j].size/2;
                   float y2 = snakes[j].yPos[k] + snakes[j].size/2;
                   
                   if(ofDist(x1, y1, x2, y2) < snakes[i].size){
                        if(k==0){
                            snake1.reset();
                            snake2.reset();
                            snake1.badSound.play();
                            return -1;
                        }
                        ret = i;

                    }
                }
            }
        }
    }
    return ret;
}

    
