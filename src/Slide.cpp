#include "Slide.hpp"

// 当選画面
Slide::Slide(Array<String> messages, String fontName) {
	m_messages = messages;
	m_fontName = fontName;
}

void Slide::draw() const {
	int32 length = (int32)m_messages.size();

	if (length == 0) {
		return;
	}
	else if (length == 1) {
		String message = m_messages.front();

		FontAsset(m_fontName)(message)
			.draw(Arg::center(Scene::Center().movedBy(5, 5)), ColorF{ 0.0, 0.7 });
		FontAsset(m_fontName)(message)
			.draw(Arg::center(Scene::Center()), Palette::Snow);
	}
	else if (length == 2) {
		for (int i = 0; i < 2; i++) {
			String message = m_messages.at(i);

			FontAsset(m_fontName)(message)
				.draw(Arg::center(Scene::Center().movedBy(5, i * 200 - 100 + 5)), ColorF{ 0.0, 0.7 });
			FontAsset(m_fontName)(message)
				.draw(Arg::center(Scene::Center().movedBy(0, i * 200 - 100)), Palette::Snow);
		}
	}
	else {
		String message = length == 7 ? U"     " : U"";
		for (int32 i = 0; i < length; i++) {
			message += m_messages.at(i);

			if (i == length / 2 - 1) {
				message += U"\n\n";
			}
			else if (i != length - 1) {
				message += U"  ";
			}
		}

		FontAsset(m_fontName)(message)
			.draw(Arg::center(Scene::Center().movedBy(5, 5)), ColorF{ 0.0, 0.7 });
		FontAsset(m_fontName)(message)
			.draw(Arg::center(Scene::Center()), Palette::Snow);
	}
}
