#pragma once

#include "Header.h"


class Font
{
private:
	ID3DXFont*	font;

public:
	Font();
	~Font();

	void setFont(ID3DXFont* font);

	void DrawScore(int score);
	void DrawLevel(int level);
	void DrawLives(int lives);

	void cleanup();
};