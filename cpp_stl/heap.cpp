// 作用: 把这一段的数组或向量做成一个堆的结构, 范围是(first, last)
void make_heap(first_pointer, end_pointer, compare_function);

// 作用: pop_heap()不是真的把最大 (最小) 的元素从堆中弹出来, 而是重新排序堆
// 它把first和last交换, 然后将[first, last - 1)的数据再做成一个堆
void pop_heap(first_pointer, end_pointer, compare_function);

// 作用: push_heap()假设由[first, last - 1)是一个有效的堆, 然后, 再把堆中的新
// 元素加进来, 做成一个堆, 
void push_heap(first_pointer, end_pointer, compare_function);

// 作用: sort_heap对[first, last)中的序列进行排序, 它假设这个序列是有效堆
// 使用时, 注意函数调用时的数组的下标, 
void sort_heap(first_pointer, end_pointer, compare_function);

bool cmp(int a, int b) {
  return a > b;
}

int main() {
  int i, number[20] = {29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40};
  make_heap(&number[0], &number[12]);
  // 结果: 51 35 40 23 29 20 26 22 19 12 17 15 
  make_heap(&number[0], &number[12], cmp);
  // 结果: 12 17 15 19 29 20 26 22 23 51 35 40  
  // 加入元素8   
  number[12] = 8;
  // 加入后调整    
  push_heap(&number[0], &number[13], cmp);
  // 结果: 8 17 12 19 29 15 26 22 23 51 35 40 20   
  // 弹出元素8    
  pop_heap(&number[0], &number[13], cmp);
  // 结果: 12 17 15 19 29 20 26 22 23 51 35 40 8   
  sort_heap(&number[0], &number[12], cmp);
  // 结果: 51 40 35 29 26 23 22 20 19 17 15 12 
  return 0;
}
