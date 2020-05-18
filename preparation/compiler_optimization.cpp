// 强制O2优化
#pragma GCC optimize(2)

// G++(MinGW32)扩栈
// 写在main()函数的最前边
int SIZE_OF_STACK = 256 << 20; // 256MB
char* p = (char*) malloc(SIZE_OF_STACK) + SIZE_OF_STACK;
__asm__("movl %0, %%esp\n"::"r"(p));

// G++(64位linux)扩栈
// 只在会爆栈的函数前后使用汇编语句会更安全
// 但要注意避免使用局部变量保存函数返回值
long rsp;

int main() {
  int SIZE_OF_STACK = 256 << 20; // 256MB
  char* p = (char*) malloc(SIZE_OF_STACK) + SIZE_OF_STACK;
  __asm__("movq %%rsp, %0"::"m"(rsp));
  __asm__("movq %0, %%rsp"::"r"(p));

  //程序体

  __asm__("movq %0, %%rsp\n"::"m"(rsp));
  return 0;
}

// C++扩栈
#pragma comment(linker, "/STACK:102400000,102400000")
