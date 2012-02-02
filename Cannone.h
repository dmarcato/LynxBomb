/*
 * Cannone.h
 *
 *  Created on: 13/ago/2010
 *      Author: dario
 */

#ifndef CANNONE_H_
#define CANNONE_H_

#include "startup.h"
#include "Proiettile.h"

class Cannone: public FrameActor {
public:
	Cannone(void);
	void drawMirino(void);
	void draw(void);
	void rotate(float x, float y, float z);
	void shoot(void);
	int getElapsedTime(void);
	int getWaitTime(void);
private:
	float xRot;				//Rotazione sull'asse x
	float yRot;				//Rotazione sull'asse y
	float zRot;				//Rotazione sull'asse z
	int lastShoot;			//Tempo ultimo colpo sparato
	int waitTime;			//Tempo di ricarica dei colpi
};

#endif /* CANNONE_H_ */
