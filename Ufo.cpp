/*
 * Ufo.cpp
 *
 *  Created on: 12/ago/2010
 *      Author: dario
 */

#include "Ufo.h"

//Costruttore, inizializzo le variabili e genero la sua luce
Ufo::Ufo(GLfloat o, int num): FrameActor() {
	lastBombTime = glutGet(GLUT_ELAPSED_TIME);
	changeDirTime = lastBombTime;
	speed = ((rand() % 20) * 0.1f) + 0.5f;
	iRadius = 0.3f;
	oRadius = 1.2f;
	orbit = o;
	yRot = 0;
	setOrigin(0, 12, orbit);

	//Imposto il valore della luce
	switch (num) {
	case 1:
		myLight = GL_LIGHT1;
		break;
	case 2:
		myLight = GL_LIGHT2;
		break;
	case 3:
		myLight = GL_LIGHT3;
		break;
	}

	//Attivo la luce per l'ufo
	GLfloat spotDir[4] = { 0, -1, 0 };
	GLfloat diffuseLight[4] = { 0, 0, 1, 1.0f };
	GLfloat specular[4] = { 0, 0, 1, 1.0f };
	glLightf(myLight, GL_SPOT_CUTOFF, 5.0f);
	glLightfv(myLight, GL_SPOT_DIRECTION, spotDir);
	glLightfv(myLight, GL_DIFFUSE, diffuseLight);
	glLightfv(myLight, GL_SPECULAR, specular);
	glEnable(myLight);
}

//Disegno l'ufo
void Ufo::draw(void) {
	//Posiziono la luce all'altezza dell'ufo
	GLfloat lightPos[4] = { getRealX(), getRealY(), getRealZ(), 1 };
	glLightfv(myLight, GL_POSITION, lightPos);

	glPushMatrix();
		rotateY(yRot);
		applyRotateTransform();
		applyTranslateTransform();
		rotateX(90);
		applyRotateTransform();
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glutSolidTorus(iRadius, oRadius, 10, 20);
	glPopMatrix();
}

//Muovo l'ufo
void Ufo::move(void) {
	int diff = (((rand() % 600) * 0.1f) + 15) * 1000;
	if ((glutGet(GLUT_ELAPSED_TIME) - changeDirTime) > diff) {
		//Cambio la direzione di movimento
		changeDirTime = time(0);
		speed = -speed;
	}
	yRot += speed;
}

//Sgancia una nuova bomba nella posizione attuale
void Ufo::dropBomb(void) {
	int diff = ((rand() % 30) + 5) * 1000;
	if ((glutGet(GLUT_ELAPSED_TIME) - lastBombTime) > diff) {
		//Genero la bomba solo se e' passato un tempo sufficiente
		createBomb();
	}
}

//Ritorna la vera coordinata X della posizione dell'ufo in base alla sua rotazione attuale
float Ufo::getRealX(void) {
	return sin(m3dDegToRad(yRot)) * orbit;
}

//Ritorna la vera coordinata Y della posizione dell'ufo in base alla sua rotazione attuale
float Ufo::getRealY(void) {
	return getOriginY();
}

//Ritorna la vera coordinata Z della posizione dell'ufo in base alla sua rotazione attuale
float Ufo::getRealZ(void) {
	return cos(m3dDegToRad(yRot)) * orbit;
}

//Genera una bomba
void Ufo::createBomb(void) {
	lastBombTime = time(0);
	addBomba(new Bomba(getRealX(), getRealY(), getRealZ()));
}
