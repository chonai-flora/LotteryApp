# LotteryApp
学内抽選会用アプリ  
使用ライブラリ: OpenSiv3D v0.6.12

## 使い方
### 操作方法
十字キーでスライドを切り替えることができます。Escキーを押す、もしくは最後のスライドが終了すると自動的にソフトが終了します。

### 景品
`config/gifts.csv` に景品情報を保存しています。以下の形式で適宜書き換えてください。
```
景品名,個数
お菓子詰め合わせ,60
3等賞,3
2等賞,2
1等賞,1
```
|景品名|個数|
|--:|:--|
|お菓子詰め合わせ|60|
|3等賞|3|
|2等賞|2|
|1等賞|1|

### タイトル
`config/title.txt` に抽選会のタイトルを入力してください。

### クラス人数
`config/members.csv` に1~5年生までの3学科+専攻科2学年の人数を入力してください。

### 最後のひとこと
最後のスライドに表示するメッセージを `config/sing_off.txt` に入力してください。複数行にわたるメッセージも表示できます。

### 当選者
実行すると `log/winners_*.txt` というログファイルが作成されます。イベント後の当選者の確認に使用してください。

### その他(拡張用)
欠席者等は `Lottery::removeStudents()` で除くことができます。
```cpp
void Main() {
    /* 省略 */
    
    // 欠席者等を除外(今回は4A-04, 4A-06, 4A-20を除外)
    lottery.removeStudents(4, Course::A, { 4, 6, 20 });
    
    /* 省略 */
}
```

学科名は `Common.hpp` で変更可能です。
```cpp
#pragma once

#include <Siv3D.hpp>

// 学科
enum class Course { MI, AC, BC, AP };
const Array<String> courseNames{ U"MI", U"AC", U"BC", U"AP" };
```
