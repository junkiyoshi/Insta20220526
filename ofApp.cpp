#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");
	
	ofBackground(255);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	// Day 062 Cardinal Red
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(183, 24, 12));
	color_palette.push_back(ofColor(175, 168, 86));
	color_palette.push_back(ofColor(220, 221, 221));

	for (int x = -240; x <= 240; x += 240) {
	
		this->draw_sun(glm::vec2(x, 0), color_palette);
	}
	 
	// Day 165 French Vanilla
	color_palette.clear();
	color_palette.push_back(ofColor(249, 233, 204));
	color_palette.push_back(ofColor(217, 160, 182));
	color_palette.push_back(ofColor(124, 91, 143));

	for (int x = -240; x <= 240; x += 240) {

		this->draw_sun(glm::vec2(x, -240), color_palette);
	}

	// Day 228 Zenith Blue
	color_palette.clear();
	color_palette.push_back(ofColor(134, 179, 224));
	color_palette.push_back(ofColor(251, 218, 205));
	color_palette.push_back(ofColor(234, 96, 148));

	for (int x = -240; x <= 240; x += 240) {

		this->draw_sun(glm::vec2(x, 240), color_palette);
	}

}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
void ofApp::draw_sun(glm::vec2 location, vector<ofColor> color_palette) {

	int small_radius = 35;
	int big_radius = 200;
	int param_span = 2;

	for (int i = 0; i < 3; i++) {

		int x = i * 235 - 235;

		ofSetColor(color_palette[i % 3]);
		ofFill();
		ofDrawRectangle(glm::vec2(x, location.y), big_radius * 1.05, big_radius * 1.05);

		for (int param_start = ofGetFrameNum() * 0.15; param_start < ofGetFrameNum() * 0.15 + 100; param_start += param_span * 2) {

			vector<glm::vec2> in, out;

			for (int param = param_start; param < param_start + param_span; param++) {

				int deg = param * 3.6 - 135;
				in.push_back(glm::vec2(x + small_radius * cos(deg * DEG_TO_RAD), location.y + small_radius * sin(deg * DEG_TO_RAD)));
				out.push_back(glm::vec2(x, location.y) + make_point(big_radius, param));
			}

			reverse(out.begin(), out.end());

			ofSetColor(color_palette[(i + 1) % 3]);
			ofFill();

			ofBeginShape();
			ofVertices(in);
			ofVertices(out);
			ofEndShape(true);

			ofDrawCircle(glm::vec2(x, location.y), small_radius * 0.8);
		}

		ofSetColor(color_palette[(i + 1) % 3]);
		ofNoFill();
		ofDrawRectangle(glm::vec2(x, location.y), big_radius * 1.05, big_radius * 1.05);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}