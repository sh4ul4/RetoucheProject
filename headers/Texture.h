#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "library.h"
#include "Draw.h"

class Texture {
public:
	SDL_Surface* surface;
	SDL_Surface* shaderedSurface;
	SDL_Texture* texture;
	SDL_Texture* shaderedTexture;
	Uint32 textureFormat = NULL;
	SDL_PixelFormat* pixelFormat;
private:
	void* lockedPixels = nullptr;
	int width = NULL;
	int height = NULL;
	int access = NULL;
	const char* path;
public:
	Texture() = delete;
	Texture(const char* path, SDL_Renderer* renderer) : lockedPixels(nullptr), path(path) {
		// load surface from image
		if (path == nullptr) { std::cout << "Wrong path name for object of class [Texture].\n"; exit(1); }
		SDL_Surface* newsurface = nullptr;
		surface = nullptr;
		shaderedSurface = nullptr;
		shaderedTexture = nullptr;
		newsurface = IMG_Load(path);
		if (newsurface == nullptr) { std::cout << "ERROR : [" << path << "] could not be loaded.\n"; exit(1); }
		// convert the pixel-format of the surface to ARGB32/ARGB8888
		pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB32);
		surface = SDL_ConvertSurface(newsurface, pixelFormat, 0);
		SDL_FreeSurface(newsurface);
		const char* error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured in Texture(): " << error_f << std::endl; }
		if (surface == nullptr) { std::cout << "ERROR : surface conversion.\n"; exit(1); }
		// create texture from surface
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(texture, &textureFormat, &access, &width, &height);
		error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured in Texture(): " << error_f << std::endl; }
	}
	~Texture() {
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(shaderedTexture);
		pixelFormat = NULL;
		SDL_FreeSurface(surface);
		SDL_FreeSurface(shaderedSurface);
		SDL_FreeFormat(pixelFormat);
		const char* error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured in ~Texture(): " << error_f << std::endl; }
	}
	void setShadered(SDL_Surface* newSurface) {
		if (newSurface == NULL) {
			std::cout << "Error occured in setShadered(): empty Surface as argument." << std::endl; exit(1);
		}
		SDL_FreeSurface(shaderedSurface);
		shaderedSurface = nullptr;
		//	shaderedSurface = SDL_CreateRGBSurface(0, newSurface->w, newSurface->h, 32, 0, 0, 0, 0);
		//	SDL_BlitSurface(newSurface, NULL, shaderedSurface, NULL);
		shaderedSurface = SDL_ConvertSurface(newSurface, newSurface->format, 0);
		if (shaderedSurface == nullptr) { std::cout << "ERROR : surface conversion.\n"; exit(1); }
	}
	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }
	const char* getPath() const { return path; }
	void updateTexture(SDL_Renderer* renderer) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		const char* error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured in updateTexture() : " << error_f << std::endl; }
		if (texture == NULL) exit(1);
	}
	void updateShaderedTexture(SDL_Renderer* renderer) {
		if (shaderedSurface == NULL) {
			std::cout << "invalid [shaderedSurface]"<< std::endl;
			exit(1);
		}
		if (shaderedTexture != nullptr) SDL_DestroyTexture(shaderedTexture);
		shaderedTexture = SDL_CreateTextureFromSurface(renderer, shaderedSurface);
		if (shaderedTexture == NULL) exit(1);
	}
	void updateShaderedTexture(SDL_Renderer* renderer, SDL_Surface* surface) {
		//if (shaderedTexture != NULL)return;
		if (surface == NULL) {
			std::cout << "invalid [surface]" << std::endl;
			exit(1);
		}
		if (shaderedTexture != nullptr) SDL_DestroyTexture(shaderedTexture);
		shaderedTexture = SDL_CreateTextureFromSurface(renderer, surface);
		if (shaderedTexture == NULL) exit(1);
	}
	void changeRGBA(const int& x, const int& y, const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a) {
		if (x < 0 || y < 0 || x > width -1 || y > height -1) {
			std::cout << "Given values out of range." << std::endl; exit(1);
		}
		Uint32* const pixels = (Uint32*)surface->pixels;
		const Uint32 pixel = SDL_MapRGBA(pixelFormat, r, g, b, a);
		pixels[(y * surface->w) + x] = pixel;
	}
	inline void getRGBA(const int& x, const int& y, Uint8* r, Uint8* g, Uint8* b, Uint8* a) const {
		Uint32* pixels = (Uint32*)surface->pixels;
		SDL_GetRGBA(pixels[(y * surface->w) + x], surface->format, r, g, b, a);
	}
	void renderTexture(SDL_Renderer* renderer, const Point2& topLeft, const unsigned int& width, const unsigned int& height, const int& flip, const double& angle) const
	{
		SDL_Rect rect_f;
		rect_f.x = 0;
		rect_f.y = 0;
		if (this->width == 0) { rect_f.w = width; }
		else rect_f.w = this->width;
		if (this->height == 0) { rect_f.h = height; }
		else rect_f.h = this->height;

		SDL_Rect dstrect_f{ topLeft.x,topLeft.y,(int)width,(int)height };

		switch (flip) {
		case 0: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		case 1: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_HORIZONTAL); break;
		case 2: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_VERTICAL); break;
		default: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		}
	}
	void renderShadered(SDL_Renderer* renderer, const Point2& topLeft, const Point2& lowRight, const int& flip, const double& angle) const 
	{
		const SDL_Rect dstrect_f{ topLeft.x,topLeft.y,lowRight.x - topLeft.x,lowRight.y - topLeft.y };

		switch (flip) {
		case 0: SDL_RenderCopyEx(renderer, shaderedTexture, NULL, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		case 1: SDL_RenderCopyEx(renderer, shaderedTexture, NULL, &dstrect_f, angle, NULL, SDL_FLIP_HORIZONTAL); break;
		case 2: SDL_RenderCopyEx(renderer, shaderedTexture, NULL, &dstrect_f, angle, NULL, SDL_FLIP_VERTICAL); break;
		default: SDL_RenderCopyEx(renderer, shaderedTexture, NULL, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		}
		const char* error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured in renderShadered(): " << error_f << std::endl; }
	}
	void saveBMP(const char* path) const {
		SDL_SaveBMP(surface, path);
		const char* error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured : " << error_f << std::endl; }
	}
	void savePNG(const char* path) const {
		IMG_SavePNG(surface, path);
		const char* error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured : " << error_f << std::endl; }
	}
	void convertSRCToPNG32(void) const {
		savePNG(path);
	}
	void saveJPG(const char* path) const {
		IMG_SaveJPG(surface, path, NULL);
		const char* error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured : " << error_f << std::endl; }
	}
	static inline Uint32 rgbaToUint32(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a) {
		return (r << 24) + (g << 16) + (b << 8) + (a);
	}
};

#endif // !TEXTURE_H
