
#pragma once
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned long  ulong;

typedef unsigned int FlagBits;

#define CC_ENUM_OPERATORS(type_)                                                                                                             \
    inline type_ operator|(type_ lhs, type_ rhs)                                                                                             \
    {                                                                                                                                        \
        return (type_)(static_cast<std::underlying_type<type_>::type /**/>(lhs) | static_cast<std::underlying_type<type_>::type /**/>(rhs)); \
    }                                                                                                                                        \
    inline void operator|=(type_ &lhs, type_ rhs)                                                                                            \
    {                                                                                                                                        \
        lhs = (type_)(static_cast<std::underlying_type<type_>::type /**/>(lhs) | static_cast<std::underlying_type<type_>::type /**/>(rhs));  \
    }                                                                                                                                        \
    inline int operator&(type_ lhs, type_ rhs)                                                                                               \
    {                                                                                                                                        \
        return (int)(static_cast<std::underlying_type<type_>::type /**/>(lhs) & static_cast<std::underlying_type<type_>::type /**/>(rhs));   \
    }                                                                                                                                        \
    inline void operator&=(type_ &lhs, type_ rhs)                                                                                            \
    {                                                                                                                                        \
        lhs = (type_)(static_cast<std::underlying_type<type_>::type /**/>(lhs) & static_cast<std::underlying_type<type_>::type /**/>(rhs));  \
    }                                                                                                                                        \
    inline bool operator||(type_ lhs, type_ rhs)                                                                                             \
    {                                                                                                                                        \
        return (static_cast<std::underlying_type<type_>::type /**/>(lhs) || static_cast<std::underlying_type<type_>::type /**/>(rhs));       \
    }                                                                                                                                        \
    inline bool operator&&(type_ lhs, type_ rhs)                                                                                             \
    {                                                                                                                                        \
        return (static_cast<std::underlying_type<type_>::type /**/>(lhs) && static_cast<std::underlying_type<type_>::type /**/>(rhs));       \
    }

#define _CC_NEW new
#define _CC_DELETE delete
#define CC_NEW(T) _CC_NEW T
#define CC_NEW_ARRAY(T, count) _CC_NEW T[count]
#define CC_DELETE(ptr) _CC_DELETE(ptr)
#define CC_DELETE_ARRAY(ptr) _CC_DELETE[](ptr)
#define CC_SAFE_DELETE(ptr) \
    if (ptr)                \
    {                       \
        CC_DELETE(ptr);     \
        (ptr) = nullptr;    \
    }
#define CC_SAFE_DELETE_ARRAY(ptr) \
    if (ptr)                      \
    {                             \
        CC_DELETE_ARRAY(ptr);     \
        (ptr) = nullptr;          \
    }
#define CC_UNSAFE_DELETE(ptr) \
    if (ptr)                  \
    {                         \
        CC_DELETE(ptr);       \
    }
#define CC_UNSAFE_DELETE_ARRAY(ptr) \
    if (ptr)                        \
    {                               \
        CC_DELETE_ARRAY(ptr);       \
    }
#define CC_SAFE_DESTROY(ptr) \
    if (ptr)                 \
    {                        \
        (ptr)->destroy();    \
        CC_DELETE(ptr);      \
        ptr = nullptr;       \
    }

#define CC_MALLOC(bytes) malloc(bytes)
#define CC_FREE(ptr) free(ptr)