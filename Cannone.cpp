/*
 * Cannone.cpp
 *
 *  Created on: 13/ago/2010
 *      Author: dario
 */

#include "Cannone.h"

//Struttura dati per vettori a 3 dimensioni
struct Vector3 {
    float x;
    float y;
    float z;
    Vector3() : x(0), y(0), z(0) {}; // initialze when created
};

//Trasforma un angolo di rotazione in un sistema di vettori
void anglesToAxes(const Vector3 angles, Vector3& left, Vector3& up, Vector3& forward) {
    const float DEG2RAD = 3.141593f / 180;
    float sx, sy, sz, cx, cy, cz, theta;

    // rotation angle about X-axis (pitch)
    theta = angles.x * DEG2RAD;
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = angles.y * DEG2RAD;
    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = angles.z * DEG2RAD;
    sz = sinf(theta);
    cz = cosf(theta);

    // determine left axis
    left.x = cy*cz;
    left.y = sx*sy*cz + cx*sz;
    left.z = -cx*sy*cz + sx*sz;

    // determine up axis
    up.x = -cy*sz;
    up.y = -sx*sy*sz + cx*cz;
    up.z = cx*sy*sz + sx*cz;

    // determine forward axis
    forward.x = sy;
    forward.y = -sx*cy;
    forward.z = cx*cy;
}

//Costruttore, inizializzo le variabili
Cannone::Cannone(void): FrameActor() {
	setOrigin(0, 0.5, 0);
	xRot = 0;
	yRot = 0;
	zRot = 0;
	waitTime = 1500;
	lastShoot = glutGet(GLUT_ELAPSED_TIME) - waitTime;
}

//Disegno il mirino del cannone
void Cannone::drawMirino(void) {
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex2f(-0.2, -0.2);
		glVertex2f(0.2, -0.2);

		glVertex2f(0.2, -0.2);
		glVertex2f(0.2, 0.2);

		glVertex2f(0.2, 0.2);
		glVertex2f(-0.2, 0.2);

		glVertex2f(-0.2, 0.2);
		glVertex2f(-0.2, -0.2);

		glVertex2f(0, 0.4);
		glVertex2f(0, -0.4);

		glVertex2f(0.4, 0);
		glVertex2f(-0.4, 0);
	glEnd();
	glEnable(GL_LIGHTING);
}

//Disegno il cannone
void Cannone::draw(void) {
	glPushMatrix();
		rotateX(xRot);
		rotateY(yRot);
		rotateZ(zRot);
		applyTransform();
		glColor3f(0.6, 0.6, 0.6);
		glutSolidSphere(0.35, 25, 43);
		switch (getCityPosition()) {
		case 0:
			glPushMatrix();
				glTranslatef(0, 0, -28);
				drawMirino();
			glPopMatrix();
			glTranslatef(0, 0, -0.6);
			glScalef(1, 1, 2.5);
			break;
		case 1:
			glPushMatrix();
				glTranslatef(28, 0, 0);
				glRotatef(90, 0, 1, 0);
				drawMirino();
			glPopMatrix();
			glTranslatef(0.6, 0, 0);
			glScalef(2.5, 1, 1);
			glRotatef(90, 0, 1, 0);
			break;
		case 2:
			glPushMatrix();
				glTranslatef(0, 0, 28);
				drawMirino();
			glPopMatrix();
			glTranslatef(0, 0, 0.6);
			glScalef(1, 1, 2.5);
			break;
		case 3:
			glPushMatrix();
				glTranslatef(-28, 0, 0);
				glRotatef(90, 0, 1, 0);
				drawMirino();
			glPopMatrix();
			glTranslatef(-0.6, 0, 0);
			glScalef(2.5, 1, 1);
			glRotatef(90, 0, 1, 0);
			break;
		}
		glutSolidTorus(0.25, 0.30, 25, 43);
	glPopMatrix();
}

//Ruoto il cannone lungo i 3 assi
void Cannone::rotate(float x, float y, float z) {
	xRot = x;
	yRot = y;
	zRot = z;
}

//Sparo un proiettile
void Cannone::shoot(void) {
	if (getElapsedTime() < waitTime) {
		//Il cannone si sta ancora ricaricando, impossibile sparare
		return;
	}
	lastShoot = glutGet(GLUT_ELAPSED_TIME);

	Vector3 angles, left, up, forward;
	angles.x = xRot;
	angles.y = yRot;
	angles.z = zRot;
	//Ottengo il sistema di riferimento per orientare il proiettile dagli angoli di rotazione
	anglesToAxes(angles, left, up, forward);

	float startX = getOriginX();
	float startY = getOriginY();
	float startZ = getOriginZ();

	//Creo il proiettile ed imposto la sua direzione
	switch (getCityPosition()) {
	case 0:
		addProiettile(new Proiettile(startX, startY, startZ, -forward.x, -forward.y, -forward.z));
		break;
	case 1:
		addProiettile(new Proiettile(startX, startY, startZ, left.x, left.y, left.z));
		break;
	case 2:
		addProiettile(new Proiettile(startX, startY, startZ, forward.x, forward.y, forward.z));
		break;
	case 3:
		addProiettile(new Proiettile(startX, startY, startZ, -left.x, -left.y, -left.z));
		break;
	}

}

//Ritorna il tempo trascorso per la ricarica
int Cannone::getElapsedTime(void) {
	if (glutGet(GLUT_ELAPSED_TIME) - lastShoot < waitTime) {
		return glutGet(GLUT_ELAPSED_TIME) - lastShoot;
	} else {
		return waitTime;
	}
}

//Ritorna il tempo necessario per la ricarica
int Cannone::getWaitTime(void) {
	return waitTime;
}
