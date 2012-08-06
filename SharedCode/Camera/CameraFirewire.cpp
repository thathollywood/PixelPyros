/*
 *  CameraFirewire.cpp
 *  PixelPhones
 *
 *  Created by Seb Lee-Delisle on 16/03/2012.
 *  Copyright 2012 seb.ly. All rights reserved.
 *
 */

#include "CameraFirewire.h"

bool CameraFirewire::setup(string _name, int width, int height, int framerate){
	
    //camera.setBayerMode(DC1394_COLOR_FILTER_GBRG);
//    camera.set1394b(true); 

    
	// setup() will pick the first camera. Or if there are multiple cameras you
	// can use the number, or the GUID of the camera.
    if(!camera.setup()) return false;
	
    camera.setBayerMode(DC1394_COLOR_FILTER_GBRG);
    
	
	unsigned int min, max; 
	camera.getBrightnessRawRange(&min, &max);
	cout << "min " << min << " max " << max << endl; 
	//camera.setExposureRaw(1);
    //camera.setFeatureAbs(<#dc1394feature_t feature#>, <#float value#>)tBayerMode(DC1394_COLOR_FILTER_GBRG);
    //camera.setGainRaw(10); 
    //camera.setShutterRaw(130); 
    name = _name; 
    frameNum = 0; 
	
	//curFrame.allocate(width, height, OF_IMAGE_COLOR);
	
	return true; 
	
}
bool CameraFirewire::update() {
	if(camera.grabVideo(curFrame)) {
		curFrame.update();
        
        cout << camera.getFrameRate() << " " << 
                camera.getGainRaw() << " " << 
                camera.getShutterRaw() << " " << 
                camera.getBrightnessRaw() << " " << 
                camera.getExposureRaw() << " " << 
                camera.getGammaRaw() << "\n"; 
                
        return true;
	}	
    return false; 
}

void CameraFirewire::draw(float x, float y) {
	curFrame.draw(x, y); 
}
ofPixelsRef CameraFirewire::getPixelsRef(){
	return curFrame.getPixelsRef();
    
}
int CameraFirewire::getWidth(){
	return camera.getWidth(); 
    
}
int CameraFirewire::getHeight(){
	return camera.getHeight(); 
    
}
bool CameraFirewire::videoSettings(){
	//camera.videoSettings(); 
	
}
void CameraFirewire::close() { 
	
}

int CameraFirewire::getGain() { 
	return camera.getGainRaw(); 
}

void CameraFirewire::setGain(int v) { 
	camera.setGainRaw(v); 
	
	//cout << "gain " << camera.getGainRaw() << "\n"; 
}

int CameraFirewire::getGamma() { 
	return camera.getGammaRaw(); 
}

void CameraFirewire::setGamma(int v) { 
	camera.setGammaRaw(v); 
	
	//cout << "gamma " << camera.getGammaRaw() << "\n"; 
}

int CameraFirewire::getBrightness() { 
	return camera.getBrightnessRaw(); 
}

void CameraFirewire::setBrightness(int v) { 
	camera.setBrightnessRaw(v); 
	
	//cout << "brightness " << camera.getGammaRaw() << "\n"; 
}

int CameraFirewire::getShutter() { 
	return camera.getShutterRaw(); 
}

void CameraFirewire::setShutter(int v) { 
	camera.setShutterRaw(v) ;
	cout << "shutter " << camera.getShutterRaw()<< "\n";  
}
