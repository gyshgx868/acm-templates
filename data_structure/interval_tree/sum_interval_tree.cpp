template <class T>
struct SumOperation {
  static T join_delta(T was, T delta) { return was + delta; }

  static T accumulate(T value, T delta, int length) {
    return value + delta * length;
  }

  static T neutral_value() { return T(); }

  static T neutral_delta() { return T(); }

  static T join_value(T left, T right) { return left + right; }
};
