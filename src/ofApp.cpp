#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth 		= 320;	// try to grab at this size.
	camHeight 		= 240;
    videoWidth = 800;
    videoHeight = (int)videoWidth*((float)camHeight/camWidth);
	
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
	vidGrabber.setDeviceID(1);
	vidGrabber.setDesiredFrameRate(10);
	vidGrabber.initGrabber(camWidth,camHeight);
	
    videoArray.reserve(10);
    videoCurrentBuffer 	= new unsigned char[camWidth*camHeight*4];
    videoOverlayBuffer  = new unsigned char[camWidth*camHeight*4];
	videoCurrent = new ofTexture();
    videoCurrent->allocate(camWidth,camHeight, GL_RGBA);
    videoOverlay = new ofTexture();
    videoOverlay->allocate(camWidth,camHeight, GL_RGBA);
	ofSetVerticalSync(true);
    ofSetFrameRate(10);
    //ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(255,255,255);
	
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    
    int newWidth  = ofGetWidth()/10;
    int newHeight = (int)(ofGetWidth()/10)*((float)camHeight/camWidth);
    //Print Images
    for(int i = 0; i < 10; i++) {
        if(i >= videoArray.size()) {
            break;
        }
        videoArray[i].draw(i*ofGetWidth()/10,ofGetHeight()-(newHeight+20),newWidth,newHeight);
    }
    
    if(playback && videoArray.size()>0) {
        videoArray[playFrame].draw((ofGetWidth()-videoWidth)/2,20,videoWidth,videoHeight);
        ofSetHexColor(0xff0000);
        ofSetHexColor(0xff0000);
        ofNoFill();
        ofSetLineWidth(4.0);
        ofRect(playFrame*ofGetWidth()/10,ofGetHeight()-(newHeight+20),newWidth,newHeight);
        ofFill();
        ++playFrame %= videoArray.size() ;
    } else {
        vidGrabber.draw((ofGetWidth()-videoWidth)/2,20,videoWidth,videoHeight);
        if(videoArray.size()>0)
            videoOverlay->draw((ofGetWidth()-videoWidth)/2,20,videoWidth,videoHeight);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c' || key == 'C'){
        if(videoArray.size() >= 10){
            videoArray.erase(videoArray.begin());
        }
        
        int totalPixels = camWidth*camHeight*4;
        delete[] videoCurrentBuffer;
        delete[] videoOverlayBuffer;
        videoCurrentBuffer = new unsigned char[totalPixels];
        videoOverlayBuffer = new unsigned char[totalPixels];
        
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i++){
            if(i%4 == 3) {
                videoOverlayBuffer[i] = 0x80;
                videoCurrentBuffer[i] = 0xFF;
            }
            else {
                videoCurrentBuffer[i] = pixels[i-(i/4)];
                videoOverlayBuffer[i] = pixels[i-(i/4)];
            }
		}
        
        delete videoOverlay;
        videoOverlay = new ofTexture();
        videoOverlay->allocate(camWidth,camHeight, GL_RGBA);
        videoOverlay->loadData(videoOverlayBuffer, camWidth, camHeight, GL_RGBA);
        
        delete videoCurrent;
        videoCurrent = new ofTexture();
        videoCurrent->allocate(camWidth,camHeight, GL_RGBA);
        videoCurrent->loadData(videoCurrentBuffer, camWidth, camHeight, GL_RGBA);
        
		videoArray.push_back(*videoCurrent);
	} else if (key == ' ') {
        playback = !playback;
        playFrame = 0;
    } else if (key == 'x' || key == 'X') {
        if(videoArray.size()>0) {
            ofImage  img2Export;
            ofPixels pix2Export;
            for(int i = 0; i < videoArray.size(); i ++) {
                videoArray[i].readToPixels(pix2Export);
                img2Export.setFromPixels(pix2Export);
                char exportFile[100];
                
                sprintf(exportFile,"/Users/agross/Documents/stopmotion/export/image-%03d.png",i);
                
                img2Export.saveImage(exportFile);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
