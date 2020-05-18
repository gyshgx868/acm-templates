// 求x前缀 (高位) 0个数
int num_leading_zeros(unsigned int x) {
  int res = 0;
  if (x >> 16) { x >>= 16; }
  else { res |= 16; }
  if (x >> 8) { x >>= 8; }
  else { res |= 8; }
  if (x >> 4) { x >>= 4; }
  else { res |= 4; }
  if (x >> 2) { x >>= 2; }
  else { res |= 2; }
  if (x >> 1) { x >>= 1; }
  else { res |= 1; }
  return res + !x;
}

// 求x后缀 (低位) 0个数
int num_trailing_zeros(unsigned int x) {
  int res = 0;
  if (!(x & 65535u)) { x >>= 16, res |= 16; }
  if (!(x & 255u)) { x >>= 8, res |= 8; }
  if (!(x & 15u)) { x >>= 4, res |= 4; }
  if (!(x & 3u)) { x >>= 2, res |= 2; }
  if (!(x & 1u)) { x >>= 1, res |= 1; }
  return res + !x;
}

// 查询0-2^32的所有x的前缀0个数
int zeros_table[65537];
void process_zeros_table() {
  zeros_table[0] = 16;
  for (int i = 1; i < 65536; ++i) {
    zeros_table[i] = zeros_table[i >> 1] - 1;
  }
}

int num_leading_zeros(unsigned int x) {
  if (x >> 16) { return zeros_table[x >> 16]; }
  return zeros_table[x & 65535u] + 16;
}
