template <class T>
T get_sum(const std::vector<T>& arr) {
  T cur_sum = T(), res = std::numeric_limits<T>::min();
  for (int i = 0; i < arr.size(); i++) {
    cur_sum = std::max(arr[i], cur_sum + arr[i]);
    res = std::max(res, cur_sum);
  }
  return res;
}
