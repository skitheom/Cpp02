# Cpp02
42 project

# C++ Module 02

## Topics

**Orthodox Canonical Form（正統派標準形）**はC++のクラス設計において「コピーセマンティクスを明示的に管理する」ための基本形

```cpp
#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

class Example {
public:
    // デフォルトコンストラクタ (引数なし。default値で初期化)
    Example(void);

    // コピーコンストラクタ (同じクラス型のオブジェクトを引数とし、新しいオブジェクトを初期化する)
    Example(const Example& other);

    // コピー代入演算子 (既存のオブジェクトに、別のオブジェクトを代入)
    Example& operator=(const Example& other);

    // デストラクタ (オブジェクトが破棄される際にリソースを解放)
    ~Example(void);
};

#endif
```

## Exercises

Module 02では、Ad-hoc polymorphism（アドホック多態性）、演算子のオーバーロード、そしてOrthodox Canonical Form（正統派標準形）を中心に進めます。最初の課題（ex00）は固定小数点数を表すクラスの構築で、このクラスをOrthodox Canonical Formで実装するのが主な目的です。以下が課題の概要です：


/*
課題 00: My First Class in Orthodox Canonical Form

        •	必要なファイル: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
        •	要件:
        •	Fixed クラスを作成し、以下のメンバーを実装：
        •	プライベート属性:

        •	パブリックメンバー関数:
        •	デフォルトコンストラクタ: 値を 0 に初期化。
        •	コピーコンストラクタ。
        •	コピー代入演算子オーバーロード。
        •	デストラクタ。
        •	getRawBits() 関数: 固定小数点数の生値を返す。
        •	setRawBits(int const raw) 関数: 生値を設定する。
        •
クラスの動作を確認するため、指定されたサンプルコードを動かしてみる。

次に、Fixed クラスをさらに発展させる課題があります

 */

 /*

$> ./a.out
Default constructor called
Copy constructor called
Copy assignment operator called // <-- This line may be missing depending on
your implementation getRawBits member function called Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
$>
 */

### Exercise 00: My First Class in
Orthodox Canonical Form

- 固定小数点数の値を格納する整数型変数
- フラクショナルビットの数を表す静的定数整数（値は8）
Exercise : 00
My First Class in Orthodox Canonical Form
Turn-in directory : ex00/
Files to turn in : Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
Forbidden functions : None
You think you know integers and floating-point numbers. How cute.
Please read this 3 pages article (1, 2, 3) to discover that you don’t. Go on, read it.
Until today, every number you used in your code was basically either an integer or a
floating-point number, or any of their variants (short, char, long, double, and so forth).
After reading the article above, it’s safe to assume that integers and floating-point num-
bers have opposite caracteristics.
But today, things will change. You are going to discover a new and awesome number
type: fixed-point numbers! Forever missing from the scalar types of most languages,



課題 00: My First Class in Orthodox Canonical Form

	•	必要なファイル: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
	•	要件:
	•	Fixed クラスを作成し、以下のメンバーを実装：
	•	プライベート属性:
	•	固定小数点数の値を格納する整数型変数。
	•	フラクショナルビットの数を表す静的定数整数（値は 8）。
	•	パブリックメンバー関数:
	•	デフォルトコンストラクタ: 値を 0 に初期化。
	•	コピーコンストラクタ。
	•	コピー代入演算子オーバーロード。
	•	デストラクタ。
	•	getRawBits() 関数: 固定小数点数の生値を返す。
	•	setRawBits(int const raw) 関数: 生値を設定する。
	•	クラスの動作を確認するため、指定されたサンプルコードを動かしてみる。

次に、Fixed クラスをさらに発展させる課題があります。

課題 01: Towards a more useful fixed-point number class

	•	必要なファイル: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
	•	要件:
	•	新たなコンストラクタとメンバー関数を追加:
	•	コンストラクタ:
	•	定数整数を受け取り、それを対応する固定小数点数に変換。
	•	定数浮動小数点数を受け取り、それを対応する固定小数点数に変換。
	•	関数:
	•	toFloat(): 固定小数点数を浮動小数点数に変換。
	•	toInt(): 固定小数点数を整数に変換。
	•	<< 演算子をオーバーロードして、固定小数点数を出力ストリームに挿入可能にする。


これらを進める準備ができたら、教えてください。一緒に進めていきましょう！




