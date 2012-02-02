/*
 * Esplosione.h
 *
 *  Created on: 12/ago/2010
 *      Author: dario
 */

#ifndef ESPLOSIONE_H_
#define ESPLOSIONE_H_

#include "startup.h"

class Esplosione: public FrameActor {
public:
	Esplosione(GLfloat x, GLfloat y, GLfloat z);
	bool draw(void);
	virtual ~Esplosione();
private:
	vector<FrameActor*> pezzi;		//Pezzi dell'esplosione
	GLfloat speed;					//Velocita dei pezzi dell'esplosione
	GLfloat radius;					//Raggio dei pezzi dell'esplosione
};

#endif /* ESPLOSIONE_H_ */
