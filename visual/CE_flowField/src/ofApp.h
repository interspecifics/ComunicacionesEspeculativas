#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxImageSequenceRecorder.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "ofxMaxim.h"
#include "maxiMFCC.h"
#include "ofxPostGlitch.h"
#include "Quark.h"
#include "ofxJSON.h"

#define HOST "localhost"
#define OSC_IN_PORT 6666
#define OSC_OUT_PORT 10001 

// ------ ------ ------ ------ ------ ------ << ofApp
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);

		
		// ------ | audio + maxim stuff |
		void audioRequested(float * input, int bufferSize, int nChannels);
		void audioReceived(float * input, int bufferSize, int nChannels);
		float 	* lAudioOut;
		float   * rAudioOut;
		float * lAudioIn;
		float * rAudioIn;
		int		initialBufferSize;
		int		sampleRate;
		double wave, sample, outputs[2], ifftVal;
		maxiMix mymix;
		maxiOsc osc;
		ofxMaxiFFTOctaveAnalyzer oct;
		int nAverages;
		float *ifftOutput;
		int ifftSize;
		float peakFreq = 0;
		float centroid = 0;
		float RMS = 0;
		ofxMaxiIFFT ifft;
		ofxMaxiFFT mfft;
		int fftSize;
		int bins, dataSize;
		maxiMFCC mfcc;
		double *mfccs;
		maxiSample samp;
		// ------ | data buff|
		vector< vector<float> > dataBuff;
		vector<float> d0;
		vector<float> mB;
		int dBuffSize;
		int nBands;
		int rot;
		float softRMS;
		// ------ | osc|
		ofxOscReceiver receiver;
		ofxOscSender senderOSC;
		int v1, v2;
		// ...... | flow|
		int scale, index;
		int cols, rows;
		float xOff, yOff, zOff;
		float inc, rr, ss;
		vector<ofVec3f> fField;
		ofVec3f ori, vE;
		ofEasyCam cam;
		// ------ rec
		ofxImageSequenceRecorder recorder;
		ofImage tImg;
		// ------ regular stuff
		int w, h, t;
		float tt;
		ofFbo fbo_a, fbo_b;
		vector<Quark> quarks_in, quarks_out, quarks;
		Quark tqk, tqq;
		ofPoint tPo;
		ofMesh mesh, mish;
		ofPoint atraktor;
		colorImgPix colorPick;
		// ------ gui stuff
		bool en_lines = false;
		bool en_rects = false;
		bool en_dsp;
		bool en_rec = false;
		// ---- CE stuff
		ofxJSONElement supArray;
		int i_ce;

};
