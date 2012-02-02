/*
 * Citta.h
 *
 *  Created on: 23/ago/2010
 *      Author: dario
 */

#ifndef CITTA_H_
#define CITTA_H_

#include "startup.h"

class Citta: public FrameActor {
public:
	Citta(float d, int s);
	void draw(void);
	int getRotation(void);
	float getLife(void);
	virtual ~Citta();
	int numPalazzi;					//Numero di palazzi per citta
	vector<Palazzo*> palazzi;		//Vettore contenente i palazzi
private:
	int rotation;					//Angolo di rotazione per il disegno
	float distance;					//Distanza dal cannone
	float larghezza;				//Larghezza della citta
};

#endif /* CITTA_H_ */
