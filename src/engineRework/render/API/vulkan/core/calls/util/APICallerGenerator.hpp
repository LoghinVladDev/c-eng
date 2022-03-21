//
// Created by loghin on 09.03.2022.
//

#if !defined(CALL_POINT)

#error Wrong Usage of "APICallerGenerator.hpp". Define CALL_POINT Symbol with specific set of rules

#else

#define __CALL_GENERATION_CALL(_name, _resolveFormula, _extensionFormula)                                                                                                                                           \
private:                                                                                                                                                                                                            \
    __CALL_GENERATION_CREATE_HANDLE(_name)                                                                                                                                                                          \
                                                                                                                                                                                                                    \
public:                                                                                                                                                                                                             \
    template < typename ... ArgumentTypes, typename R = cds :: ReturnOf < PFN_ ## _name >, typename cds :: EnableIf < std :: is_same < R, VkResult > :: value > = 0 >                                               \
    NoDiscard inline auto _name ( ArgumentTypes && ... arguments ) const noexcept -> Type ( Result ) {                                                                                                              \
        if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                            \
                                                                                                                                                                                                                    \
            __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_ ## _resolveFormula                                                                                                                                          \
                                                                                                                                                                                                                    \
            cds :: LockGuard guard ( this->_name ## Handle.lock );                                                                                                                                                  \
            if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                        \
                __CALL_GENERATION_ACQUIRE_HANDLE_ ## _resolveFormula(_name)                                                                                                                                         \
            }                                                                                                                                                                                                       \
                                                                                                                                                                                                                    \
            __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_ ## _resolveFormula ## _ ## _extensionFormula                                                                                                            \
                                                                                                                                                                                                                    \
            if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                        \
                (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String (                                                                                                                           \
                    "API Call error : Function \"" # _name "\" not found." ) );                                                                                                                                     \
                                                                                                                                                                                                                    \
                return ResultErrorFunctionHandleNotFound;                                                                                                                                                           \
            }                                                                                                                                                                                                       \
        }                                                                                                                                                                                                           \
                                                                                                                                                                                                                    \
        return static_cast < Type ( Result ) > ( this->_name ## Handle.handle ( std :: forward < ArgumentTypes > ( arguments ) ... ) );                                                                             \
    }                                                                                                                                                                                                               \
    template < typename ... ArgumentTypes, typename R = cds :: ReturnOf < PFN_ ## _name >, typename cds :: EnableIf < std :: is_same < R, void > :: value > = 0 >                                                   \
    NoDiscard inline auto _name ( ArgumentTypes && ... arguments ) const noexcept -> Type ( Result ) {                                                                                                              \
        if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                            \
                                                                                                                                                                                                                    \
            __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_ ## _resolveFormula                                                                                                                                          \
                                                                                                                                                                                                                    \
            cds :: LockGuard guard ( this->_name ## Handle.lock );                                                                                                                                                  \
            if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                        \
                __CALL_GENERATION_ACQUIRE_HANDLE_ ## _resolveFormula(_name)                                                                                                                                         \
            }                                                                                                                                                                                                       \
                                                                                                                                                                                                                    \
            __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_ ## _resolveFormula ## _ ## _extensionFormula                                                                                                            \
                                                                                                                                                                                                                    \
            if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                        \
                (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String (                                                                                                                           \
                    "API Call error : Function \"" # _name "\" not found." ) );                                                                                                                                     \
                                                                                                                                                                                                                    \
                return ResultErrorFunctionHandleNotFound;                                                                                                                                                           \
            }                                                                                                                                                                                                       \
        }                                                                                                                                                                                                           \
                                                                                                                                                                                                                    \
        this->_name ## Handle.handle ( std :: forward < ArgumentTypes > ( arguments ) ... );                                                                                                                        \
        return ResultSuccess;                                                                                                                                                                                       \
    }                                                                                                                                                                                                               \
                                                                                                                                                                                                                    \
    template < typename ... ArgumentTypes, typename F, typename R = cds :: ReturnOf < PFN_ ## _name >, cds :: EnableIf < ! std :: is_same < R, void > :: value > = 0 >                                              \
    NoDiscard inline auto _name ## IndirectIndirection ( F call, R * pResult, ArgumentTypes && ... arguments ) const noexcept -> void {                                                                             \
        * pResult = call ( std :: forward < ArgumentTypes && > ( arguments ) ... );                                                                                                                                 \
    }                                                                                                                                                                                                               \
                                                                                                                                                                                                                    \
    template < typename ... ArgumentTypes, typename F, typename R = cds :: ReturnOf < PFN_ ## _name >, cds :: EnableIf < std :: is_same < R, void > :: value > = 0 >                                                \
    NoDiscard inline auto _name ## IndirectIndirection ( F call, R * , ArgumentTypes && ... arguments ) const noexcept -> void {                                                                                    \
        call ( std :: forward < ArgumentTypes && > ( arguments ) ... );                                                                                                                                             \
    }                                                                                                                                                                                                               \
                                                                                                                                                                                                                    \
    template < typename ... ArgumentTypes, typename R = cds :: ReturnOf < PFN_ ## _name >, typename cds :: EnableIf < ! std :: is_same < R, void > :: value && ! std :: is_same < R, VkResult > :: value > = 0 >    \
    NoDiscard inline auto _name ( cds :: ReturnOf < PFN_ ## _name > * pReturn, ArgumentTypes && ... arguments ) const noexcept -> Type ( Result ) {                                                                 \
        if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                            \
                                                                                                                                                                                                                    \
            __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_ ## _resolveFormula                                                                                                                                          \
                                                                                                                                                                                                                    \
            cds :: LockGuard guard ( this->_name ## Handle.lock );                                                                                                                                                  \
            if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                        \
                __CALL_GENERATION_ACQUIRE_HANDLE_ ## _resolveFormula(_name)                                                                                                                                         \
            }                                                                                                                                                                                                       \
                                                                                                                                                                                                                    \
            __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_ ## _resolveFormula ## _ ## _extensionFormula                                                                                                            \
                                                                                                                                                                                                                    \
            if ( this->_name ## Handle.handle == nullptr ) {                                                                                                                                                        \
                (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String (                                                                                                                           \
                    "API Call error : Function \"" # _name "\" not found." ) );                                                                                                                                     \
                                                                                                                                                                                                                    \
                return ResultErrorFunctionHandleNotFound;                                                                                                                                                           \
            }                                                                                                                                                                                                       \
        }                                                                                                                                                                                                           \
                                                                                                                                                                                                                    \
        this->_name ## IndirectIndirection ( this-> _name ## Handle.handle, pReturn, std :: forward < ArgumentTypes && > ( arguments ) ... );                                                                       \
        return ResultSuccess;                                                                                                                                                                                       \
    }

#define __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INDEPENDENT
#define __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INSTANCE
#define __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_DEVICE
#define __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INSTANCE_OR_KHR  bool extensionHandle = false;
#define __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INSTANCE_OR_EXT  bool extensionHandle = false;

#define __CALL_GENERATION_CREATE_HANDLE(_name) \
    APICall < PFN_ ## _name > mutable _name ## Handle { nullptr, {} };

#define __CALL_GENERATION_ACQUIRE_HANDLE_INDEPENDENT                    __CALL_GENERATION_ACQUIRE_HANDLE_INDEPENDENT_DELAYED
#define __CALL_GENERATION_ACQUIRE_HANDLE_INDEPENDENT_DELAYED( _name ) \
    _name ## Handle.handle = reinterpret_cast < PFN_ ## _name > ( vkGetInstanceProcAddr ( nullptr, # _name ) );

#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE                       __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_DELAYED
#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_DELAYED( _name )                                                                      \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                    \
        this->instanceHandleToBeUsed = LastCreatedInstance :: acquire ();                                                               \
    }                                                                                                                                   \
                                                                                                                                        \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                    \
        (void) engine :: Type ( Logger ) :: instance().warning ("Requested Instance Function, but no Instance Handle Provided");        \
    }                                                                                                                                   \
                                                                                                                                        \
    _name ## Handle.handle = reinterpret_cast < PFN_ ## _name > ( vkGetInstanceProcAddr ( this->instanceHandleToBeUsed, # _name ) );

#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE                       __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_DELAYED
#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_DELAYED( _name )                                                                      \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                    \
        this->instanceHandleToBeUsed = LastCreatedInstance :: acquire ();                                                               \
    }                                                                                                                                   \
                                                                                                                                        \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                    \
        (void) engine :: Type ( Logger ) :: instance().warning ("Requested Instance Function, but no Instance Handle Provided");        \
    }                                                                                                                                   \
                                                                                                                                        \
    _name ## Handle.handle = reinterpret_cast < PFN_ ## _name > ( vkGetInstanceProcAddr ( this->instanceHandleToBeUsed, # _name ) );

#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_KHR                __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_KHR_DELAYED
#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_KHR_DELAYED( _name )                                                                                                   \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                                                        \
        this->instanceHandleToBeUsed = LastCreatedInstance :: acquire ();                                                                                                   \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                                                        \
        (void) engine :: Type ( Logger ) :: instance().warning ("Requested Instance Function, but no Instance Handle Provided");                                            \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    _name ## Handle.handle = reinterpret_cast < PFN_ ## _name > ( vkGetInstanceProcAddr ( this->instanceHandleToBeUsed, # _name ) );                                        \
                                                                                                                                                                            \
    if ( _name ## Handle.handle == nullptr ) {                                                                                                                              \
        extensionHandle = true;                                                                                                                                             \
        _name ## Handle.handle = reinterpret_cast < PFN_ ## _name ## KHR > ( vkGetInstanceProcAddr ( this->instanceHandleToBeUsed, __C_ENG_STRINGIFY ( _name ## KHR ) ) );  \
    }

#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_EXT                __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_EXT_DELAYED
#define __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_EXT_DELAYED( _name )                                                                                                   \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                                                        \
        this->instanceHandleToBeUsed = LastCreatedInstance :: acquire ();                                                                                                   \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    if ( this->instanceHandleToBeUsed == nullptr ) {                                                                                                                        \
        (void) engine :: Type ( Logger ) :: instance().warning ("Requested Instance Function, but no Instance Handle Provided");                                            \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    _name ## Handle.handle = reinterpret_cast < PFN_ ## _name > ( vkGetInstanceProcAddr ( this->instanceHandleToBeUsed, # _name ) );                                        \
                                                                                                                                                                            \
    if ( _name ## Handle.handle == nullptr ) {                                                                                                                              \
        extensionHandle = true;                                                                                                                                             \
        _name ## Handle.handle = reinterpret_cast < PFN_ ## _name ## EXT > ( vkGetInstanceProcAddr ( this->instanceHandleToBeUsed, __C_ENG_STRINGIFY ( _name ## EXT ) ) );  \
    }

#define __C_ENG_API_CALLER_GENERATOR_META_JOIN_AND_CALL(_prefix, _mapDef)   _prefix ## _mapDef
#define __C_ENG_API_CALLER_GENERATOR_META_CALL(_prefix, _mapDef)            __C_ENG_API_CALLER_GENERATOR_META_JOIN_AND_CALL(_prefix, _mapDef)

#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INDEPENDENT_NO_EXTENSION
#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_NO_EXTENSION
#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_DEVICE_NO_EXTENSION

#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INDEPENDENT_EXTENSION(_name)
#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_EXTENSION(_name)                                                                                    \
    if ( ! this->instanceAvailableExtensions.containsKey ( this->instanceHandleToBeUsed ) ) {                                                                       \
        (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String :: f (                                                                              \
                "Instance %#x does not have any registered extensions to extract calls for extension \"" __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) "\"" \
        ));                                                                                                                                                         \
    } else if ( ! this->instanceAvailableExtensions[ this->instanceHandleToBeUsed ].contains ( __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) ) ) {          \
        (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String :: f (                                                                              \
                "Extension \"" __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) "\" was not attached at instance's %#x creation",                              \
                this->instanceHandleToBeUsed )                                                                                                                      \
        );                                                                                                                                                          \
    }

#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_OR_KHR_EXTENSION(_name)                                                                                         \
    if ( extensionHandle && ! this->instanceAvailableExtensions.containsKey ( this->instanceHandleToBeUsed ) ) {                                                                \
        (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String :: f (                                                                                          \
                "Instance %#x does not have any registered extensions to extract calls for extension \"" __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) "\""             \
        ));                                                                                                                                                                     \
    } else if ( extensionHandle && ! this->instanceAvailableExtensions[ this->instanceHandleToBeUsed ].contains ( __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) ) ) {   \
        (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String :: f (                                                                                          \
                "Extension \"" __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) "\" was not attached at instance's %#x creation",                                          \
                this->instanceHandleToBeUsed )                                                                                                                                  \
        );                                                                                                                                                                      \
    }

#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_OR_EXT_EXTENSION(_name)                                                                                         \
    if ( extensionHandle && ! this->instanceAvailableExtensions.containsKey ( this->instanceHandleToBeUsed ) ) {                                                                \
        (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String :: f (                                                                                          \
                "Instance %#x does not have any registered extensions to extract calls for extension \"" __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) "\""             \
        ));                                                                                                                                                                     \
    } else if ( extensionHandle && ! this->instanceAvailableExtensions[ this->instanceHandleToBeUsed ].contains ( __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) ) ) {   \
        (void) engine :: Type ( Logger ) :: instance().critical ( cds :: String :: f (                                                                                          \
                "Extension \"" __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME ( _name ) "\" was not attached at instance's %#x creation",                                          \
                this->instanceHandleToBeUsed )                                                                                                                                  \
        );                                                                                                                                                                      \
    }                                                                                                                                                                           \

#define __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_DEVICE_EXTENSION(_name)


#define __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME(_name) _name ## _EXTENSION_NAME


#define __CALL                      __C_ENG_API_CALLER_GENERATOR_META_CALL(__CALL_GENERATION_, CALL_POINT)

#if ! defined ( __C_ENG_DEBUG_CALLER_GENERATOR )

__CDS_WarningSuppression_VoidPtrDereference_SuppressEnable
__CALL
__CDS_WarningSuppression_VoidPtrDereference_SuppressDisable

#undef __CALL

#undef __CALL_GENERATION_CHECK_MAKE_EXTENSION_NAME

#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INDEPENDENT_EXTENSION
#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_EXTENSION
#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_OR_KHR_EXTENSION
#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_OR_EXT_EXTENSION
#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_DEVICE_EXTENSION

#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INDEPENDENT_NO_EXTENSION
#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_INSTANCE_NO_EXTENSION
#undef __CALL_GENERATION_CHECK_EXTENSION_AVAILABILITY_DEVICE_NO_EXTENSION

#undef __CALL_GENERATION_CALL
#undef __CALL_GENERATION_CREATE_HANDLE

#undef __CALL_GENERATION_ACQUIRE_HANDLE_INDEPENDENT
#undef __CALL_GENERATION_ACQUIRE_HANDLE_INDEPENDENT_DELAYED

#undef __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE
#undef __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_DELAYED

#undef __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_KHR
#undef __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_KHR_DELAYED

#undef __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_EXT
#undef __CALL_GENERATION_ACQUIRE_HANDLE_INSTANCE_OR_EXT_DELAYED

#undef __C_ENG_API_CALLER_GENERATOR_META_JOIN_AND_CALL
#undef __C_ENG_API_CALLER_GENERATOR_META_CALL

#undef __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INDEPENDENT
#undef __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INSTANCE
#undef __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_DEVICE
#undef __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INSTANCE_OR_KHR
#undef __CALL_GENERATION_CREATE_ALTERNATIVE_CHECK_INSTANCE_OR_EXT

#undef CALL_POINT

#endif

#endif
