//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKAN_API_EXCEPTIONS_HPP__
#define __C_ENG_VULKAN_API_EXCEPTIONS_HPP__

#include <RenderEngineTypes.hpp>
#include <Preprocess.hpp>
#include <VulkanCore.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {


#define C_ENG_MAP_START     CLASS ( VulkanAPIException, ENGINE_PARENT ( RenderEngineAPIException ) )
#include <ObjectMapping.hpp>

        Class {
        public:
            explicit Constructor ( cds :: String const & message = "" ) :
                    Parent ( "Vulkan API Exception : " + message ) {

            }
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     CLASS ( VulkanAPICallException, ENGINE_PARENT ( VulkanAPIException ) )
#include <ObjectMapping.hpp>

        Class {
        public:
            explicit Constructor (
                    __C_ENG_TYPE ( Result ) result
            ) :
                    Parent (
                            cds :: String :: f (
                                    "Vulkan API Call Exception : %s",
                                    vulkan :: toString ( result )
                            )
                    ) {

            }

            explicit Constructor (
                    cds :: StringLiteral    APICallID,
                    __C_ENG_TYPE ( Result ) result
            ) :
                    Parent (
                            cds :: String :: f (
                                    "Vulkan API Call Exception : %s -> %s",
                                    APICallID,
                                    vulkan :: toString ( result )
                            )
                    ) {

            }

            explicit Constructor (
                    cds :: StringLiteral    APICallID,
                    __C_ENG_TYPE ( Result ) result,
                    cds :: sint64           lineNumber,
                    cds :: StringLiteral    fileName
            ) :
                    Parent (
                            cds :: String :: f (
                                    "%s:%lld => Vulkan API Call Exception : %s -> %s",
                                    fileName,
                                    lineNumber,
                                    APICallID,
                                    vulkan :: toString ( result )
                            )
                    ) {

            }

            explicit Constructor (
                    cds :: StringLiteral    APICallID,
                    __C_ENG_TYPE ( Result ) result,
                    cds :: sint64           lineNumber,
                    cds :: StringLiteral    fileName,
                    cds :: StringLiteral    callerFunctionName
            ) :
                    Parent (
                            cds :: String :: f (
                                    "%s:%lld in %s => Vulkan API Call Exception : %s -> %s",
                                    fileName,
                                    lineNumber,
                                    callerFunctionName,
                                    APICallID,
                                    vulkan :: toString ( result )
                            )
                    ) {

            }
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#if defined(__CDS_compiler_clang) || defined(__CDS_compiler_gcc)

#define __C_ENG_THROW_DETAILED_API_CALL_EXCEPTION(_apiCall, _retVal) throw __C_ENG_TYPE ( VulkanAPICallException ) ( _apiCall, _retVal, __LINE__, __FILE__, __PRETTY_FUNCTION__ ) // NOLINT(bugprone-reserved-identifier)
#define __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal) (void) __C_ENG_TYPE ( Logger ) :: instance()._level( cds :: String :: f ( "%s:%lld in %s => Vulkan API Call Exception : %s -> %s", __FILE__, __LINE__, __PRETTY_FUNCTION__, _apiCall, vulkan :: toString ( _retVal ) ) ) // NOLINT(bugprone-reserved-identifier)
#define __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal) __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal); __C_ENG_THROW_DETAILED_API_CALL_EXCEPTION(_apiCall, _retVal) // NOLINT(bugprone-reserved-identifier)

#elif defined(__CDS_compiler_MinGW)

#define __C_ENG_THROW_DETAILED_API_CALL_EXCEPTION(_apiCall, _retVal) throw __C_ENG_TYPE ( VulkanAPICallException ) ( _apiCall, _retVal, __LINE__, __FILE__, __PRETTY_FUNCTION__ ) // NOLINT(bugprone-reserved-identifier)
#define __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal) (void) __C_ENG_TYPE ( Logger ) :: instance()._level( cds :: String :: f ( "%s:%lld in %s => Vulkan API Call Exception : %s -> %s", __FILE__, __LINE__, __PRETTY_FUNCTION__, _apiCall, vulkan :: toString ( _retVal ) ) ) // NOLINT(bugprone-reserved-identifier)
#define __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal) __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal); __C_ENG_THROW_DETAILED_API_CALL_EXCEPTION(_apiCall, _retVal) // NOLINT(bugprone-reserved-identifier)

#elif defined(__CDS_compiler_MSVC)

#define __C_ENG_THROW_DETAILED_API_CALL_EXCEPTION(_apiCall, _retVal) throw __C_ENG_TYPE ( VulkanAPICallException ) ( _apiCall, _retVal, __LINE__, __FILE__, __FUNCSIG__ ) // NOLINT(bugprone-reserved-identifier)
#define __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal) (void) __C_ENG_TYPE ( Logger ) :: instance()._level( cds :: String :: f ( "%s:%lld in %s => Vulkan API Call Exception : %s -> %s", __FILE__, __LINE__, __FUNCSIG__, _apiCall, vulkan :: toString ( _retVal ) ) ) // NOLINT(bugprone-reserved-identifier)
#define __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal) __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION(_level, _apiCall, _retVal); __C_ENG_THROW_DETAILED_API_CALL_EXCEPTION(_apiCall, _retVal) // NOLINT(bugprone-reserved-identifier)

#else

#error Define The __C_ENG_THROW_DETAILED_API_CALL_EXCEPTION macro set for the selected compiler

#endif

    }
}

#endif //__C_ENG_VULKAN_API_EXCEPTIONS_HPP__
