
#include "DrawOperation.hpp"

using namespace std;

void traverseLoop(Loop *_loop, string _loop_name)
{
    cout << "-------\t" << _loop_name << "\t--------" << endl;
    HalfEdge *he = _loop->lHalfEdge;
    Vertex *startV = he->startV;
    do
    {
        cout << *(he->startV->point) << endl;
        he = he->nextHe;
    } while (nullptr != he && he->startV != startV);
}

void DrawLoop(Loop *_loop, float _r, float _g, float _b) {
    HalfEdge *he = _loop->lHalfEdge;
    Vertex *startV = he->startV;
    Point *p = nullptr;
    glColor3f(_r, _g, _b);
    glBegin(GL_TRIANGLES);
    do
    {
        p = he->startV->point;
        glVertex3f(p->x, p->y, p->z);
        // cout << *(he->startV->point) << endl;
        he = he->nextHe;
    } while (nullptr != he && he->startV != startV);
    glEnd();
}