int bit_count(unsigned int x) {
  x -= ((x & 0xAAAAAAAAu) >> 1);
  x = ((x & 0xCCCCCCCCu) >> 2) + (x & 0x33333333u);
  x = ((x >> 4) + x) & 0x0F0F0F0Fu;
  x = (x * 0x01010101u) >> 24;
  return x;
}

// 查询0-2^32的所有x中1的个数
int bit_table[65537];
void process_bit_table() {
  bit_table[0] = 0;
  for (int i = 1; i < 65536; i++) {
    bit_table[i] = bit_table[i >> 1] + (i & 1);
  }
}

int bit_count(unsigned int x) {
  return bit_table[x >> 16] + bit_table[x & 65535u];
}
