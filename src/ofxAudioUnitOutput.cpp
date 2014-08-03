#include "ofxAudioUnitOutput.h"
#include "ofxAudioUnitUtils.h"
#include "ofxAudioUnitHardwareUtils.h"
#include <CoreFoundation/CoreFoundation.h>

AudioComponentDescription outputDesc = {
	kAudioUnitType_Output,
#if TARGET_OS_IPHONE
	kAudioUnitSubType_RemoteIO,
#else
	kAudioUnitSubType_HALOutput,
#endif
	kAudioUnitManufacturer_Apple
};


// ----------------------------------------------------------
ofxAudioUnitOutput::ofxAudioUnitOutput()
// ----------------------------------------------------------
{
	_desc = outputDesc;
	initUnit();
}

// ----------------------------------------------------------
bool ofxAudioUnitOutput::start()
// ----------------------------------------------------------
{
	OFXAU_RET_BOOL(AudioOutputUnitStart(*_unit), "starting output unit");
}

// ----------------------------------------------------------
bool ofxAudioUnitOutput::stop()
// ----------------------------------------------------------
{
	OFXAU_RET_BOOL(AudioOutputUnitStop(*_unit), "stopping output unit");
}

#pragma mark - Hardware

#if !TARGET_OS_IPHONE

// ----------------------------------------------------------
bool ofxAudioUnitOutput::setDevice(AudioDeviceID deviceID)
// ----------------------------------------------------------
{
	UInt32 deviceIDSize = sizeof(deviceID);
	OFXAU_RET_BOOL(AudioUnitSetProperty(*_unit,
										kAudioOutputUnitProperty_CurrentDevice,
										kAudioUnitScope_Global,
										0,
										&deviceID,
										deviceIDSize),
				   "setting output unit's device ID");
}

// ----------------------------------------------------------
bool ofxAudioUnitOutput::setDevice(const string &deviceName)
// ----------------------------------------------------------
{
	std::vector<AudioDeviceID> outputDevices = AudioOutputDeviceList();
	AudioDeviceID deviceID;
	bool found = false;
	for(int i = 0; i < outputDevices.size(); i++) {
		int diff = AudioDeviceName(outputDevices[i]).compare(deviceName);
		if(!diff) {
			deviceID = outputDevices[i];
			found = true;
			break;
		}
	}
	
	if(found) {
		return setDevice(deviceID);
	} else {
		return false;
	}
}

// ----------------------------------------------------------
AudioDeviceID ofxAudioUnitOutput::getDevice()
// ----------------------------------------------------------
{
    AudioDeviceID deviceID = 0;
    UInt32 deviceIDSize = sizeof(deviceID);
    OFXAU_PRINT(AudioUnitGetProperty(*_unit,
                         kAudioOutputUnitProperty_CurrentDevice,
                         kAudioUnitScope_Global,
                         0,
                         &deviceID,
                         &deviceIDSize),
                "getting output unit's device ID");
    return deviceID;
}

// ----------------------------------------------------------
std::vector<UInt32> ofxAudioUnitOutput::getChannelMap()
// ----------------------------------------------------------
{
    UInt32 dataSize;
    Boolean writable;
    OFXAU_PRINT(AudioUnitGetPropertyInfo(*_unit,
                             kAudioOutputUnitProperty_ChannelMap,
                             kAudioUnitScope_Output,
                             0,
                             &dataSize,
                             &writable),
                "getting output unit's channel map");
    
    UInt32 numChannels = dataSize / sizeof(UInt32);
    std::vector<UInt32> channelMap(numChannels);
    
    AudioUnitGetProperty(*_unit,
                         kAudioOutputUnitProperty_ChannelMap,
                         kAudioUnitScope_Output,
                         0,
                         channelMap.data(),
                         &dataSize);
        
    return channelMap;
}

// ----------------------------------------------------------
bool ofxAudioUnitOutput::setChannelMap(std::vector<UInt32> map)
// ----------------------------------------------------------
{
    OFXAU_RET_BOOL(AudioUnitSetProperty(*_unit,
                         kAudioOutputUnitProperty_ChannelMap,
                         kAudioUnitScope_Output,
                         0,
                         map.data(),
                         map.size()*sizeof(UInt32)),
                   "setting output unit's channel map");
}

// ----------------------------------------------------------
void ofxAudioUnitOutput::getChannelLayout()
// ----------------------------------------------------------
{
    UInt32 dataSize;
    Boolean writable;
    AudioUnitGetPropertyInfo(*_unit,
                        kAudioUnitProperty_AudioChannelLayout,
                        kAudioUnitScope_Output,
                        0,
                        &dataSize,
                        &writable);

    /*AudioChannelLayout *acl = (AudioChannelLayout*)malloc(dataSize);
    
    AudioUnitGetProperty(*_unit, kAudioUnitProperty_AudioChannelLayout, kAudioUnitScope_Output, 0, acl, &dataSize);
    
    free(acl);*/
}

// ----------------------------------------------------------
void ofxAudioUnitOutput::listOutputDevices()
// ----------------------------------------------------------
{
	vector<AudioDeviceID> deviceList = AudioOutputDeviceList();
	
	for(int i = 0; i < deviceList.size(); i++) {
		cout << "ID[" << deviceList[i] << "]  \t" << "Name[" << AudioDeviceName(deviceList[i]) << "]\n";
	}
}

#endif // !TARGET_OS_IPHONE
