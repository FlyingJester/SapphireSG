#pragma once
#include "sapphire_sg.h"

struct SapphireSG_ContextGuts;

struct SapphireSG_Context {
	struct SapphireSG_ContextGuts *guts;

	enum SG_Backend backend;

	void (*swap_window_callback)(void *arg);
	void *swap_window_arg;

	struct SapphireSG_ContextGuts *(*CreateContext)();

	void (*SetCoordinateSpace)(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
		float left, float right, float top, float bottom, float near, float far);

	struct SapphireSG_ShapeGuts *(*CreateShape)(struct SapphireSG_Context *);
	struct SapphireSG_ImageGuts *(*CreateImage)(struct SapphireSG_Context *, const unsigned char *pixels, unsigned long w, unsigned long h);
	void(*DestroyImage)(struct SapphireSG_Context *, struct SapphireSG_Image *);

	void(*BindImage)(struct SapphireSG_Context *, struct SapphireSG_Image *);
	void(*UpdateShape)(struct SapphireSG_Context *, struct SapphireSG_Shape *shape);
	void(*DrawShape)(struct SapphireSG_Context *, struct SapphireSG_Shape *shape);

	void(*SetShaderParams)(struct SapphireSG_Context *ctx, struct SapphireSG_Shader *shader, 
		const struct SapphireSG_GroupAttribs *attribs);

};
