简介
================

``ObjectArray<T, N>`` 像 `C` 语言数组 ``T[N]`` 一样，容量固定，元素个数可变。
（如果元素个数固定（与容量相同），请使用 ``std::array<T,N>`` ）。

因而，你可以定义一个如下的数组：

.. code-block:: c++

   ObjectArray<int, 10> array;

   ASSERT(array.GetNum() == 0);

   int* p = array.Append(5);
   ASSERT(*p == 5);
   ASSERT(array[0] == 5);

   ASSERT(array.GetNum() == 1);

其空间代价，和运行时代价，与定义一个如下的结构体没有任何差别。

.. code-block:: c++

   struct Array {
      int array[10];
      uint8_t num;
   };

而其中 ``Append`` 操作，则相当于程序员亲自操作：

.. code-block:: c++

   o.array[o.num++] = 5;

当然，``Append`` 会提供 **边界检查** ，当元素个数达到容量时，``Append`` 操作会返回 ``nullptr``  (禁止
使用异常情况下的常规设计）。

这种 **边界检查** ，还体现在访问时：

.. code-block:: c++

   int* p = array.At(1);
   ASSERT(p == nullptr);

但是，如果你直接使用 ``operator[]`` ，则 **不会** 进行 **边界检查** （这是
一个基于接口设计、异常、性能等各种因素综合考虑后的设计决定）。

删除
-----------------

既然可以向数组中添加元素，当然也可以删除和清理。

首先你可以通过 ``Erase`` 和 ``Remove`` , ``RemoveIf`` 来删除一个元素：

``Erase`` 的参数是索引：

.. code-block:: c++

   array.Erase(2);

而 ``Remove`` 的参数是对象指针：

.. code-block:: c++

   array.Remove(&array[2]);

``RemoveIf`` 的参数则是一个 **谓词** :

.. code-block:: c++

   array.RemoveIf([value](auto&& item) { return item == value; });

这三个接口都是只删除数组中的一个元素。而对于 **无序** 且 **连续存储** 的数组，
由于删除而导致的空位，将由最后一个元素填补（如果被删除的不是最后一个的话）：
将最后一个元素，通过 ``std::move`` ，而不是 ``copy`` 到空缺位置。
（因而数组内对象的 **move 构造** 的实现很重要）。

另外，值得注意的是: ``RemoveIf`` 提供的是 **谓词** ，因而，数组内 **谓词** 成立的元素有可能不止一个。
但 ``RemoveIf`` 只会删除依先后顺序找到的第一个。

如果想删除所有满足谓词的元素，则需要使用 ``ClearIf`` :

.. code-block:: c++

   array.ClearIf([](auto&& item) { return item == 3; });

Replace
-----------------------------

你可以通过 ``Replace`` 将某个位置的对象替换为另外一个对象：

.. code-block:: c++

   struct Foo {
     Foo(char, bool);
     // ...
   };

   array.Replace(2, 'a', true); // array[2] is replaced by Foo{'a', true}

请注意，如果你想通过 ``move`` 方式用一个已有对象替换数组中某个位置的对象，需要明确进行 ``std::move`` ：

.. code-block:: c++

   Foo foo{'b', false};

   array.Replace(2, std::move(foo));

``Replace`` 的返回值为替换后的对象指针。需要注意的是，对于无序数组而言，替换前与替换后，元素在数组中的位置并不会发生变化。但对于
有序数组，其位置可能会因为保持有序而变化，从而导致返回的指针与替换前访问同一位置得到的对象指针不同。

另外，如果你希望 ``Replace`` 操作返回索引值，而不是对象指针，可以调用 ``Replace_I`` 。

类似地，``Append`` 与 ``Append_I`` 分别返回的是 **对象指针** 与 **数组索引**。 如果 ``Append`` 失败，返回 ``nullptr`` ；如果 ``Append_I`` 失败，
返回 ``std::nullopt`` 。

遍历
----------------------------------

如果你直接使用标准库算法来遍历一个 `C` 语言数组，则写法如下：

.. code-block:: c++

   std::for_each(o.array, o.array + o.num, [](int item) { /* ... */ });

或者，干脆用索引遍历：

.. code-block:: c++

   for(auto i=0; i<o.num; ++i) {
      auto&& item = o.array[i];
      /* do sth with item */
   }

而使用 ``ObjectArray<T, N>`` ，则至少（随后我们会谈到更多其它方式）有四种方式来遍历：

首先，同样是 ``lambda`` 方式：

.. code-block:: c++

   array.ForEach([](int item) { /* ... */ });

其次，也是通过索引方式：

.. code-block:: c++

   for(auto i=0; i<array.GetNum(); ++i) {
      auto&& item = array[i];
      /* do sth with item */
   }

第三，则是 `range-for` 方式：

.. code-block:: c++

   for(auto&& item : array) {
     /* do sth with item */
   }

最后，如果你想使用 `range-for` ， 同时又需要索引值，则可以：

.. code-block:: c++

   for(auto&& [item, i] : array.WithIndex()) {
     /* do sth with item & i */
   }


查找
-----------------------

如果你直接使用标准库算法去 `C` 语言数组中查找一个元素，则写法如下：

.. code-block:: c++

   auto* p = std::find_if(o.array, o.array + o.num, [](int item) { /* ... */ });
   if(p == o.array + o.num) {
     // not found
   } else {
     // found, get value by *p
   }

而使用 ``ObjectArray<T, N>`` ，则写法如下：

.. code-block:: c++

   auto* p = array.Find([](int item) { /* ... */ });
   if(p == nullptr) {
     // not found
   } else {
     // found, get value by *p
   }

当然，如果你想查到的结果用索引表示，使用标准库的做法是：

.. code-block:: c++

   auto iter = std::find_if(o.array, o.array + o.num, [](int item) { /* ... */ });
   if(iter == o.array + o.num) {
     // not found
   } else {
     auto index = p - o.array;
     // using index.
   }

而使用 ``ObjectArray<T,N>`` ，做法为：

.. code-block:: c++

   IntOpt<uint8_t> index = array.FindIndex([](int item) { /* ... */ });
   if(!index) {
     // not found
   } else {
     // using *index.
   }

当然这类的算法还有很多，即便对于同一种算法，也有不同的参数形式，这里就不再赘述。

而 ``ObjectArray<T, N>`` 这是把这些对于算法的经常性操作中的不必要的重复性因素都排除掉，让用户
只提供和关注他必须提供和关注的因素。

切片
-----------------------

**切片** ( `slice` ) 本身并不是数组，而是一种对于数组的 `view` 。这种概念对于数组的操作
极为有价值，很多编程语言都内建了切片概念（ `python` , `go` , `rust` 等)， `C++ 20` 也通
过 ``std::span`` 达到了部分对于 `slice` 的支持。

而 ``ObjectArray<T,N>`` 的 `slice` 则非常直接：

.. code-block:: c++

   auto&& slice = array.Slice(3, -2);

这样，你就得到了一个 `slice` ，其表达的范围为: ``[3, n-2)`` 。

.. note::

   用负数作为一种索引方式，很多没有接触过切片概念的人会觉得陌生和唐突。尤其是用 ``-1`` 表达
   数组的最后一个元素， 用 ``-n`` 表达倒数第 ``n`` 个元素。这与我们用 ``0`` 表达
   第一个元素的习惯，看起来是不一致的。

   当然，首先是因为 ``0`` 已经被用来表达数组的第一个元素了。不可能再用它表达倒序的第一个元素。

   其次，即便我们直接用正索引来表达数组的倒序元素，也是通过 ``array[num-1]`` 来表达数组的最后一个元素；
   用 ``array[num-n]`` 来表达倒数第 ``n`` 个元素。

   因而，它本质上与我们之前的习惯是完全一致的。

   如果依然觉得不一致，那就怪最初数组索引的设计者没有用 ``1`` 而是用 ``0`` 当作数组第一个元素的索引吧。

当然，如果你只想指定 `slice` 其中一边的边界，则可以通过：

.. code-block:: c++

   array.From(3);  // [3, n)
   array.Until(-2) // [0, n-2)

这里的切片索引方案与 `python` 一致。当给出两边的边界，比如 ``Slice(m, n)`` 时，其包含的元素
索引边界为： `[m, n-1]` 或 `[m, n)` 。因而：

.. code-block:: c++

   array.From(-2)   // last two items in the array
   array.Until(-2)  // everything except the last two items

而切片也提供了几乎所有 `ObjectArray<T,N>` 的算法接口：

.. code-block:: c++

   array.From(3).ForEach([](auto&& item) { /* */ });
   array.Until(-2).MinElem();

当然，你也可以 ``range-for`` :

.. code-block:: c++

   for(auto&& item: array.Slice(3, -2)) {
      // ...
   }

在指定切片边界时，用户有可能给出超出数组事实边界的索引，比如：

.. code-block:: c++

   ObjectArray<int, 10> array{1,2,3};

   array.Slice(-4, -5); // both are beyond left boundary.

`Object Array` 会自动对超越边界的索引进行调整：

   1. 如果超越左边界，会调整为左边界
   2. 如果超越右边界，会调整为右边界
   3. 如果用户给定的 `Slice` 范围不能构成有效范围，则整个 `Slice` 的范围为空。

比如：

.. code-block:: c++

   ObjectArray<int, 10> array{1,2,3};

   array.Until(10);    // [0, 2]
   array.From(-10);    // [0, 2]
   array.Slice(1, 10); // [1,2]

   array.Slice(-10, -20); // empty
   array.Slice(-10, 0);   // empty
   array.Slice(10, 20);   // empty


另外，你不能在一个 **右值** 数组上创建一个 `slice` 。也就是说下面的代码是不被允许的：

.. code-block:: c++

   auto&& slice = ObjectArray<int, 10>{1,2,3).Slice(2,-3); // not allowed

因而，你也不能在 `range-for` 表达式里写如下代码：

.. code-block:: c++

   for(auto&& item : ObjectArray<int, 10>{1,2,3}.Slice(2,-3)) { // not allowed
      // do sth.
   }

.. attention::

   这是因为， `slice` 仅仅是一个 `view` ，因而必然会引用一个数组。如果数组本身是一个 **右值** ，其生命周期
   仅仅在那一行代码得以维持。在那行代码执行结束后，**右值** 数组就被销毁了，导致 `slice` 变成了 `dangling slice` 。
   `ObjectArray` 通过设计，保证这样的代码会导致编译错误。

但是，如果你使用的是一个 `ArrayView` (我们会在后面章节介绍到），则可以在右值对象上创建 `slice` :

.. code-block:: c++

   int a[3] = {1,2,3};
   uint8_t num = 3;

   auto&& slice = ArrayView{a, num}.Slice(1, -1); // OK

.. attention::

   当创建并使用一个 **左值** `slice` 期间，一定要保证 `slice` 所引用的数组内元素是不可被删除的。
   否则，将可能会导致不确定的行为。

   比如，我们在一个元素个数为 ``3`` 的数组上创建了一个 `slice` : ``array.Until(3)`` 。这时 `slice`
   所引用的范围为 ``[0, 3)`` ，范围内有 ``3`` 个元素。如果此时我们删除了数组内一个元素。此时数组内元素个数为
   ``2`` ，但 `slice` 的范围依然是 ``3`` ，从而在访问时可能会引起问题。

   虽然通过增加判断逻辑可以避免这类问题，但基于绝大多数情况下都不会出现这样的问题。因而基于性能考量，把约束的保证
   留给用户。

   `rust` 通过语言的内建约束，来保证一个数组被至少一个 `slice` 引用时，数组本身是完全不允许修改的。

   但本库的 `slice` 除了与删除元素有关的所有操作被禁止外，其它的修改操作：增加元素、或替换元素相关的操作依然是允许的。

   不过需要注意的是：如果在创建一个 `slice` 时，如果 **没有** 指定右边界 (通过 ``From(n)`` ），则 `slice` 的右边界
   将会随着元素的增加而增大。


Clear
---------------------

在看到 `slice` 的索引方式之后，事实上 ``Clear`` 也可以在一个切片范围内清除：

如果想把数组所有元素清理掉，则可以调用 ``Clear`` ：

.. code-block:: c++

   ASSERT(array.GetNum() == 5);
   array.Clear();
   ASSERT(array.GetNum() == 0);

如果仅仅想清除 `[from, until)` 范围内的元素，则可以通过指定切片范围来调用 ``Clear`` ：

.. code-block:: c++

   ASSERT(array.GetNum() == 5);
   ASSERT(array[0] == 1);
   ASSERT(array[1] == 2);
   ASSERT(array[4] == 5);

   array.Clear(1, -1); // [1, 3] is cleared.

   ASSERT(array.GetNum() == 2);

   ASSERT(array[0] == 1);
   ASSERT(array[1] == 5); // array[4] is moved to array[1]


像 `slice` 一样，在清理时，可以只指定范围的其中一端：

.. code-block:: c++

   array.ClearFrom(2); // [2, n)
   array.ClearUntil(-2); // [0, n-2)

除了无条件进行 ``Clear`` 之外，你还可以通过 ``ClearIf`` 以指定谓词的方式进行清理，即在一个范围内，所有满足谓词条件的，都会被清理。

.. code-block:: c++

   array.ClearIf([](auto&& elem) { return elem > 2; });

   // range [1, -1)
   array.ClearIf(1, -1, [](auto&& elem) { return elem > 2; });

   // range [1, n)
   array.ClearFromIf(1, [](auto&& elem) { return elem > 2; });

   // range [0, n-1)
   array.ClearUntilIf(-1, [](auto&& elem) { return elem > 2; });

对于需要在一个范围内进行清理的操作，你也可以通过一个 **右值** ``Slice`` 进行：

.. code-block:: c++

   array.Slice(1,-1).Clear();
   array.From(1).ClearIf([](auto&& elem) { return elem > 2; });

但一个 **左值** ``Slice`` 不允许进行这种操作：

.. code-block:: c++

   auto&& slice = array.Slice(1,-1);

   slice.Clear(); // not allowed, compiling fail.
   slice.ClearIf([](auto&& elem) { return elem > 2; }); // not allowed, compiling fail.

.. attention::

   这是因为，**左值** slice 的生命周期很久，你可以多次调用其不同接口，因而必须维持一个 ``Slice`` 的语义完整性。

   但一个右值 ``Slice`` 在你调用 ``Clear`` 相关接口之后，就没有途径再次访问同一 ``slice`` ，因而不需要维持其语义完整性。


ScopeView
-----------------------------

**切片** 仅仅能够指定一个数组两边的边界，从而对边界内的 **连续** 范围内的元素进行访问。

但现实中，存在着一种需求：我们只对数组中非连续的 **散列** 范围内的元素感兴趣。比如，我只对
数组中的第 ``1``, ``3`` , ``7`` 个元素感兴趣。

此时，我们就可以通过一个 ``bitset`` 来指定范围，从而得到一个 `ScopedView` ：

.. code-block:: c++

   auto&& scopedView = array.Scope(0x4a);

而如果你想访问 **排除** 了这些元素的其它元素，则可以：

.. code-block:: c++

   auto&& scopedView = array.Exclude(0x4a);

当然对于这些 `ScopedView` ，你同样可以使用所有的数组算法：

.. code-block:: c++

   array.Scope(0x4a).ForEach([](auto&& item) { /* */ });
   array.Exclude(0x4a).MaxElem([](auto&& l, auto&& r) { return l > r });

当然，你也可以 ``range-for`` :

.. code-block:: c++

   for(auto&& item: array.Scope(0x3a)) {
      // ...
   }

和 `slice` 一样，当你进行 ``range-for`` 时，如果需要索引，你得到的是数组的索引，而不是
在 `ScopedView` 内的索引：

.. code-block:: c++

   for(auto&& [item, i] : array.Scope(0xf4).WithIndex()) {
      // the 1st `i` is 2, 2nd `i` is 4, and so on...
   }

更进一步的，你可以将两种 `view` 组合起来：

.. code-block:: c++

   array.From(2).Scope(0xf4);


.. attention::

  1. `Slice` 需要放在前面
  2. `Scope` 里的位图仍然是以数组的索引，而不是 `Slice` 的范围来索引的；
     当然，在 `Scope` 里超出 `Slice` 范围的元素不在 `Scope` 的访问范围内。

而指定 `Scope` 范围的访问方式，不仅仅可以通过创建一个 `ScopedView` ，还可以直接
通过算法参数来指定。比如：

.. code-block:: c++

   array.ForEach(0xa5, [](auto&& item) {});
   array.Scope(0xa5).ForEach([](auto&& item) {});

   array.MinElemEx(0xa5);
   array.Exclude(0xa5).MinElem();

   array.From(3).MaxElem(0xa5);
   array.From(3).Scope(0xa5).MaxElem();

以上三组例子，两种写法从作用上是等价的。

.. attention::

   - `ScopedView` 可以通过算法参数来替代，但 `Slice` 不能；
   - 当使用 `range-for` 时，`ScopedView` 不可能通过算法参数来替代。


另外，基于与 `slice` 同样的原因，你不能在一个右值数组对象上创建一个 `scope view` ：

.. code-block:: c++

   auto&& view = ObjectArray<int, 10>{1,2,3}.Scope(0x0a}; // not allowed.

但你却可以在一个右值 `ArrayView` 上创建一个 `scope view` :

.. code-block:: c++

   int a[3] = {1,2,3};
   uint8_t num = 3;

   auto&& view = ArrayView{a, num}.Scope(0x0a}; // OK.


CleanUp
---------------------

在了解了 `scope` 的概念之后，事实上 ``CleanUp`` 也可以在一个范围内清除：

.. code-block:: c++

   array.CleanUp(0x0a);   // 1, 3 is cleared.
   array.CleanUpEx(0x0a); // `Ex` Means `Exclude`, so 0, 2, 4 is cleared.

排序
-------------

对于任何一种可修改的 `array` 或者 `view` ，你都可以对其进行直接的排序：

.. code-block:: c++

   ObjectArray<int, 10> array{3,1,4,2};

   array.Sort();

   ASSERT(array[0] == 1);
   ASSERT(array[1] == 2);
   ASSERT(array[2] == 3);
   ASSERT(array[3] == 4);

或者进行降序排序：

.. code-block:: c++

   array.DescSort();

   ASSERT(array[0] == 4);
   ASSERT(array[1] == 3);
   ASSERT(array[2] == 2);
   ASSERT(array[3] == 1);

你能直接进行排序的原因是：数组中的对象本身可以进行 ``<`` 操作。如果不能，你就需要通过 ``lambda`` 指明
排序规则：

.. code-block:: c++

   ObjectArray<Foo, 10> array{{3}, {1}, {4}, {2}};

   array.DescSort([](auto&& l, auto&& r) { return l.a < r.a; });

   ASSERT(array[0].a == 4);
   ASSERT(array[1].a == 3);
   ASSERT(array[2].a == 2);
   ASSERT(array[3].a == 1);

如果你希望使用 **稳定排序** 算法，则可以调用 ``StableSort`` :

.. code-block:: c++

   ObjectArray<Foo, 10> array{{3}, {1}, {4}, {2}};

   array.StableSort([](auto&& l, auto&& r) { return l.a < r.a; });

   ASSERT(array[0].a == 1);
   ASSERT(array[1].a == 2);
   ASSERT(array[2].a == 3);
   ASSERT(array[3].a == 4);

当对象本身支持 ``<`` 操作时， ``StableSort`` 也提供了降序排序接口 ``StableDescSort`` 。

.. note::

   ``StableSort`` 比 ``Sort`` 性能要差，但却可以保证两个相等的对象在排序后，与排序前的顺序相同。

如果你只想对部分元素进行排序，即从整个数组中，排序出最大/最小的 ``N`` 个元素，则可以使用 ``PartialSort`` ：

.. code-block:: c++

   ObjectArray<Foo, 10> array{{3}, {1}, {4}, {2}};

   array.PartialSort([](auto&& l, auto&& r) { return l.a < r.a; }, 3);

   ASSERT(array[0].a == 1);
   ASSERT(array[1].a == 3);
   ASSERT(array[2].a == 4);
   ASSERT(array[3].a == 2);

而排序不仅仅可以在整个数组范围内进行，还可以只在一个 `slice` 范围，或者（和） `scope` 范围内进行排序：

.. code-block:: c++

   ObjectArray<int, 10> array{3,1,4,2};

   array.Slice(1, -2).DescSort();

   ASSERT(array[0] == 3);
   ASSERT(array[1] == 4);
   ASSERT(array[2] == 1);
   ASSERT(array[3] == 2);


.. code-block:: c++

   ObjectArray<int, 10> array{3,1,4,2};

   array.Scope(0x06).DescSort();

   ASSERT(array[0] == 3);
   ASSERT(array[1] == 4);
   ASSERT(array[2] == 1);
   ASSERT(array[3] == 2);


.. code-block:: c++

   ObjectArray<int, 10> array{3,1,4,2};

   array.Slice(0, -2).Scope(0x06).DescSort();

   ASSERT(array[0] == 3);
   ASSERT(array[1] == 4);
   ASSERT(array[2] == 1);
   ASSERT(array[3] == 2);



SortView
-------------------

对于数组而言，排序操作会导致对象在数组中的位置进行移动，如果对象比较大，这是一个昂贵的操作。

如果我们只是在某次需要时，对数组进行排序，但并不想改变数组本身的元素顺序，则可以通过 ``SortView`` 进行排序。

.. code-block:: c++

   ObjectArray<int, 10> array{3, 1, 4, 2};

   auto&& view = array.SortView().Sort();

   ASSERT(view[0] == 1);
   ASSERT(view[1] == 2);
   ASSERT(view[2] == 3);
   ASSERT(view[3] == 4);

   // array itself still keeps its order.
   ASSERT(array[0] == 3);
   ASSERT(array[1] == 1);
   ASSERT(array[2] == 4);
   ASSERT(array[3] == 2);

当然， 通过 `SortView` 也可以进行 ``StableSort`` 和 ``PartialSort`` ：

.. code-block:: c++

   auto&& view = array.SortView();

   view.PartialSort(3);

   ASSERT(view[0] == 1);
   ASSERT(view[1] == 3);
   ASSERT(view[2] == 4);
   ASSERT(view[3] == 2);


当然，你也可以连写：

.. code-block:: c++

   auto&& view = array.SortView().PartialSort(3);


.. note::

   `SortView` 本身是对数组的索引进行排序，而不是对对象直接排序，以降低数组元素移动所带来的成本。


而 `SortView` 也可以在 `Slice` (或/和） `Scope` 范围内创建：

.. code-block:: c++

   ObjectArray<int, 10> array{3,2,4,1};

   auto&& view = array.From(1).Scope(0x0c).SortView().Sort();

   // indices are slice ones.
   ASSERT(view[0] == 1);
   ASSERT(view[1] == 4);
   ASSERT(view.GetNum() == 2);

Rotate
-----------------------

如果你想对数组内某个范围的元素进行 **旋转** (rotate) 操作，可以直接调用数组的 ``RotateLeft`` 或 ``RotateRight`` 操作：

.. code-block:: c++

   ObjectArray<int, 10> array{3,2,4,1};

   array.RotateLeft(); // 2, 4, 1, 3
   array.RotateRight(); // 1, 3, 2, 4

事实上，这两个函数都有一个参数: ``n`` ，即旋转的次数（默认值为 ``1``） 。因而你可以：

.. code-block:: c++

   ObjectArray<int, 10> array{3,2,4,1,5};

   array.RotateLeft(2);  // 4, 1, 5, 3, 2
   array.RotateRight(2); // 1, 5, 3, 2, 4

通过 ``RangeRotateLeft(from, until, n)`` 与 ````RangeRotateRight(from, until, n)`` ，你可以在指定旋转的范围：

.. code-block:: c++

   ObjectArray<int, 10> array{3,2,4,1,5};

   array.RangeRotateLeft(1, -1, 2);  // 3, 1, 2, 4, 5
   array.RangeRotateRight(1, -1, 2); // 3, 4, 1, 2, 5

像 ``Slice`` 一样，你可以只指定范围边界的一侧：

.. code-block:: c++

   ObjectArray<int, 10> array{3,2,4,1,5};

   array.RotateLeftFrom(1, 2);   // 3, 1, 5, 2, 4
   array.RotateLeftUntil(-1, 2); // 4, 1, 3, 2, 5


自然，你也可以通过 ``Slice`` 来进行 ``Rotate`` :

.. code-block:: c++

   ObjectArray<int, 10> array{3,2,4,1,5};

   array.Slice(1, -1).RotateLeft(2);  // 3, 1, 2, 4, 5
   array.Slice(1, -1).RotateRight(2); // 3, 4, 1, 2, 5

   array.From(1).RotateLeft(2);   // 3, 1, 5, 2, 4
   array.Until(-1).RotateLeft(2); // 4, 1, 3, 2, 5


索引与序号
---------------------

当你通过 `range-for` 对各种 `Array/View` 进行遍历时，除了数组元素之外，你或许还需要 "索引" 值。

但对于索引的需要至少有两种：首先是它们在数组中的索引；其次，是遍历集合的序号。

比如，当你对一个 ``Slice`` 进行 `range-for` 操作。由于切片只是数组元素的一个子集，因而遍历过程中，每个元素在数组中的索引，与遍历序号是不一致的。但这两种需求都存在。

如果你需要的是一个元素在数组中的索引值，可以使用 ``WithIndex`` ；而如果你需要的是遍历序号，则使用 ``Enumerate`` 。 比如：

.. code-block:: c++

   auto&& slice = array.From(2);

   for(auto&& [elem, i] : slice.WithIndex()) {
      // i start from 2
   }

   for(auto&& [elem, i] : slice.Enumerate()) {
      // i start from 0
   }

而对于不连续的 ``ScopeView`` ，比如：

.. code-block:: c++

   auto&& scope = array.Scope(0x2a); // 1, 3, 5

   for(auto&& [elem, i] : scope.WithIndex()) {
      // i is 1, 3, 5 in turn.
   }

   for(auto&& [elem, i] : scope.Enumerate()) {
      // i is 0, 1, 2 in turn.
   }

而你如果通过 ``SortView`` 对一个数组进行排序，当你遍历 ``SortView`` 是， ``WithIndex`` 得到的依然是数组索引：

.. code-block:: c++

   ObjectArray<int, 10> array{3,1,4,2};

   auto&& sorted = array.SortView().Sort();

   for(auto&& [elem, i] : sorted.WithIndex()) {
      // i is 1, 3, 0, 2 in turn
   }

   for(auto&& [elem, i] : sorted.Enumerate()) {
      // i is 0, 1, 2, 3 in turn
   }

.. important::

   无论你对任何数组，或者 `view` 进行遍历时，``WithIndex`` 总是得到在数组内的索引；``Enumerate`` 总是得到序号。

   除了在 `range-for` 时之外，如果用户在调用 ``ForEach`` 等接口时，如果传入的函数需要索引，得到的索引
   也和 `range-for` 一样，是数组的索引。

   不过，用户调其它接口时，比如 ``operator[]`` 、 ``At`` 、 ``Replace`` 时，使用的索引则是在 `slice` 范围内的索引。


对象数组
------------------------

不同于 `C` 语言数组， ``ObjectArray<T, N>`` 允许存放任意的 `C++` 对象。

一旦允许存放对象，则设计上的需要考量的复杂度将大幅上升。在后续章节里，我们将详细讨论与之有关的因素及设计决定。

