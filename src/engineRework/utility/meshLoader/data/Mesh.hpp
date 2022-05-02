//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_MESH_LOADER_MESH_HPP__
#define __C_ENG_MESH_LOADER_MESH_HPP__

#include <Preprocess.hpp>
#include <CDS/Array>

#include <meshLoader/data/Vertex.hpp>
#include <meshLoader/data/Face.hpp>

constexpr auto v = cds :: Type < std :: array < cds :: uint32, 3 > > :: copyConstructible;

#define C_ENG_MAP_START CLASS ( Mesh, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine :: meshLoader {

    Class {
        using VerticesType  = cds :: Array < Type ( Vertex ) >;
        using FacesType     = cds :: Array < Type ( Face ) < 3 > >;

        Field ( TYPE ( VerticesType ),  vertices,   NO_INIT, GET_DEFAULT, SET_DEFAULT )
        Field ( TYPE ( FacesType ),     faces,      NO_INIT, GET_DEFAULT, SET_DEFAULT )

    public:
        Constructor () noexcept = default;
        Constructor ( Self const & ) noexcept = default;
        Constructor ( Self && obj ) noexcept :
                _vertices ( std :: move ( obj._vertices ) ),
                _faces ( std :: move ( obj._faces ) ) {

        }

        inline auto operator = ( Self const & obj ) noexcept -> Self & {
            if ( this == & obj ) {
                return * this;
            }

            if (v) {
                std :: cout << "a";
            }

            this->_vertices = obj._vertices;
            this->_faces    = obj._faces;

            return * this;
        }

        inline auto operator = ( Self && obj ) noexcept -> Self & {
            if ( this == & obj ) {
                return * this;
            }

            this->_vertices = std :: move ( obj._vertices );
            this->_faces    = std :: move ( obj._faces );

            return * this;
        }

        NoDiscard auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        NoDiscard inline auto operator == ( Self const & obj ) const noexcept -> bool {
            if ( this == & obj ) {
                return true;
            }

            return this->_faces == obj._faces && this->_vertices == obj._vertices;
        }

        NoDiscard inline auto equals ( cds :: Object const & obj ) const noexcept -> bool override {
            if ( this == & obj ) {
                return true;
            }

            auto const * pMesh = dynamic_cast < decltype ( this ) > ( & obj );
            if ( pMesh == nullptr ) {
                return false;
            }

            return this->operator == ( * pMesh );
        }

        NoDiscard inline auto toString () const noexcept -> cds :: String override {
            return __C_ENG_STRINGIFY ( Self ) + " "_s +
                    "{ vertices = " + this->vertices().toString() +
                    ", faces = "    + this->faces().toString() +
                    " }";
        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_MESH_LOADER_MESH_HPP__
