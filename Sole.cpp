/*
 * Sole.cpp
 *
 *  Created on: 13/ago/2010
 *      Author: dario
 */

#include "Sole.h"

//Costruttore, inizializzo le variabili
Sole::Sole(): FrameActor() {
	orbit = 50;
	inclinazione = 30;
	daySpeed = 0.08;
	nightSpeed = 0.25;
	zRot = 0;
	day = true;
	setOrigin(-orbit, 0, 0);
}

//Muovo il sole
void Sole::move(void) {
	if (day) {
		zRot -= daySpeed;
	} else {
		zRot -= nightSpeed;
	}
}

//Disegno il sole e la luce
void Sole::draw() {
	//Posiziono la luce in base alla posizione del sole, e la oriento verso la scena
	GLfloat cosX = cos(m3dDegToRad(zRot));
	GLfloat sinY = sin(m3dDegToRad(zRot));
	GLfloat cosInc = cos(m3dDegToRad(inclinazione));
	GLfloat lightPos[4] = { -cosX * orbit * cosInc, -sinY * orbit * cosInc,  orbit * cosInc, 1 };
	GLfloat spotDir[4] = { cosX * cosInc, sinY * cosInc, -1 * cosInc };
	GLfloat diffuseLight[4] = { -sinY * 3, -sinY * 1.6, -sinY * 1.2, 1.0f };
	GLfloat specular[4] = { -sinY * 3, -sinY * 1.6, -sinY * 1.2, 1.0f };

	//Colore del sole e dello sfondo in base alla posizione del sole
	GLfloat sunColor[] = {fabs(sinY) * 3, fabs(sinY) * 1.6, 0};
	GLfloat backColor[] = {fabs(sinY) - 0.5, fabs(sinY) - 0.5, (fabs(sinY) + 0.2)};

	if (lightPos[1] < 0) {
		//Notte, disattivo la luce del sole e tengo solo la luce ambientale per illuminare gli oggetti
		day = false;
		glDisable(GL_LIGHT0);
		sunColor[0] = 0.001 * 3;
		sunColor[1] = 0.001 * 1.6;
		sunColor[2] = 0;
		backColor[0] = 0.001 - 0.5;
		backColor[1] = 0.001 - 0.5;
		backColor[2] = 0.001 + 0.2;
		GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	} else {
		//Giorno, abilito la luce del sole
		day = true;
		glEnable(GL_LIGHT0);
		GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
		//Posizione la sorgente luminosa
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	}

	//Imposto il colore dello sfondo e della nebbia
	glClearColor(backColor[0], backColor[1], backColor[2], 1.0f);
	glFogfv(GL_FOG_COLOR, backColor);

	//Disegno il sole
	glPushMatrix();
		rotateX(inclinazione);
		rotateZ(zRot);
		applyRotateTransform();
		applyTranslateTransform();
		//Disabilito luce e nebbia per disegnare il sole
		glDisable(GL_LIGHTING);
		glDisable(GL_FOG);
		glColor3f(sunColor[0], sunColor[1], sunColor[2]);
		glutSolidSphere(3, 25, 43);
		glEnable(GL_LIGHTING);
		glEnable(GL_FOG);
	glPopMatrix();
}
