struct Max {
  template <class T>
  T operator ()(const T& x, const T& y) const { return std::max(x, y); }
};

struct Min {
  template <class T>
  T operator ()(const T& x, const T& y) const { return std::min(x, y); }
};
