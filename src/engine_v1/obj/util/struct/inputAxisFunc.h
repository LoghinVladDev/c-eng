//
// Created by vladl on 11/07/2020.
//

#ifndef ENG1_INPUTAXISFUNC_H
#define ENG1_INPUTAXISFUNC_H

#ifdef __cplusplus
extern "C" {
#endif

    struct INPUT_AXIS {
        int xAxis;
        int yAxis;
    };

    static struct INPUT_AXIS inp_axis;
    static int xOld = 0;
    static int yOld = 0;

    struct INPUT_AXIS* getInputAxisVar();
    void updateInputAxis( int, int );

#ifdef __cplusplus
}
#endif

#endif //ENG1_INPUTAXISFUNC_H
