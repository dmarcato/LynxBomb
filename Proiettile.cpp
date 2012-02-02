/*
 * Proiettile.cpp
 *
 *  Created on: 14/ago/2010
 *      Author: dario
 */

#include "Proiettile.h"

//Costruttore, inizializzo le variabili
Proiettile::Proiettile(float x, float y, float z, float xd, float yd, float zd): FrameActor() {
	initialSpeed = 0.8;
	speed = initialSpeed;
	distance = 0;
	radius = 0.15;
	xDir = xd;
	yDir = yd;
	zDir = zd;
	setOrigin(x, y, z);
}

//Disegno il proiettile
void Proiettile::draw(void) {
	glPushMatrix();
		setForwardDirection(xDir, yDir - (initialSpeed - speed), zDir);
		moveForward(speed);
		distance += speed;
		speed -= 0.001;
		applyTransform();
		glColor3f(1, 1, 1);
		glutSolidSphere(radius, 25, 43);
	glPopMatrix();
}

//Muovo il proiettile
bool Proiettile::move(void) {
	//Se la velocita si annulla o raggiungo terra, ritorno falso
	if (speed <= 0.01 || getOriginY() < radius) {
		return false;
	}
	return true;
}

//Ritorna il raggio del proiettile
float Proiettile::getRadius(void) {
	return radius;
}

//Distruttore, genera un'esplosione
Proiettile::~Proiettile() {
	addEsplosione(getOriginX(), getOriginY(), getOriginZ());
}
