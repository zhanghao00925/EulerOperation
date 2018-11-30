#pragma once

#include "TopologicalOperation.hpp"
#include "DrawOperation.hpp"

Solid *CreateZero()
{
    Solid *newSolid;

    Vertex *topUpperLeft;
    newSolid = mvfs(Point(-1.0, 0.5, 2.0), topUpperLeft);
    Loop *topLoop = newSolid->sFace->fLoop;
    HalfEdge *topUpperHalfEdge = mev(topUpperLeft, Point(1.0, 0.5, 2.0), topLoop);
    Vertex *topUpperRight = topUpperHalfEdge->endV;
    HalfEdge *topLeftHalfEdge = mev(topUpperLeft, Point(-1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomLeft = topLeftHalfEdge->endV;
    HalfEdge *topRightHalfEdge = mev(topUpperRight, Point(1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomRight = topRightHalfEdge->endV;
    // Make top ring
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    HalfEdge *upperLeftHalfEdge = mev(topUpperLeft, Point(-1.0, -0.5, 2.0), downLoop);
    Vertex *downUpperLeft = upperLeftHalfEdge->endV;
    HalfEdge *upperRightHalfEdge = mev(topUpperRight, Point(1.0, -0.5, 2.0), downLoop);
    Vertex *downUpperRight = upperRightHalfEdge->endV;
    HalfEdge *bottomLeftHalfEdge = mev(topBottomLeft, Point(-1.0, -0.5, -2.0), downLoop);
    Vertex *downBottomLeft = bottomLeftHalfEdge->endV;
    HalfEdge *bottomRightHalfEdge = mev(topBottomRight, Point(1.0, -0.5, -2.0), downLoop);
    Vertex *downBottomRight = bottomRightHalfEdge->endV;

    Loop *upperLoop = mef(downUpperLeft, downUpperRight, downLoop);
    Loop *rightLoop = mef(downUpperRight, downBottomRight, downLoop);
    Loop *bottomLoop = mef(downBottomRight, downBottomLeft, downLoop);
    Loop *leftLoop = mef(downBottomLeft, downUpperLeft, downLoop);

    // Debug
    // traverseLoop(topLoop, "Top Loop");
    // traverseLoop(downLoop, "Down Loop");
    // traverseLoop(upperLoop, "Upper Loop");
    // traverseLoop(bottomLoop, "Bottom Loop");
    // traverseLoop(rightLoop, "Right Loop");
    // traverseLoop(leftLoop, "Left Loop");

    // Top inner ring

    HalfEdge *topBridge = mev(topUpperLeft, Point(-0.5, 0.5, 1.5), topLoop);
    Vertex *topInnerUpperLeft = topBridge->endV;

    HalfEdge *topInnerUpperHalfEdge = mev(topInnerUpperLeft, Point(0.5, 0.5, 1.5), topLoop);
    Vertex *topInnerUpperRight = topInnerUpperHalfEdge->endV;
    HalfEdge *topInnerRightHalfEdge = mev(topInnerUpperRight, Point(0.5, 0.5, -1.5), topLoop);
    Vertex *topInnerBottomRight = topInnerRightHalfEdge->endV;
    HalfEdge *topInnerLeftHalfEdge = mev(topInnerUpperLeft, Point(-0.5, 0.5, -1.5), topLoop);
    Vertex *topInnerBottomLeft = topInnerLeftHalfEdge->endV;
    Loop *downInnerLoop = mef(topInnerBottomLeft, topInnerBottomRight, topLoop);

    Loop *topInnerLoop = kemr(topUpperLeft, topInnerUpperLeft, topLoop);

    HalfEdge *upperLeftInnerHalfEdge = mev(topInnerUpperLeft, Point(-0.5, -0.5, 1.5), downInnerLoop);
    Vertex *downInnerUpperLeft = upperLeftInnerHalfEdge->endV;
    HalfEdge *upperRightInnerHalfEdge = mev(topInnerUpperRight, Point(0.5, -0.5, 1.5), downInnerLoop);
    Vertex *downInnerUpperRight = upperRightInnerHalfEdge->endV;
    HalfEdge *bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, Point(-0.5, -0.5, -1.5), downInnerLoop);
    Vertex *downInnerBottomLeft = bottomLeftInnerHalfEdge->endV;
    HalfEdge *bottomRightInnerHalfEdge = mev(topInnerBottomRight, Point(0.5, -0.5, -1.5), downInnerLoop);
    Vertex *downInnerBottomRight = bottomRightInnerHalfEdge->endV;

    Loop *upperInnerLoop = mef(downInnerUpperLeft, downInnerUpperRight, downInnerLoop);
    Loop *rightInnerLoop = mef(downInnerUpperRight, downInnerBottomRight, downInnerLoop);
    Loop *bottomInnerLoop = mef(downInnerBottomRight, downInnerBottomLeft, downInnerLoop);
    Loop *leftInnerLoop = mef(downInnerBottomLeft, downInnerUpperLeft, downInnerLoop);

    kfmrh(downLoop, downInnerLoop);

    topInnerLoop->SetInnerLoop(true);
    downInnerLoop->SetInnerLoop(true);

    // Debug
    // traverseLoop(topInnerLoop, "Top Inner Loop");
    // traverseLoop(downInnerLoop, "Down Inner Loop");
    // traverseLoop(upperInnerLoop, "Upper Inner Loop");
    // traverseLoop(rightInnerLoop, "Right Inner Loop");
    // traverseLoop(bottomInnerLoop, "Left Inner Loop");
    // traverseLoop(leftInnerLoop, "Bottom Inner Loop");

    return newSolid;
}

Solid *CreateOne()
{
    Solid *newSolid;
    Vertex *topUpperLeft;
    newSolid = mvfs(Point(-1.0, 0.5, 2.0), topUpperLeft);
    Loop *topLoop = newSolid->sFace->fLoop;

    HalfEdge *topUpperHalfEdge = mev(topUpperLeft, Point(1.0, 0.5, 2.0), topLoop);
    Vertex *topUpperRight = topUpperHalfEdge->endV;

    HalfEdge *topLeftHalfEdge = mev(topUpperLeft, Point(-1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomLeft = topLeftHalfEdge->endV;

    HalfEdge *topRightHalfEdge = mev(topUpperRight, Point(1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomRight = topRightHalfEdge->endV;
    // Make top ring
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    sweep(topLoop->lFace, glm::vec3(0, -1, 0), 1);

    // traverseSolid(newSolid, "Solid One");
    return newSolid;
}

Solid *CreateTwo()
{
    Solid *newSolid;
    Vertex *P0;
    newSolid = mvfs(Point(-1.0, 0.5, 2.0), P0);
    Loop *topLoop = newSolid->sFace->fLoop;

    HalfEdge *H1 = mev(P0, Point(1.0, 0.5, 2.0), topLoop);
    Vertex *P1 = H1->endV;

    HalfEdge *H2 = mev(P1, Point(1.0, 0.5, -0.5), topLoop);
    Vertex *P2 = H2->endV;
    HalfEdge *H3 = mev(P2, Point(-0.5, 0.5, -0.5), topLoop);
    Vertex *P3 = H3->endV;
    HalfEdge *H4 = mev(P3, Point(-0.5, 0.5, -1.5), topLoop);
    Vertex *P4 = H4->endV;
    HalfEdge *H5 = mev(P4, Point(1.0, 0.5, -1.5), topLoop);
    Vertex *P5 = H5->endV;
    HalfEdge *H6 = mev(P5, Point(1.0, 0.5, -2.0), topLoop);
    Vertex *P6 = H6->endV;
    HalfEdge *H7 = mev(P6, Point(-1.0, 0.5, -2.0), topLoop);
    Vertex *P7 = H7->endV;
    HalfEdge *H8 = mev(P7, Point(-1.0, 0.5, 0.5), topLoop);
    Vertex *P8 = H8->endV;
    HalfEdge *H9 = mev(P8, Point(0.5, 0.5, 0.5), topLoop);
    Vertex *P9 = H9->endV;
    HalfEdge *H10 = mev(P9, Point(0.5, 0.5, 1.5), topLoop);
    Vertex *P10 = H10->endV;
    HalfEdge *H11 = mev(P10, Point(-1.0, 0.5, 1.5), topLoop);
    Vertex *P11 = H11->endV;

    Loop *downLoop = mef(P0, P11, topLoop);

    sweep(topLoop->lFace, glm::vec3(0, -1, 0), 1);

    // traverseSolid(newSolid, "Solid One");
    return newSolid;
}

Solid *CreateEight()
{
    Solid *newSolid;

    Vertex *topUpperLeft;
    newSolid = mvfs(Point(-1.0, 0.5, 2.0), topUpperLeft);
    Loop *topLoop = newSolid->sFace->fLoop;
    HalfEdge *topUpperHalfEdge = mev(topUpperLeft, Point(1.0, 0.5, 2.0), topLoop);
    Vertex *topUpperRight = topUpperHalfEdge->endV;
    HalfEdge *topLeftHalfEdge = mev(topUpperLeft, Point(-1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomLeft = topLeftHalfEdge->endV;
    HalfEdge *topRightHalfEdge = mev(topUpperRight, Point(1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomRight = topRightHalfEdge->endV;
    // Make top ring
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    HalfEdge *upperLeftHalfEdge = mev(topUpperLeft, Point(-1.0, -0.5, 2.0), downLoop);
    Vertex *downUpperLeft = upperLeftHalfEdge->endV;
    HalfEdge *upperRightHalfEdge = mev(topUpperRight, Point(1.0, -0.5, 2.0), downLoop);
    Vertex *downUpperRight = upperRightHalfEdge->endV;
    HalfEdge *bottomLeftHalfEdge = mev(topBottomLeft, Point(-1.0, -0.5, -2.0), downLoop);
    Vertex *downBottomLeft = bottomLeftHalfEdge->endV;
    HalfEdge *bottomRightHalfEdge = mev(topBottomRight, Point(1.0, -0.5, -2.0), downLoop);
    Vertex *downBottomRight = bottomRightHalfEdge->endV;

    Loop *upperLoop = mef(downUpperLeft, downUpperRight, downLoop);
    Loop *rightLoop = mef(downUpperRight, downBottomRight, downLoop);
    Loop *bottomLoop = mef(downBottomRight, downBottomLeft, downLoop);
    Loop *leftLoop = mef(downBottomLeft, downUpperLeft, downLoop);

    // Debug
    // traverseLoop(topLoop, "Top Loop");
    // traverseLoop(downLoop, "Down Loop");
    // traverseLoop(upperLoop, "Upper Loop");
    // traverseLoop(bottomLoop, "Bottom Loop");
    // traverseLoop(rightLoop, "Right Loop");
    // traverseLoop(leftLoop, "Left Loop");

    // Top inner ring

    HalfEdge *topBridge = mev(topUpperLeft, Point(-0.5, 0.5, 1.5), topLoop);
    Vertex *topInnerUpperLeft = topBridge->endV;

    HalfEdge *topInnerUpperHalfEdge = mev(topInnerUpperLeft, Point(0.5, 0.5, 1.5), topLoop);
    Vertex *topInnerUpperRight = topInnerUpperHalfEdge->endV;
    HalfEdge *topInnerRightHalfEdge = mev(topInnerUpperRight, Point(0.5, 0.5, 0.5), topLoop);
    Vertex *topInnerBottomRight = topInnerRightHalfEdge->endV;
    HalfEdge *topInnerLeftHalfEdge = mev(topInnerUpperLeft, Point(-0.5, 0.5, 0.5), topLoop);
    Vertex *topInnerBottomLeft = topInnerLeftHalfEdge->endV;
    Loop *downInnerLoop = mef(topInnerBottomLeft, topInnerBottomRight, topLoop);

    Loop *topInnerLoop = kemr(topUpperLeft, topInnerUpperLeft, topLoop);

    HalfEdge *upperLeftInnerHalfEdge = mev(topInnerUpperLeft, Point(-0.5, -0.5, 1.5), downInnerLoop);
    Vertex *downInnerUpperLeft = upperLeftInnerHalfEdge->endV;
    HalfEdge *upperRightInnerHalfEdge = mev(topInnerUpperRight, Point(0.5, -0.5, 1.5), downInnerLoop);
    Vertex *downInnerUpperRight = upperRightInnerHalfEdge->endV;
    HalfEdge *bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, Point(-0.5, -0.5, 0.5), downInnerLoop);
    Vertex *downInnerBottomLeft = bottomLeftInnerHalfEdge->endV;
    HalfEdge *bottomRightInnerHalfEdge = mev(topInnerBottomRight, Point(0.5, -0.5, 0.5), downInnerLoop);
    Vertex *downInnerBottomRight = bottomRightInnerHalfEdge->endV;

    Loop *upperInnerLoop = mef(downInnerUpperLeft, downInnerUpperRight, downInnerLoop);
    Loop *rightInnerLoop = mef(downInnerUpperRight, downInnerBottomRight, downInnerLoop);
    Loop *bottomInnerLoop = mef(downInnerBottomRight, downInnerBottomLeft, downInnerLoop);
    Loop *leftInnerLoop = mef(downInnerBottomLeft, downInnerUpperLeft, downInnerLoop);

    kfmrh(downLoop, downInnerLoop);

    topInnerLoop->SetInnerLoop(true);
    downInnerLoop->SetInnerLoop(true);

    HalfEdge *topBridge2 = mev(topUpperLeft, Point(-0.5, 0.5, -0.5), topLoop);
    Vertex *topInnerUpperLeft2 = topBridge2->endV;

    HalfEdge *topInnerUpperHalfEdge2 = mev(topInnerUpperLeft2, Point(0.5, 0.5, -0.5), topLoop);
    Vertex *topInnerUpperRight2 = topInnerUpperHalfEdge2->endV;
    HalfEdge *topInnerRightHalfEdge2 = mev(topInnerUpperRight2, Point(0.5, 0.5, -1.5), topLoop);
    Vertex *topInnerBottomRight2 = topInnerRightHalfEdge2->endV;
    HalfEdge *topInnerLeftHalfEdge2 = mev(topInnerUpperLeft2, Point(-0.5, 0.5, -1.5), topLoop);
    Vertex *topInnerBottomLeft2 = topInnerLeftHalfEdge2->endV;
    Loop *downInnerLoop2 = mef(topInnerBottomLeft2, topInnerBottomRight2, topLoop);

    Loop *topInnerLoop2 = kemr(topUpperLeft, topInnerUpperLeft2, topLoop);

    HalfEdge *upperLeftInnerHalfEdge2 = mev(topInnerUpperLeft2, Point(-0.5, -0.5, -0.5), downInnerLoop2);
    Vertex *downInnerUpperLeft2 = upperLeftInnerHalfEdge2->endV;
    HalfEdge *upperRightInnerHalfEdge2 = mev(topInnerUpperRight2, Point(0.5, -0.5, -0.5), downInnerLoop2);
    Vertex *downInnerUpperRight2 = upperRightInnerHalfEdge2->endV;
    HalfEdge *bottomLeftInnerHalfEdge2 = mev(topInnerBottomLeft2, Point(-0.5, -0.5, -1.5), downInnerLoop2);
    Vertex *downInnerBottomLeft2 = bottomLeftInnerHalfEdge2->endV;
    HalfEdge *bottomRightInnerHalfEdge2 = mev(topInnerBottomRight2, Point(0.5, -0.5, -1.5), downInnerLoop2);
    Vertex *downInnerBottomRight2 = bottomRightInnerHalfEdge2->endV;

    Loop *upperInnerLoop2 = mef(downInnerUpperLeft2, downInnerUpperRight2, downInnerLoop2);
    Loop *rightInnerLoop2 = mef(downInnerUpperRight2, downInnerBottomRight2, downInnerLoop2);
    Loop *bottomInnerLoop2 = mef(downInnerBottomRight2, downInnerBottomLeft2, downInnerLoop2);
    Loop *leftInnerLoop2 = mef(downInnerBottomLeft2, downInnerUpperLeft2, downInnerLoop2);

    kfmrh(downLoop, downInnerLoop2);

    topInnerLoop2->SetInnerLoop(true);
    downInnerLoop2->SetInnerLoop(true);

    return newSolid;
}
