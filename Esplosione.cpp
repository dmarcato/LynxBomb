/*
 * Esplosione.cpp
 *
 *  Created on: 12/ago/2010
 *      Author: dario
 */

#include "Esplosione.h"

//Costruttore, genero i pezzi dell'esplosione
Esplosione::Esplosione(GLfloat x, GLfloat y, GLfloat z): FrameActor() {
	setOrigin(x, y, z);
	speed = 0.7f;
	radius = 0.1f;
	for (int i = 0; i < 40; i++) {
		FrameActor* tmp = new FrameActor();
		tmp->setOrigin(x, y, z);
		//Creo una direzione casuale di movimento per i pezzi
		GLfloat yDir = ((rand() % 20) - 10) * 0.1f;
		GLfloat xDir = ((rand() % 20) - 10) * 0.1f;
		GLfloat zDir = ((rand() % 20) - 10) * 0.1f;
		tmp->setForwardDirection(xDir, yDir, zDir);
		pezzi.push_back(tmp);
	}
}

//Disegno i vari pezzi dell'esplosione
bool Esplosione::draw(void) {
	if (radius < 0) {
		//Esplosione terminata
		return false;
	}
	for (vector<FrameActor*>::iterator i = pezzi.begin(); i < pezzi.end(); i++) {
		(*i)->moveForward(speed);
		glPushMatrix();
			(*i)->applyTransform();
			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glutSolidSphere(radius, 13, 26);
		glPopMatrix();
	}
	speed -= 0.1f;
	radius -= 0.01f;
	return true;
}

//Distruttore, elimino i pezzi dell'espliosione
Esplosione::~Esplosione() {
	for (vector<FrameActor*>::iterator i = pezzi.begin(); i < pezzi.end(); i++) {
		delete *i;
	}
}
