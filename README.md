# Cpp02
42 project

# C++ Module 02

## Topics

* Ad*hoc polymorphism（アドホック多態性）
* 演算子のオーバーロード
* Orthodox Canonical Form

**Orthodox Canonical Form（正統派標準形）**

```cpp
#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

class Example {
public:
    // デフォルトコンストラクタ (引数なしdefault値で初期化)
    Example(void);

    // コピーコンストラクタ (同じクラス型のオブジェクトを引数とし、新しいオブジェクトを初期化する)
    Example(const Example& other);

    // デストラクタ (オブジェクトが破棄される際にリソースを解放)
    ~Example(void);

    // コピー代入演算子 (既存のオブジェクトに、別のオブジェクトを代入)
    Example& operator=(const Example& other);
};

#endif
```
## Resources
[Understanding and Using Floating Point Numbers](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point.html)

整数型（int）は accuracy に優れるが precision に欠ける（端数を表現できない）。 浮動小数点型（float）は precision に優れる（近似的に端数のある数を表せる）が、 accuracy に欠ける（データサイズが有限なため、例えば 1/3 を正確に表せない）

[Floating point number representation](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_representation.html)

現在最も普及している形式は IEEE*754 標準で、数値は「符号ビット（sign bit）」「指数部（exponent）」「仮数部（mantissa）」で構成される

#### 正規化（Normalization）:
同じ数値を複数の指数部と仮数部の組み合わせで表現できるため、非ゼロの数値では仮数の最初のビットが必ず「1」になるように正規化される。暗黙的（implicit）であり先頭の「1」はメモリには保存されない0は全てのビットが0の状態で表現される（「1.0」の形式にはできないため）

#### 指数部のエンコード（Shift*127）:
実際の指数（actual exponent）に127を足して符号なし整数（0～255）として保存する。シフトエンコードの影響で、最小の指数は*126（1*127）になる（2^*127という極端に小さな数値は表現できなくなるが1.0や0.0を正確に表現することを優先）

#### 特殊な値: 0, 無限大（Infinity）, と非数（NaN）
* 0: 全てのビットが0
* 無限大（Infinity）: 指数部の全ビットが1（最大）、仮数部はすべて0、符号で正負を区別
* 非数（NaN）: 指数部の全ビットが1、仮数部が0以外（少なくとも1ビットが1）、符号あり

計算結果を正しく管理するために必要な特殊数値

#### 非正規化数（Denormalized Numbers）

##### 定義:
指数部が全てゼロの場合、正規化数のルールが適用されず「非正規化数」として扱われる。仮数（Mantissa）には暗黙の「1」が先頭に含まれず、そのまま解釈される（例: 仮数が 0101 の場合 正規化数: 1.0101 非正規化数: 0.0101）

##### 条件:
仮数が全ビット0の場合は「0」として扱われ、非正規化数ではない（特殊ケースとしてのゼロ）。仮数に非ゼロビットが含まれている場合のみ非正規化数として解釈される

##### 特徴:
指数部が全てゼロでも、指数は「数値的には最小値（*126）」として解釈される。これにより、正規化数が扱えない小さな値（￼ 未満）を表現できる。ただし、仮数の先頭に有効な「1」が含まれないため、表現精度は正規化数に比べて低下する

#### イプシロン（Epsilon）

##### 定義:
「浮動小数点数で`1 + x > 1`を満たす最小の`x`」のこと
浮動小数点数の「精度の限界」を示す指標

##### 具体的な意味:
Mantissaの最下位ビットが表現できる最小の値に対応する。特に指数部がゼロ（エンコード後の保存値が127）の場合、Mantissaにおける最下位ビットの寄与がイプシロンになる
￼
##### 精度の限界の意義:
イプシロンは「計算の丸め誤差が発生する最小のスケール」を表し、数値計算における基準として使用される

### Effective FP Programming

あなたの理解は大枠で正しいですが、一部の表現が少し曖昧だったり、具体的な問題点が完全に伝わっていない部分があります。以下に校正した内容を示します。

#### Equality

浮動小数点数（floating point numbers）は、有限のビット数で表現されるため、**丸め誤差（rounding error）**が避けられない。そのため、== 演算子でビット単位の一致を比較しても、実用的な「等しさ」を確認することはできない

さらに、標準Cライブラリの三角関数（sin, cos など）をはじめとする多くの浮動小数点演算関数は、厳密な数学的結果ではなく多項式近似で実装されている。このため、例えば cos(π/2) の結果が理論値の 0 と完全に一致することは期待できない

##### 許容誤差を定義

実用上、浮動小数点数の等しさは「十分に近い（close enough）」という条件で判断されることが多い

```c
#define EPSILON 1.0e-7
#define flt_equals(a, b) (fabs((a) - (b)) < EPSILON)
```

EPSILON: 許容誤差を表す定数。数学で定義される「イプシロン（epsilon）」とは異なる。

この手法は、数値のスケール（magnitude）や指数部（exponent）を考慮していないため、非常に大きな数値や非常に小さな数値では適切な結果にならない。相対誤差や有効数字の視点が必要であることがわかる


#### Overflow

データ型の範囲が有限であるため、型の範囲を超えるオーバーフロー（overflow）が発生する。整数型では最大値を超えると値が反転するが、浮動小数点数ではオーバーフロー時に無限大となる

整数から浮動小数点数への変換では精度の損失に注意が必要。たとえば、int（9桁）は float（7桁）に正確に収まらない場合がある。doubleでは32ビット整数を完全に表現可能だが、型変換にはオーバーヘッドがある

また最終結果が範囲内でも中間結果が型の範囲を超える場合、計算途中でオーバーフローが生じることがある

##### 素朴な実装

以下の実装では、中間結果がオーバーフローする。たとえば、re = 1e200、im = 1e200 の場合、re^2 + im^2 = 1e400 となり、無限大になる。
```c
double magnitude(double re, double im)
{
    return sqrt(re * re + im * im);
}
```
##### 改善された実装

re と im のどちらが大きいかを確認し、小さい方を大きい方で割ることで値の範囲を調整する。これにより、中間結果のオーバーフローを回避する
```c
double magnitude(double re, double im)
{
    double r;

    re = fabs(re);
    im = fabs(im);
    if (re > im) {
        r = im / re;
        return re * sqrt(1.0 + r * r);
    }
    if (im == 0.0)
        return 0.0;
    r = re / im;
    return im * sqrt(1.0 + r * r);
}
```
#### Loss of significance

Loss of significanceは、数値計算において情報を失い、結果の精度が著しく低下する現象を指す。非常に近い数同士の減算や、大きな値と小さな値の加算で発生する。Loss of significanceを避ける一般的な方法は存在しない（計算の内容や式に応じて対処が異なるため）

例えば、複数の数字を足し合わせる際、epsilon程度の大きさの小さな値を後から大きな値に加算すると、数値が失われたり不正確になることがある。対策として、小さい値から順に加算するように数値を並べ替えて処理する方法が取られることがある

#### 指針

* 計算を繰り返すごとにfloatの値は徐々に崩壊し、精度が損なわれる
* feedback（先の出力を次の入力とする）を繰り返すと、誤差が増幅されて計算が不安定になる
* 累積的な計算を避け、初期状態や安定した値を用いて直接計算するほうが望ましい

#### 整数型を忘れずに

整数型は正確性（accuracy）に優れるため、有理数の管理に適している。特に分数を扱う場合、分母だけを整数として保持し、必要に応じて`1.0/denominator`として再生成することで、浮動小数点数の精度問題を最小限に抑えられる

[Printing floating point numbers](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_printing.html)

floating point numberをprintする関数の実装例

#### 未読

https://web.archive.org/web/20231224143018/https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html

## Exercises
### Exercise 00: My First Class in Orthodox Canonical Form

Orthodox Canonical Form（正統派標準形）の導入
固定小数点数（fixed*point number）を表すクラスの構築
* 固定小数点数の値を格納する整数型変数
* フラクショナルビットの数を表す静的定数整数（値は8）
* getRawBits() 関数: 固定小数点数の生値を返す
* setRawBits(int const raw) 関数: 生値を設定

### Exercise 01: Towards a more useful fixed*point number class

整数や浮動小数点数を固定小数点数（fixed*point number）として内部的に扱う

* 必要なファイル: Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
* 要件:
* 新たなコンストラクタとメンバー関数を追加:
* コンストラクタ:
* 定数整数を受け取り、それを対応する固定小数点数に変換
* 定数浮動小数点数を受け取り、それを対応する固定小数点数に変換
* 関数:
* toFloat(): 固定小数点数を浮動小数点数に変換
* toInt(): 固定小数点数を整数に変換
* << 演算子をオーバーロードして、固定小数点数を出力ストリームに挿入可能にする


これらを進める準備ができたら、教えてください一緒に進めていきましょう！




The previous exercise was a good start but our class is pretty useless. It can only
represent the value 0.0.
Add the following public constructors and public member functions to your class:
*  A constructor that takes a constant integer as a parameter.
It converts it to the corresponding fixed*point value. The fractional bits value is
initialized to 8 like in exercise 00.
*  A constructor that takes a constant floating*point number as a parameter.
It converts it to the corresponding fixed*point value. The fractional bits value is
initialized to 8 like in exercise 00.
*  A member function float toFloat( void ) const;
that converts the fixed*point value to a floating*point value.
*  A member function int toInt( void ) const;
that converts the fixed*point value to an integer value.
And add the following function to the Fixed class files:
*  An overload of the insertion («) operator that inserts a floating*point representation
of the fixed*point number into the output stream object passed as parameter


この問題（浮動小数点数の性質）が今回の課題にどのように関係しているかについて説明します以下のポイントに分けて整理します

1. 浮動小数点数を扱う課題の内容

今回の課題では、Fixedクラスを作成し、次のような操作を行います：
* 整数や浮動小数点数を固定小数点数（fixed*point number）として内部的に扱う
* 浮動小数点数を扱うカスタムコンストラクタ（Fixed(float value)）の実装
* 浮動小数点数を整数に変換するメソッド（toInt()）
* 浮動小数点数を小数に変換するメソッド（toFloat()）

2. 関係する課題ポイント

(1) 浮動小数点数の精度と誤差

* 浮動小数点数の計算や変換では、近似値による誤差が発生します
* 課題で Fixed(float value) を実装する際、浮動小数点数を固定小数点数として変換する必要がありますが、このとき 浮動小数点数の誤差 を考慮する必要があります

(2) 整数と浮動小数点数の性質の違い

* toInt() や toFloat() では、整数（正確性）と浮動小数点数（精度）の違いが問題になります
* 例: 浮動小数点数から整数に変換する際、小数部分を切り捨てる（または丸める）と情報が失われます
* 逆に、整数を浮動小数点数に変換すると、近似的な値を取る場合があります

(3) == を使わない設計への配慮

* 浮動小数点数で == を使った比較は誤差のため不正確になる場合があります
* 課題で、浮動小数点数の出力や内部計算を正確に扱う必要がある場合、この特性を考慮する必要があります

3. 具体的にどのように影響するか

(1) Fixed(float value) の実装

浮動小数点数を固定小数点数として内部的に保持する場合：
* 浮動小数点数を「スケーリング」して整数値として保持する必要があります
* 例えば、8ビットの小数部を持つ場合、42.42f は 4242 に変換されて保持されます
* このスケーリングの際、浮動小数点数の「丸め誤差」が影響します

(2) toFloat() の実装

固定小数点数を浮動小数点数に変換する場合：
* 逆のスケーリングが行われます
* 例えば、内部的に保持している 4242 を再び 42.42 に戻します
* この変換でも、丸め誤差が生じる可能性があります

(3) toInt() の実装

浮動小数点数を整数に変換する場合：
* 小数部分を切り捨てたり、四捨五入したりする必要があります
* この際、正確性（accuracy）が重視されますが、情報が失われる（小数部分が削除される）ことに注意が必要です

(4) 出力や比較

課題では、結果を std::ostream に出力する際に << をオーバーロードする必要があります：
* 出力結果が正確であることを保証するため、浮動小数点数の特性（丸め誤差や精度の限界）を考慮してテストする必要があります

4. 課題に対する具体的なアプローチ

例: 浮動小数点数を固定小数点数に変換

1.浮動小数点数を整数として表現するためにスケーリングを行う：

fixedPointNumber_ = roundf(value * (1 << fractionalBits_));

* value を小数部のビット数（fractionalBits_）分だけスケーリング
* スケーリング後に丸め（roundf）を行い、誤差を最小限に抑える

2.固定小数点数を浮動小数点数に戻す：

return (float)fixedPointNumber_ / (1 << fractionalBits_);



例: 浮動小数点数を整数に変換

1.小数部分を切り捨てる方法：

return fixedPointNumber_ >> fractionalBits_;

* 小数部分をそのまま捨てて整数部分だけを取り出します

2.四捨五入する方法（必要に応じて）：

return (fixedPointNumber_ + (1 << (fractionalBits_ * 1))) >> fractionalBits_;

5. まとめ

* 浮動小数点数の特性（精度の高い近似値だが正確さに欠ける）を理解することは、この課題での変換処理や誤差の回避に直接関係します
* 今回の課題では特に、浮動小数点数を固定小数点数として扱うスケーリング処理や、逆変換の精度に注意が必要です
* 誤差を最小限に抑えつつ、課題の要件に従った実装を心がけましょう

不明な点や具体的なサポートが必要であれば、気軽に聞いてください！😊


---








