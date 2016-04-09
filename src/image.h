#pragma once
#include "sapphire_sg.h"

struct SapphireSG_ImageGuts;

struct SapphireSG_Image {
    struct SapphireSG_ImageGuts *guts;
    unsigned long w, h;
};
