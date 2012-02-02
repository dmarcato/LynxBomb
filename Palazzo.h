/*
 * Palazzo.h
 *
 *  Created on: 23/ago/2010
 *      Author: dario
 */

#ifndef PALAZZO_H_
#define PALAZZO_H_

#include "baseStartup.h"

class Palazzo: public FrameActor {
public:
	Palazzo(float latoPalazzo, float x, float y, float z);
	void draw(void);
	float getLato(void);
	float getAltezza(void);
	bool addDamage(float howMuch);
	float getLife(void);
private:
	float altezza;				//Altezza del palazzo
	float lato;					//Lato della base del palazzo
	float colore[4];			//Colore del palazzo
	float danni;				//Danni subiti dal palazzo
};

#endif /* PALAZZO_H_ */
