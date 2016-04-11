#pragma once

struct SoftwareSG_Region {
	unsigned char *pixels;
	unsigned long pix_w, pix_h;

	unsigned long x, y, w, h;
};



void SoftwareSG_Blit(const struct SoftwareSG_Region *from, struct SoftwareSG_Region *to);

void SoftwareSG_BlitScale(const struct SoftwareSG_Region *from, struct SoftwareSG_Region *to);

