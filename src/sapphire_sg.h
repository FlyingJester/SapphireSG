#pragma once
#include <stdbool.h>
#include <stdlib.h>

/** @file
 *  @brief     Sapphire SG API
 *  @author    FlyingJester
 *  @date      2016
 *  @copyright Copyright (c) 2016, Martin McDonough
 *   All rights reserved.
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions are met:
 *   <ul><li>Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.</li>
 *   <li>Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.</li></ul>
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef __cplusplus
#define SAPPHIRESG_CDECL extern "C"
#define SG_DEF_ARG(X) = X
#else
#define SAPPHIRESG_CDECL
#define SG_DEF_ARG(_)
#endif


#ifdef _WIN32
	#ifdef SAPPHIRESG_EXPORTS
		#define SAPPHIRESG_API_EXPORT SAPPHIRESG_CDECL __declspec(dllexport)
	#else
		#define SAPPHIRESG_API_EXPORT SAPPHIRESG_CDECL __declspec(dllimport)
	#endif
#else
	#define SAPPHIRESG_API_EXPORT
#endif

/**
 * @brief Specifies graphics backend.
 * @note that not all backends may be available on all platforms.
 */
enum SG_Backend {
    SG_Any = 0, /**< Allows any backend to be used. This will usually use the most performant backend available. */
	SG_OpenGL2 = 8, /**< The OpenGL backend. This may use OpenGL 2.0 or OpenGL 4.1 */
	SG_OpenGL4 = 16, /**< The OpenGL backend. This may use OpenGL 2.0 or OpenGL 4.1 */
    SG_Vulkan = 64, /**< The Vulkan backend. */
    SG_Software = 128 /**< The software rendering backend. This is available on all platforms. */
};

/**
 * @brief Represents a graphics context.
 *
 * This is needed to perform any action.
 */
struct SapphireSG_Context;

struct SapphireSG_Shader;

struct SapphireSG_VertexShader;
struct SapphireSG_FragmentShader;
struct SapphireSG_GeometryShader;

struct SapphireSG_Group;

struct SapphireSG_Shape;

struct SapphireSG_Image;

/**
 * @brief Creates a Sapphire SG Context
 *
 * For some backends, @p major and @p minor can be used to hint which version of a backend to use.
 * This only has meaning for OpenGL right now, and is only a hint.
 *
 * Using @c SG_Any will allow any backend to be used. This will usually default to OpenGL 4.1 when available.
 * It is important to check which backend was used using @c SG_GetBackend as the specified backend may or may
 * not be honoured.
 *
 * @param backend Hints which backend to use
 * @param maj Hints the major version of the backend to use
 * @param min Hints the minor version of the backend to use
 * @return Returns the Context, or NULL on error
 * @see SG_Backend
 * @see SG_GetBackend
 * @see SG_DestroyContext
 */
SAPPHIRESG_API_EXPORT
struct SapphireSG_Context *SG_CreateContext(enum SG_Backend backend SG_DEF_ARG(SG_Any), unsigned maj SG_DEF_ARG(0), unsigned min SG_DEF_ARG(0));

/**
 * @brief Checks the backend of a context.
 *
 * This will never return @c SG_Any for a valid context. @p maj and @p min will be filled with the major and
 * minor version numbers (if applicable). If @p maj or @p min are NULL they will not be filled with version information.
 *
 * @param ctx Sapphire SG Context to examine
 * @param maj (out) (optional) Gets the major backend API.
 * @param min (out) (optional) Gets the minor backend API.
 * @return Backend used by the context
 * @see SG_Backend
 */
SAPPHIRESG_API_EXPORT
enum SG_Backend SG_GetBackend(const struct SapphireSG_Context *ctx, unsigned *maj SG_DEF_ARG(NULL), unsigned *min SG_DEF_ARG(NULL));

SAPPHIRESG_API_EXPORT
void SG_SetCoordinateDistance(const struct SapphireSG_Context *ctx, unsigned w, unsigned h);

SAPPHIRESG_API_EXPORT
void SG_SetCoordinateSpace(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
	float left, float right, float top, float bottom, float nearz, float farz);

/**
 * @brief Destroys a Context and frees the associated context memory.
 *
 * @note this will not free the associated memory for all created Groups and Shapes. This must be done
 * separately by the caller <i>before</i> freeing the context.
 *
 * @param ctx Sapphire SG Context to destroy
 * @return true if destruction is successful, false otherwise
 * @see SG_CreateContext
 * @see SG_DestroyGroup
 * @see SG_DestroyShape
 */
SAPPHIRESG_API_EXPORT
bool SG_DestroyContext(struct SapphireSG_Context *ctx);

SAPPHIRESG_API_EXPORT
bool SG_SetSceneEndCallback(struct SapphireSG_Context *ctx, void (*callback)(struct SapphireSG_Context *ctx, void *arg), void *arg);

/* arg should be set to the DC. This should only be used with the OpenGL backend. */
SAPPHIRESG_API_EXPORT
void SG_WGLSceneEndCallback(struct SapphireSG_Context *ctx, void *arg);

/* arg should be set to the SDL_Window. This should only be used with the OpenGL backend. */
SAPPHIRESG_API_EXPORT
void SG_SDL2SceneEndCallback(struct SapphireSG_Context *ctx, void *arg);

/* arg should be set to the EGLSurface. This can be used with the OpenGL
 * backend or the Vulkan backend, depending on the platform. */
SAPPHIRESG_API_EXPORT
void SG_EGLSceneEndCallback(struct SapphireSG_Context *ctx, void *arg);

/**
 * @brief Creates a Group for a Context.
 *
 * @param ctx Sapphire SG Context to create a new Group for
 * @return Returns the Group, or NULL on error
 * @see SG_DestroyGroup
 */
SAPPHIRESG_API_EXPORT
struct SapphireSG_Group *SG_CreateGroup(struct SapphireSG_Context *ctx);

/**
 * @brief Destroys a Group and frees the associated context memory.
 *
 * @note this will not free the associated memory for all created Shapes.
 *
 * @param ctx Context which the Group belongs to.
 * @param group Group to destroy
 * @return true if destruction is successful, false otherwise
 * @see SG_CreateGroup
 * @see SG_DestroyShape
 */
SAPPHIRESG_API_EXPORT
bool SG_DestroyGroup(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group);

SAPPHIRESG_API_EXPORT
bool SG_DrawGroup(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group);

/**
 * @brief Creates a Vertex Shader
 *
 * A Shader Program requires a Vertex Shader and a Fragment Shader, and a 
 * Shader Program is required for every Group. Some backends, such as OpenGL 2
 * and the Software backend, do not actually use the shader.
 *
 * @param ctx Contex to create a Vertex Shader for
 * @param src Shader source. The format and langauge depend on the backend,
 *        although OpenGL and Vulkan both use GLSL.
 * @param log (out) (optional) String buffer of @p length bytes to which error
 *        logs can be written.
 * @param length (optional) Length of @p log buffer.
 * @return Vertex Shader or NULL if there is an error, in which case @p log
 *        will be filled out if @p log is not NULL and @length is not zero.
 * @sa SG_CreateFragmentShader
 * @sa SG_CreateGeometryShader
 * @sa SG_CreateShader
 * @sa SG_ContextUsesShaders
 */
SAPPHIRESG_API_EXPORT
struct SapphireSG_VertexShader *SG_CreateVertexShader(struct SapphireSG_Context *ctx, const char *src,
	char *log SG_DEF_ARG(NULL), unsigned long length SG_DEF_ARG(0u));

/**
* @brief Creates a Fragment Shader
*
* A Shader Program requires a Vertex Shader and a Fragment Shader, and a
* Shader Program is required for every Group.
*
* @param ctx Contex to create a Fragment Shader for
* @param src Shader source. The format and langauge depend on the backend,
*        although OpenGL and Vulkan both use GLSL
* @param log (out) (optional) String buffer of @p length bytes to which error
*        logs can be written.
* @param length (optional) Length of @p log buffer.
* @return Vertex Shader or NULL if there is an error, in which case @p log
*        will be filled out if @p log is not NULL and @length is not zero.
* @sa SG_CreateVertexShader
* @sa SG_CreateGeometryShader
* @sa SG_CreateShader
*/
SAPPHIRESG_API_EXPORT
struct SapphireSG_FragmentShader *SG_CreateFragmentShader(struct SapphireSG_Context *ctx, const char *src,
	char *log SG_DEF_ARG(NULL), unsigned long length SG_DEF_ARG(0u));

SAPPHIRESG_API_EXPORT
struct SapphireSG_GeometryShader *SG_CreateGeometryShader(struct SapphireSG_Context *ctx, const char *src,
	char *log SG_DEF_ARG(NULL), unsigned long length SG_DEF_ARG(0u));

/**
 * @brief Creates a Shader Program
 *
 * Shader Programs are composed of one vertex shader, one fragment shader, and
 * any number of geometry shaders (or no geometry shaders at all). You can reuse
 * vertex and fragment shaders, and there is no requirement for when you can
 * destroy fragment and vertex shaders with regard to any shader programs.
 *
 * @param ctx Context to create a shader for
 * @param vert Vertex shader to use
 * @param frag Fragment shader to use
 * @param geos (optional) Array of geometry shaders to use. This array should
 *        be NULL-terminated. It can be NULL to indicate zero geometry shaders,
 *        which is equivalent to specifying an array starting with NULL.
 * @param log (out) (optional) String buffer of @p length bytes to which error
 *        logs can be written.
 * @param length (optional) Length of @p log buffer.
 * @return Shader program or NULL if there is an error, in which case @p log
 *        will be filled out if @p log is not NULL and @length is not zero.
 * @sa SG_CreateVertexShader
 * @sa SG_CreateFragmentShader
 * @sa SG_CreateGeometryShader
 */
SAPPHIRESG_API_EXPORT
struct SapphireSG_Shader *SG_CreateShader(struct SapphireSG_Context *ctx,
	struct SapphireSG_VertexShader *vert, struct SapphireSG_FragmentShader *frag,
	struct SapphireSG_GeometryShader **geos SG_DEF_ARG(NULL),
	char *log SG_DEF_ARG(NULL), unsigned long length SG_DEF_ARG(0u));

SAPPHIRESG_API_EXPORT
struct SapphireSG_Shader *SG_GetDefaultShader(struct SapphireSG_Context *ctx);

/**
 * @brief Creates a Shape for a Context.
 *
 * A Shape can be used with one or more Groups, so long as all the Groups belong to the same Context as the Shape.
 *
 * @param ctx Sapphire SG Context to create a new Shape for
 * @return Returns the Shape, or NULL on error
 * @see SG_DestroyShape
 */
SAPPHIRESG_API_EXPORT
struct SapphireSG_Shape *SG_CreateShape(struct SapphireSG_Context *ctx);

/**
 * @brief Destroys a Shape and frees the associated context memory.
 * 
 * The Shape must not be a member of any Groups when it is destroyed. It may either be removed from the Group,
 * or any Group that contains the Shape may be destroyed first.
 *
 * @param ctx Context which the Shape belongs to.
 * @param shape shape Shape to destroy
 * @return true if destruction is successful, false otherwise
 * @see SG_DestroyGroup
 * @see SG_CreateShape
 */
SAPPHIRESG_API_EXPORT
bool SG_DestroyShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);

SAPPHIRESG_API_EXPORT
void SG_SetGroupShader(struct SapphireSG_Context *ctx,
	struct SapphireSG_Group *group, struct SapphireSG_Shader *shader);

/**
 * @brief Sets the number of Shapes in a Group.
 *
 * This can either add further capacity, which must be set using @c SG_SetGroupShape, or can remove Shapes from the end
 * of the Group.
 *
 * @param ctx Context which the Group belongs to
 * @param group Group to resize
 * @param n new capacity
 * @return true if the Group was resized, false on error
 * @see SG_SetGroupShape
 * @see SG_GetGroupShape
 * @see SG_GetGroupShapeCapacity
 */
SAPPHIRESG_API_EXPORT
bool SG_SetGroupShapeCapacity(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group, unsigned n);

/**
 * @brief Gets the number of Shapes in a Group.
 *
 * @param ctx Context which the Group belongs to
 * @param group Group to resize
 * @return The capacity of the Group
 * @see SG_SetGroupShape
 * @see SG_GetGroupShape
 * @see SG_SetGroupShapeCapacity
 */
SAPPHIRESG_API_EXPORT
unsigned SG_GetGroupShapeCapacity(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group);

/**
 * @brief Sets the Shape at a certain index a Group.
 *
 * The Group must already have been resized to hold at least @p i shapes using @c SG_SetGroupShapeCapacity
 * A Shape may belong to more than one Group, and can be added to a single Group more than once, although
 * doing so will not produce different rendered results.
 *
 * @param ctx Context which the Group and Shape belongs to
 * @param group Group to set the Shape in
 * @param i index of Shape to set
 * @param shape The Shape to set in Group
 * @return true if the Shape is added, false on error
 * @see SG_GetGroupShape
 * @see SG_SetGroupShapeCapacity
 * @see SG_GetGroupShapeCapacity
 */
SAPPHIRESG_API_EXPORT
bool SG_SetGroupShape(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group, unsigned i, struct SapphireSG_Shape *shape);

/**
 * @brief Retrieves the Shape at index @p i of @p group.
 * 
 * @param ctx Context which @p group belongs to
 * @param group Group to fetch Shape from
 * @param i Index to retrieve from
 * @see SG_SetGroupShape
 * @see SG_SetGroupShapeCapacity
 * @see SG_GetGroupShapeCapacity
 */
SAPPHIRESG_API_EXPORT
struct SapphireSG_Shape *SG_GetGroupShape(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group, unsigned i);

/**
 * @brief Creates an Image
 *
 * @param ctx Contex for the image
 * @param pixels An array of pixels in RGBA order
 * @param w Width of image in pixels
 * @param h Height of image in pixels
 * @return Image if creation is successful, NULL otherwise.
 * @see SG_GetImageSize
 */
SAPPHIRESG_API_EXPORT
struct SapphireSG_Image *SG_CreateImage(struct SapphireSG_Context *ctx, const unsigned char *pixels, unsigned w, unsigned h);

SAPPHIRESG_API_EXPORT
struct SapphireSG_Image *SG_CreateSolidColorImageV(struct SapphireSG_Context *ctx, const unsigned char *rgba);

SAPPHIRESG_API_EXPORT
struct SapphireSG_Image *SG_CreateSolidColorImage(struct SapphireSG_Context *ctx,
	unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#define SG_CreateBlackImage(CTX_)  SG_CreateSolidColorImageV(CTX_, NULL)
#define SG_CreateWhiteImage(CTX_)  SG_CreateSolidColorImage(CTX_, 0xFF, 0xFF, 0xFF, 0xFF)
#define SG_CreateClearImage(CTX_)  SG_CreateSolidColorImage(CTX_, 0u,   0u,   0u,   0xFF)
#define SG_CreateRedImage(CTX_)    SG_CreateSolidColorImage(CTX_, 0xFF, 0u,   0u,   0xFF)
#define SG_CreateGreenImage(CTX_)  SG_CreateSolidColorImage(CTX_, 0u,   0xFF, 0u,   0xFF)
#define SG_CreateBlueImage(CTX_)   SG_CreateSolidColorImage(CTX_, 0u,   0u, 0xFF,   0xFF)

SAPPHIRESG_API_EXPORT
bool SG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);
/**
 * @brief Retrieves the image size of @p im
 *
 * Both w and h are optional, if you do not require one of the dimensions.
 * The values pointed to by w and h are undefined if this function fails.
 *
 * @param ctx Context which @p im belongs to
 * @param im Image to get dimensions for
 * @param w (out) (optional) The width of the image
 * @param h (out) (optional) The height of the image
 * @return true if successful, false otherwise.
 * @see SG_GetImageWidth
 * @see SG_GetImageHeight
 */
SAPPHIRESG_API_EXPORT
bool SG_GetImageSize(struct SapphireSG_Context *ctx, const struct SapphireSG_Image *im,
    unsigned *w SG_DEF_ARG(NULL), unsigned *h SG_DEF_ARG(NULL));

/**
 * @brief Gets the width of an image
 *
 * @param ctx Context which @p im belongs to
 * @param im Image to get width of
 * @return Width of @p im
 * @see SG_GetImageHeight
 * @see SG_GetImageSize
 */
SAPPHIRESG_API_EXPORT
unsigned SG_GetImageWidth(struct SapphireSG_Context *ctx, const struct SapphireSG_Image *im);

/**
 * @brief Gets the height of an image
 *
 * @param ctx Context which @p im belongs to
 * @param im Image to get height of
 * @return Height of @p im
 * @see SG_GetImageWidth
 * @see SG_GetImageSize
 */
SAPPHIRESG_API_EXPORT
unsigned SG_GetImageHeight(struct SapphireSG_Context *ctx, const struct SapphireSG_Image *im);

/**
 * @brief Sets the Vertex capacity of a Shape
 *
 * This will resize how many Vertices the Shape contains.
 *
 * @param ctx Context which @p shape belongs to
 * @param shape Shape to set the Vertex capacity of
 * @param n New Vertex capacity
 * @return Returns true if the Shape's capacity is resized, false otherwise
 * @see SG_GetShapeVertexCapacity
 */
SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexCapacity(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape, unsigned n);

/**
 * @brief Gets the Vertex capacity of a Shape
 *
 * @param ctx Context which @p shape belongs to
 * @param shape Shape to get the Vertex capacity of
 * @return The capacity of @p shape
 */
SAPPHIRESG_API_EXPORT
unsigned SG_GetShapeVertexCapacity(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape);

/**
 * @brief Gets the number of Vertices in a Shape.
 *
 * @param ctx Context which the Shape belongs to
 * @param shape @c Shape to resize
 * @return The capacity of the @c Shape
 * @see SG_SetShapeVertexCapacity
 */
SAPPHIRESG_API_EXPORT
unsigned SG_GetShapeVertexCapacity(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape);

/**
 * @brief Sets the @c Image for @p shape
 *
 * Behaviour is undefined if a @c Shape is drawn without an @c Image assigned to it.
 *
 * @param ctx Context which @p shape belongs to
 * @param shape Shape to set the @c Image of
 * @param im New @c Image for @p shape
 * @return true if changing the @c Image of @p shape is successful, false otherwise
 * @see SG_GetShapeImage
 */
SAPPHIRESG_API_EXPORT
bool SG_SetShapeImage(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape, struct SapphireSG_Image *im);

/**
 * @brief Gets the @c Image for @p shape
 *
 * @param ctx Context which @p shape belongs to
 * @param shape Shape to get the @c Image of
 * @return The @c Image of @p shape, or NULL if no @c Image is set on @p shape or if an error occurs.
 * @see SG_GetShapeImage
 */
SAPPHIRESG_API_EXPORT
const struct SapphireSG_Image *SG_GetShapeImage(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape);

/**
 * @brief Sets the vertex coordinates of a @c Vertex in @p shape
 *
 * Note that @p z is reserved for future use. It should be 1.0
 *
 * @param ctx @c Context which @p shape belongs to
 * @param shape @c Shape to set the vertex of
 * @param i Index of @c Vertex to set
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Unused, should be 1.0
 */
SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexPosition(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape,
    unsigned i, float x, float y, float z SG_DEF_ARG(1.0f));

SAPPHIRESG_API_EXPORT
bool SG_GetShapeVertexPosition(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape,
    unsigned i, float *x SG_DEF_ARG(NULL), float *y SG_DEF_ARG(NULL), float *z SG_DEF_ARG(NULL));

/**
* @brief Sets the texture coordinates of a @c Vertex in @p shape
*
* @param ctx @c Context which @p shape belongs to
* @param shape @c Shape to set the texture coordinates of
* @param i Index of @c Vertex to set
* @param u U coordinate
* @param v V coordinate
*/
SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexTexturePosition(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape,
    unsigned i, float u, float v);

SAPPHIRESG_API_EXPORT
bool SG_GetShapeVertexTexturePosition(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape,
	unsigned i, float *u SG_DEF_ARG(NULL), float *v SG_DEF_ARG(NULL));

SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexColorV(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape,
	unsigned i, const unsigned char *rgba);

SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexColor(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape,
	unsigned i, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

SAPPHIRESG_API_EXPORT
bool SG_GetShapeVertexColorV(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape,
	unsigned i, unsigned char *rgba);

SAPPHIRESG_API_EXPORT
bool SG_GetShapeVertexColor(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape,
	unsigned i, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a);
