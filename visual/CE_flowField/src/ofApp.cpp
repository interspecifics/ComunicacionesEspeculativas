#include "ofApp.h"

/*
1. particulas en una deriva interminable hacia el espectador
	.reactivo al sonido
	·hay que seleccionar manualmente el archivo de datos a leer


*/


//--------------------------------------------------------------
void ofApp::setup(){
	w = ofGetWidth();
	h = ofGetHeight();
	ofSetFrameRate(24);
	// ------ ------ ------ ------ ------ ------ | dsp |
	sampleRate = 44100;
	initialBufferSize = 512;
	lAudioOut = new float[initialBufferSize];
	rAudioOut = new float[initialBufferSize];
	lAudioIn = new float[initialBufferSize];
	rAudioIn = new float[initialBufferSize];
	memset(lAudioOut, 0, initialBufferSize * sizeof(float));
	memset(rAudioOut, 0, initialBufferSize * sizeof(float));
	memset(lAudioIn, 0, initialBufferSize * sizeof(float));
	memset(rAudioIn, 0, initialBufferSize * sizeof(float));

	fftSize = 1024;
	mfft.setup(fftSize, 512, 256);
	ifft.setup(fftSize, 512, 256);
	nAverages = 12;
	oct.setup(sampleRate, fftSize / 2, nAverages);
	mfccs = (double*)malloc(sizeof(double) * 13);
	mfcc.setup(512, 42, 13, 20, 20000, sampleRate);
	ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
	ofSoundStreamSetup(2, 2, this, sampleRate, initialBufferSize, 4); // Call this last ! 
																	  // fft :: 512 , mfft.magnitudes[i] , pitch/timbral/vol
																	  // MFCC :: 13 , mfccs[i] , timbre/vocal
																	  // CosQ :: 104, oct.averages[i] , 12 bands/oct
																	  // peak :: peakFreq, spectral centroid :: centroid, rms::RMS
	nBands = 104;
	dBuffSize = 16;
	d0.resize(nBands);
	mB.resize(nBands);
	dataBuff.resize(dBuffSize);
	for (int n = 0; n < dBuffSize; n++) { dataBuff[n].resize(nBands); }
	// ------ ------ ------ ------ ------ ------ | fbo |
	fbo_a.allocate(w, h, GL_RGBA);
	fbo_a.begin(); ofClear(0, 0); fbo_a.end();	
	fbo_b.allocate(w, h, GL_RGBA);
	fbo_b.begin(); ofClear(0, 0); fbo_b.end();
	// ------ ------ ------ ------ ------ ------ | quarks |
	int nQ = 10000;
	quarks.resize(0);
	for (int i = 0; i < nQ; i++) {
		Quark yoQ;
		//yoQ.setup(ofVec3f(w/2, h/2, 0));
		yoQ.setup(ofVec3f(ofRandom(w), ofRandom(h), -90));
		quarks.push_back(yoQ);
	}
	cout << "created " << quarks.size() << " quarks.." << endl;
	atraktor = ofPoint(0, 0, 0);
	en_dsp = true;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	glPointSize(2);
	//rec + img
	recorder.setPrefix(ofToDataPath("./rec/rec_"));
	recorder.setFormat(".png");
	colorPick.setup("cI/w03.jpg");
	// flow field
	scale = 35; 
	inc = 0.01;
	cols = floor(w / scale);
	rows = floor(h / scale);
	zOff = 0;
	fField.resize(0);
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			fField.push_back(ofVec3f(0, 0, 0));
		}
	}

	i_ce = 0;
	// --------- 
	//bool suc = supArray.open("./angles_1500550145.json");
	//bool suc = supArray.open("./angles_1500550954.json");
	bool suc = supArray.open("./angles_1500549651.json");
	//bool suc = supArray.open("./angles_1500549608.json");
	//bool suc = supArray.open("./angles_1500549234.json");
	//bool suc = supArray.open("./angles_1500485949.json");
	//bool suc = supArray.open("./angles_1500550979.json");
	if (suc) ofLogNotice("ofApp::setup") << "[JSON] :: vector field :: " << supArray.size();
	cout << "Created " << fField.size() << " field w/" << cols <<","<< rows << endl;
}


//--------------------------------------------------------------
void ofApp::update(){
	t = ofGetElapsedTimeMillis();
	tt = ofGetElapsedTimef();
	std::stringstream strm;
	strm << "[pensar]: " << ofGetFrameRate() << " fps";
	ofSetWindowTitle(strm.str());
	// ------ ------ ------ ------ ------ ------ | osc |
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		// --- mixer
		if (m.getAddress() == "/ctrlr/A0") {
			v1 = m.getArgAsFloat(0);
			cout << "[ini1]: " << v1 << "\n";
		}
	}
	// ------ ------ ------ ------ ------ ------ | dsp |
	if (en_dsp == true) {
		for (int b = 0; b < nBands; b++) { if (oct.averages[b] > 0) { d0[b] = oct.averages[b]; } }
		for (int n = dBuffSize - 1; n > 0; n--) { dataBuff[n] = dataBuff[n - 1]; }
		dataBuff[0] = d0;
		for (int b = 0; b < nBands; b++) {
			mB[b] = 0;
			for (int n = 0; n < dBuffSize; n++) { mB[b] += dataBuff[n][b]; }
			mB[b] /= dBuffSize;
		}
		//softRMS = ofLerp(softRMS, RMS, 0.2);
	}



	// ------ ------ ------ ------ ------ ------ | draw |
	fbo_b.begin();
	ofClear(0, 0);
	//cout << "income:";
	// flow field
	ofEnableBlendMode(OF_BLENDMODE_SCREEN);
	yOff = 0;
	for (int y = 0; y < rows; y++) {
		xOff = 0; 
		for (int x = 0; x < cols; x++) {
			//cout << "["<<x << "," << y<<"]";
			// set vectors
			index = (x + y * cols); // pixel index
			rr = ofNoise(xOff, yOff, zOff) * TWO_PI;
			ss = ofNoise(xOff, yOff, zOff, tt/100) * TWO_PI;
			xOff += inc;
			if (t % 2 == 0) {
				vE = ofVec3f(scale*cos(ss), scale*sin(ss), ofMap(ss, 0, TWO_PI, 0.02, 2));
				ori = ofVec3f(x*scale, y*scale, ofMap(ss, 0, TWO_PI, 0.02, 2));
			}
			else {
				vE = ofVec3f(scale*cos(rr), scale*sin(rr), ofMap(rr, 0, TWO_PI, 0.2, 2));
				ori = ofVec3f(x*scale, y*scale, ofMap(rr, 0, TWO_PI, 0.02, 2));
			}
			float aaa = supArray[i_ce][index].asFloat();
			vE = ofVec3f(scale*cos(aaa), scale*sin(aaa), ofMap(aaa, -PI, PI, -2, 2));
			fField[index] = ofVec3f(vE);

			}
		yOff += inc;
		zOff += 0.000001 + (0.0005*RMS);
	}
	i_ce++;
	if (i_ce >= supArray.size()) {
		i_ce = 0;
	}
	ofSetColor(255);

	// quarks 
	cam.begin();
	mesh.clear();
	ofPushMatrix();
	ofTranslate(-w / 2, -h / 2, 0);
	//cout << "\n\n\t\t drawing" << endl;
	for (int i = 0; i < quarks.size(); i++) {
		int tx = floor(quarks[i].pos.x / scale);
		int ty = floor(quarks[i].pos.y / scale);
		int index = ofClamp((tx + ty*cols),0, cols*rows-1); // pixel index
		//cout << "i:" << index;
		quarks[i].maxVel = 1 + 1 * mB[i % 103];
		ofVec3f force = ofVec3f(fField[index]*(0.01+mB[103- (i % 103)]));
		quarks[i].applyForce(force);

		quarks[i].update(); 
		mesh.addVertex(quarks[i].pos);
		//mesh.addColor(ofColor(255, 255));
		mesh.addColor(ofColor(255, ofMap(mB[i % 103], 0, 1, 25, 255)));

	}
	mesh.drawWireframe();
	ofPopMatrix();
	cam.end();

	ofDisableBlendMode();
	fbo_b.end();


	// ------ ------ ------ ------ ------ ------ | draw |
	fbo_a.begin();
	ofClear(0, 0);
	mesh.drawWireframe();
	fbo_a.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	fbo_b.draw(0, 0);
	// r + sh
	if (en_rec) {
		tImg.grabScreen(0, 0, ofGetWidth(), ofGetHeight()); 
		recorder.addFrame(tImg);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') en_rec = !en_rec;
	if (key == 't') {
		if (recorder.isThreadRunning()) {
			recorder.stopThread();
		}
		else {
			recorder.startThread(false, true);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	atraktor = ofPoint(x, y, 0);
}




//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		wave = lAudioIn[i];
		if (mfft.process(wave)) {
			mfft.magsToDB();
			oct.calculate(mfft.magnitudesDB);

			float sum = 0;
			float maxFreq = 0;
			int maxBin = 0;
			for (int i = 0; i < fftSize / 2; i++) {
				sum += mfft.magnitudes[i];
				if (mfft.magnitudes[i] > maxFreq) {
					maxFreq = mfft.magnitudes[i];
					maxBin = i;
				}
			}
			centroid = sum / (fftSize / 2);
			peakFreq = (float)maxBin / fftSize * 44100;

			mfcc.mfcc(mfft.magnitudes, mfccs);
		}
		lAudioOut[i] = 0;
		rAudioOut[i] = 0;
	}
}


//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
	/* You can just grab this input and stick it in a double, then use it above to create output*/
	float sum = 0;
	for (int i = 0; i < bufferSize; i++) {
		/* you can also grab the data out of the arrays*/
		lAudioIn[i] = input[i * 2];
		rAudioIn[i] = input[i * 2 + 1];

		sum += input[i * 2] * input[i * 2];
	}
	RMS = sqrt(sum);
}