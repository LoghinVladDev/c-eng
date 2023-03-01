//
// Created by loghin on 01/03/23.
//

#ifndef __C_ENG_EVENT_HPP__
#define __C_ENG_EVENT_HPP__

#include <base/core/Object.hpp>

namespace engine::io {

    class Event : public Object {
    protected:
        explicit Event (Object const * pEmitter) noexcept;

    public:
        enum TypeFlagBits : cds::uint32 {
            WindowEventBit                      = 0x00'00'00'01U,
            KeyEventBit                         = 0x00'00'00'02U,
            MouseEventBit                       = 0x00'00'00'04U,
            ControllerEventBit                  = 0x00'00'00'08U,

            PressEventBit                       = 0x00'00'00'10U,
            ReleaseEventBit                     = 0x00'00'00'20U,
            MoveEventBit                        = 0x00'00'00'40U,

         /* free bit                            = 0x00'00'00'80U, */

            WindowResizeEventBit                = 0x00'00'01'00U,
            WindowFrameBufferResizeEventBit     = 0x00'00'02'00U,
            WindowCloseEventBit                 = 0x00'00'04'00U,
            WindowContentScaleEventBit          = 0x00'00'08'00U,
            WindowRestoreEventBit               = 0x00'00'10'00U,
            WindowMinimizeEventBit              = 0x00'00'20'00U,
            WindowMaximizeEventBit              = 0x00'00'40'00U,
            WindowGainFocusEventBit             = 0x00'00'80'00U,
            WindowLoseFocusEventBit             = 0x00'01'00'00U,
            WindowRefreshRequestEventBit        = 0x00'02'00'00U,

         /* free bit                            = 0x00'04'00'00U, */
         /* free bit                            = 0x00'08'00'00U, */

            MouseEnterEventBit                  = 0x00'10'00'00U,
            MouseLeaveEventBit                  = 0x00'20'00'00U,
            MouseScrollEventBit                 = 0x00'40'00'00U,

         /* free bit                            = 0x00'80'00'00U, */

            ControllerConnectEventBit           = 0x01'00'00'00U,
            ControllerDisconnectEventBit        = 0x02'00'00'00U,
            ControllerAxisEventBit              = 0x04'00'00'00U,
            ControllerHatEventBit               = 0x08'00'00'00U,

         /* free bit                            = 0x10'00'00'00U, */
         /* free bit                            = 0x20'00'00'00U, */
         /* free bit                            = 0x40'00'00'00U, */

            CustomEventBit                      = 0x80'00'00'00U
        };

        using TypeFlags = cds::uint32;

        ~Event () noexcept override = default;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "Event";
        }

        __CDS_NoDiscard constexpr auto emitter () const noexcept -> Object const * {
            return this->parent();
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto typeFlags () const noexcept -> TypeFlags {
            return CustomEventBit;
        }
    };

}


#endif //__C_ENG_EVENT_HPP__
