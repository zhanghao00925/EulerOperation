#pragma once

#include "TopologicalOperation.hpp"

#include "string"
#include <GLFW/glfw3.h>

using namespace std;

void traverseLoop(Loop *_loop, string _loop_name);

void DrawLoop(Loop *_loop, float _r, float _g, float _b);