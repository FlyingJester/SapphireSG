#pragma once
#include "sapphire_sg.h"

struct SapphireSG_Vertex {
    float data[5];
	unsigned char color[4];
};

#define SG_X_INDEX 0
#define SG_Y_INDEX 1
#define SG_Z_INDEX 2
#define SG_U_INDEX 3
#define SG_V_INDEX 4

#define SG_X(X_) X_.data[SG_X_INDEX]
#define SG_Y(X_) X_.data[SG_Y_INDEX]
#define SG_Z(X_) X_.data[SG_Z_INDEX]
#define SG_U(X_) X_.data[SG_U_INDEX]
#define SG_V(X_) X_.data[SG_V_INDEX]

#define SG_XYZ(THAT_, X_A, Y_A, Z_A) SG_X(THAT_) = X_A; SG_Y(THAT_) = Y_A; SG_Z(THAT_) = Z_A
#define SG_UV(THAT_, U_A, V_A) SG_U(THAT_) = U_A; SG_V(THAT_) = V_A

struct SapphireSG_ShapeGuts;

struct SapphireSG_Shape {
    struct SapphireSG_ShapeGuts *guts;
    struct SapphireSG_Image *image;
	bool dirty;

    unsigned num_vertices, vertices_capacity;
    struct SapphireSG_Vertex *vertices;
};
