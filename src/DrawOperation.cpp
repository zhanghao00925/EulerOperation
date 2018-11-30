
#include "DrawOperation.hpp"

using namespace std;

void DrawLoop(Loop *_loop, float _r, float _g, float _b)
{
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out

    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glEnd(); // Begin drawing the color cube with 6 quads
}

void DrawSolid(Solid *_solid, const bool _line)
{
    Face *startF = _solid->sFace;
    Face *f = _solid->sFace;
    do
    {
        if (f != nullptr)
            DrawFace(f, _line);
        f = f->nextF;
    } while (nullptr != f && f != startF);
}

void DrawFace(Face *_face, const bool _line)
{
    Loop *startL;
    Loop *l;

    if (!_line)
    {
        // Draw Inner Loop
        glEnable(GL_STENCIL_TEST);
        glClearStencil(0);
        glClear(GL_STENCIL_BUFFER_BIT);
        // Write 1's into stencil buffer where the hole will be
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_ALWAYS, 1, ~0);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    }
    startL = _face->fLoop;
    l = _face->fLoop;
    do
    {

        if (l != nullptr && l->isInnerLoop())
        {
            if (!_line)
            {
                DrawLoop2(l);
            }
            else
            {
                DrawLoop(l);
            }
        }
        l = l->nextL;
    } while (nullptr != l && l != startL);
    if (!_line)
    {
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilFunc(GL_EQUAL, 0, ~0);
        glDepthMask(GL_TRUE);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    }
    // Draw Outter Loop
    startL = _face->fLoop;
    l = _face->fLoop;
    do
    {
        if (l != nullptr && !l->isInnerLoop())
        {
            if (!_line)
            {
                DrawLoop2(l);
            }
            else
            {
                DrawLoop(l);
            }
        }
        l = l->nextL;
    } while (nullptr != l && l != startL);
    if (!_line)
    {
        glDisable(GL_STENCIL_TEST);
    }
}

void DrawLoop(Loop *_loop)
{

    glBegin(GL_LINE_LOOP); // Begin drawing the color cube with 6 quads
    HalfEdge *startHe = _loop->lHalfEdge;
    HalfEdge *he = _loop->lHalfEdge;
    Vertex *startV = he->startV;
    do
    {
        glm::vec3 point = he->startV->point->p;
        glm::vec3 color = he->startV->point->color;
        glColor3f(1, 0, 0); // Green
        glVertex3f(point.x, point.y, point.z);
        he = he->nextHe;
    } while (nullptr != he && he != startHe);
    glEnd();
}

struct TessData
{
    GLdouble data[6];
    TessData(glm::vec3 point, glm::vec3 color)
    {
        data[0] = point.x;
        data[1] = point.y;
        data[2] = point.z;
        data[3] = color.r;
        data[4] = color.g;
        data[5] = color.b;
    }
};
void DrawLoop2(Loop *_loop)
{
    GLuint id = glGenLists(1); // create a display list
    if (!id)
        return; // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if (!tess)
        return; // failed to create tessellation object, return 0

    GLdouble quad1[6] = {-1, 3, 0, 1, 1, 1};
    GLdouble quad2[6] = {0, 0, 0, 1, 1, 1};
    GLdouble quad3[6] = {1, 3, 0, 1, 1, 1};
    GLdouble quad4[6] = {0, 2, 0, 1, 1, 1};
    GLdouble quad5[6] = {-1, 5, 0, 1, 1, 1};

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK *)())tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK *)())tessEndCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK *)())tessVertexCB);

    glNewList(id, GL_COMPILE);
    glColor3f(1, 1, 1);
    gluTessBeginPolygon(tess, 0); // with NULL data
    gluTessBeginContour(tess);
    HalfEdge *startHe = _loop->lHalfEdge;
    HalfEdge *he = _loop->lHalfEdge;
    Vertex *startV = he->startV;
    vector<TessData> quadList;
    do
    {
        glm::vec3 point = he->startV->point->p;
        glm::vec3 color = he->startV->point->color;
        TessData data(point, color);
        quadList.push_back(data);
        he = he->nextHe;
    } while (nullptr != he && he != startHe);
    for (int i = 0; i < quadList.size(); i++)
    {
        gluTessVertex(tess, quadList[i].data, quadList[i].data);
    }
    // gluTessVertex(tess, quad1, quad1);
    // gluTessVertex(tess, quad2, quad2);
    // gluTessVertex(tess, quad3, quad3);
    // gluTessVertex(tess, quad4, quad4);
    // gluTessVertex(tess, quad5, quad5);

    gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();

    gluDeleteTess(tess); // delete after tessellation

    glCallList(id);
}

GLuint tessellate1()
{
}

///////////////////////////////////////////////////////////////////////////////
// GLU_TESS CALLBACKS
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessBeginCB(GLenum which)
{
    glBegin(which);
}

void CALLBACK tessEndCB()
{
    glEnd();
}

void CALLBACK tessVertexCB(const GLvoid *data)
{
    // cast back to double type
    const GLdouble *ptr = (const GLdouble *)data;

    glColor3dv(ptr + 3);
    glVertex3dv(ptr);
}
