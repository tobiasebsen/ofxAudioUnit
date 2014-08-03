#pragma once

#include "ofxAudioUnitBase.h"

// ofxAudioUnitOutput wraps the AUHAL output unit on OSX
// and the RemoteIO unit on iOS

// This unit drives the "pull" model of Core Audio and
// sends audio to the actual hardware (ie. speakers / headphones)

class ofxAudioUnitOutput : public ofxAudioUnit
{
public:
	ofxAudioUnitOutput();
	~ofxAudioUnitOutput(){stop();}
	
	bool start();
	bool stop();
	
	bool setDevice(AudioDeviceID deviceID);
	bool setDevice(const string &deviceName);
    AudioDeviceID getDevice();
    
    std::vector<UInt32> getChannelMap();
    bool setChannelMap(std::vector<UInt32> map);
    
    void getChannelLayout();

	static void listOutputDevices();
};
