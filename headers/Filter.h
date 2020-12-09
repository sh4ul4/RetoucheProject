#pragma once
#include "Texture.h"
#include "Window.h"

class Filter {
public:
	void filter(Texture& texture, const Window& w, const double& value) {
		Uint32* const pixels = (Uint32*)texture.surface->pixels;
		for (int x = 0; x < texture.getHeight(); x++) {
			for (int y = 0; y < texture.getWidth(); y++) {
				/*// get pixel data
				Uint8 r, g, b, a;
				SDL_GetRGBA(pixels[(y * texture.surface->w) + x], texture.surface->format, &r, &g, &b, &a);
				int R = r;
				int G = g;
				int B = b;
				int A = a;
				// modify pixel data
				R += value;
				G += value;
				B += value;
				A;
				// check pixel data
				if (R > 255)R = 255;
				if (R < 0)R = 0;
				if (G > 255)G = 255;
				if (G < 0)G = 0;
				if (B > 255)B = 255;
				if (B < 0)B = 0;
				if (A > 255)A = 255;
				if (A < 0)A = 0;
				// put pixel data
				const Uint32 pixel = SDL_MapRGBA(texture.pixelFormat, R, G, B, A);
				pixels[(y * texture.surface->w) + x] = pixel;*/
			}
		}
		texture.updateTexture(w.getRenderer());
	}
};

class ContrastFilter : public Filter {
public:
    void filter(Texture& texture, const Window& w, const double& value) {
		const double contrast = pow((100 + value) / 100, 2);
		if (texture.surface == nullptr) { std::cout << "Error in filter: surface is nullptr" << std::endl; }
		SDL_LockSurface(texture.surface);
		Uint32* pixels = (Uint32*)texture.surface->pixels;
		for (int x = 0; x < texture.surface->h; x++) {
			for (int y = 0; y < texture.surface->w; y++) {
				// get pixel data
				Uint8 r, g, b, a;
				SDL_GetRGBA(pixels[(y * texture.surface->w) + x], texture.surface->format, &r, &g, &b, &a);
				int R = r;
				int G = g;
				int B = b;
				int A = a;
				// modify pixel data
				R = (int)(((((R / 255.0) - 0.5) * contrast) + 0.5) * 255.0);
				G = (int)(((((G / 255.0) - 0.5) * contrast) + 0.5) * 255.0);
				B = (int)(((((B / 255.0) - 0.5) * contrast) + 0.5) * 255.0);
				A;
				// check pixel data
				if (R > 255)R = 255;
				if (R < 0)R = 0;
				if (G > 255)G = 255;
				if (G < 0)G = 0;
				if (B > 255)B = 255;
				if (B < 0)B = 0;
				if (A > 255)A = 255;
				if (A < 0)A = 0;
				// put pixel data
				r = R;
				g = G;
				b = B;
				a = A;
				const Uint32 pixel = SDL_MapRGBA(texture.pixelFormat, r, g, b, a);
				pixels[(y * texture.surface->w) + x] = pixel;
			}
		}
		SDL_UnlockSurface(texture.surface);
		texture.updateTexture(w.getRenderer());
    }
};