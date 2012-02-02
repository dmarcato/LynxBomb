/*
 * Bomba.cpp
 *
 *  Created on: 11/ago/2010
 *      Author: dario
 */

#include "Bomba.h"

//Costruttore, inizializzo le variabili e posiziono la bomba
Bomba::Bomba(GLfloat x, GLfloat y, GLfloat z): FrameActor() {
	radius = 0.4;
	setOrigin(x, y, z);
	speed = ((rand() % 5) + 3) * 0.005f;
}

//Disegno la bomba
void Bomba::draw(void) {
	glPushMatrix();
		applyTransform();
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glutSolidSphere(radius, 13, 26);
	glPopMatrix();
}

//Faccio cadere la bomba
bool Bomba::fall(void) {
	moveUp(-speed);
	//Se tocca terra, ritorna falso
	if (getOriginY() < radius) {
		return false;
	}
	return true;
}

//Ritorna il raggio della bomba
float Bomba::getRadius(void) {
	return radius;
}

//Distruttore, genero un'esplosione
Bomba::~Bomba() {
	addEsplosione(getOriginX(), getOriginY(), getOriginZ());
}
