#include "util/byteutils.h"

uint32_t bswap_32(uint32_t value)
{
    return ((value >> 24) & 0xff) |
        ((value << 8) & 0xff0000) |
        ((value >> 8) & 0xff00) |
        ((value << 24) & 0xff000000);
}