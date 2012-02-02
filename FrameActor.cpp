/*
 * FrameActor.cpp
 *
 *  Created on: 13/ago/2010
 *      Author: dario
 */

#include "FrameActor.h"

//Costruttore, inizializzo i vettori
FrameActor::FrameActor() {
	origin[0] = 0.0f;
	origin[1] = 0.0f;
	origin[2] = 0.0f;
	moveDirection[0] = 0.0f;
	moveDirection[1] = 0.0f;
	moveDirection[2] = -1.0f;
}

//Applica tutte le trasformazioni
void FrameActor::applyTransform() {
	applyTranslateTransform();
	applyRotateTransform();
}

//Applica le trasformazioni di rotazione
void FrameActor::applyRotateTransform() {
	for (vector<float*>::iterator i = rotateStack.begin(); i < rotateStack.end(); i++) {
		glRotatef((*i)[0], (*i)[1], (*i)[2], (*i)[3]);
	}
	rotateStack.clear();
}

//Applico le trasformazioni di traslazione
void FrameActor::applyTranslateTransform() {
	glTranslatef(origin[0], origin[1], origin[2]);
}

//Muovo l'oggetto lungo il vettore "up"
void FrameActor::moveUp(float delta) {
	setOrigin(origin[0], origin[1] + delta, origin[2]);
}

//Muovo l'oggetto secondo il vettore di movimento
void FrameActor::moveForward(float delta) {
	setOrigin(origin[0] + (moveDirection[0] * delta), origin[1] + (moveDirection[1] * delta), origin[2] + (moveDirection[2] * delta));
}

//Aggiungo una rotazione generica
void FrameActor::rotate(float angle, float x, float y, float z) {
	float *tmp = new float[4];
	tmp[0] = angle;
	tmp[1] = x;
	tmp[2] = y;
	tmp[3] = z;
	rotateStack.push_back(tmp);
}

//Imposto la direzione di movimento
void FrameActor::setForwardDirection(float x, float y, float z) {
	moveDirection[0] = x;
	moveDirection[1] = y;
	moveDirection[2] = z;
}

//Muovo l'oggetto lungo il vettore "left"
void FrameActor::moveRight(float delta) {
	setOrigin(origin[0] + delta, origin[1], origin[2]);
}

//Imposto l'origine dell'oggetto
void FrameActor::setOrigin(float x, float y, float z) {
	origin[0] = x;
	origin[1] = y;
	origin[2] = z;
}

//Aggiungo una rotazione lungo l'asse Y
void FrameActor::rotateY(float angle) {
	rotate(angle, 0, 1.0, 0);
}

//Aggiungo una rotazione lungo l'asse Z
void FrameActor::rotateZ(float angle) {
	rotate(angle, 0, 0, 1.0);
}

//Aggiungo una rotazione lungo l'asse X
void FrameActor::rotateX(float angle) {
	rotate(angle, 1.0, 0, 0);
}

//Ritorna la coordinata Y dell'origine
float FrameActor::getOriginY() {
	return origin[1];
}

//Ritorna la coordinata Z dell'origine
float FrameActor::getOriginZ() {
	return origin[2];
}

//Ritorna le coordinate dell'origine
M3DVector3f* FrameActor::getOrigin() {
	return &origin;
}

//Ritorna la coordinata X dell'origine
float FrameActor::getOriginX() {
	return origin[0];
}

//Imposta la coordinata Y dell'origine
void FrameActor::setOriginY(float value) {
	origin[1] = value;
}

//Imposta la coordinata Z dell'origine
void FrameActor::setOriginZ(float value) {
	origin[2] = value;
}

//Imposta la coordinata X dell'origine
void FrameActor::setOriginX(float value) {
	origin[0] = value;
}
