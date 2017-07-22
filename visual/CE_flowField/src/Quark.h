// ------ ------ ------ ------ ------ ------ << Quarks
class Quark {
public:
	ofVec3f pos, vel, acc;
	bool isDead;
	float rad, mass;
	ofColor color;
	int maxVel = 3;

	Quark::Quark() {};
	Quark::~Quark() {};

	void Quark::setup(ofVec3f p0) {
		pos = p0;
		rad = ceil(ofRandom(20));
		mass = ofRandom(0.01, 30.5);
		vel = ofVec3f(ofRandom(-0.3,0.3), ofRandom(-0.4,0.4), 0);
		//vel = ofVec3f(0, 0, 0);
		acc = ofVec3f(0, 0, 0);
		color = ofColor(255, 255);
	}

	void Quark::update() {
		vel = vel + acc;
		vel.limit(maxVel);
		pos = pos + vel;
		acc = acc * 0;

		if (pos.x > ofGetWidth()) pos.x = 0;
		if (pos.x < 0) pos.x = ofGetWidth()-1;
		if (pos.y > ofGetHeight()) pos.y = 0;
		if (pos.y < 0) pos.y = ofGetHeight()-1;
		if (pos.z > 100) pos.z = -100;
		if (pos.z < -100) pos.z = 100;
		//pos.z = vel.length() * 100;
	}

	ofVec3f Quark::goPoint(ofVec3f p1) {
		float G = 9.81;
		ofVec3f f1 = (p1 - pos);
		float dist = f1.length();
		f1.normalize();
		float strength = (G*mass) / (dist*dist);
		ofVec3f force = f1*strength;
		return force;
	}

	void Quark::applyForce(ofVec3f f0) {
		ofVec3f force = f0 * mass;
		acc = acc + force;
	}

	void Quark::follow(vector<ofVec3f> fF, int sc) {
	}
};

class colorImgPix {
public:
	string fileName;
	ofPixels pix;
	ofColor color;
	ofPoint pc;
	// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

	colorImgPix::colorImgPix() {};
	colorImgPix::~colorImgPix() {};
	
	void colorImgPix::setup(std::string fn) {
		fileName = fn;
		ofLoadImage(pix, fileName);
		pc = ofPoint(0, 0, 0);
	}
	ofColor colorImgPix::pick() {
		//pos = int(ofRandom(pix.size()));
		pc.x += 2 * ofMap(ofNoise(ofGetElapsedTimef()), 0, 0.5, -2, 2);
		pc.y += 2 * ofMap(ofNoise(ofGetElapsedTimeMillis() / 3), 0, 0.5, -2, 2);
		if (pc.x > 1000) pc.x -= 1000;
		if (pc.x < 0) pc.x += 1000;
		if (pc.y > 1000) pc.y -= 1000;
		if (pc.y < 0) pc.y += 1000;
		int ipp = (3 * (pc.y * 1023 + pc.x));
		color = pix.getColor(pc.x, pc.y);
		return color;
	}


};