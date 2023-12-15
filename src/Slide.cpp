#include "Slide.hpp"

// 当選画面
Slide::Slide(const Array<String>& messages, const String& fontname)
	: m_messages(messages)
	, m_fontname(fontname) {}

void Slide::textWithShadow(const String& message, Vec2 pos) const {
	pos += Scene::Center();

	FontAsset(m_fontname)(message)
		.draw(Arg::center(pos.movedBy(5, 5)), ColorF{ 0.0, 0.7 });
	FontAsset(m_fontname)(message)
		.draw(Arg::center(pos), Palette::Snow);
}

void Slide::draw() const {
	const int32 length = static_cast<int32>(m_messages.size());

	if (length == 0) {
		return;
	}
	else if (length == 1) {
		const String message{ m_messages.front() };

		textWithShadow(message, { 0, 0 });
	}
	else if (length == 2) {
		for (int32 i = 0; i < 2; i++) {
			const String message{ m_messages.at(i) };

			textWithShadow(message, { 0, i * 200 - 100 });
		}
	}
	else {
		String message{ U"" };
		for (int32 i = 0; i < length; i++) {
			message += m_messages.at(i) + U"  ";

			if (i == length / 2 - 1) {
				textWithShadow(message, { 0, -100 });
				message.clear();
			}
			else if (i == length - 1) {
				textWithShadow(message, { 0, 100 });
			}
		}
	}
}
