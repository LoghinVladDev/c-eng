//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_MESH_LOADER_TYPES_HPP__
#define __C_ENG_MESH_LOADER_TYPES_HPP__

#include <Preprocess.hpp>
#include <meshLoader/MeshLoader.hpp>

#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

namespace engine :: meshLoader {

    __C_ENG_PRE_DECLARE_CLASS ( MeshLoaderThread );

    enum class MeshLoaderThreadState {
        Idle,
        Preparing,
        ReadingFile,
        ProcessingContents,
        Cleanup,
        Error,
        Finished,
    };

    struct MeshLoaderContext {
        MeshLoaderThreadState   state;
        cds :: Path             path;
        cds :: Mutex            contextLock;
        Type ( Mesh )         * pMesh;
        cds :: String           errorReason;
    };

    struct MeshLoaderJobData {
        MeshLoaderJobID             jobID;
        MeshLoaderContext           context;
        Type ( MeshLoaderThread ) * pCurrentWorker;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_MESH_LOADER_TYPES_HPP__
