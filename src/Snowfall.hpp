#pragma once
#include "Common.hpp"

class Snowfall {
public:
	Snowfall(bool isCrystal, Texture emoji);
	void update();
	void draw() const;

private:
	Vec2 m_pos;
	Vec2 m_delta;
	double m_size;
	double m_alpha;
	bool m_isCrystal;
	Circle m_circle;
	Texture m_emoji;
};
