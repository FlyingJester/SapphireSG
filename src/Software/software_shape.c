#include "software_shape.h"

static enum SoftwareSG_DrawMode software_sg_get_mode(unsigned i) {
	switch (i) {
	case 0:
		return eNullDrawMode;
	case 1:
		return ePointsDrawMode;
	case 2:
		return eLinesDrawMode;
	case 4:
		return eTriangleFanDrawMode;
	}
	return eTriangleStripDrawMode;
}

struct SapphireSG_ShapeGuts *OpenGLSG_CreateShape(struct SapphireSG_Context *ctx){
	struct SapphireSG_ShapeGuts *const guts = malloc(sizeof(struct SapphireSG_ShapeGuts));
	if(guts)
		guts->mode = eNullDrawMode;

	return guts;
}

void OpenGLSG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {
	shape->guts->mode = software_sg_get_mode(shape->num_vertices);
}

void OpenGLSG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {
	/* Check for direct or scaled blit */
	if (shape->num_vertices == 4 && shape->guts->mode == eTriangleFanDrawMode) {
		if (shape->vertices[0].data[0] == shape->vertices[3].data[0] &&
			shape->vertices[0].data[1] == shape->vertices[1].data[1] &&
			shape->vertices[1].data[0] == shape->vertices[2].data[0] &&
			shape->vertices[2].data[1] == shape->vertices[3].data[1]) {



		}
	}

}
