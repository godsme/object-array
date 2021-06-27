
ArrayView
=======================

除了我们自己需要明确定义和管理的数组之外，还有另外一族数组，它们属于已经定义好的 ``POD`` 数据
结构中所包含的数组。

一个可以做出的假设是，由于这些数组都是 ``POD`` 的，因而必然是平凡的。

但是，为了操作的方便性，我们往往又会为这些 ``POD`` 数组加上一层 ``wrapper`` ，让它们可以在
不增加任何开销的情况下，变为逻辑功能更加内聚的对象。

这些数组，根据是从外而来的消息，还是由内往外的消息，又可以分为只读和可写的。

结合这些需求，需要定义如下两种 ``ArrayView`` ：（之所以被称做 `view` ，是因为 `view` 本身并不
拥有数据，它只是查看或操作别人持有的数据。

ConstArrayView
----------------------------

.. code-block:: c++

   template <typename OBJ, std::size_t MAX_NUM, typename ELEM = OBJ>
   struct ConstArrayView {
      using SizeType = DeduceSizeType_T<MAX_NUM>;
      using ElemType = ELEM;
      using ViewTrait = typename ArrayViewTrait<OBJ, ELEM>::Type;

      ConstArrayView(OBJ const* array, std::size_t n)
         : elems(ViewTrait::ConstObjToElem(array))
         , num(std::min(MAX_NUM, n))
      {}

      ElemType const* elems;
      SizeType num;
   };

ArrayView
--------------------------

.. code-block:: c++

   template <typename OBJ, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = OBJ>
   struct ArrayView {
      using ElemType = ELEM;
      using ViewTrait = typename ArrayViewTrait<OBJ, ELEM>::Type;

      ArrayView(OBJ* array, SIZE_TYPE& n)
         : elems(ViewTrait::ObjToElem(array))
         , num(n)
      {}

      ElemType* elems;
      SIZE_TYPE& num;
   };


自动识别
--------------------------

除非你明确定义，否则，你不会直接使用 ``ConstArrayView`` 。
你只需要使用 ``ArrayView`` ，然后依靠模版类的自动类型推演来自动决定。比如：

.. code-block:: c++

   struct Foo {
      int array[10];
      uint16_t num;
   };

   Foo foo{{1,2,3,4}, 4};

   ArrayView view1{foo.array, foo.num}; // ArrayView

   view1.Append(5); // so you can append

   Foo const& constRef = foo;

   ArrayView view2{foo.array, foo.num}; // ConstArrayView

   view2.Append(5); // compiling error.

``ArrayView<T,N>`` 可以使用 ``ObjectArray<T, N>`` 的一切接口和算法。




