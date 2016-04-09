#pragma once
#include "sapphire_sg.h"
#include "image.h"
#include "shape.h"
#include "group.h"

struct SapphireSG_ContextGuts;
struct SapphireSG_GroupGuts;


struct SapphireSG_Group {
    struct SapphireSG_GroupGuts *guts;

    unsigned num_shapes, shapes_capacity;
    struct SapphireSG_Shape *shapes;
};

struct SapphireSG_Context {
    struct SapphireSG_ContextGuts *guts;

    struct SapphireSG_ContextGuts *(*CreateContext)();
    struct SapphireSG_ShapeGuts *(*CreateShape)(struct SapphireSG_Context *);
    struct SapphireSG_ImageGuts *(*CreateImage)(struct SapphireSG_Context *, const unsigned char *pixels, unsigned long w, unsigned long h);
    void (*DestroyImage)(struct SapphireSG_Context *, struct SapphireSG_Image *);

    void (*BindImage)(struct SapphireSG_Context *, struct SapphireSG_Image *);
    void (*DrawShape)(struct SapphireSG_Shape *shape);
};
