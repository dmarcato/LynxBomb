/*
 * Proiettile.h
 *
 *  Created on: 14/ago/2010
 *      Author: dario
 */

#ifndef PROIETTILE_H_
#define PROIETTILE_H_

#include "startup.h"

class Proiettile: public FrameActor {
public:
	Proiettile(float x, float y, float z, float xd, float yd, float zd);
	void draw(void);
	bool move(void);
	float getRadius(void);
	virtual ~Proiettile();
private:
	double initialSpeed;			//Velocita iniziale del proiettile
	double speed;					//Velocita attuale del proiettile
	float distance;					//Distanza percorsa dal proiettile
	float radius;					//Raggio del proiettile
	float xDir;						//Direzione lungo l'asse X
	float yDir;						//Direzione lungo l'asse Y
	float zDir;						//Direzione lungo l'asse Z
};

#endif /* PROIETTILE_H_ */
