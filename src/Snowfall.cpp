#include "Snowfall.hpp"

// 雪
Snowfall::Snowfall(bool isCrystal, Texture emoji) {
	m_pos = Vec2{ Random(Scene::Width()), Random(Scene::Height()) };
	m_delta = Vec2{ -Random(1.5), Random(1.5, 3.0) };
	m_size = Random(15.0, 40.0);
	m_alpha = Random(0.75);
	m_isCrystal = isCrystal;
	m_circle = Circle{ { 0, 0 },  m_size / 3 };
	m_emoji = emoji;
}

void Snowfall::update() {
	m_pos += m_delta;
	if (-m_size > m_pos.x) {
		m_pos.x = m_size + Scene::Width();
	}
	if (m_pos.y > m_size + Scene::Height()) {
		m_pos.y = -m_size;
	}
}

void Snowfall::draw() const {
	if (m_isCrystal) {
		m_emoji
			.resized(m_size)
			.draw(m_pos, ColorF{ 1, m_alpha });
	}
	else {
		m_circle
			.movedBy(m_pos)
			.draw(ColorF{ 1, m_alpha });
	}
}
