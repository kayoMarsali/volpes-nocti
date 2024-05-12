#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
// Signed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean types
typedef int b32;
typedef bool b8;

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

#define INVALID_ID           0xFFFFFFFF

#define DRAW_LAYER_DEBUG     0x80000000
#define DRAW_LAYER_UI        0x40000000

#define DRAW_LAYER_FRGND3    0x00008000
#define DRAW_LAYER_FRGND2    0x00004000
#define DRAW_LAYER_FRGND1    0x00002000
#define DRAW_LAYER_FRGND0    0x00001000

#define DRAW_LAYER_LEVEL     0x00000100

#define DRAW_LAYER_BKGND3    0x00000080
#define DRAW_LAYER_BKGND2    0x00000040
#define DRAW_LAYER_BKGND1    0x00000020
#define DRAW_LAYER_BKGND0    0x00000010

#define DRAW_LAYER_NEUTRAL   0x00000008
#define DRAW_LAYER_ENEMIES   0x00000004
#define DRAW_LAYER_ITEMS     0x00000002
#define DRAW_LAYER_PLAYER    0x00000001

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

#define GETBIT(x) (1<<x)