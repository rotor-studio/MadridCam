//
//  xml.cpp
//  MadridCam
//
//  Created by LOL on 27/03/2020.
///Users/lol/Documents/OF/of_v0.10.1_osx_release/examples/input_output/xmlExample/src/ofApp.h

#include "xml.hpp"


//--------------------------------------------------------------
void xml::read(){
    
    if(!settings.load("settings/settings.xml")){
        ofLogError() << "Couldn't load file";
    }
    
    settings.setTo("settings");
    if(settings.exists("urlCam")) {
        urlCameras = settings.getValue("urlCam");
        
        ofLog()<<"Set urlCameras to: "+urlCameras;
    }
    if(settings.exists("ext")) {
        ext = settings.getValue("ext");
    }
       
    ofLog()<<"Set extension to: "+ext;
        
    if(settings.exists("timeToCapture")) {
        timer = settings.getValue("timeToCapture", 0);
    }
        ofLog()<<"Set time limit to: "+ofToString(timer);
    
    if(settings.exists("columns")) {
        columns = settings.getValue("columns", 0);
    }
    ofLog()<<"Set columns to: "+ofToString(columns);
    settings.setToParent();
    
   settings.setTo("cameras");
   if(settings.exists("camId")) {
       totalCameras=settings.getNumChildren("camId");
    for(int i=0;i<totalCameras;i++){
        
         cameras[i] = settings.getValue("camId["+ofToString(i)+"]");
         ofLog()<<"Camera ID: "+cameras[i];
     }
    }
    ofLog()<<"Get total size of cameras: "+ofToString(totalCameras);
    settings.setToParent();
    

    
}
