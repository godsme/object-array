
ScatteredArray
=========================

常规的数组，在空间上是连续的。如果一个常规数组的元素是可以增删的，那么在删除元素时，如果数组本身
是无序的，则只需要将数组最后一个元素移动到被删除的 `slot` ，以继续保持数组的连续性。这相对于有序
数组要求将所有后续元素整体前移已经是一个重大的性能促进。

但即便只移动一个元素，如果元素较大，也是一种运行时代价。对于需要频繁增删的无序数组而言，将数组
空间看作一种可分配的内存资源，每次需要增加元素时，从中分配一个空间的 `slot` ，删除时，只是将对应的
`slot` 释放回去。这样做的结果，有效的数组元素的空间将不再保证连续，而是散列在整个数组空间里。

这样的数组，称为 **散列数组** ( `ScatteredArray` ) 。

.. code-block:: c++

   template<typename OBJ, std::size_t MAX_NUM>
   struct ScatteredArrayHolder {
      using SizeType   = DeduceSizeType_t<MAX_NUM>;
      using ElemType   = DeduceElemType_T<OBJ>;

      ElemType elems[MAX_NUM];
      BitSet<MAX_NUM> occupied{};
   };

``ScatteredArray`` 和 ``ObjectArray`` 一样，都要考虑 copy/move 构造/赋值，
是否需要提供非平凡析构函数的问题等等，其解决思路与 ``ObjectArray`` 一致，这里就不再赘述。

.. attention::

   对于 `ScatteredArray` ，你不能创建 `Slice` ，跟不能创建 `ScopedView` , 因为
   基于 `ScatteredArray` 的性质，这些操作本身没有意义。

   但是，其它的算法，比如 `Find`, `MinElem` , `ForEach`, `range-for`, `Sort`, `SortObject` 都是支持的。

`ScatteredArray` 的 `range-for` 以及 `ForEach` ，只会遍历所有有效的元素。
