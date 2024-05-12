#include "kmath.h"
#include <math.h>
#include <random>
#include <time.h>

static u64 internal_seed = 0;

namespace utils::math {
    void seed_rng() {
        seed_rng(time(NULL));
    }
    void seed_rng(u64 seed) {
        internal_seed = seed;
    }
    void run_rng() {
        internal_seed = internal_seed * 6364136223846793005 + 1;
    }
    u8  lcg_rand_8() {
        run_rng();
        return (u8)((internal_seed >> 32) & 0xFF);
    }
    u16 lcg_rand_16() {
        run_rng();
        return (u16)((internal_seed >> 32) & 0xFFFF);

    }
    u32 lcg_rand_32() {
        run_rng();
        return (u32)((internal_seed >> 32) & 0xFFFFFFFF);

    }
}