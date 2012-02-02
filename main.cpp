#include "startup.h"
#include "Collisioni.h"

#define NUM_UFO 3

Sole sun;											//Oggetto sole
vector<Ufo*> ufo;									//Vettore contenente gli ufo
vector<Esplosione*> esplosioni;						//Vettore contenente le esplosioni da mostrare
vector<Bomba*> bombe;								//Vettore contenente le bombe che cadono
vector<Proiettile*> proiettili;						//Vettore contenente i proiettili sparati
Cannone cannon;										//Oggetto cannone
vector<Citta*> cittadelle;							//Vettore contenente le citta con i palazzi

float zoomStep = 1.0;								//Fattore di zoom

int windowWidth = 800;								//Larghezza finestra
int windowHeight = 600;								//Altezza finestra

int cityPosition = 0;								//A quale citta sto puntando

//Imposto i valori per la luce
GLfloat backColor[] = {0, 0, 0.1};
GLfloat specref[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

//Imposto i valori per il punto di vista
float cityPos[4][3] = {
	{ 0, 3.5, 4.5 },
	{ -4.5, 3.5, 0 },
	{ 0, 3.5, -4.5 },
	{ 4.5, 3.5, 0 }
};
float centerPos[4][3] = {
	{ 0, 2.0, 0.3 },
	{ -0.3, 2.0, 0 },
	{ 0, 2.0, -0.3 },
	{ 0.3, 2.0, 0 }
};
GLdouble eyeX = cityPos[0][0];
GLdouble eyeY = cityPos[0][1];
GLdouble eyeZ = cityPos[0][2];
GLdouble centerX = centerPos[0][0];
GLdouble centerY = centerPos[0][1];
GLdouble centerZ = centerPos[0][2];
GLdouble upX = 0.0;
GLdouble upY = 1.0;
GLdouble upZ = 0.0;

//Ritorna la citta attualmente puntata
int getCityPosition() {
	int pos = cityPosition % 4;
	if (pos < 0) pos = 4 + pos;
	return pos;
}

//Aggiunge un'esplosione alla scena alle coordinate specificate
void addEsplosione(GLfloat x, GLfloat y, GLfloat z) {
	esplosioni.push_back(new Esplosione(x, y, z));
}

//Aggiunge una bomba alla scena
void addBomba(Bomba* b) {
	bombe.push_back(b);
}

//Aggiunge un proiettile alla scena
void addProiettile(Proiettile* p) {
	proiettili.push_back(p);
}

//Ritorna la larghezza della finestra
int getWindowWidth(void) {
	return windowWidth;
}

//Ritorna l'altezza della finestra
int getWindowHeight(void) {
	return windowHeight;
}

//Inizializza i parametri per OpenGL
void setupGL(void) {
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	//Attivo trasparenza
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Imposto materiali
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glEnable(GL_NORMALIZE);

	//Imposta il colore di sfondo
	glClearColor(backColor[0], backColor[1], backColor[2], 1.0f);
	//Imposto wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Imposto nebbia
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, backColor);
	glFogf(GL_FOG_START, 48.0f);
	glFogf(GL_FOG_END, 65.0f);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	//Nascondo il cursore
	glutSetCursor(GLUT_CURSOR_NONE);

	//Creo gli ufo
	for (int i = 0; i < NUM_UFO; i++) {
		GLfloat orbit = -36 + i * 3.0;//(-200 + ((rand() % 100) - 50)) * 0.1f;
		ufo.push_back(new Ufo(orbit, i+1));
	}

	//Creo le citta
	for (int i = 0; i < 4; i++) {
		cittadelle.push_back(new Citta(30, i));
	}

}

//Disegno il pavimento
void drawGround(void) {
	GLfloat fExtent = 50.0f;
	GLfloat fStep = 1.0f;
	GLfloat y = 0.0;
	GLfloat iStrip, iRun;

	for (iStrip = -fExtent; iStrip <= fExtent; iStrip += fStep) {
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glColor3f(100.0 / 255, 59.0 / 255, 19.0 / 255);
			for (iRun = fExtent; iRun >= -fExtent; iRun -= fStep) {
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(iStrip, y, iRun);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(iStrip + fStep, y, iRun);
			}
		glEnd();
	}
}

//Imposta una visuale bidimensionale
void windowSize2d(GLsizei w, GLsizei h, float left, float right, float bottom, float top) {
	//Evita divisione per 0
	if (h == 0) h = 1;

	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;

	//Imposta il viewport alle dimensioni della finestra
	glViewport(0, 0, w, h);

	//Resetta il sistema di coordinate
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Calcola il volume di clipping
	if (windowWidth <= windowHeight) {
		glOrtho(left, right, bottom / aspectRatio, top / aspectRatio, 1.0, -1.0);
	} else {
		glOrtho(left, right * aspectRatio , bottom, top, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Disabilito luci, nebbia e profondita per il 2D
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	glDisable(GL_DEPTH_TEST);
}

//Imposta una visuale tridimensionale
void windowSize3d(GLsizei w, GLsizei h) {
	windowWidth = w;
	windowHeight = h;

	//Evita divisione per 0
	if (h == 0) h = 1;

	glViewport(0, 0, w, h);

	GLfloat fAspect = (GLfloat)w / (GLfloat)h;

	//Resetta il sistema di coordinate
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Calcola il volume di clipping
	gluPerspective(35.0f, fAspect, 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Imposto il punto di vista
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY,upZ);

	//Abilito luci, nebbia e profondita per il 3D
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
	glEnable(GL_DEPTH_TEST);
}

//Disegna una minimappa per segnalare ufo e bombe
void drawMinimap(void) {
	//Imposto la visuale 2D
	windowSize2d(windowWidth, windowHeight, -10, 100, -10, 100);

	//Sfondo
	glPushMatrix();
		glTranslatef(-10, -10, 0);
		glColor4f(1, 1, 1, 0.2);
		glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(20, 0);
			glVertex2f(20, 20);
			glVertex2f(0, 20);
		glEnd();
	glPopMatrix();

	//Segno la visuale
	glPushMatrix();
		glRotatef(-90 * cityPosition, 0, 0, 1);
		glTranslatef(0, 0, -1);
		glColor4f(0.3, 0.3, 0.3, 0.2);
		glBegin(GL_TRIANGLES);
			glVertex2f(0, 0);
			glVertex2f(9, 9);
			glVertex2f(-9, 9);
		glEnd();
	glPopMatrix();

	//Segno le bombe
	for (vector<Bomba*>::iterator i = bombe.begin(); i < bombe.end(); i++) {
		glPushMatrix();
			glTranslatef((*i)->getOriginX() * 10 / 42, -(*i)->getOriginZ() * 10 / 42, -1);
			glColor4f(1, 0, 0, 0.7);
			glBegin(GL_QUADS);
				glVertex2f(0, 0);
				glVertex2f(0.5, 0);
				glVertex2f(0.5, 0.5);
				glVertex2f(0, 0.5);
			glEnd();
		glPopMatrix();
	}

	//Segno gli ufo
	for (vector<Ufo*>::iterator i = ufo.begin(); i < ufo.end(); i++) {
		glPushMatrix();
			glTranslatef((*i)->getRealX() * 10 / 42, -(*i)->getRealZ() * 10 / 42, -1);
			glColor4f(0, 0, 1, 0.7);
			glBegin(GL_QUADS);
				glVertex2f(0, 0);
				glVertex2f(0.5, 0);
				glVertex2f(0.5, 0.5);
				glVertex2f(0, 0.5);
			glEnd();
		glPopMatrix();
	}

	//Ritorno alla visuale 3D
	windowSize3d(windowWidth, windowHeight);
}

//Disegna la barra di caricamento per sparare i colpi
void drawLoadingBar(void) {
	//Imposto la visuale 2D
	windowSize2d(windowWidth, windowHeight, -100, 90, -0.5, 100);

	//Sfondo
	glPushMatrix();
		glTranslatef(-0.2, -0.1, 0);
		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(20.4, 0);
			glVertex2f(20.4, 3.3);
			glVertex2f(0, 3.3);
		glEnd();
	glPopMatrix();

	//Barra percentuale
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glColor4f(1, 0, 1, 0.6);
		glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f((20 * cannon.getElapsedTime()) / cannon.getWaitTime(), 0);
			glVertex2f((20 * cannon.getElapsedTime()) / cannon.getWaitTime(), 3);
			glVertex2f(0, 3);
		glEnd();
	glPopMatrix();

	//Ritorno alla visuale 3D
	windowSize3d(windowWidth, windowHeight);
}

//Disegno le barre della vita delle citta
void drawCityLife(void) {
	//Imposto la visuale 2D
	windowSize2d(windowWidth, windowHeight, -100, 12.5, -0.5, 100);

	int k = 0, vitaTot = 0;
	for (vector<Citta*>::iterator i = cittadelle.begin(); i < cittadelle.end(); i++) {
		vitaTot += (*i)->getLife();

		//Sfondo
		glPushMatrix();
			glTranslatef(-0.2 + 4 * k, -0.1, 0);
			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
				glVertex2f(0, 0);
				glVertex2f(3.3, 0);
				glVertex2f(3.3, 20.4);
				glVertex2f(0, 20.4);
			glEnd();
		glPopMatrix();

		//Percentuale vita cittadella
		glPushMatrix();
			glTranslatef(4 * k++, 0, 0);
			glColor4f(0, 1, 0, 0.6);
			glBegin(GL_QUADS);
				glVertex2f(0, 0);
				glVertex2f(3, 0);
				glVertex2f(3, 20 * (*i)->getLife());
				glVertex2f(0, 20 * (*i)->getLife());
			glEnd();
		glPopMatrix();
	}

	if (vitaTot == 0) {
		//Termino il programma
		cout << "Citta' distrutte!" << endl;
		exit(0);
	}

	//Ritorno alla visuale 3D
	windowSize3d(windowWidth, windowHeight);
}

//Disegno la scena attuale
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Controllo collisioni
	checkSphereCollision(&proiettili, &bombe);
	checkPlaneCollision(&proiettili, &cittadelle);
	checkPlaneCollision(&bombe, &cittadelle);

	glPushMatrix();
		//Disegno il sole
		sun.draw();

		//Disegno il pavimento
		drawGround();

		//Disegno le città
		for (vector<Citta*>::iterator i = cittadelle.begin(); i < cittadelle.end(); i++) {
			(*i)->draw();
		}

		//Disegno gli ufo
		for (vector<Ufo*>::iterator i = ufo.begin(); i < ufo.end(); i++) {
			(*i)->draw();
		}

		//Disegno le bombe
		for (vector<Bomba*>::iterator i = bombe.begin(); i < bombe.end(); i++) {
			(*i)->draw();
		}

		//Disegno i proiettili
		for (vector<Proiettile*>::iterator i = proiettili.begin(); i < proiettili.end(); i++) {
			(*i)->draw();
		}

		//Disegno le eventuali esplosioni
		for (vector<Esplosione*>::iterator i = esplosioni.begin(); i < esplosioni.end(); i++) {
			if (!(*i)->draw()) {
				delete *i;
				esplosioni.erase(i);
			}
		}

		//Disegno il cannone
		cannon.draw();
	glPopMatrix();

	//Disegno la minimappa
	drawMinimap();
	//Disegno il tempo di ricarica
	drawLoadingBar();
	//Disegno la vita delle cittadelle
	drawCityLife();

	glutSwapBuffers();
}

//Imposto la visuale verso la citta scelta
void setCityView() {
	int pos = getCityPosition();
	eyeX = cityPos[pos][0];
	eyeY = cityPos[pos][1];
	eyeZ = cityPos[pos][2];
	centerX = centerPos[pos][0];
	centerY = centerPos[pos][1];
	centerZ = centerPos[pos][2];

	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY,upZ);
	glutPostRedisplay();
}

//Gestione tasti
void normalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:	//Tasto esc, chiudo il programma
		exit(0);
		break;
	case 'a':	//Mi sposto sulla citta a sinistra
		cityPosition--;
		setCityView();
		break;
	case 'd':	//Mi sposto sulla citta a destra
		cityPosition++;
		setCityView();
		break;
	case 'w': //Wheel up, zoom in
		if (cityPos[0][2] > zoomStep) {
			cityPos[0][2] -= zoomStep;
			cityPos[1][0] += zoomStep;
			cityPos[2][2] += zoomStep;
			cityPos[3][0] -= zoomStep;
			setCityView();
		}
		break;
	case 's': //Wheel down, zoom out
		if (cityPos[0][2] < 50) {
			cityPos[0][2] += zoomStep;
			cityPos[1][0] -= zoomStep;
			cityPos[2][2] -= zoomStep;
			cityPos[3][0] += zoomStep;
			setCityView();
		}
		break;
	}
}

//Funzione temporizzata per muovere gli oggetti
void animate(int value) {
	//Sposto gli ufo e genero bombe
	for (vector<Ufo*>::iterator i = ufo.begin(); i < ufo.end(); i++) {
		(*i)->move();
		(*i)->dropBomb();
	}

	//Faccio cadere le bombe
	for (vector<Bomba*>::iterator i = bombe.begin(); i < bombe.end(); i++) {
		if (!(*i)->fall()) {
			delete *i;
			bombe.erase(i);
		}
	}

	//Muovo i proiettili
	for (vector<Proiettile*>::iterator i = proiettili.begin(); i < proiettili.end(); i++) {
		if (!(*i)->move()) {
			delete *i;
			proiettili.erase(i);
		}
	}

	//Muovo il sole
	sun.move();

	glutPostRedisplay();
	glutTimerFunc(33, animate, 1);
}

//Gestione movimento mouse, ricalcolo il punto di vista in base alle coordinate del mouse
void mouseMove(int x, int y) {
	GLdouble z = 0.01;
	x = windowWidth - x;
	glReadPixels (x, y, 1, 1, GL_DEPTH_COMPONENT, GL_DOUBLE, &z);

	GLdouble objX, objY, objZ;
	GLdouble mv[16], pm[16];
	GLint vp[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);
	glGetIntegerv(GL_VIEWPORT, vp);
	gluUnProject(x, y, z, mv, pm, vp, &objX, &objY, &objZ);

	float yCalc = ((windowHeight / 2.0f) - y) / (windowHeight / 2.0f);
	float xCalc = -((windowWidth / 2.0f) - x) / (windowWidth / 2.0f);
	if (yCalc < 0) yCalc = 0;
	if (yCalc > 0.6) yCalc = 0.6;
	if (xCalc > 0.73) xCalc = 0.73;
	if (xCalc < -0.73) xCalc = -0.73;
	float xRot = 0;
	float yRot = asin(xCalc);
	float zRot = 0;
	switch (getCityPosition()) {
	case 0:
		eyeX = objX;
		xRot = asin(yCalc);
		break;
	case 1:
		eyeZ = objZ;
		zRot = asin(yCalc);
		break;
	case 2:
		eyeX = objX;
		xRot = -asin(yCalc);
		break;
	case 3:
		eyeZ = objZ;
		zRot = -asin(yCalc);
		break;
	}
	eyeY = objY;

	//Ruoto il cannone verso la direzione del mouse
	cannon.rotate(m3dRadToDeg(xRot), m3dRadToDeg(yRot), m3dRadToDeg(zRot));

	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY,upZ);
	glutPostRedisplay();
}

//Gestione tasti del mouse
void mouseClick(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:	//Tasto sinistro del mouse, sparo
			cannon.shoot();
			break;
		case 3: //Wheel up, zoom in
			if (cityPos[0][2] > zoomStep) {
				cityPos[0][2] -= zoomStep;
				cityPos[1][0] += zoomStep;
				cityPos[2][2] += zoomStep;
				cityPos[3][0] -= zoomStep;
				setCityView();
			}
			break;
		case 4: //Wheel down, zoom out
			if (cityPos[0][2] < 50) {
				cityPos[0][2] += zoomStep;
				cityPos[1][0] -= zoomStep;
				cityPos[2][2] -= zoomStep;
				cityPos[3][0] += zoomStep;
				setCityView();
			}
			break;
		}
	}
}

int main(int argc, char *argv[]) {

	//Inizializzo il random
	srand(time(0));

	//Inizializzo GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("LynxBomb");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(windowSize3d);
	glutKeyboardFunc(normalKeys);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
	glutTimerFunc(33, animate, 1);

	setupGL();

	//Stampo alcune informazioni a console
	cout << "Obiettivo del gioco: difendere le citta' dalle bombe." << endl;
	cout << "Comandi:" << endl;
	cout << "Movimento mouse: ruoto il cannone" << endl;
	cout << "Tasto sinistro del mouse: sparo" << endl;
	cout << "'a': sposta la visuale sulla citta' di sinistra" << endl;
	cout << "'d': sposta la visuale sulla citta' di destra" << endl;
	cout << "'w' o rotellina su: aumenta lo zoom" << endl;
	cout << "'s' o rotellina giu': diminuisci lo zoom" << endl;
	cout << "esc: esci dal gioco" << endl;

	glutMainLoop();

	return 0;
}
