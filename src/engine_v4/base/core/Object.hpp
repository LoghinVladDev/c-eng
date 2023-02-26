//
// Created by loghin on 26/02/23.
//

#ifndef __C_ENG_OBJECT_HPP__
#define __C_ENG_OBJECT_HPP__

#include <CDS/Object>

#include <base/core/Toggles.hpp>

#if __C_ENG_LOGGING_ENABLED


#include <base/core/Compiler.hpp>
#include <base/io/logging/Logger.hpp>

#ifndef __C_ENG_OBJ_LOG
#define __C_ENG_OBJ_LOG(_level, _message) this->logger()->log(engine::io::Logger::Level::_level, _message, __C_ENG_E_FILE__, __C_ENG_E_FUNCTION__, __C_ENG_E_LINE__, this)
#endif

#else

#ifndef __C_ENG_OBJ_LOG
#define __C_ENG_OBJ_LOG(_level, _message)
#endif


#endif

namespace engine {

    class Object : public cds::Object {
    private:
        Object const * _pParent {nullptr};

    protected:
        explicit Object (Object const * pParent = nullptr) noexcept;

    public:
        ~Object () noexcept override = default;

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto className () const noexcept -> cds::StringView = 0;
        __CDS_NoDiscard constexpr auto parent () const noexcept -> Object const * {
            return this->_pParent;
        }

#if __C_ENG_LOGGING_ENABLED
    private:
        io::Logger const * _pLogger;

    public:
        __CDS_NoDiscard auto logger () const noexcept -> io::Logger const *;
        auto setLogger (io::Logger const * pLogger) noexcept -> void;
#endif
    };

}

#endif //__C_ENG_OBJECT_HPP__
