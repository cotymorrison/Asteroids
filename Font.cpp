#include "Font.h"



Font::Font()
{
}

Font::~Font()
{
	cleanup();
}

void Font::cleanup()
{
	SAFE_RELEASE( font );
}

void Font::setFont(ID3DXFont* font)
{
	SAFE_RELEASE( this->font );

	this->font = font;
}