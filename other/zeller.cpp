int zeller(int year, int month, int day) {
  if (month < 3) {
    month += 12;
    year -= 1;
  }
  int c = year / 100;
  int y = year % 100;
  int w = (y + (y / 4) + (c / 4) - (2 * c) +
      ((26 * (month + 1)) / 10) + day - 1) % 7;
  if (w < 0) { w += 7; }
  return w;  // 0表示周日
}
