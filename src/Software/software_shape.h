#pragma once
#include "../backend.h"

enum SoftwareSG_DrawMode {
	eNullDrawMode,
	ePointsDrawMode,
	eLinesDrawMode,
	eTriangleFanDrawMode,
	eTriangleStripDrawMode
};

struct SapphireSG_ShapeGuts {
	enum SoftwareSG_DrawMode mode;
};

struct SapphireSG_ShapeGuts *OpenGLSG_CreateShape(struct SapphireSG_Context *ctx);
void OpenGLSG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);
void OpenGLSG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);
