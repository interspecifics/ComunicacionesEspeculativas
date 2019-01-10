#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
	//- base
	ofBackground(0);
	ofSetVerticalSync(true);
	ofSetFrameRate(12);
	h = ofGetHeight();
	w = ofGetWidth();

	//- osc
	osc_sender.setup(OSC_HOST, OSC_OUT_PORT);

	//- no gui
	gridSz = 10;
	cout << "OK1: " << gridSz << endl;

	//- files
	load_dir();

	//- rec 
	img_recorder.setPrefix(ofToDataPath("imgs/ce_extract_"));
	img_recorder.setFormat("png");

	// other inits
	grayImg = toCv(imgList[0]);
	//cvtColor(actImg, grayImg, CV_RGB2GRAY);
	prevImg = grayImg;

	scale = 0;
	isLoad = false;
	blackFlag = false;
	showGui = true;
	index_img = 0;
	index1 = 1;

	en_edges	= false;
	edge_thr1	= 60;
	edge_thr2	= 85;

	lkQ			= 0.61;
	lkMxLv		= 4;
	lkMnDist	= 5;
	lkWinSz		= 30;

	cutCM		= 7.0;
	vlThrA		= 6;
	vlThrB		= 48;
}




//--------------------------------------------------------------
void ofApp::update(){
	//- timings
	t = ofGetElapsedTimeMillis();
	tt = ofGetElapsedTimef();
	
	//- title and data
	std::stringstream strm;
	strm << "CE_exTraktor // fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	// check state
	if (load_new == true) {
		load_dir();
		load_new = false;
	}

	//- no sequence, just update index and flag
	t0 = ofGetElapsedTimeMillis();
	if ((t0 - t1) > 80) {
		if (index_img < nImgs - 3) { //
			index_img++;
			blackFlag = true;
		}
		else {
			index_img = 0;
			if (en_write == true) {
				// escribe a archivo
				if (!db.save(path + ".json", true)) {
					ofLogNotice("ofApp::setup") << "db.json written unsuccessfully.";
				} else {
					ofLogNotice("ofApp::setup") << "db.json written successfully.";
				}
				// y desactiva write mode
				en_write = false;
			}
			if (en_record== true) {
				// escribe a archivo
				ofLogNotice("ofApp::setup") << "image sequence written successfully.";
				en_record = false;
			}
		}
		t1 = ofGetElapsedTimeMillis();
	}
	
	//- if flagged, process
	if (blackFlag) {
		// get image, get bw
		/*actImg = toCv(imgList[index_img]);
		cvtColor(actImg, grayImg, CV_RGB2GRAY);
		nexImg = toCv(imgList[index_img+1]);
		cvtColor(nexImg, grayImg2, CV_RGB2GRAY);*/
		grayImg = toCv(imgList[index_img]);
		grayImg2 = toCv(imgList[index_img + 1]);
		// if edges
		if (en_edges == true) {
			Canny(grayImg, edge, edge_thr1, edge_thr2);
			edge.update();
			Canny(grayImg2, edge2, edge_thr1, edge_thr2);
			edge2.update();
		}
		//
		// then optoflow
		LK.setWindowSize(lkWinSz);
		LK.setQualityLevel(lkQ);
		LK.setMinDistance(lkMnDist);
		LK.setMaxLevel(lkMxLv);
		LK.setFeaturesToTrack(feats);
		if (en_edges == true) LK.calcOpticalFlow(edge); 
		else LK.calcOpticalFlow(imgList[index_img]); 
		new_feats = LK.getMotion();
		// and draw on FBO
		fbo_B.begin();
		ofClear(0, 0);
		// do lines -use LK.draw(0, 0) alternatively-
		for (int i = 0; i < new_feats.size(); i++) {
			//ofNoFill();
			float lll = new_feats[i].length();
			if (lll >= vlThrA && lll <= vlThrB) {
				ofSetColor(ofColor::fromHsb(ofMap(lll, vlThrA, vlThrB, 0, 255), 255, 255, 48));
				ofDrawRectangle(ofVec2f(feats[i].x, feats[i].y), gridSz, gridSz);
				ofSetColor(255, 127); // originale scale
				ofLine(ofVec2f(feats[i].x, feats[i].y), ofVec2f(feats[i].x, feats[i].y) + new_feats[i]/2);
			}
			ofFill();
			ofDrawRectangle(ofVec2f(feats[i].x-1, feats[i].y-1), 2, 2);
			;
		}
		fbo_B.end();

		// draw the other fBO
		fbo_A.begin();
		ofClear(0, 0);
		//if (en_edges == true) { edge.draw(0, 0); }
		//else { imgList[index_img].draw(0, 0); }
		imgList[index_img].draw(0, 0);
		fbo_A.end();

		// if writing data
		if (en_write == true) {
			entry.clear();
			entry["filename"] = fList[index_img];
			entry["edges"] = ofToString(en_edges == true ? " on" : "off");
			entry["edgThrA"] = edge_thr1;
			entry["edgThrB"] = edge_thr2;
			entry["lkQ"] = lkQ;
			entry["lkWinSz"] = lkWinSz;
			entry["vlThrA"] = vlThrA;
			entry["vlThrB"] = vlThrB;
			entry["index"] = index_img;
			entry["gridSize"] = gridSz;
			entry["gridWN"] = iw / gridSz;
			entry["gridHN"] = ih / gridSz;
			delist.clear();
			for (int i = 0; i < new_feats.size(); i++) {
				float lll = new_feats[i].length();
				if (lll >= vlThrA && lll <= vlThrB) {
					mini.clear();
					mini.append(int(1000 * new_feats[i].x));
					mini.append(int(1000 * new_feats[i].y));
					mini.append(int(1000 * new_feats[i].angle(ofVec2f(0, 1))));
					mini.append(int(1000 * new_feats[i].length()));
					delist.append(mini);
				}
				else {
					mini.clear();
					mini.append(0);
					delist.append(mini);
				}
			}
			entry["opticflow"] = delist;
			db.append(entry);
		}
		//blackFlag = false;
	} // end blackflag activity
}



//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255, 255);
	fbo_A.draw(0, 0);
	ofSetColor(255, 192);
	fbo_B.draw(0, 0);

	if (blackFlag == true) {
		if (en_record == true) {
			tImg.grabScreen(0, 0, w, h);
			img_recorder.addFrame(tImg);
		}
		blackFlag = false;
	}

	ofDrawBitmapStringHighlight("[edG]: " + ofToString(en_edges == true ? " on" : "off")
						+ "\t[write]: " + ofToString(en_write == true ? " on" : "off")
						+ "\t[edgThrA]: " + ofToString(edge_thr1)
						+ "\t[edgThrB]: " + ofToString(edge_thr2)
						+ "\t[lkQ]: " + ofToString(lkQ) 
						+"\t[vlThrA]: " + ofToString(vlThrA)
						+ "\t[vlThrB]: " + ofToString(vlThrB)
						+ "\t[fN]: " + ofToString(index_img), iw/2 - 500, 20, 10);
	
	ofDisableBlendMode();

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'e') { en_edges = !en_edges; }
	if (key == 's') { edge_thr1 = edge_thr1 > 0 ? edge_thr1 - 1 : 0; }
	if (key == 'd') { edge_thr1 = edge_thr1 <= 255 ? edge_thr1 + 1 : 255; }
	if (key == 'x') { edge_thr2 = edge_thr2 > 0 ? edge_thr2 - 1 : 0; }
	if (key == 'c') { edge_thr2 = edge_thr2 <= 255 ? edge_thr2 + 1 : 255; }

	//if (key == 'f') { lkQ = lkQ >= 0.005 ? lkQ - 0.005 : 0.005; }
	//if (key == 'g') { lkQ = lkQ <= 0.995 ? lkQ + 0.005 : 0.995; }
	if (key == 'v') { vlThrA = vlThrA > 0 ? vlThrA - 1 : 0; }
	if (key == 'b') { vlThrA = vlThrA < 255 ? vlThrA + 1 : 0; }
	if (key == 'f') { vlThrB = vlThrB > 0 ? vlThrB - 1 : 0; }
	if (key == 'g') { vlThrB = vlThrB < 255 ? vlThrB + 1 : 0; }

	if (key == 'l') { load_dir(); }

	if (key == 'k') { 
		en_write = true;
		index_img = -1;
		db.clear();
	}

	if (key == 'z') {
		tImg.grabScreen(0, 0, w, h);
		tImg.saveImage("imgs/frame_" + ofToString(t) + ".png");
	}

	if (key == 'r') {
		if (img_recorder.isThreadRunning()) {
			img_recorder.stopThread();
		}
		else {
			img_recorder.startThread(false, true);
		}
		en_record = true;
		index_img = -1;
		t1 = ofGetElapsedTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::exit() {
	img_recorder.waitForThread();
}



//--------------------------------------------------------------LOAD DIR
void ofApp::load_dir() {
	// ... ... ... --- --- ... ... ... --- --- ... ... --- files
	ofFileDialogResult result = ofSystemLoadDialog("Selecciona un archivo de la secuencia");
	if (result.bSuccess) {
		filepath = result.getPath();
		path = filepath.substr(0, filepath.rfind("\\"));
		while (path.find("\\") != string::npos) path.replace(path.find("\\"), 1, "/");
		cout << "[file]: " << filepath << endl;
		cout << "[path]: " << path << endl;
		nImgs = dir.listDir(path);
		nImgs = nImgs <= 700 ? nImgs : 700;
		fList.resize(0);
		cout << "[C_E]: " << nImgs << " images: " << endl;
		imgList.resize(nImgs);
		for (int i = 0; i < nImgs - 1; i++) {
			string fn = dir.getPath(1400+i);
			imgList[i].load(fn);
			fList.push_back(fn);
			cout << "\t." << i << ".";
		}; cout << endl;
		isLoad = true;
	}
	if (nImgs > 0) {
		iw = imgList[0].getWidth();
		ih = imgList[0].getHeight();
		cout << iw << "," << ih << endl;
	} else {
		iw = 0;
		ih = 0;
	}

	// features 
	feats.resize(0); // mesh
	for (int ix = 0; ix <= int(iw / gridSz)*10; ix += gridSz) {
		for (int iy = 0; iy <= int(ih / gridSz)*10; iy += gridSz) {
			feats.push_back(cv::Point2f(ix, iy));
			//LK.setFeaturesToTrack(feats);
		}
	}

	// fbos
	fbo_A.allocate(iw, ih, GL_RGBA);
	fbo_B.allocate(iw, ih, GL_RGBA);
	fbo_C.allocate(iw, ih, GL_RGBA);
	fbo_D.allocate(iw, ih, GL_RGBA);
	buffer.allocate(iw, ih, GL_RGBA);
	rImg.allocate(iw, ih, OF_IMAGE_COLOR_ALPHA);
	optoMap.allocate(iw, ih, OF_IMAGE_COLOR_ALPHA);

	grayImg = toCv(imgList[0]);
	//cvtColor(actImg, grayImg, CV_RGB2GRAY);
	prevImg = grayImg;
}