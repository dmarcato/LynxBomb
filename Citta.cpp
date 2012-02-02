/*
 * Citta.cpp
 *
 *  Created on: 23/ago/2010
 *      Author: dario
 */

#include "Citta.h"

//Costruttore, inizializzo le variabili e genero i palazzi
Citta::Citta(float d, int s): FrameActor() {
	numPalazzi = 20;
	distance = d;
	rotation = s * 90;
	larghezza = 30;
	int latoPalazzo = 3;
	for (int i = 0; i < numPalazzi / 2; i++) {
		palazzi.push_back(new Palazzo(latoPalazzo, -larghezza / 2.0 + i * (latoPalazzo + 0.5), 0, 0));
	}
	int k = 0;
	for (int i = numPalazzi / 2; i < numPalazzi; i++) {
		palazzi.push_back(new Palazzo(latoPalazzo, -larghezza / 2.0 + 0.5 + (k++ * (latoPalazzo + 0.5)), 0, -latoPalazzo - 0.5));
	}
}

//Disegno la citta e i palazzi
void Citta::draw(void) {
	glPushMatrix();
		//Ruoto la visuale per disegnare la citta nella posizione corretta
		rotateY(rotation);
		applyRotateTransform();
		setOrigin(0, 0, -distance);
		applyTransform();
		//Disegno i palazzi
		for (vector<Palazzo*>::iterator i = --palazzi.end(); i >= palazzi.begin(); i--) {
			glPushMatrix();
				(*i)->draw();
			glPopMatrix();
		}
	glPopMatrix();
}

//Ritorna la rotazione della citta
int Citta::getRotation(void) {
	return rotation;
}

//Ritorna la vita totale della citta (da 0 a 1)
float Citta::getLife(void) {
	float tot = 0.0f;
	for (vector<Palazzo*>::iterator i = palazzi.begin(); i < palazzi.end(); i++) {
		tot += (*i)->getLife();
	}
	return tot / numPalazzi;
}

//Distruttore, elimino i palazzi generati dalla citta
Citta::~Citta() {
	for (vector<Palazzo*>::iterator i = palazzi.begin(); i < palazzi.end(); i++) {
		delete *i;
	}
}
