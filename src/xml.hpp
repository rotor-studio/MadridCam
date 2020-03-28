//
//  xml.hpp
//  MadridCam
//
//  Created by LOL on 27/03/2020.
//
#include "ofMain.h"
#define xml_hpp
#include "ofxXmlPoco.h"

class xml{

public:
    
    void read();
    
    ofxXmlPoco settings;
    
    string urlCameras;
    string ext;
    int totalCameras, columns;
    string cameras[200];
    float timer;
    
 
};
