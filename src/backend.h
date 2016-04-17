#pragma once
#include "sapphire_sg.h"
#include "image.h"
#include "shape.h"
#include "group.h"
#include "context.h"

#define GENERIC_CTX_ELEMENT_INIT(CTX_, E_, P_) CTX_->E_ = P_ ## _ ## E_
#define GENERIC_CTX_INIT(CTX_, PREFIX_)\
	GENERIC_CTX_ELEMENT_INIT(CTX_, CreateContext, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, SetCoordinateSpace, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, CreateImage, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, DestroyImage, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, BindImage, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, CreateShape, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, DestroyShape, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, DrawShape, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, UpdateShape, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, CreateVertexShader, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, CreateFragmentShader, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, CreateShader, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, GetDefaultShader, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, DestroyShader, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, DestroyVertexShader, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, DestroyFragmentShader, PREFIX_);\
	GENERIC_CTX_ELEMENT_INIT(CTX_, SetShaderParams, PREFIX_)
