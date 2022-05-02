//
// Created by loghin on 5/2/22.
//

#include "MeshLoader.hpp"

using namespace cds;

namespace engine :: meshLoader {

    auto startJob ( MeshLoaderJobInput const & input ) noexcept -> MeshLoaderJobID {
        return 0U;
    }

    auto queryJobStatus ( MeshLoaderJobID ) noexcept -> MeshLoaderJobStatus {
        return MeshLoaderJobStatus :: Running;
    }

    auto acquireJobResults ( MeshLoaderJobOutput & output ) noexcept -> bool {
        auto status = queryJobStatus ( output.jobID );
        if ( status != MeshLoaderJobStatus :: Finished ) {
            return false;
        }

        return true;
    }

}
