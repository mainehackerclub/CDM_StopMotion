#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofVideoGrabber 		vidGrabber;
        unsigned char * 	videoCurrentBuffer;
        unsigned char *     videoOverlayBuffer;
        vector<ofTexture>   videoArray;
        ofTexture *			videoCurrent;
        ofTexture *			videoOverlay;
        
        int 				camWidth;
        int 				camHeight;
        int 				videoWidth;
        int 				videoHeight;
        int                 frameRate;
    
        bool                playback = false;
        int                 playFrame = 0;
};
