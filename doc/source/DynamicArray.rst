DynamicArray
===================

故名思议，``DynamicArray`` 的数组元素都是从某种 ``Allocator`` 中动态分配，数组本身只持有元素的指针。

同时，对于数组的各种操作，又会屏蔽掉这些细节，与直接访问一个 ``ObjectArray<T, N>`` 没有差别。



