#pragma once

#include "ofMain.h"
#include "ofURLFileLoader.h"
#include "xml.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
        void urlResponse(ofHttpResponse & response);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    float timeRaw, timeLimit ,triggerTime[200];
    int totalCams,count[200], xPos,yPos,desplazaX, desplazaY, extremo;
    
       ofImage img[200];
       string cameras[200];
       bool loading;
       bool drawCams;
       bool GUI;
       bool full;
       bool web;
    
    xml settings;
    string initPath;
    
		
};
