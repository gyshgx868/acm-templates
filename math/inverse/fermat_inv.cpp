template <class T, class U = T>
T get_inv(T a, U mod) { return quick_pow(a, mod - 2, mod); }
