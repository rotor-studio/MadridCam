#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Resolution and app size, etc...
    ofSetWindowShape(1920,1080);
    ofSetWindowTitle("SIMPLE PUBLIC CAMS TOOL V.01");
    ofBackground(0, 0, 0);
    
    ofRegisterURLNotification(this);
    
    //Read settings
    settings.read();
    
    //Some variables
    timeRaw=0;
    timeLimit=settings.timer;
    totalCams=settings.totalCameras;
    
    xPos=0;
    yPos=0;
    desplazaX=0;
    desplazaY=0;
    extremo= settings.columns;
    
    //Load all images from url
     for(int i=0;i<totalCams;i++){
    //to load synchronously
         cameras[i]=settings.urlCameras+settings.cameras[i]+settings.ext;
    ofLog()<<cameras[i];
    img[i].load(cameras[i]);
    triggerTime[i]=0;
    }
    
    //Gui & fullscreen
    GUI=true;
    full=false;
    
    initPath = ofToString(ofGetDay())+"_"+ofToString(ofGetMonth())+"_"+ofToString(ofGetYear());
    ofDirectory dir(initPath);
    if(!dir.exists()){
        dir.create(true);
    }
    
     web = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //WindowFull
    ofSetFullscreen(full);
    
    //GetTime
    timeRaw= ofGetElapsedTimef();
  
   for(int i=0;i<totalCams;i++){
       
    //Calculate minutes.
    if(timeRaw > 30.0f){
        triggerTime[i]++;
        ofResetElapsedTimeCounter();
    }
    //Request photo
    if(triggerTime[i]>1 && !loading ){
        
        count[i]++;
        string path = initPath+"/"+settings.cameras[i];
        
        ofDirectory dir(path);
        if(!dir.exists()){
        dir.create(true);
        }
        
        loading=true;
        
        //Here fix the number tag for secuence propouses
        string ceros;
        if(count[i]<10){
            ceros = "000"+ofToString(count[i]);
        }else if(count[i]<100){
            ceros = "00"+ofToString(count[i]);
        }else if(count[i]<1000){
             ceros = "0"+ofToString(count[i]);
        }
        else if(count[i]<10000){
            ceros = ofToString(count[i]);
        }
        
        //to load synchronously
        string filename = initPath+"/"+settings.cameras[i]+"/"+ofToString(ceros)+settings.ext;
        
        
        img[i].save(filename);
        
        ofLog()<<"TimeRaw: "+ofToString(timeRaw)+" | "+"TimeUp: "+ofToString(triggerTime[i]);
        ofLog()<<"Save image in: "+initPath+"/"+settings.cameras[i]+"/"+settings.cameras[i]+"_"+ofToString(count[i])+settings.ext;
        
        img[i].clear();
        
        img[i].load(cameras[i]);
        ofLog()<<"Load image from: "+cameras[i];
        
        loading=false;
        triggerTime[i]=0;
    
        
    }
       
    }

}

//--------------------------------------------------------------
void ofApp::urlResponse(ofHttpResponse & response){
    if(response.status==200 && response.request.name == "tsingy_forest"){
        for(int i=0;i<totalCams;i++){
        img[i].load(response.data);
        loading=false;
        }
    }else{
        cout << response.status << " " << response.error << " for request " << response.request.name << endl;
        if(response.status!=-1) loading=false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    //Display images from cameras
    ofSetColor(255, 255, 255);

    for(int i=0;i<totalCams;i++){
        
        if(i==0){
            xPos=0;
            yPos=0;
            desplazaX=0;
            desplazaY=0;
        }
        else if(desplazaX == extremo){
            //ofLog()<<"Desplaza";
            desplazaY++;
            yPos= desplazaY*ofGetHeight()/extremo;
            xPos= 0;
            desplazaX=0;
        }
        else{
            xPos= xPos+ofGetWidth()/extremo;
        }
        ofSetColor(255,255,255);
        img[i].draw(xPos,yPos,ofGetWidth()/extremo,ofGetHeight()/extremo);

        
         //ofLog()<<"PosX: "+ofToString(xPos)+" | "+"PosY: "+ofToString(yPos);
        desplazaX++;
       
        
        //For GUI stuff
        if(GUI){
            
            if(loading){
                ofDrawBitmapStringHighlight("Loading new frames...", 20,20);
            }else if(!loading){
            ofDrawBitmapStringHighlight("Time: "+ofToString(ofGetHours())+":"+ofToString(ofGetMinutes()) +":"+ofToString(ofGetSeconds()), 20,40);
            ofDrawBitmapStringHighlight("Date: "+ofToString(ofGetDay())+" | "+ofToString(ofGetMonth()) +" | "+ofToString(ofGetYear()), 20,60);
            ofDrawBitmapStringHighlight("TimeRaw: "+ofToString(timeRaw)+" | "+"Trigger: "+ofToString(triggerTime[i]), 20,80);
            ofDrawBitmapStringHighlight("TimeLimit: "+ofToString(settings.timer), 20,100);
            ofDrawBitmapStringHighlight("Getting images from: "+settings.urlCameras, 20,140);
            ofDrawBitmapStringHighlight("FullScreen > F", 20,180);
            ofDrawBitmapStringHighlight("Hide GUI > G", 20,200);
            
                
            
                if(mouseX>20 && mouseX<400 && mouseY > ofGetHeight()-100 && mouseY < ofGetHeight()){
                    web=true;
                    ofSetColor(0,255,0,20);
                    ofRect(14,ofGetHeight()-70, 412,50);
                    
                }
                else if(mouseX > 200 && mouseY < ofGetHeight()-50){
                    web=false;
                    ofSetColor(255,255,255);
                }
                ofDrawBitmapStringHighlight("By Roman Torre | romantorre.net | rotor-studio.net", 20,ofGetHeight()-50);
                ofDrawBitmapStringHighlight("Made with openframeworks.cc", 20,ofGetHeight()-30);
            
            }
        }
   }

}

//--------------------------------------------------------------
void ofApp::exit() {
    ofUnregisterURLNotification(this);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key =='f'){
        full =! full;
    }
    if(key =='g'){
        GUI =! GUI;
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

    if(web){
      ofLaunchBrowser("https://www.romantorre.net");
        web=false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
