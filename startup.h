#ifndef STARTUP_H_
#define STARTUP_H_

#include "baseStartup.h"

using std::vector;
using std::cout;
using std::endl;

//Prototipi classi e funzioni
class Bomba;
class Proiettile;
void addEsplosione(GLfloat, GLfloat, GLfloat);
int getCityPosition();
void addBomba(Bomba*);
void addProiettile(Proiettile*);
void windowSize2d(GLsizei, GLsizei, float, float, float, float);
void windowSize3d(GLsizei, GLsizei);
int getWindowWidth(void);
int getWindowHeight(void);

#include "Esplosione.h"
#include "Bomba.h"
#include "Ufo.h"
#include "Cannone.h"
#include "Sole.h"
#include "Proiettile.h"
#include "Palazzo.h"
#include "Citta.h"

#endif /* STARTUP_H_ */
