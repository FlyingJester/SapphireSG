#pragma once

struct SapphireSG_ContextGuts {

	unsigned major, minor;



};

struct SapphireSG_ContextGuts *OpenGLSG_CreateContext();
void OpenGLSG_SetCoordinateSpace(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
	float left, float right, float top, float bottom, float nearz, float farz);