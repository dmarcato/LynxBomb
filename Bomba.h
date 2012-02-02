/*
 * Bomba.h
 *
 *  Created on: 11/ago/2010
 *      Author: dario
 */

#ifndef BOMBA_H_
#define BOMBA_H_

#include "startup.h"

class Bomba: public FrameActor {
public:
	Bomba(GLfloat x, GLfloat y, GLfloat z);
	void draw(void);
	bool fall(void);
	float getRadius(void);
	virtual ~Bomba();
private:
	GLfloat radius;			//Raggio della bomba
	GLfloat speed;			//Velocita di caduta della bomba
};

#endif /* BOMBA_H_ */
