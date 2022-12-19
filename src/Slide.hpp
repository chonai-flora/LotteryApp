#pragma once
#include "Common.hpp"

class Slide {
public:
	Slide(Array<String> messages, String fontName);
	void draw() const;

private:
	Array<String> m_messages;
	String m_fontName;
};
