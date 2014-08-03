#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitMidi.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	void drawOscilloscopeGrid();
	void drawOscilloscopeLabels();
	void drawOscilloscopeLines();
	
	ofxAudioUnitSampler sampler;
	ofxAudioUnitFilePlayer filePlayer;
	ofxAudioUnitNetReceive netReceive;
	ofxAudioUnitSpeechSynth speechSynth;
	ofxAudioUnitMidiReceiver midiReceiver;
	ofxAudioUnitInput input;
	
	ofxAudioUnitOutput output;
	
	ofxAudioUnitTap tap;
	ofPolyline oscLineLeft, oscLineRight;
	
	ofxAudioUnit * activeUnit;
};