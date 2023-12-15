#pragma once
#include "Common.hpp"

class Slide {
public:
	Slide(const Array<String>& messages,const String& fontname);
	void draw() const;

private:
	Array<String> m_messages;
	String m_fontname;

	void textWithShadow(const String& message, Vec2 pos) const;
};
