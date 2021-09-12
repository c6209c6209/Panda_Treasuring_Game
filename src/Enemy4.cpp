#include "Enemy4.hpp"
Enemy4::Enemy4(int x, int y, int w, int h) : Enemy("play/nctufox.png", x, y, w, h, 16, 100) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}
