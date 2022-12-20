# LotteryApp
学内抽選会用アプリ

使用言語: C++  
使用ライブラリ: OpenSiv3D v0.6.6

## 使い方
`Main.cpp` の `lottery` に1~5年生までの3学科+専攻科2学年の人数を以下の形式で指定し、`gifts` に `{ 景品名, 人数 }` の形式で入力し実行するとスライドが表示されます。
欠席者等は `Lottery::removeStudents()` で除くことができます。
```Main.cpp
void Main() {
    /* 省略 */

    // 1~5年生までの3学科+専攻科2学年の人数を指定
    Lottery lottery(43, 42, 45,
                    47, 43, 42,
		    44, 43, 50,
		    44, 44, 38,
		    39, 45, 39,
		    31, 35);

    /* 省略 */
    
    // 欠席者等を除外(今回は4A-04, 4A-06, 4A-20を除外)
    lottery.removeStudents(4, Course::A, {4, 6, 20});

    /* 省略 */

    // { 景品名, 人数 } の形式で入力
    const Array<std::pair<String, int32>> gifts = {
	{ U"お菓子詰め合わせ(60名)", 60 },
	{ U"3等賞(3名)", 3 },
	{ U"2等賞(2名)", 2 },
	{ U"1等賞(1名)", 1 }
    };
    
    /* 省略 */
}
```
十字キーでスライドを切り替えることができ、最後のスライドが終了すると自動的にソフトが終了します。
`App/winners.txt` に当選者のログが残ります。再度実行するとログも書き換わるため注意して下さい。



学科名は `Common.hpp` で変更可能です。
```Common.hpp
#pragma once

#include <Siv3D.hpp> // OpenSiv3D v0.6.4

// 学科
enum class Course { A, B, C, D };
const Array<String> courseNames{ U"A-", U"B-", U"C-", U"D-" };
```
