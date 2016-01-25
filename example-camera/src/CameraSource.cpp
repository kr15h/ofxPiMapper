#include "CameraSource.h"

CameraSource::CameraSource(){
	name = "Camera Source";
	
	_cameraWidth = 320;
    _cameraHeight = 240;
	
	vector<ofVideoDevice> devices = _videoGrabber.listDevices();
	_cameraFound = false;

	for(int i = 0; i < devices.size(); i++){
		if(devices[i].bAvailable){
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
			_cameraFound = true;
			break;
		}
	}
	
	if(_cameraFound){
		_videoGrabber.setDeviceID(0);
		_videoGrabber.setup(_cameraWidth, _cameraHeight);
	}
	
	allocate(_cameraWidth, _cameraHeight);
}

void CameraSource::update(){
	if(_videoGrabber.isInitialized()){
		_videoGrabber.update();
	}
}

void CameraSource::draw(){
	ofClear(0);
	ofSetHexColor(0xffffff);
	
	if(_videoGrabber.isInitialized()){
		ofDisableNormalizedTexCoords();
		_videoGrabber.draw(0, 0);
		ofEnableNormalizedTexCoords();
	}else{
		ofDrawBitmapString("no camera", _cameraWidth / 2.0f - 40.0f, _cameraHeight / 2.0f + 10.0f);
	}
}