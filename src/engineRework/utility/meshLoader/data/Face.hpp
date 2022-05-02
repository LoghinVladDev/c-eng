//
// Created by loghin on 5/2/22.
//

#ifndef __C_ENG_MESH_LOADER_FACE_HPP__
#define __C_ENG_MESH_LOADER_FACE_HPP__

#include <Preprocess.hpp>
#include <CDS/Object>
#include <meshLoader/data/Face.hpp>

#define C_ENG_MAP_START CLASS ( Face, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine :: meshLoader {

    template < cds :: uint32 _faceCount = 3U >
    Class {
    public:
        constexpr static auto faceCount = _faceCount;

        using BaseType = cds :: uint32 [ faceCount ];

    private:
        BaseType data { 0U };

    public:
        Constructor () noexcept = default;
        Constructor ( Self const & ) noexcept = default;
        Constructor ( Self && obj ) noexcept = default;

        Constructor ( BaseType const & object ) noexcept : data ( object ) { }
        Constructor ( BaseType && object ) noexcept : data ( std :: move ( object ) ) { }

        constexpr auto operator = ( Self const & obj ) noexcept -> Self & {
            if ( this == & obj ) {
                return * this;
            }

            this->data = obj.data;

            return * this;
        }

        constexpr auto operator = ( Self && obj ) noexcept -> Self & {
            if ( this == & obj ) {
                return * this;
            }

            this->data = std :: move ( obj.data );

            return * this;
        }

        constexpr auto operator = ( BaseType const & obj ) noexcept -> Self & {
            this->data = obj;
            return * this;
        }

        constexpr auto operator = ( BaseType && obj ) noexcept -> Self & {
            this->data = std :: move ( obj );
            return * this;
        }

        constexpr auto operator [] ( int i ) noexcept -> cds :: uint32 & { return this->data[i]; }
        constexpr auto operator [] ( int i ) const noexcept -> cds :: uint32 { return this->data[i]; }

    private:
        template < cds :: uint32 currentIndex, cds :: EnableIf < currentIndex >= _faceCount - 1 > = 0 >
        constexpr auto toStringRec ( std :: ostream & out ) const noexcept -> std :: ostream & {
            return out << this->data [ currentIndex ] << " ]";
        }

        template < cds :: uint32 currentIndex, cds :: EnableIf < currentIndex < _faceCount - 1 > = 0 >
        constexpr auto toStringRec ( std :: ostream & out ) const noexcept -> std :: ostream & {
            return toStringRec < currentIndex + 1 > ( out << this->data [ currentIndex ] );
        }

    public:
        NoDiscard inline auto toString () const noexcept -> cds :: String override {
            std :: stringstream oss;
            oss << __C_ENG_STRINGIFY ( Self ) << " [ ";
            (void) this->toStringRec < 0 > ( oss );
            return oss.str ();
        }

    private:
        template < cds :: uint32 currentIndex, cds :: EnableIf < currentIndex >= _faceCount > = 0 >
        constexpr auto hashRec ( cds :: Index & finalHash ) const noexcept -> cds :: Index & {
            return finalHash;
        }

        template < cds :: uint32 currentIndex, cds :: EnableIf < currentIndex < _faceCount > = 0 >
        constexpr auto hashRec ( cds :: Index & finalHash ) const noexcept -> cds :: Index & {
            constexpr auto stepSize     = sizeof ( cds :: Index ) * 8 / _faceCount;
            constexpr auto shiftWith    = stepSize * currentIndex;

            finalHash = finalHash + this->data [ currentIndex ] << shiftWith;

            return finalHash;
        }

    public:
        NoDiscard constexpr auto hash () const noexcept -> cds :: Index override {
            cds :: Index hash = 0;
            return this->hashRec < 0 > ( hash );
        }

        NoDiscard constexpr auto operator == ( Self const & obj ) const noexcept -> bool {
            return this->data == obj.data;
        }

        NoDiscard inline auto equals ( cds :: Object const & obj ) const noexcept -> bool override {
            if ( this == & obj ) {
                return true;
            }

            auto pFace = dynamic_cast < decltype ( this ) > ( & obj );
            if ( pFace == nullptr ) {
                return false;
            }

            return this->data == pFace->data;
        }

        NoDiscard inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_MESH_LOADER_FACE_HPP__
