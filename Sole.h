/*
 * Sole.h
 *
 *  Created on: 13/ago/2010
 *      Author: dario
 */

#ifndef SOLE_H_
#define SOLE_H_

#include "startup.h"

class Sole: public FrameActor {
public:
	Sole();
	void move(void);
	void draw(void);
private:
	float daySpeed;					//Velocita di rotazione di giorno
	float nightSpeed;				//Velocita di rotazione di notte
	float zRot;						//Rotazione lungo l'asse Z
	float orbit;					//Distanza dal centro
	float inclinazione;				//Inclinazione di rotazione
	bool day;						//Giorno o notte?
};

#endif /* SOLE_H_ */
