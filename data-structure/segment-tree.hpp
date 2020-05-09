#include <vector>
#include <cassert>

/*
 * @title セグメントツリー
 * @docs docs/data-structure/segment-tree.md
 */

template<typename T, typename F, typename ID>
struct segment_tree {
    int n;
    F f;
    ID id;
    std::vector<T> data;
    segment_tree(int n, F f, ID id) : n(n), f(f), id(id), data(n << 1, id()) {}
    template<typename I>
    segment_tree(I begin, I end, F f, ID id) : n(end - begin), f(f), id(id), data(n << 1) {
        std::copy(begin, end, data.begin() + n);
        for (int i = n - 1; i > 0; i--) { data[i] = f(data[i << 1 | 0], data[i << 1 | 1]); }
    }
    void set(int i, const T &x) {
        assert(0 <= i && i < n);
        data[i += n] = x;
        while (i >>= 1) { data[i] = f(data[i << 1 | 0], data[i << 1 | 1]); }
    }
    T operator[](int i) const { return data[i + n]; }
    T get_sum(int l, int r) const {
        assert(0 <= l && l < n);
        assert(0 < r && r <= n);
        T a = id(), b = id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { a = f(a, data[l++]); }
            if (r & 1) { b = f(data[--r], b); }
        }
        return f(a, b);
    }
};
#define segtree_decl(T, name, n, f, id) segment_tree<T, decltype(f), decltype(id)> name(n, f, id)
