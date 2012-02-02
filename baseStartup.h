#ifndef BASESTARTUP_H_
#define BASESTARTUP_H_

// Bring in OpenGL
// Windows
#ifdef WIN32
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include <gl\glut.h>		// Glut (Free-Glut on Windows)
#endif

// Mac OS X
#ifdef __APPLE__
#include <OpenGL/gl.h>		// Apple OpenGL haders (version depends on OS X SDK version)
#include <OpenGL/glu.h>		// OpenGL Utilities
#include <Glut/glut.h>		// Apples Implementation of GLUT

// Just ignore sleep on Apple
#define Sleep(x)

#endif

#ifdef linux
#include <GL/glut.h>
#include <stdlib.h>

// Just ignore sleep in linux too
#define Sleep(x)
#endif

// Altre librerie
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <sstream>

#include "math3d.h"

#include "FrameActor.h"

#endif /* BASESTARTUP_H_ */
