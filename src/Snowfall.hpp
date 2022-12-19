#pragma once
#include "Common.hpp"

class Snowfall {
public:
	Snowfall(bool isCrystal);
	void update();
	void draw(Texture texture) const;

private:
	Vec2 m_pos;
	Vec2 m_delta;
	double m_size;
	double m_alpha;
	bool m_isCrystal;
	Circle m_circle;
};
