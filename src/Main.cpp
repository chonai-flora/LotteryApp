#include "Common.hpp"
#include "Slide.hpp"
#include "Lottery.hpp"
#include "Snowfall.hpp"

namespace App {
	String title = U"クリスマス抽選会";
	String closingMessage = U"当たった人も当たらなかった人も いいクリスマスを過ごせますように♡";
}

void Main() {
	// ウィンドウ・フォント・テクスチャ設定
	Window::SetTitle(App::title);
	Window::SetFullscreen(true);
	FontAsset::Register(U"ListFont1", 80, Typeface::Heavy);
	FontAsset::Register(U"ListFont2", 100, Typeface::Heavy);
	FontAsset::Register(U"TitleFont", 120, Typeface::Heavy);
	const Texture snowEmoji{ U"❄"_emoji };
	const Polygon rightArrow{ { 60, 0 }, { 0, 30 }, { 15, 0 }, { 0, -30 } };
	const Polygon leftArrow{ rightArrow.scaled(-1, 1) };
	const Image image{ U"../img/back1.png" };
	const Texture background{ image.scaled(Scene::Size()) };

	// 雪を生成
	Array<Snowfall> snowfalls;
	for (int i = 0; i < 250; i++) {
		bool isCrystal = (i % 2 == 0);
		snowfalls << Snowfall(isCrystal, snowEmoji);
	}

	// 抽選会初期化
	Lottery lottery(43, 42, 45,
					47, 43, 42,
					44, 43, 50,
					44, 44, 38,
					39, 45, 39,
					0, 0);

	// 当選者のログファイル
	TextWriter logFile(U"winners.txt");
	if (not logFile) {
		throw Error{ U"Failed to open `winners.txt`" };
	}

	// 休学・退学等を除外
	//lottery.removeStudents(3, Course::MI, {});

	// 抽選・当選画面を生成
	const Array<std::pair<String, int32>> gifts = {
		{ U"カップラーメンセット(60名)", 60 },
		{ U"お菓子セット(60名)", 60 },
		{ U"ハーゲンダッツ(40名)", 40 },
		{ U"ギフトカード(7名)", 7 },
		{ U"3等 手袋(1名)", 1 },
		{ U"3等 トートバッグ(1名)", 1 },
		{ U"3等 ハンカチ(1名)", 1 },
		{ U"2等 yogibo(1名)", 1 },
		{ U"2等 ブランケット(1名)", 1 },
		{ U"1等 ドライヤー(1名)", 1 },
		{ U"1等 プロジェクター(1名)", 1 },
		{ U"1等 スピーカー(1名)", 1 },
		{ U"1等 ワイヤレスイヤフォン(1名)", 1 },
	};
	Array<Slide> slides{ Slide({ App::title }, U"TitleFont") };
	for (const auto& [title, n] : gifts) {
		slides << Slide({ title.split(U' ') }, U"TitleFont");
		if (n % 10 == 0) {
			slides << Slide(lottery.chooseStudents(10, title, logFile, false), U"ListFont1");
			for (int i = 1; i < n / 10; i++) {
				bool insertLineFeed = (i == n / 10 - 1);
				slides << Slide(lottery.chooseStudents(10, U"", logFile, insertLineFeed), U"ListFont1");
			}
		}
		else {
			slides << Slide(lottery.chooseStudents(n, title, logFile), U"ListFont2");
		}
	}
	slides << Slide({ App::closingMessage.split(U' ') }, U"ListFont1");

	// slides の先頭からイテレータをまわす
	auto slide = slides.begin();

	while (System::Update() && slide != slides.end()) {
		// 背景画像表示
		background.draw();

		// 雪を降らせる
		for (auto& snowfall : snowfalls) {
			snowfall.update();
			snowfall.draw();
		}

		// スライド表示
		slide->draw();

		// 飾り
		if (slide == slides.begin()) {
			double ratio = Math::Cos(Scene::Time() * 2);
			for (int i = 0; i < 2; i++) {
				const int32 delta = (i == 0 ? 5 : 0);
				const Point pos = Scene::Center().movedBy(delta, delta);
				const Color color = (i == 0 ? Palette::Black : Palette::White);
				rightArrow
					.scaled(1, ratio)
					.movedBy(pos.movedBy(-250, 250))
					.draw(color);
				leftArrow
					.scaled(1, ratio)
					.movedBy(pos.movedBy(250, 250))
					.draw(color);
				FontAsset(U"ListFont1")(U"START")
					.draw(Arg::center(pos.movedBy(0, 250)), color);
			}
		}

		// 十字キーでスライド切り替え
		if (KeyRight.down()) {
			++slide;
		}
		if (slide != slides.begin() && KeyLeft.down()) {
			--slide;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加（Slack や Twitter, BBS で気軽に質問や情報交換ができます）
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
