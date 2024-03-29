//
// Created by loghin on 16.01.2022.
//

#ifndef __C_ENG_QUEUE_FAMILY_HPP__
#define __C_ENG_QUEUE_FAMILY_HPP__

#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>
#include <CDS/Array>

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     CLASS ( QueueFamily,    ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( PhysicalDevice );

        Class {
            using UndefinedQueryResult = void;

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
            struct PerformanceCounterProperties {
                __C_ENG_TYPE ( PerformanceCounter )             counter;
                __C_ENG_TYPE ( PerformanceCounterDescription )  description;
            };
#endif

            Field ( ENGINE_TYPE ( QueueFamilyDetails ),                     details,                        NO_INIT,                            GET_DEFAULT, SET_NONE )

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
            Field ( TYPE ( cds :: Array < PerformanceCounterProperties > ), performanceCounterProperties,   NO_INIT,                            GET_DEFAULT, SET_NONE )
#endif

            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                       index,                          DEFAULT_VALUE ( 0U ),               GET_DEFAULT, SET_NONE )
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDevice const * ),       physicalDevice,                 DEFAULT_VALUE ( nullptr ),          GET_DEFAULT, SET_NONE )

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
            auto getQueueFlagsWithPresent ( Type ( SurfaceHandle ) ) const noexcept (false) -> Type ( QueueFlags );
#endif

        public:

            auto init ( __C_ENG_TYPE ( PhysicalDevice ) const *, cds :: uint32, __C_ENG_TYPE ( QueueFamilyDetails ) const & ) noexcept (false) -> Self &;
            auto clear () noexcept -> Self & override;

            __C_ENG_NO_DISCARD constexpr auto hash () const noexcept -> cds :: Index override {
                return static_cast < cds :: Index > ( this->_index );
            }

            template < typename QueryResult >
            class Query;

            __C_ENG_NO_DISCARD auto query () const noexcept -> Query < UndefinedQueryResult >;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     NESTED_CLASS ( Query,   ENGINE_TYPE ( QueueFamily ),    PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        template < typename QueryResult >
        Class {
        private:

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
            Type ( SurfaceHandle )          surface         { nullptr }; // NOLINT(clion-misra-cpp2008-8-0-1)
#endif

            Nester                  const * pQueueFamily    { nullptr }; // NOLINT(clion-misra-cpp2008-8-0-1)

            Constructor ( Nester const * ) noexcept; // NOLINT(google-explicit-constructor)

            friend class Nester;

        public:
            template < typename R >
            Constructor ( Self < R > const & ) noexcept; // NOLINT(google-explicit-constructor)

            template < typename R >
            Constructor ( Self < R > && ) noexcept; // NOLINT(google-explicit-constructor)

            template < typename R >
            auto select () const noexcept -> Self < R >;

            template < typename R = QueryResult, cds :: EnableIf < ! cds :: isSame < R, Nester :: UndefinedQueryResult > () > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
            auto execute () const noexcept -> QueryResult;

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
            template < typename R = QueryResult, cds :: EnableIf < cds :: isSame < R, Type ( QueueFlags ) > () > = 0 >
            auto withSurface ( Type ( SurfaceHandle ) ) noexcept -> Self < QueryResult >;
#endif

        };

        template < typename QueryResult >
        template < typename R >
        auto Self < QueryResult > :: select () const noexcept -> Self < R > {
            return Self < R > ( * this );
        }

        template < typename QueryResult >
        template < typename R >
        Self < QueryResult > :: Constructor (
                Self < R > const & query
        ) noexcept :
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
                surface ( query.surface ),
#endif
                pQueueFamily ( query.pQueueFamily ) {

        }

        template < typename QueryResult >
        Self < QueryResult > :: Constructor (
                Nester const * pQueueFamily
        ) noexcept :
                pQueueFamily ( pQueueFamily ) {

        }

        template < typename QueryResult >
        template < typename R >
        Self < QueryResult > :: Constructor (
                Self < R > && query
        ) noexcept :
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
                surface ( cds :: exchange ( query.surface, nullptr ) ),
#endif
                pQueueFamily ( cds :: exchange ( query.pQueueFamily, nullptr ) ) {

        }

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
        template < typename QueryResult >
        template < typename R, cds :: EnableIf < cds :: isSame < R, Type ( QueueFlags ) > () > >
        auto Self < QueryResult > :: withSurface (
                Type ( SurfaceHandle ) handle
        ) noexcept -> Self < QueryResult > {
            this->surface = handle;
            return * this;
        }
#endif

        template < typename QueryResult >
        template < typename R, cds :: EnableIf < ! cds :: isSame < R, Nester :: UndefinedQueryResult > () > > // NOLINT(clion-misra-cpp2008-5-3-1)
        auto Self < QueryResult > :: execute () const noexcept -> QueryResult {
            if constexpr ( cds :: isSame < R, Type ( QueueFlags ) > () ) {
                return this->pQueueFamily->getQueueFlagsWithPresent ( this->surface );
            }

            return QueryResult ();
        }

        inline auto Nester :: query () const noexcept -> Self < Nester :: UndefinedQueryResult > {
            return Self < Nester :: UndefinedQueryResult > ( this );
        }

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#endif //__C_ENG_QUEUE_FAMILY_HPP__
