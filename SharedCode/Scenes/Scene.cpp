//
//  Scene.cpp
//  SceneCalibration
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "Scene.h"


Scene::Scene(ParticleSystemManager & psm, ofRectangle triggerarea) : particleSystemManager(psm) {
    init(triggerarea);
}

Scene::Scene(ParticleSystemManager & psm, ofRectangle triggerarea, SceneShader *sceneShader) : particleSystemManager(psm) {
    init(triggerarea);
    shader = sceneShader;
}

void Scene::init(ofRectangle triggerarea) {
	active = false; 
	stopping = false;
	triggerArea = triggerarea;
	//setTriggerArea(triggerarea);
	currentArrangementIndex = -1;
	activeArrangements = 0;
}

void Scene :: start() {
	stopping = false; 
	if (startArrangement(0)) active = true;
}

void Scene::initShaderParameters() {
    shader->bloomValue = 0.5;
    shader->gammaValue = 1.2;
    shader->blackPoint = 0.0;
    shader->whitePoint = 1.0;
}

SceneShader *Scene::getShader() {
    return shader;
}

void Scene :: stop() { 
	
	for(int i=0; i<arrangements.size(); i++) {

		arrangements[i]->stop();
		
	}
	stopping = true; 
	
}

bool Scene :: update(float deltaTime) {

	if(!active) return false; 
	activeArrangements = 0;
	
	for(int i=0; i<arrangements.size(); i++) {
	
//        if ( updateTriggerArea ) 
//        {
//            std::cout << "updating trigger area" << std::endl;
//            arrangements[i]->updateLayout(triggerArea, arrangements[i]->minimumSpacing);
//        }
//		
//		if ( updateTriggerDebug ) 
//        {
//            std::cout << "updating trigger debug" << std::endl;
//            arrangements[i]->updateDebug(triggerDebug);
//        }
		//if(ofGetMousePressed()) arrangements[i]->updateLayout(triggerArea, max(1, min(300,ofGetMouseY())));
		if( arrangements[i]->update(deltaTime)) activeArrangements++;
		
		//THIS LINE MAKES IT AUTO CONTINUE - maybe a scene flag? 
		//else if ((!stopping) && (i==currentArrangementIndex)) next();
		
	}
	
	
	if((stopping) && (activeArrangements==0) ) {
		active = false;
	}

	return active; 
	
	
}


bool Scene:: draw() {

	if(!active) return false; 
	for(int i=0; i<arrangements.size(); i++) {
		
		arrangements[i]->draw();
		
	}
	
	return true; 

}
void Scene :: updateMotion(MotionManager& motionManager, cv::Mat homography){
	
	for(int i = 0; i<arrangements.size(); i++) {
		
		Arrangement * arrangement = arrangements[i];

		arrangement->updateMotion(motionManager, homography);
		
//		float motion = motionManager.getMotionAtPosition(trigger->pos, trigger->radius*2, homography); 
//		trigger->registerMotion(motion/255);
		
		//cout << motion << endl; 
		
		
	}
	
}

void Scene :: updateTriggerSettings(ofRectangle triggerarea, float spacing){

	for(int i = 0; i<arrangements.size() ; i++) {
		arrangements[i]->updateLayout(triggerarea, spacing);
	}

}

void  Scene :: setShowTriggerDebug(bool showDebug) {
	triggerDebug = showDebug;
	
	for(int i = 0; i<arrangements.size() ; i++) {
		arrangements[i]->updateDebug(triggerDebug);
	}
	
}

void  Scene :: setTriggersDisabled(bool disabled) {
	
	for(int i = 0; i<arrangements.size() ; i++) {
		arrangements[i]->setTriggersDisabled(disabled);
	}
	
}



Arrangement& Scene ::addArrangement(TriggerPattern& pattern, bool fixedPosition) {
	arrangements.push_back(new Arrangement(particleSystemManager, triggerArea, fixedPosition));
	//arrangements.back()->setTriggerArea(triggerArea);
	arrangements.back()->setPattern(pattern, triggerArea, 50);
	
	
}


bool Scene :: startArrangement(int num) {
	
	if((num>=arrangements.size())|| (stopping))  return false;
	if(currentArrangementIndex>=0) {
		arrangements[currentArrangementIndex]->stop();
	}
	
	arrangements[num]->start();
	currentArrangementIndex = num; 
	return true;
	
	
}


bool Scene :: next() {
	if(arrangements.size()==0) return false;
	
	int nextArrangement = currentArrangementIndex+1;
	if(nextArrangement>=arrangements.size())
		nextArrangement = 0;
	
	startArrangement(nextArrangement);
	
	
}

bool Scene :: previous() {

	if(arrangements.size()==0) return false;
	
	int prevArrangement = currentArrangementIndex-1;
	if(prevArrangement<0)
		prevArrangement = arrangements.size();
	
	startArrangement(prevArrangement);


}