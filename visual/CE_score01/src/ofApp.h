#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxGui"
#include "ofxOsc.h"

#define OSC_IN_PORT 8888

class ofApp : public ofBaseApp{

  public
    void setup();
    void update();
    void draw();
    void videos();
    void interface();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void gotMessage(ofMessage msg);

    ofxUISuperCanvas *gui0;
    ofxUISuperCanvas *gui1;

    void guiEvent(ofxUIEventArgs &e);

    bool drawPadding;

/// ---- Mixer control
ofxPanel gui;
ofxGuiGroup mixerGroup
ofxFloatSlider imageAlpha, videoAlpha, cameraAlpha,

//// --- Video and image
ofTexture image;
ofVideoPlayer video;
ofVideoGrabber camera;


//// ------ OSC data
float p01, p02, p03;
ofxOscReceiver receiver;


//// ----- Offscreen part 1 (swarming movility)
vector<ofTexture> part_01;
ofFbo fbo1;
int index_01;

int fNo_01;
int img_paeni_01;
int ofDirectory dir;
int tt00, tt1, tt03
int


ofMesh mesh;




};

#endif
