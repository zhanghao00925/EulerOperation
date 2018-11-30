#pragma once

#include <iostream>
#include <string>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Solid;
class Face;
class Loop;
class HalfEdge;
class Edge;
class Vertex;
class Edge;
class Point;

class Scene
{
public:
  Solid *solidList;
};

class Solid
{
public:
  Solid() : prevS(nullptr), nextS(nullptr), sFace(nullptr), edgeList(nullptr) {}
  Solid *prevS, *nextS;
  Face *sFace;
  Edge *edgeList;
};

class Face
{
public:
  Face() : fSolid(nullptr), prevF(nullptr), nextF(nullptr), fLoop(nullptr) {}
  Solid *fSolid;
  Face *prevF, *nextF;
  Loop *fLoop;
  int size();
};

class Loop
{
public:
  Loop() : lFace(nullptr), prevL(nullptr), nextL(nullptr), lHalfEdge(nullptr), innerLoop(false) {}
  Face *lFace;
  Loop *prevL, *nextL;
  HalfEdge *lHalfEdge;
  int size();
  bool innerLoop;
  bool isInnerLoop() const {
    return innerLoop;
  }
  void SetInnerLoop(bool _state) {
    innerLoop = _state;
    return;
  }
};

class HalfEdge
{
public:
  HalfEdge() : heLoop(nullptr), prevHe(nullptr), edge(nullptr), nextHe(nullptr), adjacentHe(nullptr), startV(nullptr), endV(nullptr) {}
  Loop *heLoop;
  HalfEdge *prevHe, *nextHe;
  HalfEdge *adjacentHe;
  Edge *edge;
  Vertex *startV, *endV;
};

class Edge
{
public:
  Edge() : prevE(nullptr), nextE(nullptr), firstHe(nullptr), secondHe(nullptr) {}
  Edge *prevE, *nextE;
  HalfEdge *firstHe, *secondHe;
};

class Vertex
{
public:
  Vertex() : prevV(nullptr), nextV(nullptr), point(nullptr) {}
  Vertex *prevV, *nextV;
  Point *point;
};

class Point
{
public:
  Point() : p(0, 0, 0) {
    color = glm::vec3(rand() % 255 / 255.0f, rand() % 255 / 255.0f, rand() % 255 / 255.0f);
  }
  Point(double _x, double _y, double _z) : p(_x, _y, _z) {}
  void SetPoint(double _x, double _y, double _z)
  {
    p.x = _x;
    p.y = _y;
    p.z = _z;
  }
  void SetPoint(Point _point)
  {
    p.x = _point.p.x;
    p.y = _point.p.y;
    p.z = _point.p.z;
  }
  friend inline ostream &operator<<(ostream &os, Point &point)
  {
    os << "( " << point.p.x << ", " << point.p.y << ", " << point.p.z << " )";
    return os;
  }
  glm::vec3 p;
  glm::vec3 color;
};

Solid *mvfs(Point _point, Vertex *&_vertex);
HalfEdge *mev(Vertex *_vertex, Point _point, Loop *_loop);
Loop *mef(Vertex *_vertex_1, Vertex *_vertex_2, Loop*& _largeLoop);
Loop *kemr(Vertex *_vertex_1, Vertex *_vertex_2, Loop*& _largeLoop);
void kfmrh(Loop *_outter_loop, Loop *_inner_loop);
Solid *sweep(Face *_face, glm::vec3 direction, float distance);

void swapLoop(Loop*& _loop_1, Loop*& _loop_2);

void traverseSolid(Solid *_solid, string _solid_name);
void traverseFace(Face *_face, string _face_name);
void traverseLoop(Loop *_loop, string _loop_name);