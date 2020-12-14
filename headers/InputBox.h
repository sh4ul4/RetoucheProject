#pragma once
#include "Input.h"
#include "Texture.h"
#include "Window.h"
#include "Button.h"

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
	void render(const Point2& PanelPosition, const Window& win) {
		if (texture == nullptr)return;
		SDL_Rect rect_f{ 0,0,w,h };
		SDL_Rect dstrect_f{ position.x + PanelPosition.x,position.y+PanelPosition.y,w,h };
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
	int maxWidth;
	// Button
	Button validationButton;
	std::string validatedText;
public:
	InputBox() = delete;
	InputBox(const Point2& position, const int& maxWidth, const Window& w) :position(position), maxWidth(maxWidth) {
		tb = TextBox(text.c_str(), "../fonts/font.ttf", 12, black, position, 0, 0, w);
		validationButton = Button(Point2(maxWidth - 11, 0), 10, 10); // button-position is relative
	}
	void render(const Point2& Panelposition, const Window& w) {
		if (updated)tb.update(text.c_str(), "../fonts/font.ttf", 12, black, position + Panelposition, 0, 0, w);
		tb.render(Panelposition, w);
		validationButton.render(position + Panelposition, black,w);
		updated = false;
	}
	void clear() {
		text.clear();
	}
	std::string getText() {
		return text;
	}
	std::string getValidatedText() {
		return validatedText;
	}
	void update(InputEvent& event,const Point2& panelPosition) {
		const char c = event.GetChar();
		if (c == NULL);
		else if (c == -1 && text.empty() == false) text.pop_back();
		else text += c;
		updated = true;
		// validation part
		if (event.mouse.leftClick && validationButton.inside(Point2(event.mouse.x, event.mouse.y) - position - panelPosition)) {
			validatedText = text;
			event.mouse.leftClick = false;
		}
	}
};