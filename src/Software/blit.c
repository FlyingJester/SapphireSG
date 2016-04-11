#include "blit.h"
#include <string.h>
#include <stdint.h>

void SoftwareSG_Blit(const struct SoftwareSG_Region *from, struct SoftwareSG_Region *to) {

	const uint32_t *const from_pix = (uint32_t *)from->pixels;
	uint32_t *const to_pix = (uint32_t *)to->pixels;

	unsigned from_x = from->x, from_y = from->y,
		to_x = to->x, to_y = to->y;

	while (from_y < from->h && from_y < from->pix_h &&
		to_y < to->h && to_y < to->pix_h) {

		while (from_x < from->w && from_x < from->pix_w &&
			to_x < to->w && to_x < to->pix_w) {

			to_pix[to_x + (to_y * to->pix_w)] = from_pix[from_x + (from_y * from->pix_w)];

			from_x++;
			to_x++;
		}
		from_y++;
		to_y++;
	}

}

void SoftwareSG_BlitScale(const struct SoftwareSG_Region *from, struct SoftwareSG_Region *to){

	/* TODO: Scale these values to avoid breaks in source */
	const float to_scale_x = ((float)to->w) / ((float)from->w),
		to_scale_y = ((float)to->h) / ((float)from->h),
		from_scale_x = 1.0f / to_scale_x,
		from_scale_y = 1.0f / to_scale_y;

	if (to_scale_x <= 0.01f || to_scale_y <= 0.01f)
		return;

	if (to_scale_x <= 1.01f && to_scale_x >= 0.99f &&
		to_scale_y <= 1.01f && to_scale_y >= 0.99f) {

		SoftwareSG_Blit(from, to);

	}
	else {
		const uint32_t *const from_pix = (uint32_t *)from->pixels;
		uint32_t *const to_pix = (uint32_t *)to->pixels;

		float from_x = (float)from->x, from_y = (float)from->y,
			to_x = (float)to->x, to_y = (float)to->y;

		while (from_y < from->h && from_y < from->pix_h &&
			to_y < to->h && to_y < to->pix_h) {

			while (from_x < from->w && from_x < from->pix_w &&
				to_x < to->w && to_x < to->pix_w) {

				to_pix[(int)(to_x + (to_y * to->pix_w))] = from_pix[(int)(from_x + (from_y * from->pix_w))];

				from_x+= from_scale_x;
				to_x+= to_scale_x;
			}
			from_y+=from_scale_y;
			to_y+=to_scale_y;
		}
	}
}
