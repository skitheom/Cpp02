# Cpp02
42 project

# C++ Module 02

## Topics

* Adhoc polymorphism（アドホック多態性）
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

