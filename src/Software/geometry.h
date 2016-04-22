#pragma once
#include <stdbool.h>

struct SoftwareSG_Box{
	float x, y, w, h;
};

struct SoftwareSG_Segment{
	float x1, y1, x2, y2;
};

struct SoftwareSG_Point{
	float x, y;
};

struct SoftwareSG_ParametricTriangle{
	float u1, v1, u2, v2, u3, v3;
};

void SoftwareSG_InitBox(struct SoftwareSG_Box *box, float x, float y, float w, float h);
void SoftwareSG_InitSegment(struct SoftwareSG_Segment *seg, float x1, float, float x2, float y2);
void SoftwareSG_InitSegmentEquation(struct SoftwareSG_Segment *seg, float x, float m, float b);
void SoftwareSG_InitPoint(struct SoftwareSG_Point *pt, float x, float y);

#define SoftwareSG_CopySegment(FROM_, TO_)\
    do{\
        (TO_)->x1 = (FROM_)->x1;\
        (TO_)->y1 = (FROM_)->y1;\
        (TO_)->x2 = (FROM_)->x2;\
        (TO_)->y2 = (FROM_)->y2;\
    }while(0)

bool SoftwareSG_BoxEqual(const struct SoftwareSG_Box *box1, const struct SoftwareSG_Box *box2);
bool SoftwareSG_SegmentEqual(const struct SoftwareSG_Segment *seg1, const struct SoftwareSG_Segment *sg2);
bool SoftwareSG_PointEqual(const struct SoftwareSG_Point *p1, const struct SoftwareSG_Point *p2);

void SoftwareSG_SegmentMidpoint(struct SoftwareSG_Point *pt, const struct SoftwareSG_Segment *seg);
void SoftwareSG_SolveForIntersection(struct SoftwareSG_Point *pt,
    float slope1, float b1, float slope2, float b2);
void SoftwareSG_SolveForIntersectionRay(struct SoftwareSG_Point *pt,
    const struct SoftwareSG_Point *pt1, float slope1, const struct SoftwareSG_Point *pt2, float slope2);
float SoftwareSG_YIntercept(const struct SoftwareSG_Point *pt, float slope);

void SoftwareSG_PositionBox(struct SoftwareSG_Box *box, const struct SoftwareSG_Point *pt);
void SoftwareSG_MoveSegment(struct SoftwareSG_Segment *seg,
	const struct SoftwareSG_Point *p1, const struct SoftwareSG_Point *p2);

float SoftwareSG_Distance(float x1, float y1, float x2, float y2);

bool SoftwareSG_BoxesIntersect(const struct SoftwareSG_Box *b1, const struct SoftwareSG_Box *b2);

bool SoftwareSG_PointInBox(const struct SoftwareSG_Box *box, const struct SoftwareSG_Point *pt);

float SoftwareSG_SegmentSlope(const struct SoftwareSG_Segment *seg);

void SoftwareSG_SegmentBoundingBox(const struct SoftwareSG_Segment *seg, struct SoftwareSG_Box *bounds);
bool SoftwareSG_SegmentIntersectsBox(const struct SoftwareSG_Segment *seg, const struct SoftwareSG_Box *box);
bool SoftwareSG_SegmentsIntersect(struct SoftwareSG_Point *pt, bool bound,
	const struct SoftwareSG_Segment *seg1, const struct SoftwareSG_Segment *seg2);

bool SoftwareSG_Affine(const struct SoftwareSG_ParametricTriangle *uv, float *u, float *v, const struct SoftwareSG_Point *in,
	const struct SoftwareSG_Segment *ab_seg, const struct SoftwareSG_Segment *bc_seg);

bool SoftwareSG_WithinPolygon(const struct SoftwareSG_Point *p, const struct SoftwareSG_Segment *segments, unsigned n);
bool SoftwareSG_BoundPolygon(struct SoftwareSG_Box *out, const struct SoftwareSG_Segment *segments, unsigned n);
