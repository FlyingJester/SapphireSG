#pragma once

void SoftwareSG_Bresenham(int x1, int y1, int x2, int y2,
	void (draw_op)(int x, int y, void *arg), void *arg);
