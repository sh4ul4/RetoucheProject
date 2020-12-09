#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "library.h"
#include "Draw.h"

class Texture {
public:
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	//Uint32 textureFormat = NULL;
	SDL_PixelFormat* pixelFormat = nullptr;
private:
	void* lockedPixels = nullptr;
	int access = NULL;
	const char* path;
public:
	Texture() = delete;
	Texture(const char* path, SDL_Renderer* renderer) : lockedPixels(nullptr), path(path) {
		// load surface from image
		if (path == nullptr) { std::cout << "Wrong path name for object of class [Texture].\n"; exit(1); }
		SDL_Surface* newsurface = nullptr;
		surface = nullptr;
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
		//SDL_QueryTexture(texture, &textureFormat, &access, &width, &height);
		error_f = SDL_GetError();
		if (*error_f) { std::cout << "Error occured in Texture(): " << error_f << std::endl; }
	}
	~Texture() {
		if(texture)SDL_DestroyTexture(texture);
		if(surface)SDL_FreeSurface(surface);
		if(pixelFormat)SDL_FreeFormat(pixelFormat);
		//const char* error_f = SDL_GetError();
		//if (*error_f) { std::cout << "Error occured in ~Texture(): " << error_f << std::endl; }
	}
	int getWidth() const { return surface->w; }
	int getHeight() const { return surface->h; }
	const char* getPath() const { return path; }
	void updateTexture(SDL_Renderer* renderer) {
		if (surface == nullptr) { std::cout << "ERROR : surface is nullptr\n"; exit(1); }
		if (renderer == nullptr) { std::cout << "ERROR : renderer is nullptr\n"; exit(1); }
		if(texture != nullptr) SDL_DestroyTexture(texture);
		texture = nullptr;
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == nullptr) {
			std::cout << "Error occured in updateTexture() : " << SDL_GetError() << std::endl;
			exit(1);
		}
	}
	void changeRGBA(const int& x, const int& y, const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a) {
		if (x < 0 || y < 0 || x > getWidth() -1 || y > getHeight() -1) {
			std::cout << "Given values out of range." << std::endl; exit(1);
		}
		Uint32* const pixels = (Uint32*)surface->pixels;
		const Uint32 pixel = SDL_MapRGBA(pixelFormat, r, g, b, a);
		pixels[(y * surface->w) + x] = pixel;
	}
	inline void getRGBA(const int& x, const int& y, Uint8* r, Uint8* g, Uint8* b, Uint8* a) const {
		Uint32 const* pixels = (Uint32*)surface->pixels;
		SDL_GetRGBA(pixels[(y * surface->w) + x], surface->format, r, g, b, a);
	}
	void renderTexture(SDL_Renderer* renderer, const Point2& topLeft, const unsigned int& width, const unsigned int& height, const int& flip, const double& angle) const
	{
		SDL_Rect rect_f;
		rect_f.x = 0;
		rect_f.y = 0;
		if (this->getWidth() == 0) { rect_f.w = width; }
		else rect_f.w = this->getWidth();
		if (this->getHeight() == 0) { rect_f.h = height; }
		else rect_f.h = this->getHeight();

		SDL_Rect dstrect_f{ topLeft.x,topLeft.y,(int)width,(int)height };
		if (texture == nullptr) {
			std::cout << "Error occured in renderTexture(): texture is nullptr" << std::endl;
			return;
		}
		switch (flip) {
		case 0: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		case 1: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_HORIZONTAL); break;
		case 2: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_VERTICAL); break;
		default: SDL_RenderCopyEx(renderer, texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		}
		const char* error_f = SDL_GetError();
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

class TextureManager {
	std::vector<Texture>textures;
public:
	void addTexture(const char* path, SDL_Renderer* renderer) {
		textures.emplace_back(path, renderer);
	}
	Texture* at(const int& i) {
		return &textures[i];
	}
};

#endif // !TEXTURE_H
