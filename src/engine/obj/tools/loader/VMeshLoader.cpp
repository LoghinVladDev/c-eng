//
// Created by loghin on 07.06.2021.
//

#include "VMeshLoader.hpp"

auto engine::VMeshLoader::RawMesh::indices () const noexcept -> Array < uint32 > {
    Array < uint32 > finalIndices;
    finalIndices.resize(this->faces().size() * 3);

    Index i = 0;
    for (auto const &item : this->faces()) {
        finalIndices[i++] = item[0];
        finalIndices[i++] = item[1];
        finalIndices[i++] = item[2];
    }

    return finalIndices;
}

#include <sstream>
#include <iomanip>

auto engine::VMeshLoader::RawMesh::RawVertex::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "v " << std::fixed << std::setprecision(6) << _x << ' ' << _y << ' ' << _z;
    return oss.str();
}

auto engine::VMeshLoader::RawMesh::RawFace::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "f " << _v[0] << ' ' << _v[1] << ' ' << _v[2];
    return oss.str();
}

auto engine::VMeshLoader::RawMesh::toString() const noexcept -> String {
    std::stringstream oss;

    for ( auto & v : this->vertices() )
        oss << v.toString() << '\n';
    oss << '\n';
    for ( auto & f : this->faces() )
        oss << f.toString() << '\n';
    oss << '\n';

    return oss.str();
}


//auto engine::VMeshLoader::requestModelLoad(const Path &) noexcept -> LoaderThread {
//
//}

auto engine::VMeshLoader::jobsExecuting() const noexcept -> bool {
//    this->_loaders.values().any([](auto v) -> bool { v.get(). })
}

auto engine::VMeshLoader::waitForAllJobs() const noexcept -> void {
//    while ( this->jobsExecuting() );
    this->_loaders.values().forEach([](auto v){v.get()->join();});
}

#include <CDS/Range>
auto engine::VMeshLoader::RawMesh::demoPrepareAsset() noexcept -> void {
    this->_demoVertices.resize(this->_vertices.size());
    for ( auto i : Range(this->_vertices.size()) )
        this->_demoVertices[i] = VVertex { { this->_vertices[i], {0.5f, 0.5f, 0.5f}, {} } };
    auto in = this->indices();
    this->_demoIndices.resize(in.size());

    for ( auto i : Range(in.size()) )
        this->_demoIndices[i] = in[i];
}