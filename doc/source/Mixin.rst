Mixin
================

正如我们之前所见，`ObjectArray` 库里包含多种 `array` 以及 `view` 。

而相关的算法，一些在这些 `array/view` 中均可复用，而另外一些只能在少数 `array/view` 中可复用。
有少数甚至只能在个别 `array/view` 中单独使用。如何解决这种变化多端的复用问题？

**组合式设计** 是解决多种变化方向问题的利器。

而对于 `ObjectArray` 库， 这种组合式设计的手段是 `mixin` 。

核心算法和扩展算法
----------------------------

对于很多算法而言，只要你实现了最核心的一个或几个，其它的都可以基于它进行实现。比如：

.. code-block:: c++

   template<typename PRED>
   auto FindIndex(PRED &&pred) const -> std::optional<SizeType>;

   template<typename PRED>
   auto Find(PRED &&pred) const -> ObjectType const&;


只要你实现基于谓词的 ``FindIndex`` 和 ``Find`` （事实上，如果不考虑 ``Find`` 与 ``FindIndex`` 在算法上可以给出不同实现的因素，二者只需要实现其中一个，
另外一个即可以据它实现），你就可以扩展出下列算法：

.. code-block:: c++

   auto FindIndex(ObjectType const& obj) const -> std::optional<SizeType> {
      return FindIndex([&](auto&& elem) { return elem = obj; });
   }

   auto Find(ObjectType const& obj) const -> auto* {
       return Find([&](auto&& elem) { return elem == obj;});
   }

   template<typename PRED, __pReD_cHeCkEr>
   auto Exists(PRED &&pred) const -> bool {
       return Find(std::forward<PRED>(pred)) != nullptr;
   }

concept
-----------------------

我们随后以 ``SimpleFind`` 和 ``SimpleFindExt`` 这一族算法的 `mixin` 设计为例，来讨论整个 `mixin` 体系
的设计。

首先，``SimpleFind`` 和 ``SimpleFindExt`` 的之间的关系如下：

.. image:: images/simple-find-ext.png

如果你仔细看这张图，会发现 ``SimpleFindExt`` 本身是一个 `mixin` ，而它所依赖的是一个抽象的
被称作 `concept` 的元素。

`concept` 不是 `class` 或 `template` ，它是一个被 `C++ 20` 标准化了的概念。但事实上，即便
这个概念没有被标准化，没有任何语法元素支持，它也是早就存在的设计概念。

简单说， `concept` 就相当于我们熟悉的用于 **运行时多态** 的 `interface` ，或 **纯虚类** 。
但它不是用于 **运行时多态** ，而是用于 **编译时多态** 。因而它是一个静态接口，没有任何运行时代价。

由于编译时多态是基于特征的（而不是函数接口，虽然特征也可以是函数接口），因而 `concept` 所描述的是
一个模版对于它要依赖的类型的特征要求。所有可以用来实例化这个模版的类型都必须满足这些特征。

事实上，在 `C++ 20` 之前，这些要求也是存在的（否则就不可能编译通过），但由于没有语法元素来明确
描述这些要求，因而一则对于代码阅读者无法通过一份接口规范来清晰地知道这些约束是什么；二则，当编译
出错时，晦涩的出错信息让程序员很难快速定位出出错的原因。

无论如何，即便你仍在使用 `C++ 17` ，甚至更早的编译器，你无法直接通过语法元素直接表达，但这并不
妨碍从设计概念上， `concept` 依然是存在的。

现在回到我们的问题。为何 ``SimpleFindExt`` 依赖的是一个抽象的 `concept` ，而不是一个具体的类？

像所有的多态一样，因为变化。对于 ``SimpleFind`` 这样一个 `concept` ，我们的库里至少有两种不同的
需求，因而有两种不同的实现：

.. image:: images/multi-simple-find.png


分类
-------------

在进一步讨论之前，我们先将我们的 `Array` 和 `View` 进行一下分类：

  1. `NonScopedArrayLike`

     - `ScatteredArray`
     - `ScopedArrayView`

  2. `ScopedArrayLike`

     - `ObjectArray`
     - `ArrayView` / `ConstArrayView`
     - `Slice`


NonScopedSimpleFind
--------------------------

之所以会有这两种不同的 ``SimpleFind`` ，是因为 `ScopedArrayLike` 而言，
它们自身都有一个 ``Scope`` ，而对于 `NonScopedArrayLike` ，
则没有 ``Scope`` ，而这两种的 ``Find`` 实现是不一样的。

但是一旦各自给出了最核心的 ``Find`` ，那么所有基于它们的扩展算法 （ ``SimpleFindExt`` ）则是完全一样的。

而这其中最有趣的一点是： ``ScopedSimpleFind`` 所依赖的 ``ScopedFind`` ，本身属于 `NonScopedArrayLike` 一族的
正常接口，因为我们可以写出如下代码：

.. code-block:: c++

   ObjectArray<int, 10> array;

   array.Find(0xa5, [](auto&& item) { return item == 5 }); // 1st argument is a scope.

   array.Scope(0xa5).Find([](auto&& item) { return item == 5 });

但是却不允许对 `ScopedArrayLike` 一族提供上述的接口（ 因为它们已经属于 `Scoped` )。

因而，对于 `NonScopedArrayLike` 一族，存在 ``ScopedFind`` 以及它的扩展 ``ScopedFindExt`` 等一族接口。
但 `ScopedArrayLike` 却没有这样的接口。

但有趣的地方也正在于此，`ScopedArrayLike` 一族的 ``SimpleFind`` 实现却可以通过复用 ``ScopedFind`` `mixin` 来实现。

它们的关系如下图所示：

.. image:: images/simple-scoped-find.png


NonScopedSimpleFind
-------------------------------

而具体到 ``NonScopedSimpleFind`` 的实现，它也需要依赖一个 `concept` :  ``RangedArrayLike`` 。
因为 ``Find`` 与 ``FindIndex`` 的算法实现，仅仅需要依赖两类元素：

   1. 搜索的 `Range` : `[begin, end)` ，对应如下两个方法：

      - ``IndexBegin() -> SizeType``
      - ``IndexEnd() -> SizeType``

   2. 每个索引位置的对象：

      - ``GetObj(i) -> ObjectType const&``


而拥有这三个接口的概念为 ``RangedArrayLike`` 。而对于此 `concept` 的实现，可以分为两类：

   1. ``ObjectArray``, ``ArrayView`` ，它们的 `range` 是 `[0, num)` ;
   2. ``Slice`` 的 `range` 是切片创建时指定的 `range` ；

由于现在我们讨论的是 `NonScopedSimpleFind` ，因而 `ScopedArrayLike` 一族的因素暂时不予讨论。

因而，它们的关系如下：

.. image:: images/ranged-array-like.png

图中，`RangedViewArrayHolder` 对应的就是 `slice` 的数据类。而 ``RangedArray`` 这个 `mixin` ，
则由 ``ObjectArray`` 和 ``ArrayView`` 组合。

如果只考虑 `NonScopedArrayLike` ，那么 ``RangedArray`` 到具体的数据类的关系如下：

.. image:: images/array-like.png

在这样的关系下， ``RangeArray`` 三个方法的实现如下：

.. code-block:: c++

   template <_concept::ArrayLike T>
   struct RangedArray {
      auto IndexBegin() const -> SizeType {
         return 0;
      }

      auto IndexEnd() const -> SizeType {
         return (ArrayLike const*)(this)->GetRange();
      }

      auto GetObj(SizeType n) const -> ObjectType const& {
         return ArrayLike::ElemToObject((ArrayLike const*)(this)->Elems()[n]);
      }
   };

为何 ``IndexEnd()`` 调用的是 ``GetRange`` ，而不是直接返回数组元素的个数： ``num`` ？

这是因为，``ArrayLike`` 这个 `concept` 不仅仅是 `NonScopedArrayLike` 才有的概念，
`ScopedArrayLike` （ ``ScatteredArray`` ）同样有这个概念。 ``ScatteredArray`` 的
``GetRange`` 返回的不是 ``num`` (它没有这个属性），而是 ``MAX_SIZE`` （代表它遍历的范围
是整个数组空间）。


ScopedSimpleFind
-------------------------------

`ScopedSimpleFind` 相对于 `NonScopedSimpleFind` ，复杂度稍微上升了一点，因为它需要一个额外的
接口: ``GetScope`` 。而 ``Find`` 操作，只能在 `scope` 指定的范围内进行。

而 `ScopedView` 与 `ScatteredArray` 都属于此类。它们的关系如下：

.. image:: images/scoped-find.png

其中 `ScopedView` 聚合了一个提供了 `RangedArrayLike` 概念的对象，无论那个对象是
一个 `ObjectArray` , `ArrayView` 还是一个 `Slice` ，`ScopedView` 都并不关心，
只要它们都提供了 `RangeArrayLike` 概念所要求的接口。

而 `ScopeView` 只是通过转调它们的 `RangedArrayLike` 接口来让自己也成为一个
满足 `RangedArrayLike` 概念的对象。

而 `ScatteredView` 则通过 `RangedArray mixin` 来让自己满足 `RangedArrayLike` 概念。

而两者都通过自己所持有的 ``BitMap`` 类型的数据来满足 `ScopedArrayAlike` 概念。

如果一个对象既满足 `RangedArrayLike` 概念， 又满足 `ScopedArrayAlike` 概念，从语义上就满足
了 `RangedArrayLike + ScopedArrayAlike` 概念。而 `C++ 20` 则通过 ``RangedArrayLike && ScopedArrayAlike`` 来
表达这种概念上的组合关系。我们将这个组合后的概念，定义为一个新概念 `ScopedRangedArrayLike` ：

.. image:: images/scoped-ranged-concept.png
   :align: center
   :scale: 30 %

mixin
--------------

到了现在，我们需要来谈一下什么叫 `mixin` 了。

简而言之， `mixin` 是个可以与对象进行组合的 `class/template class` 。它本身不应该有任何数据，
因而可以通过 ``std::is_empty_v<MIXIN>``  谓词断言。

由于它本身没有任何数据，因而拼接在对象身上不会引起对象二进制结构 （内存布局）的任何变化。所以，它们
的 ``this`` 指针的位置与整个对象的 ``this`` 指针位置一致。

这样的 `mixin` 与其它语言比如 `scala` 所提供的 `trait` 概念上很相似。（ `scala trait` 允许
提供算法实现，并且其 `trait` 组合顺序与声明顺序一致）。

之所以使用 `mixin` 这样的概念，是为了让一个 `mixin` 所提供的实现，能够在不同的对象间方便的复用。

组合
---------------

现在到了我们进行组合的时候了。我们先来看看 ``ObjectArray`` :

.. image:: images/object-array-simple-find.png

从图中优美的线条我们看出，这是一个层层依赖的结构。

因而，对于 `mixin` 我们可以使用单线继承的方式来进行组合：

.. image:: images/obj-array-compose.png

而其中每个 `mixin` 都是类似于下面的定义：

.. code-block:: c++

   template <Concept T>
   struct Mixin : T  {
      using Self = T;
      using Self::method; // import T::method
      using typename Self::Type // import T::Type
      // more imports

      // its own algorithm.
      auto DoSth() -> Bar {
         // ...
      }

      // more algorithms.
      // ...
   };

我们总是将被依赖的 `mixin` 放在父类的位置；如果相互双方没有任何依赖关系
（比如 ``SimpleFindExt`` 与 ``ScopedFindExt`` )，那么它们在继承线上先后顺序也无所谓。

这样的组合方式，有一个明显的问题：子类对于父类同名函数的遮掩问题（比如 `SimpleFindExt`` 与 ``ScopedFindExt`` 里都有 ``Find`` ，
虽然它们的参数列表并不相同）。

对于这样的问题，没有自动解决的办法，只能要么避免各个 `mixin` 间出现同名函数（需要全局知识）；要么放在下面的 `mixin` 如果知道放在上面
的某个 `mixin` 存在与自己同名的函数，就负责明确地通过 ``using`` 来 `import` （这也需要全局知识）。

这当然是一个令人讨厌的地方，但对于所有 `mixin` 都在我们的控制之中（我们只是想通过分解为 `mixin` 达到复用目的），
这一点并不会带来明显的设计和维护负担。

