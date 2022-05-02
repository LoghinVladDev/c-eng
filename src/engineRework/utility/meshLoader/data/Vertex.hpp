//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_MESH_LOADER_VERTEX_HPP__
#define __C_ENG_MESH_LOADER_VERTEX_HPP__

#include <Preprocess.hpp>
#include <CDS/Object>

#define C_ENG_MAP_START CLASS ( Vertex, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine :: meshLoader {

    Class {
    private:
        glm :: vec3 data = { 0.0F, 0.0F, 0.0F };
    public:
        constexpr Constructor () noexcept = default;
        constexpr Constructor ( Self const & ) noexcept = default;
        constexpr Constructor ( Self && ) noexcept = default;

        constexpr auto operator = ( Self const & obj ) noexcept -> Self & {
            if ( this == & obj ) {
                return * this;
            }

            this->data = obj.data;

            return * this;
        }

        explicit constexpr Constructor ( float scalar ) noexcept :
                data ( scalar ) {

        }

        constexpr Constructor ( float x, float y, float z ) noexcept :
                data ( x, y, z ) {

        }

        constexpr Constructor ( glm :: vec3 const & data ) noexcept :
                data ( data ) {

        }

        NoDiscard constexpr auto x () const noexcept -> float { return this->data.x; }
        NoDiscard constexpr auto y () const noexcept -> float { return this->data.y; }
        NoDiscard constexpr auto z () const noexcept -> float { return this->data.z; }

        NoDiscard constexpr auto x () noexcept -> float & { return this->data.x; }
        NoDiscard constexpr auto y () noexcept -> float & { return this->data.y; }
        NoDiscard constexpr auto z () noexcept -> float & { return this->data.z; }

        constexpr auto operator = ( glm :: vec3 const & obj ) noexcept -> Self & {
            this->data = obj;
            return * this;
        }

        constexpr operator glm :: vec3 const & () const noexcept { return this->data; }
        constexpr operator glm :: vec3 & () noexcept { return this->data; }

        NoDiscard constexpr auto operator == ( Self const & obj ) const noexcept -> bool {
            return this->data == obj.data;
        }

        NoDiscard constexpr auto operator == ( glm :: vec3 const & obj ) const noexcept -> bool {
            return this->data == obj;
        }

        NoDiscard inline auto equals ( cds :: Object const & obj ) const noexcept -> bool override {
            if ( this == & obj ) {
                return true;
            }

            auto pVertex = dynamic_cast < decltype ( this ) > ( & obj );
            if ( pVertex == nullptr ) {
                return false;
            }

            return pVertex->data == this->data;
        }

        NoDiscard constexpr auto hash () const noexcept -> cds :: Index override {
            return
                    static_cast < cds :: uint32 > ( this->x() * 1000000.0F ) +
                    static_cast < cds :: uint32 > ( this->y() * 1000.0F ) +
                    static_cast < cds :: uint32 > ( this->z() );
        }

        NoDiscard inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        NoDiscard inline auto toString () const noexcept -> cds :: String override {
            std :: stringstream oss;
            oss
                    << __C_ENG_STRINGIFY ( Self )
                    << "{ x = " << this->data.x
                    << ", y = " << this->data.y
                    << ", z = " << this->data.z
                    << " }";
            return oss.str();
        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_MESH_LOADER_VERTEX_HPP__
