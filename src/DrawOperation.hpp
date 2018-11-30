#pragma once

#include "TopologicalOperation.hpp"
#include <string>
#include <vector>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// GLFW
#include <GLFW/glfw3.h>
// GLUT
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

void DrawSolid(Solid *_solid, const bool _line = false);
void DrawFace(Face *_face, const bool _line);
void DrawLoop(Loop *_loop);
void DrawLoop2(Loop *_loop);

void CALLBACK tessBeginCB(GLenum which);
void CALLBACK tessEndCB();
void CALLBACK tessErrorCB(GLenum errorCode);
void CALLBACK tessVertexCB(const GLvoid *data);