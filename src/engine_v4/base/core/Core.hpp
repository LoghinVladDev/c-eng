//
// Created by loghin on 25/02/23.
//

#ifndef __C_ENG_CORE_HPP__
#define __C_ENG_CORE_HPP__

namespace engine {

    using KeyModifierFlags = cds::uint16;


    enum KeyType {
        KeyUnknown,
        KeySpace,
        KeyApostrophe,
        KeyComma,              /* , */
        KeyMinus,              /* - */
        KeyPeriod,             /* . */
        KeySlash,              /* / */
        Key0,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,
        KeySemicolon,          /* ; */
        KeyEqual,              /* = */
        KeyA,
        KeyB,
        KeyC,
        KeyD,
        KeyE,
        KeyF,
        KeyG,
        KeyH,
        KeyI,
        KeyJ,
        KeyK,
        KeyL,
        KeyM,
        KeyN,
        KeyO,
        KeyP,
        KeyQ,
        KeyR,
        KeyS,
        KeyT,
        KeyU,
        KeyV,
        KeyW,
        KeyX,
        KeyY,
        KeyZ,
        KeyLeftBracket,        /* [ */
        KeyBackslash,          /* \ */
        KeyRightBracket,       /* ] */
        KeyGraveAccent,        /* ` */
        KeyWorld1,             /* non-US #1 */
        KeyWorld2,             /* non-US #2 */
        KeyEscape,
        KeyEnter,
        KeyTab,
        KeyBackspace,
        KeyInsert,
        KeyDelete,
        KeyRight,
        KeyLeft,
        KeyDown,
        KeyUp,
        KeyPageUp,
        KeyPageDown,
        KeyHome,
        KeyEnd,
        KeyCapsLock,
        KeyScrollLock,
        KeyNumLock,
        KeyPrintScreen,
        KeyPause,
        KeyF1,
        KeyF2,
        KeyF3,
        KeyF4,
        KeyF5,
        KeyF6,
        KeyF7,
        KeyF8,
        KeyF9,
        KeyF10,
        KeyF11,
        KeyF12,
        KeyF13,
        KeyF14,
        KeyF15,
        KeyF16,
        KeyF17,
        KeyF18,
        KeyF19,
        KeyF20,
        KeyF21,
        KeyF22,
        KeyF23,
        KeyF24,
        KeyF25,
        KeyKeypad0,
        KeyKeypad1,
        KeyKeypad2,
        KeyKeypad3,
        KeyKeypad4,
        KeyKeypad5,
        KeyKeypad6,
        KeyKeypad7,
        KeyKeypad8,
        KeyKeypad9,
        KeyKeypadDecimal,
        KeyKeypadDivide,
        KeyKeypadMultiply,
        KeyKeypadSubtract,
        KeyKeypadAdd,
        KeyKeypadEnter,
        KeyKeypadEqual,
        KeyLeftShift,
        KeyLeftControl,
        KeyLeftAlt,
        KeyLeftSuper,
        KeyRightShift,
        KeyRightControl,
        KeyRightAlt,
        KeyRightSuper,
        KeyMenu,
    };


    enum KeyModifierFlagBits {
        KeyModifierNone         = 0x0000U,
        KeyModifierShiftBit     = 0x0001U,
        KeyModifierControlBit   = 0x0002U,
        KeyModifierAltBit       = 0x0004U,
        KeyModifierSuperBit     = 0x0008U,
        KeyModifierCapsLockBit  = 0x0010U,
        KeyModifierNumLockBit   = 0x0020U
    };


    enum MouseButtonType {
        MouseButton1,
        MouseButton2,
        MouseButton3,
        MouseButton4,
        MouseButton5,
        MouseButton6,
        MouseButton7,
        MouseButton8,
        MouseButton9,
        MouseButton10,
        MouseButton11,
        MouseButton12,
        MouseButton13,
        MouseButton14,
        MouseButton15,
        MouseButton16,

        MouseButtonLeft,
        MouseButtonRight,
        MouseButtonMiddle,

        MouseButtonUnknown
    };


    enum class ApiProvenience {
        Proprietary,
        OpenSource,
        ThirdParty
    };


    struct Point2D {
        int x;
        int y;
    };


    struct Point2DF {
        float x;
        float y;
    };


    struct Point3D {
        int x;
        int y;
        int z;
    };


    struct Point3DF {
        float x;
        float y;
        float z;
    };


    using Scale2D   = Point2D;
    using Scale2DF  = Point2DF;
    using Scale3D   = Point3D;
    using Scale3DF  = Point3DF;


    struct Size2D {
        int width;
        int height;
    };


    struct Size2DF {
        float width;
        float height;
    };


    struct Size3D {
        int width;
        int height;
        int depth;
    };


    struct Size3DF {
        float width;
        float size;
        float depth;
    };


    struct Rect2D {
        Point2D position;
        Size2D  size;
    };


    struct Rect2DF {
        Point2DF    position;
        Size2DF     size;
    };


    struct Rect3D {
        Point3D position;
        Size3D  size;
    };


    struct Rect3DF {
        Point3DF    position;
        Size3DF     size;
    };


    struct Version {
        cds::uint32 variant;
        cds::uint32 major;
        cds::uint32 minor;
        cds::uint32 patch;
    };


    struct ApiInfo {
        char    const * pApiName;
        char    const * pApiPurpose;
        char    const * pVendorInfo;
        ApiProvenience  provenience;
        cds::uint32     vendorId;
        Version         version;
    };

}

#endif //__C_ENG_CORE_HPP__
