//
// Created by loghin on 7/18/20.
//

#ifndef ENG1_LIGHTS_H
#define ENG1_LIGHTS_H

struct SLight {
    float constant;
    float linear;
    float quadratic;

    float distanceLimit;
};

//values from http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation

#ifdef __POINT_LIGHT_SAMPLES

#define __GEN_LIGHT_VAL(_d,_c,_l,_q,_i) constexpr SLight LIGHT_INTENSITY_ ## _i = {_c, _l, _q, _d}

__GEN_LIGHT_VAL(7.0f, 1.0f, 0.7f, 1.8f,  0);
__GEN_LIGHT_VAL(13.0f, 1.0f, 0.35f, 0.44f, 1);
__GEN_LIGHT_VAL(20.0f, 1.0f, 0.22f, 0.20f, 2);
__GEN_LIGHT_VAL(32.0f, 1.0f, 0.14f, 0.07f, 3);
__GEN_LIGHT_VAL(50.0f, 1.0f, 0.09f, 0.032f, 4);
__GEN_LIGHT_VAL(65.0f, 1.0f, 0.07f, 0.017f,5);
__GEN_LIGHT_VAL(100.0f, 1.0f, 0.045f, 0.0075f, 6);
__GEN_LIGHT_VAL(160.0f, 1.0f, 0.027f, 0.0028f, 7);
__GEN_LIGHT_VAL(200.0f, 1.0f, 0.022f, 0.0019f, 8);
__GEN_LIGHT_VAL(325.0f, 1.0f, 0.014f, 0.0007f, 9);
__GEN_LIGHT_VAL(600.0f, 1.0f, 0.007f, 0.0002f, 10);
__GEN_LIGHT_VAL(3250.0f, 1.0f, 0.0014f, 0.000007f, 11);

#undef __GEN_LIGHT_VAL

#define __LIGHT_GET_CASE(_id) case _id: return LIGHT_INTENSITY_ ## _id

constexpr SLight getLightStructByID(int id) {
    if(id <= 0)
        return LIGHT_INTENSITY_0;
    switch(id) {
        __LIGHT_GET_CASE(1);
        __LIGHT_GET_CASE(2);
        __LIGHT_GET_CASE(3);
        __LIGHT_GET_CASE(4);
        __LIGHT_GET_CASE(5);
        __LIGHT_GET_CASE(6);
        __LIGHT_GET_CASE(7);
        __LIGHT_GET_CASE(8);
        __LIGHT_GET_CASE(9);
        __LIGHT_GET_CASE(10);
        default :
            return LIGHT_INTENSITY_11;
    }
}

#undef __LIGHT_GET_CASE

constexpr SLight getLightByTargetDistance(int distance) {
    constexpr SLight arrLights[] = {
            LIGHT_INTENSITY_0,
            LIGHT_INTENSITY_1,
            LIGHT_INTENSITY_2,
            LIGHT_INTENSITY_3,
            LIGHT_INTENSITY_4,
            LIGHT_INTENSITY_5,
            LIGHT_INTENSITY_6,
            LIGHT_INTENSITY_7,
            LIGHT_INTENSITY_8,
            LIGHT_INTENSITY_9,
            LIGHT_INTENSITY_10,
            LIGHT_INTENSITY_11
    };

    if(distance <= arrLights[0].distanceLimit)
        return arrLights[0];
    if(distance >= arrLights[11].distanceLimit)
        return arrLights[11];

    for(int i = 1; i < 12; i++) {
        if ( arrLights[i - 1].distanceLimit < distance && distance < arrLights[i].distanceLimit ) {
            if (arrLights[i - 1].distanceLimit - distance > arrLights[i].distanceLimit - distance)
                return arrLights[i];
            else
                return arrLights[i - 1];
        }
    }

    return arrLights[11];
}

#endif

#endif //ENG1_LIGHTS_H