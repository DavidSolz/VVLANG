#ifndef SLOT_TYPE_HPP
#define SLOT_TYPE_HPP

#define SLOT_TYPE_STR {"generic", "byte", "integer", "short", "long", "float", "double", "ubyte", "uinteger", "ushort", "ulong", "string", "vec2", "vec4", "vec8"}

enum slot_type
{
    /* SPECIAL */
    GENERIC,

    /* SIGNED */
    BYTE,
    INTEGER,
    SHORT,
    LONG,
    FLOAT,
    DOUBLE,

    /* UNSIGNED */
    UBYTE,
    UINTEGER,
    USHORT,
    ULONG,

    /* VECTOR */
    STRING,
    FLOAT2,
    FLOAT4,
    FLOAT8,

    NUM_SLOT_TYPES
};

#endif
