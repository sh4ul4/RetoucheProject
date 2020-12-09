#pragma once
#include "Input.h"
#include "Texture.h"
#include "Window.h"

class TextBox {
	SDL_Texture* texture = nullptr;
	Point2 position = { 0,0 };
	int flip = 0;
	double angle = 0;
	int w = 0, h = 0;
public:
	TextBox(){}
	TextBox(const char* text, const char* fontStyle, const int& fontSize, const Color& color,
		const Point2& topLeft, const int& flip, const double& angle, const Window& window) :position(topLeft), flip(flip), angle(angle) {
		TTF_Font* font = TTF_OpenFont(fontStyle, fontSize);
		if (!font) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			exit(1);
			// handle error
		}
		TTF_SizeText(font, text, &w, &h);
		SDL_Surface* surface = TTF_RenderText_Solid(font, text, color.toSDL_Color());
		texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	~TextBox() {
		SDL_DestroyTexture(texture);
	}
	void update(const char* text, const char* fontStyle, const int& fontSize, const Color& color,
		const Point2& topLeft, const int& flip, const double& angle, const Window& window) {
		this->position = position;
		this->flip = flip;
		this->angle = angle;
		TTF_Font* font = TTF_OpenFont(fontStyle, fontSize);
		if (!font) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			exit(1);
			// handle error
		}
		TTF_SizeText(font, text, &w, &h);
		SDL_Surface* surface = TTF_RenderText_Solid(font, text, color.toSDL_Color());
		SDL_DestroyTexture(texture);
		texture = nullptr;
		texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
	}
	void render(const Window& win) {
		if (texture == nullptr)return;
		SDL_Rect rect_f{ 0,0,w,h };
		SDL_Rect dstrect_f{ position.x,position.y,w,h };
		switch (flip) {
		case 0: SDL_RenderCopyEx(win.getRenderer(), texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		case 1: SDL_RenderCopyEx(win.getRenderer(), texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_HORIZONTAL); break;
		case 2: SDL_RenderCopyEx(win.getRenderer(), texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_VERTICAL); break;
		default: SDL_RenderCopyEx(win.getRenderer(), texture, &rect_f, &dstrect_f, angle, NULL, SDL_FLIP_NONE); break;
		}
	}
};

class InputBox {
	std::string text;
	TextBox tb;
	Point2 position;
	bool updated = false;
public:
	InputBox(const Point2& position, const Window& w) :position(position) {
		tb = TextBox(text.c_str(), "../fonts/font.ttf", 12, black, position, 0, 0, w);
	}
	void render(const Window& w) {
		if (updated)tb.update(text.c_str(), "../fonts/font.ttf", 12, black, position, 0, 0, w);
		tb.render(w);
		updated = false;
	}
	void clear() {
		text.clear();
	}
	std::string getText() {
		return text;
	}
	void update(InputEvent& event) {
		const char c = event.GetChar();
		if (c == NULL);
		else if (c == -1 && text.empty() == false) text.pop_back();
		else text += c;
		updated = true;
	}
};