bool nim(const std::vector<int>& sg) {
  int res = 0;
  for (int i = 0; i < sg.size(); i++) { res ^= sg[i]; }
  return res != 0;
}
