/*
 * Palazzo.cpp
 *
 *  Created on: 23/ago/2010
 *      Author: dario
 */

#include "Palazzo.h"

//Costruttore, inizializzo le variabili
Palazzo::Palazzo(float latoPalazzo, float x, float y, float z): FrameActor() {
	setOrigin(x, y, z);
	altezza = rand() % 7 + 2;
	lato = latoPalazzo;
	//Creo un colore casuale
	colore[0] = rand() % 100 / 100.0;
	colore[1] = rand() % 100 / 100.0;
	colore[2] = rand() % 100 / 100.0;
	danni = 0;
}

//Disegna il palazzo
void Palazzo::draw(void) {
	glPushMatrix();
		applyTransform();
		glColor4f(colore[0], colore[1], colore[2], 1.0 - danni);
		glTranslatef(0, altezza / 2.0, 0);
		glScalef(lato, altezza, lato);
		glutSolidCube(1);
	glPopMatrix();
}

//Ritorna la dimensione del lato di base
float Palazzo::getLato(void) {
	return lato;
}

//Ritorna l'altezza del palazzo
float Palazzo::getAltezza(void) {
	return altezza;
}

//Aggiunge danni al palazzo
bool Palazzo::addDamage(float howMuch) {
	danni += howMuch;
	if (danni >= 1) {
		danni = 1;
		return false;
	}
	return true;
}

//Ritorna la vita del palazzo (1-danni)
float Palazzo::getLife(void) {
	return 1.0 - danni;
}
