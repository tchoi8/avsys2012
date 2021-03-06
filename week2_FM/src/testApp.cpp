#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    stream.setup(this, 2, 0, 44100, 512, 4);
    soundBuffer = new float[512];
    
    
    carrierWave.setup(44100);
    carrierWave.setFrequency(800);
    carrierWave.setVolume(0.02);

    modulatorWave.setup(44100);
    modulatorWave.setFrequency(5.0);
    modulatorWave.setVolume(1.0);
    
    
    carrierMinFreq = 400;
    carrierMaxFreq = 1400;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
//     //carrierWave.setFrequency( max(1,mouseX) );  // don't want to give a negative frequency...

    modulatorWave.setFrequency( max(1,mouseY) );  // don't want to give a negative frequency...

}

//--------------------------------------------------------------
void testApp::draw(){

    
    ofFill();
    ofSetColor(255);
    ofRect(200,200,512, 200);
    
    ofNoFill();
    ofSetColor(0);
    ofBeginShape();
    for (int i = 0; i < 512; i++){
        ofVertex(200 + i, 300 + 100 * soundBuffer[i] * 10.0);
    }
    ofEndShape();
    
    
    ofDrawBitmapStringHighlight("frequency:  " + ofToString(carrierWave.frequency), ofPoint(200,50));
     ofDrawBitmapStringHighlight("modulatorWave:  " + ofToString(modulatorWave.frequency), ofPoint(200,100));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){

	for (int i = 0; i < bufferSize; i++){
        
        
        float freq = ofMap(modulatorWave.getSample(), -1,1, carrierMinFreq, carrierMaxFreq);
        carrierWave.setFrequency(freq);
        
        float sample = carrierWave.getSample();
        
        
        output[i*nChannels    ] = sample;
        output[i*nChannels + 1] = sample;
        
        soundBuffer[i] = sample;
	}
    
    
}
