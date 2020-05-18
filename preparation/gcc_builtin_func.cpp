// 返回x的最后一位1的是从后向前第几位, 比如7368 (1110011001000) 返回4
int __builtin_ffs(unsigned int x)
// 返回前导的0的个数
int __builtin_ctz(unsigned int x)
// 返回后面的0个个数, 和__builtin_clz相对
int __builtin_popcount(unsigned int x)
// 返回二进制表示中1的个数
int __builtin_parity(unsigned int x)
// 返回x的奇偶校验位, 也就是x的1的个数模2的结果
int __builtin_clz(unsigned int x)

// 此外, 这些函数都有相应的usigned long和usigned long long版本,
// 只需要在函数名后面加上l或ll就可以了, 比如int __builtin_clzll
