#include "bresenham.h"

void SoftwareSG_Bresenham(int x1, int y1, int x2, int y2,
	void (draw_op)(int x, int y, void *arg), void *arg) {

	if (x1 == x2) {
		if (y1 == y2) {
			draw_op(x1, y1, arg);
		}
		else{
			const int ya = (y1 > y2) ? y2 : y1,
				yb = (y1 > y2) ? y1 : y2;

			int i = ya;

			do {
				draw_op(x1, i, arg);
			} while (i++ != yb);
		}
	}
	else if (y1 == y2) {

		const int xa = (x1 > x2) ? x2 : x1,
			xb = (x1 > x2) ? x1 : x2;

		int i = xa;

		do {
			draw_op(i, y1, arg);
		} while (i++ != xb);
	}
	else {
		const int dx = x2 - x1,
			dy = y2 - y1,
			gy = (dy > 0) ? 1 : -1;

		int y = y1, x = x1;

		float err = 0.0f,
			derr = ((float)dy) / ((float)dx);

		if (derr < 0)
			derr = -derr;

		while (x != x1) {

			draw_op(x, y, arg);

			err += derr;
			while (err >= 0.5f) {
				y += gy;
				draw_op(x, y, arg);
				err--;
			}
		}
	}

}

