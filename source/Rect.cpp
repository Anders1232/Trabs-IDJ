#include "Rect.h"

Rect::Rect(void): x(0), y(0), w(0), h(0)
{
}
Rect::Rect(float x, float y, float w, float h):x(x), y(y), w(w), h(h)
{
}
Rect::operator SDL_Rect ()const
{
	SDL_Rect rec;
	rec.x= x;
	rec.y= y;
	rec.w= w;
	rec.h= h;
	return rec;
}
Rect::operator Vec2 ()const
{
	return Vec2(x, y);
}
Rect Rect::operator+(Vec2 const &a) const
{
	return Rect(x+a.x, y+a.y, w, h);
}
//		SDL_Rect operator-(SDL_Rect const &b) const;
Rect Rect::operator=(Vec2 const &a)
{
	x=a.x;
	y=a.y;
	return *this;
}
Vec2 Rect::Center(void) const
{
	return Vec2(x+(0.5 * w), y+(0.5 * h) );

}
