#include "geometry.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define SSG_MAX(A_, B_) (A_ > B_ ? A_ : B_)
#define SSG_MIN(A_, B_) (A_ > B_ ? B_ : A_)
#define SSG_EPSILON 0.001f

void SoftwareSG_InitBox(struct SoftwareSG_Box *box, float x, float y, float w, float h){
	assert(box);

	box->x = x;
	box->y = y;
	box->h = h;
	box->w = w;
}

void SoftwareSG_InitSegment(struct SoftwareSG_Segment *seg, float x1, float y1, float x2, float y2){
	assert(seg);

	seg->x1 = x1;
	seg->y1 = y1;
	seg->x2 = x2;
	seg->y2 = y2;
}

void SoftwareSG_InitSegmentEquation(struct SoftwareSG_Segment *seg, float x1, float m, float b){

	const float x2 = (x1>0.0) ? -1.0f : 1.0f;

	seg->x1 = x1;
	seg->y1 = (m * x1) + b;

	seg->x2 = x2;
	seg->y2 = (m * x2) + b;

}

void SoftwareSG_InitPoint(struct SoftwareSG_Point *pt, float x, float y){
	assert(pt);

	pt->x = x;
	pt->y = y;
}

bool SoftwareSG_BoxEqual(const struct SoftwareSG_Box *box1, const struct SoftwareSG_Box *box2){
	assert(box1);
	assert(box2);

	return box1 == box2 ||
	(
		box1->x == box2->x &&
		box1->y == box2->y &&
		box1->w == box2->w &&
		box1->h == box2->h
	);
}

bool SoftwareSG_SegmentEqual(const struct SoftwareSG_Segment *seg1, const struct SoftwareSG_Segment *seg2){
	assert(seg1);
	assert(seg2);

	return seg1 == seg2 ||
	(
		seg1->x1 == seg2->x1 &&
		seg1->y1 == seg2->y1 &&
		seg1->x2 == seg2->x2 &&
		seg1->y2 == seg2->y2
	);
}

bool SoftwareSG_PointEqual(const struct SoftwareSG_Point *p1, const struct SoftwareSG_Point *p2){
	assert(p1);
	assert(p2);

	return p1 == p2 ||
		( fabs(p1->x - p2->x) < SSG_EPSILON && fabs(p1->y - p2->y) < SSG_EPSILON );

}

void SoftwareSG_PositionBox(struct SoftwareSG_Box *box, const struct SoftwareSG_Point *pt){
	assert(box);
	assert(pt);

	box->x = pt->x;
	box->y = pt->y;
}

void SoftwareSG_MoveSegment(struct SoftwareSG_Segment *seg,
	const struct SoftwareSG_Point *p1, const struct SoftwareSG_Point *p2){
	assert(seg);
	assert(p1);
	assert(p2);

	seg->x1 = p1->x;
	seg->y1 = p1->y;
	seg->x2 = p2->x;
	seg->y2 = p2->y;
}

void SoftwareSG_SegmentMidpoint(struct SoftwareSG_Point *pt, const struct SoftwareSG_Segment *seg){
	pt->x = (seg->x1 + seg->x2) / 2;
	pt->y = (seg->y1 + seg->y2) / 2;
}

void SoftwareSG_SolveForIntersection(struct SoftwareSG_Point *pt,
    float slope1, float b1, float slope2, float b2){
    
    pt->x = (b2 - b1) / (slope1 - slope2);
    pt->y = ((slope1 * b2) - (slope2 * b1)) / (slope1 - slope2);
}
void SoftwareSG_SolveForIntersectionRay(struct SoftwareSG_Point *pt,
    const struct SoftwareSG_Point *pt1, float slope1, const struct SoftwareSG_Point *pt2, float slope2){
    
    SoftwareSG_SolveForIntersection(pt,
        slope1, SoftwareSG_YIntercept(pt1, slope1),
        slope2, SoftwareSG_YIntercept(pt2, slope2));
}
float SoftwareSG_YIntercept(const struct SoftwareSG_Point *pt, float slope){
    return pt->y - (pt->x * slope);
}

float SoftwareSG_Distance(float x1, float y1, float x2, float y2){
	const float a = (x1 - x2),
		b = (y1 - y2);
	
	return (float)sqrt((a*a) + (b*b));
}

float SoftwareSG_SegmentDistance(const struct SoftwareSG_Segment *seg){
	return SoftwareSG_Distance(seg->x1, seg->y1, seg->x2, seg->y2);
}

bool SoftwareSG_BoxesIntersect(const struct SoftwareSG_Box *box1, const struct SoftwareSG_Box *box2){

	if(box1->x > box2->x){
		if(box2->x + box2->w < box1->x)
			return false;
	}
	else{
		if(box1->x + box1->w < box2->w)
			return false;
	}
	
	if(box1->y > box2->y){
		if(box2->y + box2->h < box1->y)
			return false;
	}
	else{
		if(box1->y + box1->h < box2->y)
			return false;
	}
	
	return true;
}

bool SoftwareSG_PointInBox(const struct SoftwareSG_Box *box, const struct SoftwareSG_Point *pt){
	if(pt->x < box->x)
		return false;
	if(pt->x > box->x + box->w)
		return false;
	if(pt->y < box->y)
		return false;
	if(pt->y > box->y + box->h)
		return false;
	return true;
}

float SoftwareSG_SegmentSlope(const struct SoftwareSG_Segment *seg){
	if(seg->x1 == seg->x2)
		return 10e8;
	else
		return ((float)(seg->y2 - seg->y1)) / ((float)(seg->x2 - seg->x1));
}

void SoftwareSG_SegmentBoundingBox(const struct SoftwareSG_Segment *seg, struct SoftwareSG_Box *bounds){
	if(seg->x1 < seg->x2){
		bounds->x = seg->x1;
		bounds->w = seg->x2 - seg->x1;
	}
	else{
		bounds->x = seg->x2;
		bounds->w = seg->x1 - seg->x2;
	}
	if(seg->y1 < seg->y2){
		bounds->y = seg->y1;
		bounds->h = seg->y2 - seg->y1;
	}
	else{
		bounds->y = seg->y2;
		bounds->h = seg->y1 - seg->y2;
	}
}

bool SoftwareSG_SegmentIntersectsBox(const struct SoftwareSG_Segment *seg, const struct SoftwareSG_Box *box);

/* Taken from an old TurboSphere algorithm. */
bool SoftwareSG_SegmentsIntersect(struct SoftwareSG_Point *pt, bool bound,
	const struct SoftwareSG_Segment *seg1, const struct SoftwareSG_Segment *seg2){	

	/* If the segments' bounding boxes do not intersect, the segments cannot intersect. */
	struct SoftwareSG_Box box1, box2;
	SoftwareSG_SegmentBoundingBox(seg1, &box1);
	SoftwareSG_SegmentBoundingBox(seg2, &box2);

	if(bound && !SoftwareSG_BoxesIntersect(&box1, &box2))
		return false;

	{
		/* We will need the slopes later.
		 * Rise/Run, difference of Y over difference of X
		 */
		const float slope1 = SoftwareSG_SegmentSlope(seg1),
			slope2 = -SoftwareSG_SegmentSlope(seg1);

		/* Finding the Y-intercept.
		 * b = y-mx
		 */
		const float intercept1 = (float)seg1->y1 - (seg1->x1 * slope1),
			intercept2 = (float)seg2->y1 - (seg2->x1 * slope2);

		struct SoftwareSG_Point intersect;

		/* If the slope of s1 is infinity */
		if(seg1->x1 == seg1->x2){
			/* We know an X for seg2's equation (seg1's only X), we can plug it inti seg2's euqation. */
			intersect.x = seg1->x1;
			intersect.y = (slope2 * seg1->x1) + intercept2;
		}
		else if(seg2->x1 == seg2->x2){
			/* We know an X for seg1's equation (seg2's only X), we can plug it inti seg1's euqation. */
			intersect.x = seg2->x1;
			intersect.y = (slope1 * seg2->x1) + intercept1;
		}
		else{
			/* 
			 * y = mx + b
			 * ----------
			 * m1 * x + b1 = m2 * x + b2
			 * m1 * x = m2 * x + b2 - b1
			 * m1 * x - m2 * x = b2 - b1
			 * x * ( m1 - m2 ) = b2 - b1
			 * x = ( b2 - b1 ) / ( m1 - m2 )
			 */
			
			intersect.x = (intercept2 - intercept1) / (slope1 - slope2);
			intersect.y = (slope1 * intersect.x) + intercept1;
		}

		if((!bound) || SoftwareSG_PointInBox(&box1, &intersect)){
			if(pt){
				pt->x = intersect.x;
				pt->y = intersect.y;
			}
			return true;
		}
		return false;
	}

	assert(false);
	return false;
}

bool SoftwareSG_AffineN(const struct SoftwareSG_ParametricTriangle *uv, float *u, float *v,
	const struct SoftwareSG_Point *in,
    const struct SoftwareSG_Segment *ab_seg, const struct SoftwareSG_Segment *bc_seg,
	float ab_len, float bc_len, float ab_slope, float bc_slope){

    struct SoftwareSG_Point ab1, bc1, bc2;
    struct SoftwareSG_Point ab_pt, bc_pt;
    
    ab1.x = ab_seg->x1;
    ab1.y = ab_seg->y1;
    bc1.x = bc_seg->x1;
    bc1.y = bc_seg->y1;
    bc2.x = bc_seg->x2;
    bc2.y = bc_seg->y2;

    if(SoftwareSG_PointEqual(&ab1, in)){
        u[0] = uv->u1;
        v[0] = uv->v1;
        return true;
    }
    if(SoftwareSG_PointEqual(&bc1, in)){
        u[0] = uv->u2;
        v[0] = uv->v2;
        return true;
    }
    if(SoftwareSG_PointEqual(&bc2, in)){
        u[0] = uv->u3;
        v[0] = uv->v3;
        return true;
    }

    {
        const float ab_y_intercept = SoftwareSG_YIntercept(&ab1, ab_slope),
            bc_y_intercept = SoftwareSG_YIntercept(&bc1, bc_slope);

        SoftwareSG_SolveForIntersectionRay(&ab_pt, &ab1, ab_slope, in, bc_slope);
        SoftwareSG_SolveForIntersectionRay(&bc_pt, &bc1, bc_slope, in, ab_slope);
        
        const float ab_t = (SoftwareSG_Distance(ab_pt.x, ab_pt.y, bc1.x, bc1.y) / ab_len),
            bc_t = (SoftwareSG_Distance(bc_pt.x, bc_pt.y, bc2.x, bc2.y) / bc_len);

        u[0] = (bc_t * uv->u2) + ((1.0f - bc_t) * uv->u3);
        v[0] = (ab_t * uv->v1) + ((1.0f - ab_t) * uv->v2);
        
        if(*u < 0.0f)
            u[0] = 0.0f;
        else if(*u > 1.0f)
            u[1] = 1.0f;
            
        if(*v < 0.0f)
            v[0] = 0.0f;
        else if(*v > 1.0f)
            v[1] = 1.0f;
        
        
        return true;
    }
}

bool SoftwareSG_Affine(const struct SoftwareSG_ParametricTriangle *uv, float *u, float *v,
	const struct SoftwareSG_Point *in,
        const struct SoftwareSG_Segment *ab_seg, const struct SoftwareSG_Segment *bc_seg){

	const float ab_len = SoftwareSG_SegmentDistance(ab_seg),
		bc_len = SoftwareSG_SegmentDistance(bc_seg);
	
	const float ab_slope = SoftwareSG_SegmentSlope(ab_seg),
		bc_slope = SoftwareSG_SegmentSlope(bc_seg);
	
	return SoftwareSG_AffineN(uv, u, v, in, ab_seg, bc_seg, ab_len, bc_len, ab_slope, bc_slope);
}


bool SoftwareSG_WithinPolygon(const struct SoftwareSG_Point *p, const struct SoftwareSG_Segment *segments, unsigned num_segments){
	unsigned parity = 0;
	unsigned i = 0;
	
	float min_x = -1.0f;

	struct SoftwareSG_Segment test_segment;

	for(i=0; i<num_segments; i++){
		if(segments[i].x1 < min_x)
			min_x = segments[i].x1;
		if(segments[i].x2 < min_x)
			min_x = segments[i].x2;
	}

	test_segment.x1 = min_x - 1.0f;
	test_segment.y1 = test_segment.y2 = p->y;
	test_segment.x2 = p->x;

	for(i=0; i<num_segments; i++){

		if(SoftwareSG_SegmentsIntersect(NULL, true, segments + i, &test_segment))
			parity++;
	}

	return parity % 2;

}

bool SoftwareSG_BoundPolygon(struct SoftwareSG_Box *box, const struct SoftwareSG_Segment *segments, unsigned num_segments){
	float min_x = segments[0].x1, max_x = segments[0].x1,
		min_y = segments[0].y1, max_y = segments[0].y1;
	unsigned i;
	for(i=0; i<num_segments; i++){
		if(segments[i].x1 < min_x)
			min_x = segments[i].x1;
		else if(segments[i].x1 > max_x)
			max_x = segments[i].x1;
		if(segments[i].x2 < min_x)
			min_x = segments[i].x2;
		else if(segments[i].x2 > max_x)
			max_x = segments[i].x2;

		if(segments[i].y1 < min_y)
			min_y = segments[i].y1;
		else if(segments[i].y1 > max_y)
			max_y = segments[i].y1;
		if(segments[i].y2 < min_y)
			min_y = segments[i].y2;
		else if(segments[i].y2 > max_x)
			max_y = segments[i].y2;
	}
	
	box->x = min_x;
	box->y = min_y;
	
	box->w = max_x - min_x;
	box->h = max_y - min_y;

	return true;
}

