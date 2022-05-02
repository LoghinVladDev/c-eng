//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_MESH_LOADER_HPP__
#define __C_ENG_MESH_LOADER_HPP__

#include <Preprocess.hpp>
#include <CDS/Object>
#include <CDS/Path>
#include <meshLoader/data/Mesh.hpp>

#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

namespace engine :: meshLoader {

    using MeshLoaderJobID           = cds :: uint32;

    struct MeshLoaderErrorMessage {

    };

    using MeshLoaderErrorCallback   = auto (*) ( MeshLoaderErrorMessage const & ) noexcept -> void;

    enum class MeshLoaderJobStatus {
        NotStarted,
        Running,
        FinishedError,
        Finished
    };

    struct MeshLoaderJobInput {
        cds :: Path             inputPath;
        MeshLoaderErrorCallback errorCallback;
        Type ( Mesh )         * pMeshOutput;
    };

    struct MeshLoaderJobOutput {
        MeshLoaderJobID jobID;
    };

    extern auto startJob ( MeshLoaderJobInput const & ) noexcept -> MeshLoaderJobID;
    extern auto queryJobStatus ( MeshLoaderJobID ) noexcept -> MeshLoaderJobStatus;
    extern auto acquireJobResults ( MeshLoaderJobOutput & ) noexcept -> bool;
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_MESH_LOADER_HPP__
