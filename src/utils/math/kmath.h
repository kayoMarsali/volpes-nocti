#pragma once
#include "defines.h"
#include "utils/logger/logger.h"

typedef union Vector2f {
    struct {
        f32 x;
        f32 y;
    };
    struct {
        f32 w;
        f32 h;
    };
    struct {
        f32 u;
        f32 v;
    };
    f32 data[2];
    Vector2f() : x(0.0f), y(0.0f) {};
    Vector2f(f32 _x, f32 _y) : x(_x), y(_y) {};

    inline void print() { K_LOG_INFO("%2f, %2f", x, y);}
} Vector2f;
typedef union Vector2i {
    struct {
        i32 x;
        i32 y;
    };
    struct {
        i32 w;
        i32 h;
    };
    struct {
        i32 u;
        i32 v;
    };
    i32 data[2];
    Vector2i() : x(0), y(0) {};
    Vector2i(i32 _x, i32 _y) : x(_x), y(_y) {};
} Vector2i;
typedef union Vector2u {
    struct {
        u32 x;
        u32 y;
    };
    struct {
        u32 w;
        u32 h;
    };
    struct {
        u32 u;
        u32 v;
    };
    u32 data[2];
    Vector2u() : x(0), y(0) {};
    Vector2u(u32 _x, u32 _y) : x(_x), y(_y) {};
} Vector2u;

namespace utils::math {
    void seed_rng();
    void seed_rng(u64 seed);
    void run_rng();
    u8  lcg_rand_8();
    u16 lcg_rand_16();
    u32 lcg_rand_32();
}