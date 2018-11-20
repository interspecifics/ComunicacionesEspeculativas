/*
 * [CE_Extractor] :: 2018.0710
 * Comunicaciones Especulativas
 * emmanuel@interspecifics.cc
 * -----------------------------
 *
 * extract LK optical flow features from timelapses
 * save it to json files
 * key options

 * resize a batch of files
 $ ffmpeg -i F:/DATA/speccoms/v16/a%04d.jpg -vf scale=1920*1080 F:/DATA/speccoms/v16_hd/a%04d.png
 
 + v1.0
	original data format
 + v1.1
	compact data format
	minimal indicator layers
 */

// mould rush // raphael kim
// client

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxImageSequenceRecorder.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "ofxJSON.h"

#define OSC_HOST "localhost"
#define OSC_IN_PORT 11111
#define OSC_OUT_PORT 11000

using namespace cv;
using namespace ofxCv;


//--------------------------------------------------------APP CLASS

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void load_dir();

	void keyPressed(int key);
	void keyReleased(int key);
	void exit();

	ofVideoGrabber camera;
	cv::Mat grabberGray; 
	ofxCv::FlowPyrLK flow;
	ofVec2f p1;
	ofRectangle rect;
	vector<cv::Point2f> feats;

	// neu controls
	bool en_edges;
	bool en_write;
	bool en_record;
	int edge_thr1, edge_thr2;

	float lkQ;
	int lkMxLv, lkMnDist;
	int lkWinSz;
	float cutCM;
	int vlThrA, vlThrB;

	// json 
	ofxJSONElement db, entry, delist, mini;

	// 
	std::string path, filepath;
	vector<string> fList;

	// ------ ------ ------ ------ ------ ------ | gui |
	bool showGui;
	ofxPanel gui;

	ofxToggle load_new;
	ofxToggle enable_record;

	ofxToggle en_Simpleblob;
	ofxFloatSlider ampli, diff_thresh, contour_thresh;
	ofxToggle en_track;

	ofxIntSlider val_ofColumn;
	ofxToggle send_ofColumn;
	ofxToggle send_ofBlobs;
	ofxToggle send_sBlobs;

	// ------ ------ ------ ------ ------ ------ | osc |
	ofxOscReceiver osc_recver;
	ofxOscSender osc_sender;

	// ------ ------ ------ ------ ------ ------ | rec stuff |
	ofxImageSequenceRecorder img_recorder;
	bool isRecording;

	// ------ ------ ------ ------ ------ ------ | imgs |
	ofDirectory dir;
	bool isLoad;

	int nImgs;
	int ih, iw;
	int gridSz, scale;
	bool blackFlag;
	int index_img;
	int t0, t1, index1;
	vector<ofImage> imgList;
	vector<cv::Mat> matList;
	cv::Mat tempMat;
	ofImage tempImg;
	ofFbo fbo_A, fbo_B, fbo_C, fbo_D;
	ofPixels pixs;
	ofColor cColor, nColor;
	ofImage optoMap;
	ofFbo buffer;

	ofxCv::FlowPyrLK LK;
	ofxCv::FlowFarneback FB;
	ofxCv::Flow* curFlow;
	vector<ofPoint> old_feats;
	vector<ofVec2f> new_feats;
	ofColor dirColor;
	int transpa;

	// --------------------- NRML
	int w, h, t;
	float tt;

	// --------------------- BLOB
	ofImage gray, edge, edge2;
	cv::Mat prevImg, diffImg, actImg, nexImg, grayImg, grayImg2;
	ofImage rImg, sImg, tImg;

	vector<int> theQueue;
	int auxLabel;
	bool isHere;
	int pX, pY;
};

