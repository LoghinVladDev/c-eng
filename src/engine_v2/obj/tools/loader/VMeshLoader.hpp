//
// Created by loghin on 07.06.2021.
//

#ifndef C_ENG_VMESHLOADER_HPP
#define C_ENG_VMESHLOADER_HPP

#include <VObject.hpp>
#include <CDS/Thread>
#include <CDS/Boolean>
#include <CDS/Path>
#include <CDS/Pointer>
#include <CDS/Optional>
#include <CDS/Array>
#include <CDS/HashMap>

#include <vector>
#include <VVertex.hpp>

namespace engine {

    class VMeshLoader : public VObject {
    private:
        //// private variables
        //// private functions

    public:
        class RawMesh : public VObject {
        public:
            class RawVertex : public VObject {
            private:
                float _x {0.0f};
                float _y {0.0f};
                float _z {0.0f};

            public:
                RawVertex () noexcept = default;
                RawVertex (RawVertex const &) noexcept = default;
                RawVertex (RawVertex &&) noexcept = default;
                RawVertex (float x, float y, float z) noexcept : _x(x), _y(y), _z(z) {}
                RawVertex (glm::vec3 const & o) noexcept : _x(o.x), _y(o.y), _z(o.z) {}
                RawVertex (glm::vec3 && o) noexcept : _x(std::exchange(o.x, 0.0f)), _y(std::exchange(o.y, 0.0f)), _z(std::exchange(o.z, 0.0f)) {}
                ~RawVertex () noexcept override = default;

                constexpr auto x () noexcept -> float & { return this->_x; }
                constexpr auto y () noexcept -> float & { return this->_y; }
                constexpr auto z () noexcept -> float & { return this->_z; }

                [[nodiscard]] constexpr auto x () const noexcept -> float { return this->_x; }
                [[nodiscard]] constexpr auto y () const noexcept -> float { return this->_y; }
                [[nodiscard]] constexpr auto z () const noexcept -> float { return this->_z; }

                auto operator = (RawVertex const &) noexcept -> RawVertex & = default;
                auto operator = (RawVertex &&) noexcept -> RawVertex & = default;

                inline auto operator = ( glm::vec3 const & o ) noexcept -> RawVertex & {
                    this->_x = o.x;
                    this->_y = o.y;
                    this->_z = o.z;
                    return * this;
                }

                inline auto operator = ( glm::vec3 && o ) noexcept -> RawVertex & {
                    this->_x = std::exchange(o.x, 0.0f);
                    this->_y = std::exchange(o.y, 0.0f);
                    this->_z = std::exchange(o.z, 0.0f);
                    return * this;
                }

                operator glm::vec3 () const noexcept { return {_x, _y, _z}; }

                [[nodiscard]] auto toString () const noexcept -> String override;

                [[nodiscard]] auto hash () const noexcept -> Index override {
                    return
                        static_cast < Index > ( this->_x * 100000.0f ) +
                        static_cast < Index > ( this->_y * 1000.0f ) +
                        static_cast < Index > ( this->_z * 10.0f );
                }
                [[nodiscard]] auto copy () const noexcept -> RawVertex * override { return new RawVertex(* this); }

                auto operator == (RawVertex const & o) const noexcept -> bool {
                    if ( this == & o ) return true;
                    return _x == o._x && _y == o._y && _z == o._z;
                }

                [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype (this) > ( & o );
                    if ( p == nullptr ) return false;
                    return this->operator == (* p);
                }
            };
            class RawFace : public VObject {
            private:
                uint32 _v[3] = {0, 0, 0};

            public:
                constexpr auto operator [] (int i) noexcept -> uint32 & { return _v[i]; }
                constexpr auto operator [] (int i) const noexcept -> uint32 { return _v[i]; }

                constexpr auto v1 () noexcept -> uint32 & { return _v[0]; }
                constexpr auto v2 () noexcept -> uint32 & { return _v[1]; }
                constexpr auto v3 () noexcept -> uint32 & { return _v[2]; }

                [[nodiscard]] constexpr auto v1 () const noexcept -> uint32 { return _v[0]; }
                [[nodiscard]] constexpr auto v2 () const noexcept -> uint32 { return _v[1]; }
                [[nodiscard]] constexpr auto v3 () const noexcept -> uint32 { return _v[2]; }

                [[nodiscard]] auto toString () const noexcept -> String override;
                [[nodiscard]] auto copy () const noexcept -> RawFace * override { return new RawFace(*this); }
                [[nodiscard]] auto hash () const noexcept -> Index override {
                    return (_v[0] << 16) | (_v[1] << 8 ) ^ (_v[2] >> 2);
                }

                [[nodiscard]] auto operator == (RawFace const & f) const noexcept -> bool {
                    if ( this == & f ) return true;

                    return _v[0] == f._v[0] && _v[1] == f._v[1] && f._v[2] == _v[2];
                }

                [[nodiscard]] auto equals ( Object const & o ) const noexcept -> bool override {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return this->operator == (*p);
                }

                operator std::vector < uint32 > () const noexcept { return {_v[0], _v[1], _v[2] }; }
                operator Array < uint32 > () const noexcept { return { _v[0], _v[1], _v[2] }; }
            };

        private:
            Array < RawVertex > _vertices;
            Array < RawFace >   _faces;

            std::vector < engine :: VVertex > _demoVertices;
            std::vector < uint16 > _demoIndices;

        public:

            auto demoPrepareAsset() noexcept -> void;

            RawMesh () noexcept = default;
            RawMesh (RawMesh const &) noexcept = default;
            RawMesh (RawMesh &&) noexcept = default;
            ~RawMesh () noexcept override = default;

            [[nodiscard]] constexpr auto vertices () const noexcept -> Array < RawVertex > const & { return this->_vertices; }
            [[nodiscard]] constexpr auto faces () const noexcept -> Array < RawFace > const & { return this->_faces; }

            constexpr auto vertices () noexcept -> Array < RawVertex > & { return this->_vertices; }
            constexpr auto faces () noexcept -> Array < RawFace > & { return this->_faces; }

            [[nodiscard]] auto indices () const noexcept -> Array < uint32 >;

            [[nodiscard]] auto toString () const noexcept -> String override;

            [[nodiscard]] constexpr auto demoVertices () const noexcept -> std::vector < engine :: VVertex > const & { return this->_demoVertices; }
            [[nodiscard]] constexpr auto demoIndices () const noexcept -> std::vector < uint16 > const & { return this->_demoIndices; }
        };

        template < typename OnFinishCallback >
        class LoaderThread : public Thread {
        public:
            class InputPathInvalid : public std::exception {
            public:
                [[nodiscard]] auto what () const noexcept -> StringLiteral override {
                    return "Invalid File Path Given / No File Path Given";
                }
            };

        private:
            Boolean::Atomic             _isRunning          {false};
            Boolean::Atomic             _isDone             {false};

            UniquePointer < Path >      _pObjectFilePath    {nullptr};

            ForeignPointer < RawMesh >  _mesh               {nullptr};

            bool                        _hasCallback        {false};
            OnFinishCallback            _callback;

            auto run () noexcept (false) -> void override;

            auto readVertex (std::ifstream &) noexcept (false) -> void;
            auto readFace (std::ifstream &) noexcept (false) -> void;

        public:
            LoaderThread () noexcept = default;
            LoaderThread (OnFinishCallback const & callback) noexcept :
                    _hasCallback(true),
                    _callback(callback) {

            }

            LoaderThread (OnFinishCallback const & callback, Path const & path) noexcept :
                    _hasCallback(true),
                    _callback(callback),
                    _pObjectFilePath(path.copy()) {

            }

            LoaderThread (LoaderThread const & o) noexcept :
                    _hasCallback (o._hasCallback) {
                if ( this->_hasCallback )
                    this->_callback = o._callback;
            }

            LoaderThread (LoaderThread && o) noexcept :
                    _hasCallback (std::exchange(o._hasCallback, false)),
                    _callback (std::move(o._callback)),
                    _mesh(std::exchange(o._mesh, nullptr)),
                    _pObjectFilePath(std::move(o._pObjectFilePath)),
                    _isDone(std::move(o._isDone)),
                    _isRunning(std::move(o._isRunning)) {

            }

            ~LoaderThread () noexcept override = default;

            auto setInputPath (Path const & p) noexcept -> LoaderThread & {
                if ( ! this->_isRunning && ! this->_isDone )
                    this->_pObjectFilePath = p.copy();

                return * this;
            }

            auto setMeshPtr ( RawMesh * pMesh ) noexcept -> LoaderThread & {
                if ( ! this->_isRunning && ! this->_isDone )
                    this->_mesh.reset(pMesh);

                return * this;
            }

            inline auto isRunning () const noexcept -> Boolean { return this->_isRunning; }
            inline auto isDone () const noexcept -> Boolean { return this->_isDone; }
            inline auto toString () const noexcept -> String override {
                return String("LoaderThread { from = ") + this->_pObjectFilePath.valueAt() +
                    ", running = " + this->_isRunning.toString() + ", ended = " + this->_isDone.toString() + " }";
            }

            inline auto mesh () const noexcept -> Optional < RawMesh * > {
                if ( this->isDone() ) return { this->_mesh.get() };
                return { };
            }
        };

    private:
        HashMap < Path,  RawMesh * > _models;
        HashMap < RawMesh *, Thread * > _loaders;

    public:

        //// public variables

        //// public functions
//        auto requestModelLoad (Path const &) noexcept -> LoaderThread &;

        ~VMeshLoader () noexcept override {
            this->waitForAllJobs();
        }

        template < typename OnLoadCallback >
        auto requestModelLoad (Path const &, OnLoadCallback const &) noexcept -> void;

        auto jobsExecuting () const noexcept -> bool;
        auto waitForAllJobs () const noexcept -> void;

        [[nodiscard]] auto toString () const noexcept -> String override { return ""; }
    };
}


#include <fstream>
template < typename OnFinishCallback >
auto engine::VMeshLoader::LoaderThread <OnFinishCallback> ::run () noexcept(false) -> void {
    if ( this->_pObjectFilePath.isNull() )
        throw InputPathInvalid ();

    this->_isRunning = true;

    std::ifstream objFile;
    objFile.open(this->_pObjectFilePath->toString());

    try {
        while (!objFile.eof()) {
            char ID = static_cast < char > ( objFile.get() );

            if ( ID == 'v' ) this->readVertex(objFile);
            if ( ID == 'f' ) this->readFace(objFile);

            objFile.get(); // '\n'
        }
    } catch ( std::exception const & e ) {
        std::cout << "Bad File Read / EOF with exceptions on : " << e.what() << '\n';
    }

    objFile.close();

    this->_mesh->vertices().shrinkToSize(this->_mesh->vertices().size());
    this->_mesh->indices().shrinkToSize(this->_mesh->indices().size());

    this->_mesh->demoPrepareAsset();

    this->_isDone = true;
    this->_isRunning = false;

    if ( this->_hasCallback ) {
        this->_callback ( reinterpret_cast < RawMesh const & > (* this->_mesh) );
    }
}

template < typename OnFinishCallback >
auto engine::VMeshLoader::LoaderThread <OnFinishCallback> ::readVertex(std::ifstream & in) noexcept(false) -> void {
    RawMesh::RawVertex rv;
    in >> rv.x() >> rv.y() >> rv.z();

    this->_mesh->vertices().add(std::move(rv));
}

template < typename OnFinishCallback >
auto engine::VMeshLoader::LoaderThread <OnFinishCallback> ::readFace(std::ifstream & in) noexcept(false) -> void {
    RawMesh::RawFace rf;
    in >> rf[0] >> rf[1] >> rf[2];

    this->_mesh->faces().add(std::move(rf));
}

template < typename OnLoadCallback >
auto engine::VMeshLoader::requestModelLoad(Path const & path, OnLoadCallback const & onLoadCallback) noexcept -> void {
    auto model = new RawMesh();
    auto t = new LoaderThread (onLoadCallback, path);

    this->_models[path] = model;
    this->_loaders[model] = t;

    t->setMeshPtr ( model );
    t->start();
}

#endif //C_ENG_VMESHLOADER_HPP
