#pragma once
#include "Texture.h"
#include "Window.h"

class Filter {
public:
	void filter(Texture& texture, const Window& w) {
		Uint32* const pixels = (Uint32*)texture.surface->pixels;
		for (int x = 0; x < texture.getHeight(); x++) {
			for (int y = 0; y < texture.getWidth(); y++) {
				// get pixel data
				Uint8 r, g, b, a;
				SDL_GetRGBA(pixels[(y * texture.surface->w) + x], texture.surface->format, &r, &g, &b, &a);
				// modify pixel data
				r++;
				g++;
				b++;
				a;
				// check pixel data
				if (r > 255)r = 255;
				if (r < 0)r = 0;
				if (g > 255)g = 255;
				if (g < 0)g = 0;
				if (b > 255)b = 255;
				if (b < 0)b = 0;
				if (a > 255)a = 255;
				if (a < 0)a = 0;
				// put pixel data
				const Uint32 pixel = SDL_MapRGBA(texture.pixelFormat, r, g, b, a);
				pixels[(y * texture.surface->w) + x] = pixel;
			}
		}
		texture.updateTexture(w.getRenderer());
	}
};