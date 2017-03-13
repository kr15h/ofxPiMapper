#include "CameraSource.h"

CameraSource::CameraSource(){
	name = "Camera Source";
	
	_cameraWidth = 1280;
    _cameraHeight = 720;
	
	#ifdef TARGET_RASPBERRY_PI
		_omxCameraSettings.width = _cameraWidth;
		_omxCameraSettings.height = _cameraHeight;
		_omxCameraSettings.framerate = 30;
		_omxCameraSettings.enableTexture = true;
		_omxCameraSettings.doRecording = false;
	
		_videoGrabber.setup(_omxCameraSettings);
	#else
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
	#endif

	allocate(_cameraWidth, _cameraHeight);
}

void CameraSource::update(){
	#ifndef TARGET_RASPBERRY_PI
		if(_videoGrabber.isInitialized()){
			_videoGrabber.update();
		}
	#endif
}

void CameraSource::draw(){
	ofClear(0);
	ofSetHexColor(0xffffff);
	#ifdef TARGET_RASPBERRY_PI
		ofDisableNormalizedTexCoords();
		_videoGrabber.draw(0, 0);
		ofEnableNormalizedTexCoords();
	#else
		if(_videoGrabber.isInitialized()){
			ofDisableNormalizedTexCoords();
			_videoGrabber.draw(0, 0);
			ofEnableNormalizedTexCoords();
		}else{
			ofDrawBitmapString("no camera", _cameraWidth / 2.0f - 40.0f, _cameraHeight / 2.0f + 10.0f);
		}
	#endif
}
