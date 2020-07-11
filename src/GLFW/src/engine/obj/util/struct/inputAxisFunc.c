//
// Created by vladl on 11/07/2020.
//
#include "inputAxisFunc.h"

void updateInputAxis( int x, int y ) {
    inp_axis.xAxis = (x - xOld);
    inp_axis.yAxis = (y - yOld);

    xOld = x;
    yOld = y;
}

struct INPUT_AXIS* getInputAxisVar() {
    return &inp_axis;
}