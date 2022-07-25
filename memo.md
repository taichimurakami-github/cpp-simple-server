# cpp に関するあれこれメモ

## アドレス演算子（&）と間接演算子（\*）の動作の違い

- 参照：[->、\*、&、[]演算子って奥深い](http://marupeke296.com/CPP_Operator.html)
- 毎回ごちゃごちゃになるので整理。

### アドレス演算子の振る舞い

まずは動作の振る舞いを確認。

- [アドレス演算子は、変数が割り当てられているメモリのアドレスを得る演算子である](http://www.ctrl.mae.nagoya-u.ac.jp/~asai/resources/ptrdoc/node5.html)
  - つまり、**変数からポインタを取得する**のに用いる
- 変数宣言以外で用いると、**READ_ONLY で動作**する
  - `Person me; Person &address_me = me` : OK。この場合、address_me には Person 型となる。&が無いときと同じ。
    - 変数名 me のアドレスを address_me に書き写している
    - つまりここでは、`address_meのポインタ = meのポインタ = &me`となる
    - ここでミソなのは、`address_meの実体 = meの実体`であること。アドレスを書き写したのだから当然である。
  - `Person &address_me;` : ERROR。変数宣言時は初期値が必要。

### 間接演算子の振る舞い

- [間接演算子は、ポインタが指すメモリをＣ言語の変数として扱うための演算子である](http://www.ctrl.mae.nagoya-u.ac.jp/~asai/resources/ptrdoc/node5.html)
  - つまり、**ポインタから変数を取得する**のに用いる

### おまけ：配列参照演算子（[]）

- 配列演算子の意味は、`[]`左のポインタのサイズに対して、`[]`内の整数をかけ合わせたアドレスを返しているだけ。
- つまり、a を int 型とすると、`a[1] = (&a[0] + 1)`を行っている
  - !!!ポインタ演算はポインタ分の加減算に変換される!!!
  - ex) `int a* = 0; a + 1 = a[1] = a + sizeof(&a)`;

## スコープ解決演算子（::）の振る舞い

- クラスと名前空間に対して使用可能
- クラスの静的メンバーを呼び出す
- 左辺に何も書かないとグローバル空間を指す
- 割と直感的に動作するので助かる。アドレス関連の演算子ももう少しシンプルにできなかったのだろうか

```cpp
namespace NamespaceA{
    int x;
}

namespace NamespaceC{
    namespace NamespaceC1{
        int x;
    }
}

namespace NamespaceD{
    class ClassD{
    public:
        class ClassD1{
        public:
            int x;
        };
    };
}

namespace NamespaceE{
    using namespace NamespaceC;
}
int x;

int main() {
    int x;

    // the x in main()
    x = 0;
    // The x in the global namespace
    ::x = 1;

    // The x in the A namespace
    NamespaceA::x = 2;

    NamespaceD:: NamespaceD1::x = 6; //The x in the D1 class in the D namespace
    NamespaceE::ClassD::ClassD1 e1; //...
}


```
