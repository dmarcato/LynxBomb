/*
 * Collisioni.h
 *
 *  Created on: 30/ago/2010
 *      Author: dario
 */

#ifndef COLLISIONI_H_
#define COLLISIONI_H_

#include "startup.h"

//Collisioni proiettile-bomba
void checkSphereCollision(vector<Proiettile*>* source, vector<Bomba*>* elements) {
	for (vector<Proiettile*>::iterator i = source->begin(); i < source->end(); i++) {
		for (vector<Bomba*>::iterator j = elements->begin(); j < elements->end(); j++) {
			//Calcolo la distanza tra i centri delle 2 sfere
			double dist = m3dGetDistance(*(*i)->getOrigin(), *(*j)->getOrigin());
			//Se la distanza e' minore della somma dei 2 raggi, la collisione avviene
			if (dist <= (*i)->getRadius() + (*j)->getRadius()) {
				delete *i;
				source->erase(i);
				delete *j;
				elements->erase(j);
				break;
			}
		}
	}
}

//Collisioni bomba-palazzi
void checkPlaneCollision(vector<Bomba*>* source, vector<Citta*>* elements) {
	for (vector<Citta*>::iterator i = elements->begin(); i < elements->end(); i++) {
		float angolo = -m3dDegToRad((*i)->getRotation());
		float cityPos[3];
		//Calcolo la posizione reale della citta
		cityPos[0] = cos(angolo) * (*i)->getOriginX() - sin(angolo) * (*i)->getOriginZ();
		cityPos[1] = (*i)->getOriginY();
		cityPos[2] = sin(angolo) * (*i)->getOriginX() + cos(angolo) * (*i)->getOriginZ();
		for (vector<Palazzo*>::iterator j = (*i)->palazzi.begin(); j < (*i)->palazzi.end(); j++) {
			float dim[3];
			//Calcolo le dimensioni del palazzo
			dim[0] = (*j)->getLato() / 2;
			dim[1] = (*j)->getAltezza();
			dim[2] = (*j)->getLato() / 2;
			for (vector<Bomba*>::iterator k = source->begin(); k < source->end(); k++) {
				float pos[3];
				//Calcolo la posizione reale della bomba rispetto al palazzo
				pos[0] = (*k)->getOriginX() - (cityPos[0] + cos(angolo) * (*j)->getOriginX() - sin(angolo) * (*j)->getOriginZ());
				pos[1] = (*k)->getOriginY() - (cityPos[1] + (*j)->getOriginY());
				pos[2] = (*k)->getOriginZ() - (cityPos[2] + sin(angolo) * (*j)->getOriginX() + cos(angolo) * (*j)->getOriginZ());

				bool beccato = true;
				//Se almeno una coordinata della bomba esce dal palazzo la collisione non avviene
				for (int a = 0; a < 3; a++) {
					if (fabs(pos[a]) > (dim[a] + (*k)->getRadius())) beccato = false;
				}
				if (beccato) {
					delete *k;
					source->erase(k);
					//Aggiungo i danni al palazzo
					if (!(*j)->addDamage(0.25)) {
						delete *j;
						(*i)->palazzi.erase(j);
					}
				}
			}
		}
	}
}

//Collisioni proiettili-palazzi
void checkPlaneCollision(vector<Proiettile*>* source, vector<Citta*>* elements) {
	for (vector<Citta*>::iterator i = elements->begin(); i < elements->end(); i++) {
		float angolo = -m3dDegToRad((*i)->getRotation());
		float cityPos[3];
		//Calcolo la posizione reale della citta
		cityPos[0] = cos(angolo) * (*i)->getOriginX() - sin(angolo) * (*i)->getOriginZ();
		cityPos[1] = (*i)->getOriginY();
		cityPos[2] = sin(angolo) * (*i)->getOriginX() + cos(angolo) * (*i)->getOriginZ();
		for (vector<Palazzo*>::iterator j = (*i)->palazzi.begin(); j < (*i)->palazzi.end(); j++) {
			float dim[3];
			//Calcolo le dimensioni del palazzo
			dim[0] = (*j)->getLato() / 2;
			dim[1] = (*j)->getAltezza();
			dim[2] = (*j)->getLato() / 2;
			for (vector<Proiettile*>::iterator k = source->begin(); k < source->end(); k++) {
				float pos[3];
				//Calcolo la posizione reale del proiettile rispetto al palazzo
				pos[0] = (*k)->getOriginX() - (cityPos[0] + cos(angolo) * (*j)->getOriginX() - sin(angolo) * (*j)->getOriginZ());
				pos[1] = (*k)->getOriginY() - (cityPos[1] + (*j)->getOriginY());
				pos[2] = (*k)->getOriginZ() - (cityPos[2] + sin(angolo) * (*j)->getOriginX() + cos(angolo) * (*j)->getOriginZ());

				bool beccato = true;
				//Se almeno una coordinata del proiettile esce dal palazzo la collisione non avviene
				for (int a = 0; a < 3; a++) {
					if (fabs(pos[a]) > (dim[a] + (*k)->getRadius())) beccato = false;
				}
				if (beccato) {
					delete *k;
					source->erase(k);
					//Aggiungo i danni al palazzo
					if (!(*j)->addDamage(0.15)) {
						delete *j;
						(*i)->palazzi.erase(j);
					}
				}
			}
		}
	}
}

#endif /* COLLISIONI_H_ */
