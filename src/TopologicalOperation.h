#include <iostream>

using namespace std;

class Solid;
class Face;
class Loop;
class HalfEdge;
class Edge;
class Vertex;
class Edge;
class Point;

class Vector
{
public:
  Vector(double _x = 0.0, double _y = 0.0, double _z = 0.0) : x(_x), y(_y), z(_z) {}
  double x, y, z;
  Vector operator+(const Vector &_v)
  {
    Vector temp;
    temp.x = this->x + _v.x;
    temp.y = this->y + _v.y;
    temp.z = this->z + _v.z;
    return temp;
  }

  Vector operator-(const Vector &_v)
  {
    Vector temp;
    temp.x = this->x - _v.x;
    temp.y = this->y - _v.y;
    temp.z = this->z - _v.z;
    return temp;
  }
};
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
};

class Loop
{
public:
  Loop() : lFace(nullptr), prevL(nullptr), nextL(nullptr), lHalfEdge(nullptr) {}
  Face *lFace;
  Loop *prevL, *nextL;
  HalfEdge *lHalfEdge;
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
  Point() : x(0.0), y(0.0), z(0.0) {}
  Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  void SetPoint(double _x, double _y, double _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }
  void SetPoint(Point _point)
  {
    x = _point.x;
    y = _point.y;
    z = _point.z;
  }
  friend inline ostream &operator<<(ostream &os, Point &point)
  {
    os << "( " << point.x << ", " << point.y << ", " << point.z << " )";
    return os;
  }
  double x, y, z;
};

Solid *mvfs(Point _point, Vertex *&_vertex);
HalfEdge *mev(Vertex *_vertex, Point _point, Loop *_loop);
Loop *mef(Vertex *_vertex_1, Vertex *_vertex_2, Loop *_loop);
Loop *kemr(Vertex *_vertex_1, Vertex *_vertex_2, Loop *_loop);
void kfmrh(Loop *_outter_loop, Loop *_inner_loop);
Solid *sweep(Face *_face, Vector direction, double distance);