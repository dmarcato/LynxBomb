/*
 * FrameActor.h
 *
 *  Created on: 13/ago/2010
 *      Author: dario
 */

#ifndef FRAMEACTOR_H_
#define FRAMEACTOR_H_

#include "baseStartup.h"

using std::vector;

class FrameActor {
public:
	FrameActor();
	void applyTransform();
	void applyRotateTransform();
	void applyTranslateTransform();
	void setOrigin(float x, float y, float z);
	void setOriginX(float value);
	void setOriginY(float value);
	void setOriginZ(float value);
	void setForwardDirection(float x, float y, float z);
	void moveForward(float delta);
	void moveRight(float delta);
	void moveUp(float delta);
	void rotate(float angle, float x, float y, float z);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	M3DVector3f* getOrigin(void);
	float getOriginX();
	float getOriginY();
	float getOriginZ();
	virtual float getRadius(void) { return 0; };
protected:
	vector<float*> rotateStack;			//Rotazioni da eseguire
	M3DVector3f moveDirection;			//Direzione di movimento
	M3DVector3f origin;					//Posizione di disegno iniziale
};

#endif /* FRAMEACTOR_H_ */
