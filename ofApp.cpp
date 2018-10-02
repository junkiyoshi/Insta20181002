#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	float radius = 300.f;
	float small_radius = 80.f;
	float deg_span = 10.f;
	float small_deg_span = 30.f;

	for (int deg = 0; deg < 360; deg += deg_span) {

		for (int small_deg = 0; small_deg < 360; small_deg += small_deg_span) {

			float noise_value = ofNoise(deg * 0.05, small_deg * 0.05, ofGetFrameNum() * 0.005);
			float tmp_small_radius = small_radius * noise_value;

			ofSetColor(255 - noise_value * 255);

			ofBeginShape();

			ofVertex(this->make_point(radius, deg, tmp_small_radius, small_deg));
			ofVertex(this->make_point(radius, deg + deg_span, tmp_small_radius, small_deg));
			ofVertex(this->make_point(radius, deg + deg_span, tmp_small_radius, small_deg + small_deg_span));
			ofVertex(this->make_point(radius, deg, tmp_small_radius, small_deg + small_deg_span));

			ofEndShape(true);
		}
	}


	this->cam.end();
}

//--------------------------------------------------------------
ofPoint ofApp::make_point(float radius, float deg, float small_radius, float small_deg) {

	float x_1 = radius * cos(deg * DEG_TO_RAD);
	float y_1 = radius * sin(deg * DEG_TO_RAD);

	float x_2 = small_radius * cos(small_deg * DEG_TO_RAD) * cos(deg * DEG_TO_RAD);
	float y_2 = small_radius * cos(small_deg * DEG_TO_RAD) * sin(deg * DEG_TO_RAD);

	float x = x_1 + x_2;
	float y = y_1 + y_2;
	float z = small_radius * sin(small_deg * DEG_TO_RAD);

	return ofPoint(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}