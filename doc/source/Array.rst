
ObjectArray
===================

有了 ``Placement`` ，我们现在就可以设计我们的数组。

首先，让我们搭一个基本的架子：

.. code-block:: c++

   template <typename OBJ, std::size_t MAX_NUM>
   struct Array {
      using SizeType = DeduceSizeType_T<MAX_NUM>;
      using ElemType = DeduceElemType_T<OBJ>

      ElemType elems[MAX_NUM];
      SizeType num{};
   };


在这个简单的架子中，有几个要点：

   1. 模版参数很直接，说明了我们希望存放在数组中的对象类型，以及预留的个数。
   2. 由于我们希望自动选择，对于 **可平凡构造** 的类型直接存放对象类型 ``OBJ`` ；否则存放 ``Placement<OBJ>`` ；而这个选择，由 ``DeduceElemType_T<OBJ>`` 完成。
   3. 由于我们希望尽可能不浪费内存，按照 ``MAX_NUM`` 我们可以自动推理出最小的SizeType。

自动选择
------------------

了解了 ``Placement`` ，我们就知道一个静态数组，是否使用 ``Placement`` 。简单说，原则就是：如果一个
类型 ``T`` 本身的 **默认构造** 是平凡的（默认构造的平凡性，必然意味着析构的平凡性），
那么我们就让数组的元素类型直接使用 ``T`` ，否则，则使用 ``Placement<T>`` 作为数组元素。

.. code-block:: c++

    template<typename T>
    auto DeduceElemType() -> auto {
       if constexpr(std::is_trivially_default_constructible_v<T>) {
           return T{};
       } else {
           return Placement<T>{};
       }
    }

    template<typename T>
    using DeduceElemType_T = decltype(DeduceElemType());


copy/move 构造与赋值
--------------------------------

一个 `array` ，当然至少是应该能够 copy/move 构造的。

我们先增加比较简单的 **copy 构造** :

.. code-block:: c++

   template <typename OBJ, std::size_t MAX_NUM>
   struct Array {
      using SizeType = DeduceSizeType_T<MAX_NUM>;
      using ElemType = DeduceElemType_T<OBJ>
      using Trait    = ObjectTrait<ElemType>;

    private:
        auto ConstructFrom(ElemType* array) -> void {
            if constexpr (std::is_trivially_copyable_v<ELEM>) {
                ::memcpy(elems, array, sizeof(ELEM) * num);
            } else {
                for(int i=0; i<num; i++) {
                    Trait::Emplace(elems[i], Trait::ToObject(array[i]));
                }
            }
        }

   public:
      Array(Array const& rhs) : num{rhs.num} {
          ConstructFrom(rhs.elems);
      }

   protected:
      ElemType elems[MAX_NUM];
      SizeType num{};
   };

对于数组的拷贝构造，很简单，是按照对方数组的实际数目，将对方的元素一个个 **copy构造** 给自己。

但这中间有一个重要的优化点。如果我们数组的元素类型是 **可平凡拷贝** 的（这就意味着一定是可平凡默认构造的，
按照我们的自动选择规则， `ElemType` 一定不可能是 `Placement<T>` ；但即便是 **可平凡默认构造** 的，也
并不代表它是 **可平凡拷贝** 的），我们就可以直接 ``::memcpy`` ，这往往比一个个进行 **copy构造** 有
更好的性能。

我们再增加 **move 构造** :

.. code-block:: c++

   template <typename OBJ, std::size_t MAX_NUM>
   struct Array {
      using SizeType = DeduceSizeType_T<MAX_NUM>;
      using ElemType = DeduceElemType_T<OBJ>;
      using Trait    = ObjectTrait<ElemType>;

    private:
        template<typename U>
        auto ConstructFrom(U* array) -> void {
            if constexpr (std::is_trivially_copyable_v<ELEM>) {
                ::memcpy(elems, array, sizeof(ELEM) * num);
            } else {
                for(int i=0; i<num; i++) {
                    Trait::Emplace(elems[i], std::move(Trait::ToObject(array[i])));
                }
            }
        }

        auto ClearContent(SizeType from) -> void {
            if constexpr (!std::is_trivially_destructible_v<ELEM>) {
                for(int i=from; i<num; i++) Trait::Destroy(elems[i]);
            }
        }

        auto Clear() -> void {
            ClearContent(0);
            num = 0;
        }

        auto MoveFrom(ObjectArrayHolder&& rhs) {
            ConstructFrom(rhs.elems);
            rhs.Clear();
        }

   public:
      Array(Array const& rhs) : num{rhs.num} {
          ConstructFrom(rhs.elems);
      }

      Array(Array&& rhs) : num{rhs.num} {
          MoveFrom(rhs);
      }

   protected:
      ElemType elems[MAX_NUM];
      SizeType num{};
   };

**move 构造** ，相对于 **copy 构造** ，有两点重要的差异：

  1. 如果不能进行直接拷贝，则只能将对方的元素一个个通过 ``std::move`` 移动过来；
  2. 移动结束后，要将对方的数组清理掉（因为它的元素已经移动给我们了）。

需要注意的是，在 `move` 的阶段，我们重构了 ``ConstructFrom`` ，让它可以和 **copy 构造** 复用。
首先，我们将其改为了泛型函数，其模版参数 ``U`` 在 `copy` 的场景下，是 `const` 指针；而在 `move` 场景下，
是 `non-const` 指针。其次，无论是 `copy` 还是 `move` ，我们都调用了 ``std::move`` ：

.. code-block:: c++

   Trait::Emplace(elems[i], std::move(Trait::ToObject(array[i])));

在 `copy` 场景下， 由于 `array` 是 `const` 的， ``std::move(OBJ const&)`` 的结果
是 ``OBJ const&&`` 类型, 这毫无疑问会匹配到 `OBJ` 的拷贝构造。

在 `move` 场景下，`array` 是 `non-const` 的，``std::move(OBJ&)`` 的结果是 ``OBJ&&`` ，
如果 `OBJ` 提供了移动构造，则会毫不犹豫的与之匹配。否则，依然与 `OBJ` 拷贝构造匹配。无论如何
都是我们期待的结果。

而在 ``Clear`` 阶段；我们再一次利用 **平凡性** 进行了优化：如果 `OBJ` 是可平凡析构的，那就什么也
不用做，只是简单的把 ``num`` 设置为 ``0`` 即可。否则，就老老实实一次将每个元素进行析构。

而对于 **copy/move 赋值** 函数的实现，与构造类似，这里就不再赘述。

而这一切都是通过库自动判断完成，程序员完全不需要操心。

析构
-----------------

下一个问题是， ``Array<T,N>`` 自身是否需要明确定义一个析构函数？

首先，如果 ``T`` 本身是可平凡析构的，那么事实上我们在析构阶段什么都不用做（num清零也没有意义）。

但如果 ``T`` 本身是不可平凡析构的，我们就应该在析构时老老实实将每个元素进行析构。

因而，前者我们无需提供析构函数，而后者则必须提供。

当然也可以无脑全部都提供。但问题的麻烦在于，这不仅仅是增加一个析构函数那么简单。一旦我们明确
为一个类定义了析构函数，它就肯定变成 **不可平凡析构** 的。而这样的性质会一层层传播给它所有的持有者。
本来大家可能都是 **可平凡析构** 的，因而什么也不用做。现在倒好，每个它的宿主，无论直接还是间接的，
都必须要在析构时做工了。

`sucks!!`

所以，我们必须 **按需** 为 ``Array<T,N>`` 提供构造函数。 ``C++ 20`` 可以通过 ``requires`` 语法
直接决定一个函数的存在性。但在 ``C++ 17`` 时代，我们只能通过 **继承类** 来解决这个问题。

.. code-block:: c++

   template<typename OBJ, std::size_t MAX_NUM,
            bool = std::is_trivially_destructible_v<OBJ>>
   struct ArrayExt : Array<OBJ, MAX_NUM> {
        using Parent = Array<OBJ, MAX_NUM>;
        using Parent::Parent;
    };

   template<typename OBJ, std::size_t MAX_NUM>
   struct ArrayExt<OBJ, MAX_NUM, false> : Array<OBJ, MAX_NUM> {
        using Parent = Array<OBJ, MAX_NUM>;
        using Parent::Parent;

        ~ArrayExt() { Parent::ClearContent(0); }
    };

    template<typename OBJ, std::size_t MAX_NUM>
    using ObjectArray = ArrayExt<OBJ, MAX_NUM>;

Rule Of Five
------------------

一旦我们为 ``Array<T,N>`` 根据需要明确提供了析构函数，按照 `C++` 的
规则， **move 构造/赋值** 也都不再自动生成默认函数（ **copy 构造/赋值** 则会依然默认生成）。

此时，即便 ``T`` 本身是 **可move构造** 的，它也会转而匹配到 **copy 构造** ，让本来可以
通过 `move` 的得到的性能优化悄悄地丧失。

此时，就必须显式声明 **move 构造/赋值** （如果 ``T`` 支持的话）。
哪怕声明为 ``=default`` 也必须显式声明。

可 `C++` 有另外一个规则，一旦你显式声明了 **move 构造** （和/或） **move 赋值** 函数，
那么 **copy 构造/赋值** 的隐式声明也会消失，这等于是不再允许 **copy 构造/赋值** 。
如果这不是你的意图，则你必须也要显式声明 **copy 构造/赋值** （如果 ``T`` 支持的话）。

这种连环规则，其实就是 `rule of five` 由来的部分原因。一旦你明确定义一个，就必须同时考虑其它四个。

.. code-block:: c++

   template<typename OBJ, std::size_t MAX_NUM,
            bool = std::is_trivially_destructible_v<OBJ>
   struct ArrayExt : Array<OBJ, MAX_NUM> {
        using Parent = Array<OBJ, MAX_NUM>;
        using Parent::Parent;
    };

   template<typename OBJ, std::size_t MAX_NUM>
   struct ArrayExt<OBJ, MAX_NUM, false> : Array<OBJ, MAX_NUM> {
        using Parent = Array<OBJ, MAX_NUM>;
        using Parent::Parent;

        ArrayExt(ArrayExt const& rhs) = default;
        auto operator=(ArrayExt const& rhs) -> ArrayExt& = default;

        ArrayExt(ArrayExt&& rhs) = default;
        auto operator=(ArrayExt&& rhs) -> ArrayExt& = default;

        ~ArrayExt() { Parent::ClearContent(0); }
    };

    template<typename OBJ, std::size_t MAX_NUM>
    using ObjectArray = ArrayExt<OBJ, MAX_NUM>;

