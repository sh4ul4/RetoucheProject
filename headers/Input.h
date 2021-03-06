#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "library.h"

struct Mouse {
	int x = 0; // Mouse-X-Position
	int y = 0; // Mouse-Y-Position
	bool rightClick = false; // 1 if clic else 0
	bool leftClick = false; // 1 if clic else 0
	bool moving = false; // indicates if mouse is moving or not
	void setBack(void) {
		x = y = rightClick = leftClick = moving = 0;
	}
};

struct KeyBoard { // Key-entries
	 // Basic Characters
	bool a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, p = 0, q = 0, r = 0, s = 0, t = 0, u = 0, v = 0, w = 0, x = 0, y = 0, z = 0;
	bool A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0, I = 0, J = 0, K = 0, L = 0, M = 0, N = 0, O = 0, P = 0, Q = 0, R = 0, S = 0, T = 0, U = 0, V = 0, W = 0, X = 0, Y = 0, Z = 0;
	// Arrows
	bool up = 0, down = 0, left = 0, right = 0;
	// Numbers
	bool _0 = 0, _1 = 0, _2 = 0, _3 = 0, _4 = 0, _5 = 0, _6 = 0, _7 = 0, _8 = 0, _9 = 0;
	// F#
	bool F1 = 0, F2 = 0, F3 = 0, F4 = 0, F5 = 0, F6 = 0, F7 = 0, F8 = 0, F9 = 0, F10 = 0, F11 = 0, F12 = 0;
	// Special Characters
	bool tab = 0;
	bool plus = 0;
	bool minus = 0;
	bool slash = 0;
	bool backslash = 0;
	bool equal = 0;
	bool point = 0;
	bool semicolon = 0;
	bool escape = 0;
	bool space = 0;
	bool enter = 0;
	bool delete_ = 0;
	bool quote = 0;
	bool comma = 0;
	bool shift = 0;
	bool backSpace = 0;
	void setBack(void)
	{
		a = b = c = d = e = f = g = h = i = j = k = l = m = n = o = p = q = r = s = t = u = v = w = x = y = z =
		A = B = C = D = E = F = G = H = I = J = K = L = M = N = O = P = Q = R = S = T = U = V = W = X = Y = Z =
		up = down = left = right =
		_0 = _1 = _2 = _3 = _4 = _5 = _6 = _7 = _8 = _9 =
		F1 = F2 = F3 = F4 = F5 = F6 = F7 = F8 = F9 = F10 = F11 = F12 =
		tab = plus = minus = slash = backslash = equal = point = semicolon =
		escape = space = enter = delete_ = quote = comma = shift = backSpace = 0;
	}
};

class InputEvent {
public:
	SDL_Event event;
	Mouse mouse;
	KeyBoard keyboard;
	InputEvent() {
		update();
	}
	void update() {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) exit(0); // exit the window
			//mouse
			if (event.type == SDL_MOUSEMOTION) { // mouse motions
				mouse.moving = true;
				SDL_GetMouseState(&mouse.x, &mouse.y);
			}
			else { mouse.moving = false; }
			if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) { mouse.leftClick = true; }
			if ((event.type == SDL_MOUSEBUTTONUP) && (event.button.button == SDL_BUTTON_LEFT)) { mouse.leftClick = false; }
			if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_RIGHT)) { mouse.rightClick = true; }
			if ((event.type == SDL_MOUSEBUTTONUP) && (event.button.button == SDL_BUTTON_RIGHT)) { mouse.rightClick = false; }
			else { mouse.rightClick = false; }
			//keyboard
			if (event.type == SDL_KEYDOWN) { // if the user presses a key down
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: keyboard.escape = true; break;
				case SDLK_LEFT: keyboard.left = true; break;
				case SDLK_RIGHT: keyboard.right = true; break;
				case SDLK_UP: keyboard.up = true; break;
				case SDLK_DOWN: keyboard.down = true; break;
				case SDLK_SPACE: keyboard.space = true; break;
				case SDLK_RETURN: keyboard.enter = true; break;
				case SDLK_DELETE: keyboard.delete_ = true; break;
				case SDLK_QUOTE: keyboard.quote = true; break;
				case SDLK_COMMA: keyboard.comma = true; break;
				case SDLK_LSHIFT: keyboard.shift = true; break;
				case SDLK_RSHIFT: keyboard.shift = true; break;
				case SDLK_BACKSPACE: keyboard.backSpace = true; break;
				case SDLK_a: keyboard.a = true; break;
				case SDLK_b: keyboard.b = true; break;
				case SDLK_c: keyboard.c = true; break;
				case SDLK_d: keyboard.d = true; break;
				case SDLK_e: keyboard.e = true; break;
				case SDLK_f: keyboard.f = true; break;
				case SDLK_g: keyboard.g = true; break;
				case SDLK_h: keyboard.h = true; break;
				case SDLK_i: keyboard.i = true; break;
				case SDLK_j: keyboard.j = true; break;
				case SDLK_k: keyboard.k = true; break;
				case SDLK_l: keyboard.l = true; break;
				case SDLK_m: keyboard.m = true; break;
				case SDLK_n: keyboard.n = true; break;
				case SDLK_o: keyboard.o = true; break;
				case SDLK_p: keyboard.p = true; break;
				case SDLK_q: keyboard.q = true; break;
				case SDLK_r: keyboard.r = true; break;
				case SDLK_s: keyboard.s = true; break;
				case SDLK_t: keyboard.t = true; break;
				case SDLK_u: keyboard.u = true; break;
				case SDLK_v: keyboard.v = true; break;
				case SDLK_w: keyboard.w = true; break;
				case SDLK_x: keyboard.x = true; break;
				case SDLK_y: keyboard.y = true; break;
				case SDLK_z: keyboard.z = true; break;
				case SDLK_0: keyboard._0 = true; break;
				case SDLK_1: keyboard._1 = true; break;
				case SDLK_2: keyboard._2 = true; break;
				case SDLK_3: keyboard._3 = true; break;
				case SDLK_4: keyboard._4 = true; break;
				case SDLK_5: keyboard._5 = true; break;
				case SDLK_6: keyboard._6 = true; break;
				case SDLK_7: keyboard._7 = true; break;
				case SDLK_8: keyboard._8 = true; break;
				case SDLK_9: keyboard._9 = true; break;
				case SDLK_F1: keyboard.F1 = true; break;
				case SDLK_F2: keyboard.F2 = true; break;
				case SDLK_F3: keyboard.F3 = true; break;
				case SDLK_F4: keyboard.F4 = true; break;
				case SDLK_F5: keyboard.F5 = true; break;
				case SDLK_F6: keyboard.F6 = true; break;
				case SDLK_F7: keyboard.F7 = true; break;
				case SDLK_F8: keyboard.F8 = true; break;
				case SDLK_F9: keyboard.F9 = true; break;
				case SDLK_F10: keyboard.F10 = true; break;
				case SDLK_F11: keyboard.F11 = true; break;
				case SDLK_F12: keyboard.F12 = true; break;
				case SDLK_TAB: keyboard.tab = true; break;
				case SDLK_PLUS: keyboard.plus = true; break;
				case SDLK_MINUS: keyboard.minus = true; break;
				case SDLK_SLASH: keyboard.slash = true; break;
				case SDLK_BACKSLASH: keyboard.backslash = true; break;
				case SDLK_EQUALS: keyboard.equal = true; break;
				case SDLK_DECIMALSEPARATOR: keyboard.point = true; break;
				case SDLK_SEMICOLON: keyboard.semicolon = true; break;
				default: break;
				}
			}
			if (event.type == SDL_KEYUP) { // if the user releases a key
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: keyboard.escape = false; break;
				case SDLK_LEFT: keyboard.left = false; break;
				case SDLK_RIGHT: keyboard.right = false; break;
				case SDLK_UP: keyboard.up = false; break;
				case SDLK_DOWN: keyboard.down = false; break;
				case SDLK_SPACE: keyboard.space = false; break;
				case SDLK_RETURN: keyboard.enter = false; break;
				case SDLK_DELETE: keyboard.delete_ = false; break;
				case SDLK_QUOTE: keyboard.quote = false; break;
				case SDLK_COMMA: keyboard.comma = false; break;
				case SDLK_LSHIFT: keyboard.shift = false; break;
				case SDLK_RSHIFT: keyboard.shift = false; break;
				case SDLK_BACKSPACE: keyboard.backSpace = false; break;
				case SDLK_a: keyboard.a = false; break;
				case SDLK_b: keyboard.b = false; break;
				case SDLK_c: keyboard.c = false; break;
				case SDLK_d: keyboard.d = false; break;
				case SDLK_e: keyboard.e = false; break;
				case SDLK_f: keyboard.f = false; break;
				case SDLK_g: keyboard.g = false; break;
				case SDLK_h: keyboard.h = false; break;
				case SDLK_i: keyboard.i = false; break;
				case SDLK_j: keyboard.j = false; break;
				case SDLK_k: keyboard.k = false; break;
				case SDLK_l: keyboard.l = false; break;
				case SDLK_m: keyboard.m = false; break;
				case SDLK_n: keyboard.n = false; break;
				case SDLK_o: keyboard.o = false; break;
				case SDLK_p: keyboard.p = false; break;
				case SDLK_q: keyboard.q = false; break;
				case SDLK_r: keyboard.r = false; break;
				case SDLK_s: keyboard.s = false; break;
				case SDLK_t: keyboard.t = false; break;
				case SDLK_u: keyboard.u = false; break;
				case SDLK_v: keyboard.v = false; break;
				case SDLK_w: keyboard.w = false; break;
				case SDLK_x: keyboard.x = false; break;
				case SDLK_y: keyboard.y = false; break;
				case SDLK_z: keyboard.z = false; break;
				case SDLK_0: keyboard._0 = false; break;
				case SDLK_1: keyboard._1 = false; break;
				case SDLK_2: keyboard._2 = false; break;
				case SDLK_3: keyboard._3 = false; break;
				case SDLK_4: keyboard._4 = false; break;
				case SDLK_5: keyboard._5 = false; break;
				case SDLK_6: keyboard._6 = false; break;
				case SDLK_7: keyboard._7 = false; break;
				case SDLK_8: keyboard._8 = false; break;
				case SDLK_9: keyboard._9 = false; break;
				case SDLK_F1: keyboard.F1 = false; break;
				case SDLK_F2: keyboard.F2 = false; break;
				case SDLK_F3: keyboard.F3 = false; break;
				case SDLK_F4: keyboard.F4 = false; break;
				case SDLK_F5: keyboard.F5 = false; break;
				case SDLK_F6: keyboard.F6 = false; break;
				case SDLK_F7: keyboard.F7 = false; break;
				case SDLK_F8: keyboard.F8 = false; break;
				case SDLK_F9: keyboard.F9 = false; break;
				case SDLK_F10: keyboard.F10 = false; break;
				case SDLK_F11: keyboard.F11 = false; break;
				case SDLK_F12: keyboard.F12 = false; break;
				case SDLK_TAB: keyboard.tab = false; break;
				case SDLK_PLUS: keyboard.plus = false; break;
				case SDLK_MINUS: keyboard.minus = false; break;
				case SDLK_SLASH: keyboard.slash = false; break;
				case SDLK_BACKSLASH: keyboard.backslash = false; break;
				case SDLK_EQUALS: keyboard.equal = false; break;
				case SDLK_DECIMALSEPARATOR: keyboard.point = false; break;
				case SDLK_SEMICOLON: keyboard.semicolon = false; break;
				default: break;
				}
			}
			if (keyboard.shift == true) { // if the user presses a key down
				if (keyboard.a) {
					keyboard.a = false; keyboard.A = true;
				}
				if (keyboard.b) {
					keyboard.b = false; keyboard.B = true;
				}
				if (keyboard.c) {
					keyboard.c = false; keyboard.C = true;
				}
				if (keyboard.d) {
					keyboard.d = false; keyboard.D = true;
				}
				if (keyboard.e) {
					keyboard.e = false; keyboard.E = true;
				}
				if (keyboard.f) {
					keyboard.f = false; keyboard.F = true;
				}
				if (keyboard.g) {
					keyboard.g = false; keyboard.G = true;
				}
				if (keyboard.h) {
					keyboard.h = false; keyboard.H = true;
				}
				if (keyboard.i) {
					keyboard.i = false; keyboard.I = true;
				}
				if (keyboard.j) {
					keyboard.j = false; keyboard.J = true;
				}
				if (keyboard.k) {
					keyboard.k = false; keyboard.K = true;
				}
				if (keyboard.l) {
					keyboard.l = false; keyboard.L = true;
				}
				if (keyboard.m) {
					keyboard.m = false; keyboard.M = true;
				}
				if (keyboard.n) {
					keyboard.n = false; keyboard.N = true;
				}
				if (keyboard.o) {
					keyboard.o = false; keyboard.O = true;
				}
				if (keyboard.p) {
					keyboard.p = false; keyboard.P = true;
				}
				if (keyboard.q) {
					keyboard.q = false; keyboard.Q = true;
				}
				if (keyboard.r) {
					keyboard.r = false; keyboard.R = true;
				}
				if (keyboard.s) {
					keyboard.s = false; keyboard.S = true;
				}
				if (keyboard.t) {
					keyboard.t = false; keyboard.T = true;
				}
				if (keyboard.u) {
					keyboard.u = false; keyboard.U = true;
				}
				if (keyboard.v) {
					keyboard.v = false; keyboard.V = true;
				}
				if (keyboard.w) {
					keyboard.w = false; keyboard.W = true;
				}
				if (keyboard.x) {
					keyboard.x = false; keyboard.X = true;
				}
				if (keyboard.y) {
					keyboard.y = false; keyboard.Y = true;
				}
				if (keyboard.z) {
					keyboard.z = false; keyboard.Z = true;
				}
			}
			else {
				if (keyboard.A) {
					keyboard.a = true; keyboard.A = false;
				}
				if (keyboard.B) {
					keyboard.b = true; keyboard.B = false;
				}
				if (keyboard.C) {
					keyboard.c = true; keyboard.C = false;
				}
				if (keyboard.D) {
					keyboard.d = true; keyboard.D = false;
				}
				if (keyboard.E) {
					keyboard.e = true; keyboard.E = false;
				}
				if (keyboard.F) {
					keyboard.f = true; keyboard.F = false;
				}
				if (keyboard.G) {
					keyboard.g = true; keyboard.G = false;
				}
				if (keyboard.H) {
					keyboard.h = true; keyboard.H = false;
				}
				if (keyboard.I) {
					keyboard.i = true; keyboard.I = false;
				}
				if (keyboard.J) {
					keyboard.j = true; keyboard.J = false;
				}
				if (keyboard.K) {
					keyboard.k = true; keyboard.K = false;
				}
				if (keyboard.L) {
					keyboard.l = true; keyboard.L = false;
				}
				if (keyboard.M) {
					keyboard.m = true; keyboard.M = false;
				}
				if (keyboard.N) {
					keyboard.n = true; keyboard.N = false;
				}
				if (keyboard.O) {
					keyboard.o = true; keyboard.O = false;
				}
				if (keyboard.P) {
					keyboard.p = true; keyboard.P = false;
				}
				if (keyboard.Q) {
					keyboard.q = true; keyboard.Q = false;
				}
				if (keyboard.R) {
					keyboard.r = true; keyboard.R = false;
				}
				if (keyboard.S) {
					keyboard.s = true; keyboard.S = false;
				}
				if (keyboard.T) {
					keyboard.t = true; keyboard.T = false;
				}
				if (keyboard.U) {
					keyboard.u = true; keyboard.U = false;
				}
				if (keyboard.V) {
					keyboard.v = true; keyboard.V = false;
				}
				if (keyboard.W) {
					keyboard.w = true; keyboard.W = false;
				}
				if (keyboard.X) {
					keyboard.x = true; keyboard.X = false;
				}
				if (keyboard.Y) {
					keyboard.y = true; keyboard.Y = false;
				}
				if (keyboard.Z) {
					keyboard.z = true; keyboard.Z = false;
				}
			}
		}
	}
	char GetChar()
	{
		update();
		if (keyboard.A == 1) { keyboard.A = false; return 'A'; }
		else if (keyboard.B == 1) { keyboard.B = false; return 'B'; }
		else if (keyboard.C == 1) { keyboard.C = false; return 'C'; }
		else if (keyboard.D == 1) { keyboard.D = false; return 'D'; }
		else if (keyboard.E == 1) { keyboard.E = false; return 'E'; }
		else if (keyboard.F == 1) { keyboard.F = false; return 'F'; }
		else if (keyboard.G == 1) { keyboard.G = false; return 'G'; }
		else if (keyboard.H == 1) { keyboard.H = false; return 'H'; }
		else if (keyboard.I == 1) { keyboard.I = false; return 'I'; }
		else if (keyboard.J == 1) { keyboard.J = false; return 'J'; }
		else if (keyboard.K == 1) { keyboard.K = false; return 'K'; }
		else if (keyboard.L == 1) { keyboard.L = false; return 'L'; }
		else if (keyboard.M == 1) { keyboard.M = false; return 'M'; }
		else if (keyboard.N == 1) { keyboard.N = false; return 'N'; }
		else if (keyboard.O == 1) { keyboard.O = false; return 'O'; }
		else if (keyboard.P == 1) { keyboard.P = false; return 'P'; }
		else if (keyboard.Q == 1) { keyboard.Q = false; return 'Q'; }
		else if (keyboard.R == 1) { keyboard.R = false; return 'R'; }
		else if (keyboard.S == 1) { keyboard.S = false; return 'S'; }
		else if (keyboard.T == 1) { keyboard.T = false; return 'T'; }
		else if (keyboard.U == 1) { keyboard.U = false; return 'U'; }
		else if (keyboard.V == 1) { keyboard.V = false; return 'V'; }
		else if (keyboard.W == 1) { keyboard.W = false; return 'W'; }
		else if (keyboard.X == 1) { keyboard.X = false; return 'X'; }
		else if (keyboard.Y == 1) { keyboard.Y = false; return 'Y'; }
		else if (keyboard.Z == 1) { keyboard.Z = false; return 'Z'; }
		else if (keyboard.a == 1) { keyboard.a = false; return 'a'; }
		else if (keyboard.b == 1) { keyboard.b = false; return 'b'; }
		else if (keyboard.c == 1) { keyboard.c = false; return 'c'; }
		else if (keyboard.d == 1) { keyboard.d = false; return 'd'; }
		else if (keyboard.e == 1) { keyboard.e = false; return 'e'; }
		else if (keyboard.f == 1) { keyboard.f = false; return 'f'; }
		else if (keyboard.g == 1) { keyboard.g = false; return 'g'; }
		else if (keyboard.h == 1) { keyboard.h = false; return 'h'; }
		else if (keyboard.i == 1) { keyboard.i = false; return 'i'; }
		else if (keyboard.j == 1) { keyboard.j = false; return 'j'; }
		else if (keyboard.k == 1) { keyboard.k = false; return 'k'; }
		else if (keyboard.l == 1) { keyboard.l = false; return 'l'; }
		else if (keyboard.m == 1) { keyboard.m = false; return 'm'; }
		else if (keyboard.n == 1) { keyboard.n = false; return 'n'; }
		else if (keyboard.o == 1) { keyboard.o = false; return 'o'; }
		else if (keyboard.p == 1) { keyboard.p = false; return 'p'; }
		else if (keyboard.q == 1) { keyboard.q = false; return 'q'; }
		else if (keyboard.r == 1) { keyboard.r = false; return 'r'; }
		else if (keyboard.s == 1) { keyboard.s = false; return 's'; }
		else if (keyboard.t == 1) { keyboard.t = false; return 't'; }
		else if (keyboard.u == 1) { keyboard.u = false; return 'u'; }
		else if (keyboard.v == 1) { keyboard.v = false; return 'v'; }
		else if (keyboard.w == 1) { keyboard.w = false; return 'w'; }
		else if (keyboard.x == 1) { keyboard.x = false; return 'x'; }
		else if (keyboard.y == 1) { keyboard.y = false; return 'y'; }
		else if (keyboard.z == 1) { keyboard.z = false; return 'z'; }
		else if (keyboard.comma == 1) { keyboard.comma = false; return ','; }
		else if (keyboard.minus == 1) { keyboard.minus = false; return '-'; }
		else if (keyboard.quote == 1) { keyboard.quote = false; return '\''; }
		else if (keyboard.space == 1) { keyboard.space = false; return ' '; }
		else if (keyboard.delete_ == 1) { keyboard.delete_ = false; return -1; }
		else if (keyboard.backSpace == 1) { keyboard.backSpace = false; return -1; }
		else if (keyboard.semicolon == 1) { keyboard.semicolon = false; return ';'; }
		else { return NULL; }
	}
};

#endif // !INPUT_H
