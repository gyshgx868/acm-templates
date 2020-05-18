// 返回x第k个1的位次 (从低到高, 0-31)
int kth_bit(unsigned int x, int k) {
  int s[5], res = 0, t;
  s[0] = x;
  s[1] = x - ((x & 0xAAAAAAAAu) >> 1);
  s[2] = ((s[1] & 0xCCCCCCCCu) >> 2) + (s[1] & 0x33333333u);
  s[3] = ((s[2] >> 4) + s[2]) & 0x0F0F0F0Fu;
  s[4] = ((s[3] >> 8) + s[3]) & 0x00FF00FFu;
  t = s[4] & 65535u;
  if (t < k) { k -= t, res |= 16, x >>= 16; }
  t = (s[3] >> res) & 255u;
  if (t < k) { k -= t, res |= 8, x >>= 8; }
  t = (s[2] >> res) & 15u;
  if (t < k) { k -= t, res |= 4, x >>= 4; }
  t = (s[1] >> res) & 3u;
  if (t < k) { k -= t, res |= 2, x >>= 2; }
  t = (s[0] >> res) & 1u;
  if (t < k) { k -= t, res |= 1, x >>= 1; }
  return res;
}

// 统计x低位开始连续的1, 例如7返回7
unsigned int continuous_ones(unsigned int x) {
  return x & (x ^ (x + 1));
}

// 获得当前x (x中有k个1) 的字典序下一位
unsigned int next_comb(unsigned int x) {
  unsigned int l = x & (-x), y = x + l;
  return y | (((x ^ y) / l) >> 2);
}
