template <class T>
struct MaxOperation {
  static T join_delta(T was, T delta) { return std::max(was, delta); }

  static T accumulate(T value, T delta, int length) {
    return std::max(value, delta);
  }

  static T neutral_value() { return std::numeric_limits<T>::min(); }

  static T neutral_delta() { return std::numeric_limits<T>::min(); }

  static T join_value(T left, T right) { return std::max(left, right); }
};
