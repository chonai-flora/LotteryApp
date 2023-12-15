#include "Common.hpp"
#include "Slide.hpp"
#include "Lottery.hpp"
#include "Snowfall.hpp"

void Main() {
	// ウィンドウ設定
	TextReader reader{ U"config/title.txt" };
	if (not reader) {
		throw Error{ U"Failed to load `config/title.txt`" };
	}
	const String windowTitle{ reader.readLine().value_or(U"抽選会") };
	Window::SetTitle(windowTitle);
	Window::SetFullscreen(true);

	// フォント・テクスチャ設定
	for (const auto& size : Range(80, 120, 20)) {
		FontAsset::Register(Format(size), size, Typeface::Heavy);
	}
	const Texture snowEmoji{ U"❄"_emoji };
	const Polygon rightArrow{ { 60, 0 }, { 0, 30 }, { 15, 0 }, { 0, -30 } };
	const Polygon leftArrow{ rightArrow.scaled(-1, 1) };
	const Texture background{ Image{ Resource(U"assets/background.jpg") }.scaled(Scene::Size()) };

	// 雪を生成
	Array<Snowfall> snowfalls;
	for (int i = 0; i < 250; i++) {
		const bool isCrystal = (i % 2 == 0);
		snowfalls << Snowfall(isCrystal, snowEmoji);
	}

	// 1~5年生までの3学科+専攻科2学年の人数を指定
	const CSV members{ U"config/members.csv" };
	if (not members) {
		throw Error{ U"Failed to load `config/members.csv`" };
	}
	const Array<Array<String>> membersData{ members.getData() };
	Lottery lottery(Parse<int32>(membersData[1][1]), Parse<int32>(membersData[1][2]), Parse<int32>(membersData[1][3]),
					Parse<int32>(membersData[2][1]), Parse<int32>(membersData[2][2]), Parse<int32>(membersData[2][3]),
					Parse<int32>(membersData[3][1]), Parse<int32>(membersData[3][2]), Parse<int32>(membersData[3][3]),
					Parse<int32>(membersData[4][1]), Parse<int32>(membersData[4][2]), Parse<int32>(membersData[4][3]),
					Parse<int32>(membersData[5][1]), Parse<int32>(membersData[5][2]), Parse<int32>(membersData[5][3]),
					Parse<int32>(membersData[1][4]), Parse<int32>(membersData[2][4]));

	// 当選者のログファイル
	const String dateFormat{
		DateTime::Now()
			.format()
			.replace(U"-", U"")
			.replace(U" ", U"T")
			.replace(U":", U"")
	};
	TextWriter logFile(U"log/winners_{}.txt"_fmt(dateFormat));
	if (not logFile) {
		throw Error{ U"Failed to load a new log file." };
	}

	// 休学・退学等を除外
	//lottery.removeStudents(3, Course::MI, {});

	// 抽選・当選画面を生成
	Array<Slide> slides{ Slide({ windowTitle }, U"120") };
	const CSV gifts{ U"config/gifts.csv" };
	if (not gifts) {
		throw Error{ U"Failed to load `config/gifts.csv`" };
	}

	for (const auto& gift : gifts.getData().slice(1, gifts.rows() - 1)) {
		const int32 giftCount = Parse<int32>(gift[1]);
		const String title{ U"{}({}名)"_fmt(gift[0], giftCount) };

		slides << Slide(title.split(U' '), U"120");
		const int32 l = 0, r = static_cast<int32>(Math::Ceil(giftCount / 10.0));
		for (int32 i = l; i < r; i++) {
			const int32 n = Min(giftCount - i * 10, 10);
			const bool insertLineFeed = (i + 1 == r);
			slides << Slide(lottery.chooseStudents(n, i == 0 ? title : U"", logFile, insertLineFeed), n > 6 ? U"80" : U"100");
		}
	}
	TextReader singOff{ U"config/sing_off.txt" };
	if (not singOff) {
		throw Error{ U"Failed to load `config/sing_off.txt`" };
	}
	slides << Slide(singOff.readAll().split(U'\n'), U"80");

	// slides の先頭からイテレータをまわす
	auto slide = slides.begin();

	while (System::Update() && slide != slides.end()) {
		// 背景画像表示
		background.draw(0, 0, ColorF(1, 0.5));

		// 雪を降らせる
		for (auto& snowfall : snowfalls) {
			snowfall.update();
			snowfall.draw();
		}

		// スライド表示
		slide->draw();

		// 飾り
		if (slide == slides.begin()) {
			const double ratio = Math::Cos(Scene::Time() * 2);
			for (int32 i = 0; i < 2; i++) {
				const int32 delta = (i == 0 ? 5 : 0);
				const Point pos{ Scene::Center().movedBy(delta, delta) };
				const Color color{ (i == 0 ? Palette::Black : Palette::White) };

				rightArrow
					.scaled(1, ratio)
					.movedBy(pos.movedBy(-250, 250))
					.draw(color);
				leftArrow
					.scaled(1, ratio)
					.movedBy(pos.movedBy(250, 250))
					.draw(color);
				FontAsset(U"80")(U"START")
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
