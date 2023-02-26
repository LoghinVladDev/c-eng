//
// Created by loghin on 25/02/23.
//

#ifndef __C_ENG_CORE_HPP__
#define __C_ENG_CORE_HPP__

namespace engine {

    struct Point2D {
        int x;
        int y;
    };


    struct Point2DF {
        float x;
        float y;
    };


    struct Point3D {
        int x;
        int y;
        int z;
    };


    struct Point3DF {
        float x;
        float y;
        float z;
    };


    struct Size2D {
        int width;
        int height;
    };


    struct Size2DF {
        float width;
        float height;
    };


    struct Size3D {
        int width;
        int height;
        int depth;
    };


    struct Size3DF {
        float width;
        float size;
        float depth;
    };


    struct Rect2D {
        Point2D position;
        Size2D  size;
    };


    struct Rect2DF {
        Point2DF    position;
        Size2DF     size;
    };


    struct Rect3D {
        Point3D position;
        Size3D  size;
    };


    struct Rect3DF {
        Point3DF    position;
        Size3DF     size;
    };


    struct Version {
        cds::uint32 variant;
        cds::uint32 major;
        cds::uint32 minor;
        cds::uint32 patch;
    };


    enum class ApiProvenience {
        Proprietary,
        OpenSource,
        ThirdParty
    };


    struct ApiInfo {
        char    const * pApiName;
        char    const * pApiPurpose;
        char    const * pVendorInfo;
        ApiProvenience  provenience;
        cds::uint32     vendorId;
        Version         version;
    };

}

#endif //__C_ENG_CORE_HPP__
