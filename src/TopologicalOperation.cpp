#include "TopologicalOperation.h"

Solid *mvfs(Point _point, Vertex *&_vertex)
{
    // Create empty Solid, face and loop
    Solid *newSolid = new Solid();
    Face *newFace = new Face();
    Loop *newLoop = new Loop();

    // Set vertex
    _vertex = new Vertex();
    _vertex->point = new Point();
    _vertex->point->SetPoint(_point);

    // Set ptrs
    newSolid->sFace = newFace;
    newFace->fSolid = newSolid;

    newFace->fLoop = newLoop;
    newLoop->lFace = newFace;

    return newSolid;
}

// 构造一个新点，同时构造一条连接新点和给定点的边
HalfEdge *mev(Vertex *_vertex, Point _point, Loop *_loop)
{
    // Create empty half edge, edge and vertex
    HalfEdge *newHalfEdge_1 = new HalfEdge();
    HalfEdge *newHalfEdge_2 = new HalfEdge();
    Edge *newEdge = new Edge();

    // Set ptrs between half edge
    newEdge->firstHe = newHalfEdge_1;
    newEdge->secondHe = newHalfEdge_2;
    newHalfEdge_1->edge = newEdge;
    newHalfEdge_2->edge = newEdge;
    newHalfEdge_1->adjacentHe = newHalfEdge_2;
    newHalfEdge_2->adjacentHe = newHalfEdge_1;

    // Set ptrs with vertex
    Vertex *newVertex = new Vertex();
    newVertex->point = new Point();
    newVertex->point->SetPoint(_point);

    newHalfEdge_1->startV = _vertex;
    newHalfEdge_1->endV = newVertex;
    newHalfEdge_2->startV = newVertex;
    newHalfEdge_2->endV = _vertex;

    // Set ptrs with loop
    newHalfEdge_1->heLoop = _loop;
    newHalfEdge_2->heLoop = _loop;

    newHalfEdge_1->nextHe = newHalfEdge_2;
    newHalfEdge_2->prevHe = newHalfEdge_1;
    if (nullptr == _loop->lHalfEdge)
    {
        newHalfEdge_2->nextHe = newHalfEdge_1;
        newHalfEdge_1->prevHe = newHalfEdge_2;
        _loop->lHalfEdge = newHalfEdge_1;
    }
    else
    {
        HalfEdge *he;
        for (he = _loop->lHalfEdge; he->nextHe->startV != _vertex; he = he->nextHe)
        {
        }
        newHalfEdge_2->nextHe = he->nextHe;
        he->nextHe->prevHe = newHalfEdge_2;

        newHalfEdge_1->prevHe = he;
        he->nextHe = newHalfEdge_1;
    }

    // Add edge to list
    Solid *oldSolid = _loop->lFace->fSolid;
    Edge *e = oldSolid->edgeList;
    if (nullptr == e)
    {
        oldSolid->edgeList = newEdge;
    }
    else
    {
        while (e->nextE != nullptr)
        {
            e = e->nextE;
        }
        e->nextE = newEdge;
        newEdge->prevE = e;
    }
    return newHalfEdge_1;
}

Loop *mef(Vertex *_vertex_1, Vertex *_vertex_2, Loop *_loop)
{
    Solid *oldSolid = _loop->lFace->fSolid;

    // Create new edge
    HalfEdge *newHalfEdge_1 = new HalfEdge();
    HalfEdge *newHalfEdge_2 = new HalfEdge();
    Edge *newEdge = new Edge();

    // Set edge's ptrs
    newEdge->firstHe = newHalfEdge_1;
    newEdge->secondHe = newHalfEdge_2;
    newHalfEdge_1->edge = newEdge;
    newHalfEdge_2->edge = newEdge;
    newHalfEdge_1->adjacentHe = newHalfEdge_2;
    newHalfEdge_2->adjacentHe = newHalfEdge_1;

    newHalfEdge_1->startV = _vertex_1;
    newHalfEdge_1->endV = _vertex_2;
    newHalfEdge_2->startV = _vertex_2;
    newHalfEdge_2->endV = _vertex_1;

    HalfEdge *he;
    for (he = _loop->lHalfEdge; he->startV != _vertex_1; he = he->nextHe)
    {
    }
    HalfEdge *firstHalfEdge = he;

    for (he = _loop->lHalfEdge; he->startV != _vertex_2; he = he->nextHe)
    {
    }
    HalfEdge *secondHalfEdge = he;

    newHalfEdge_2->nextHe = firstHalfEdge;
    newHalfEdge_2->prevHe = secondHalfEdge->prevHe;
    newHalfEdge_1->nextHe = secondHalfEdge;
    newHalfEdge_1->prevHe = firstHalfEdge->prevHe;
    firstHalfEdge->prevHe->nextHe = newHalfEdge_1;
    firstHalfEdge->prevHe = newHalfEdge_2;
    secondHalfEdge->prevHe->nextHe = newHalfEdge_2;
    secondHalfEdge->prevHe = newHalfEdge_1;

    _loop->lHalfEdge = newHalfEdge_1;
    Loop *newLoop = new Loop();
    newLoop->lHalfEdge = newHalfEdge_2;

    Face *newFace = new Face();
    newFace->fLoop = newLoop;
    newLoop->lFace = newFace;
    newFace->fSolid = oldSolid;

    Face *f;
    for (f = oldSolid->sFace; f->nextF != nullptr; f = f->nextF)
    {
    }
    f->nextF = newFace;
    newFace->prevF = f;

    Edge *e = oldSolid->edgeList;
    if (nullptr == e)
    {
        oldSolid->edgeList = newEdge;
    }
    else
    {
        while (e->nextE != nullptr)
        {
            e = e->nextE;
        }
        e->nextE = newEdge;
        newEdge->prevE = e;
    }

    return newLoop;
}

Loop *kemr(Vertex *_vertex_1, Vertex *_vertex_2, Loop *_loop)
{
    Loop *newLoop = new Loop();

    HalfEdge *he;
    for (he = _loop->lHalfEdge; !(_vertex_1 == he->startV && _vertex_2 == he->endV); he = he->nextHe)
    {
    }

    Edge *e = he->edge;
    he->nextHe->prevHe = he->adjacentHe->prevHe;
    he->adjacentHe->prevHe->nextHe = he->nextHe;

    he->prevHe->nextHe = he->adjacentHe->nextHe;
    he->adjacentHe->nextHe->prevHe = he->prevHe;

    _loop->lHalfEdge = he->prevHe;
    newLoop->lHalfEdge = he->nextHe;

    Face *oldFace = _loop->lFace;
    newLoop->lFace = oldFace;

    Loop *lp;
    for (lp = oldFace->fLoop; nullptr != lp->nextL; lp = lp->nextL)
    {
    }
    lp->nextL = newLoop;
    newLoop->prevL = lp;

    Solid *oldSolid = _loop->lFace->fSolid;
    e = oldSolid->edgeList;
    if (e == he->edge)
    {
        oldSolid->edgeList = he->edge->nextE;
        oldSolid->edgeList->prevE = e->prevE;
    }
    else
    {
        while (e->nextE != he->edge)
        {
            e = e->nextE;
        }
        e->nextE = he->edge->nextE;
        e->nextE->prevE = e;
    }

    return newLoop;
}

void kfmrh(Loop *_outter_loop, Loop *_inner_loop)
{
    Face *face_1 = _outter_loop->lFace;
    Face *face_2 = _inner_loop->lFace;

    Loop *lp;
    for (lp = face_1->fLoop; nullptr != lp->nextL; lp = lp->nextL)
    {
    }
    lp->nextL = _inner_loop;
    _inner_loop->prevL = lp;
    _inner_loop->lFace = face_1;

    // delete face_2;

    Solid *oldSolid = face_1->fSolid;
    Face *f = oldSolid->sFace;
    if (f == face_2)
    {
        oldSolid->sFace = f->nextF;
        oldSolid->sFace->prevF = f->prevF;
    }
    else
    {
        while (f->nextF != face_2)
        {
            f = f->nextF;
        }
        f->nextF = face_2->nextF;
        f->nextF->prevF = f;
    }

    return;
}

Solid *sweep(Face *_face, Vector direction, double distance) {
    
}