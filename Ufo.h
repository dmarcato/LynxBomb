/*
 * Ufo.h
 *
 *  Created on: 12/ago/2010
 *      Author: dario
 */

#ifndef UFO_H_
#define UFO_H_

#include "startup.h"

class Ufo: public FrameActor {
public:
	Ufo(GLfloat o, int num);
	void draw(void);
	void move(void);
	void dropBomb(void);
	void createBomb(void);
	float getRealX(void);
	float getRealY(void);
	float getRealZ(void);
private:
	int myLight;					//Luce dell'ufo
	GLfloat iRadius;				//Raggio interno dell'ufo
	GLfloat oRadius;				//Raggio esterno dell'ufo
	int lastBombTime;				//Tempo di sgancio dell'ultima bomba
	int changeDirTime;				//Tempo di ultimo cambio senso di rotazione
	GLfloat speed;					//Velocita dell'ufo
	GLfloat orbit;					//Distanza dell'orbita dell'ufo
	GLfloat yRot;					//Rotazione lungo l'asse Y
};

#endif /* UFO_H_ */
