#include "TopologicalOperation.h"
#include "string"

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

int main(int argc, char const *argv[])
{
    // 0
    Solid *newSolid;
    Vertex *topUpperLeft;
    newSolid = mvfs(Point(0.0, 1.0, 0.0), topUpperLeft);
    Loop *topLoop = newSolid->sFace->fLoop;

    HalfEdge *topUpperHalfEdge = mev(topUpperLeft, Point(2.0, 1.0, 0.0), topLoop);
    Vertex *topUpperRight = topUpperHalfEdge->endV;

    HalfEdge *topLeftHalfEdge = mev(topUpperLeft, Point(0.0, 1.0, -2.0), topLoop);
    Vertex *topBottomLeft = topLeftHalfEdge->endV;

    HalfEdge *topRightHalfEdge = mev(topUpperRight, Point(2.0, 1.0, -2.0), topLoop);
    Vertex *topBottomRight = topRightHalfEdge->endV;
    // Make top ring
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    HalfEdge *upperLeftHalfEdge = mev(topUpperLeft, Point(0.0, 0.0, 0.0), downLoop);
    Vertex *downUpperLeft = upperLeftHalfEdge->endV;
    HalfEdge *upperRightHalfEdge = mev(topUpperRight, Point(2.0, 0.0, 0.0), downLoop);
    Vertex *downUpperRight = upperRightHalfEdge->endV;
    HalfEdge *bottomLeftHalfEdge = mev(topBottomLeft, Point(0.0, 0.0, -2.0), downLoop);
    Vertex *downBottomLeft = bottomLeftHalfEdge->endV;
    HalfEdge *bottomRightHalfEdge = mev(topBottomRight, Point(2.0, 0.0, -2.0), downLoop);
    Vertex *downBottomRight = bottomRightHalfEdge->endV;

    Loop *upperLoop = mef(downUpperLeft, downUpperRight, downLoop);
    Loop *rightLoop = mef(downUpperRight, downBottomRight, downLoop);
    Loop *bottomLoop = mef(downBottomRight, downBottomLeft, downLoop);
    Loop *leftLoop = mef(downBottomLeft, downUpperLeft, downLoop);

    // Debug
    traverseLoop(topLoop, "Top Loop");
    traverseLoop(downLoop, "Down Loop");

    traverseLoop(upperLoop, "Upper Loop");
    traverseLoop(rightLoop, "Right Loop");
    traverseLoop(leftLoop, "Left Loop");
    traverseLoop(bottomLoop, "Bottom Loop");

    // Top inner ring
    HalfEdge *topBridge = mev(topUpperLeft, Point(0.5, 1.0, -0.5), topLoop);
    Vertex *topInnerUpperLeft = topBridge->endV;

    HalfEdge *topInnerUpperHalfEdge = mev(topInnerUpperLeft, Point(1.5, 1.0, -0.5), topLoop);
    Vertex *topInnerUpperRight = topInnerUpperHalfEdge->endV;
    HalfEdge *topInnerRightHalfEdge = mev(topInnerUpperRight, Point(1.5, 1.0, -1.5), topLoop);
    Vertex *topInnerBottomRight = topInnerRightHalfEdge->endV;
    HalfEdge *topInnerLeftHalfEdge = mev(topInnerUpperLeft, Point(0.5, 1.0, -1.5), topLoop);
    Vertex *topInnerBottomLeft = topInnerLeftHalfEdge->endV;

    Loop *topInnerLoop = mef(topInnerBottomLeft, topInnerBottomRight, topLoop);
    Loop *downInnerLoop = kemr(topUpperLeft, topInnerUpperLeft, topLoop);


    HalfEdge *upperRightInnerHalfEdge = mev(topInnerUpperRight, Point(1.5, 0.0, -0.5), downInnerLoop);
    Vertex *downInnerUpperRight = upperRightInnerHalfEdge->endV;
    HalfEdge *bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, Point(0.5, 0.0, -1.5), downInnerLoop);
    Vertex *downInnerBottomLeft = bottomLeftInnerHalfEdge->endV;
    HalfEdge *bottomRightInnerHalfEdge = mev(topInnerBottomRight, Point(1.5, 0.0, -1.5), downInnerLoop);
    Vertex *downInnerBottomRight = bottomRightInnerHalfEdge->endV;
    HalfEdge *upperLeftInnerHalfEdge = mev(topInnerUpperLeft, Point(0.5, 0.0, -0.5), downInnerLoop);
    Vertex *downInnerUpperLeft = upperLeftInnerHalfEdge->endV;
    traverseLoop(downInnerLoop, "Down Inner Loop");


    // Loop *upperInnerLoop = mef(downInnerUpperLeft, downInnerUpperRight, downInnerLoop);
    // Loop *rightInnerLoop = mef(downInnerUpperRight, downInnerBottomRight, downInnerLoop);
    // Loop *bottomInnerLoop = mef(downInnerBottomRight, downInnerBottomLeft, downInnerLoop);
    // Loop *leftInnerLoop = mef(downInnerBottomLeft, downInnerUpperLeft, downInnerLoop);

    // // Debug
    // traverseLoop(topInnerLoop, "Top Inner Loop");
    // traverseLoop(downInnerLoop, "Down Inner Loop");

    // traverseLoop(upperInnerLoop, "Upper Inner Loop");
    // traverseLoop(rightInnerLoop, "Right Inner Loop");
    // traverseLoop(bottomInnerLoop, "Left Inner Loop");
    // traverseLoop(leftInnerLoop, "Bottom Inner Loop");

    // kfmrh(topLoop, topInnerLoop);
    // kfmrh(downLoop, downInnerLoop);

    return 0;
}
