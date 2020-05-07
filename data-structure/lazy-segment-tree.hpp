#include <vector>
#include <cassert>

template<typename T, typename U, typename F, typename G, typename H, typename ZT, typename ZU>
struct lazy_segment_tree {
    int n;
    F f;
    G g;
    H h;
    ZT zero_t;
    ZU zero_u;
    std::vector<T> data;
    std::vector<U> lazy;
    lazy_segment_tree(int n, F f, G g, H h, ZT zero_t, ZU zero_u)
        : n(n), f(f), g(g), h(h), zero_t(zero_t), zero_u(zero_u), data(n << 1, zero_t()), lazy(n << 1, zero_u()) {}
    template<typename I>
    lazy_segment_tree(I begin, I end, F f, G g, H h, ZT zero_t, ZU zero_u)
        : n(end - begin), f(f), g(g), h(h), zero_t(zero_t), zero_u(zero_u), data(n << 1), lazy(n << 1, zero_u()) {
        std::copy(begin, end, data.begin() + n);
        for (int i = n - 1; i > 0; i--) { data[i] = f(data[i << 1 | 0], data[i << 1 | 1]); }
    }
    void propagate(int i) {
        if (i < 1) { return; }
        data[i] = h(data[i], lazy[i], i >= n ? 1 : 2 << std::__lg((n - 1) / i));
        if (i < n) {
            lazy[i << 1 | 0] = g(lazy[i << 1 | 0], lazy[i]);
            lazy[i << 1 | 1] = g(lazy[i << 1 | 1], lazy[i]);
        }
        lazy[i] = zero_u();
    }
    void add(int l, int r, const U &x) {
        assert(0 <= l && l < n);
        assert(0 < r && r <= n);
        l += n, r += n - 1;
        for (int i = std::__lg(r); i > 0; i--) {
            propagate(l >> i);
            propagate(r >> i);
        }
        static auto apply = [&](int i) { lazy[i] = g(lazy[i], x), propagate(i); };
        for (int i = l, j = r + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) { apply(i++); }
            if (j & 1) { apply(--j); }
        }
        for (int i = 1; l >>= 1, r >>= 1; i <<= 1) {
            data[l] = f(h(data[l << 1 | 0], lazy[l << 1 | 0], i), h(data[l << 1 | 1], lazy[l << 1 | 1], i));
            data[r] = f(h(data[r << 1 | 0], lazy[r << 1 | 0], i), h(data[r << 1 | 1], lazy[r << 1 | 1], i));
        }
    }
    T get_sum(int l, int r) {
        assert(0 <= l && l < n);
        assert(0 < r && r <= n);
        l += n, r += n - 1;
        for (int i = std::__lg(r); i > 0; i--) { propagate(l >> i), propagate(r >> i); }
        T a = zero_t(), b = zero_t();
        for (r++; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { propagate(l), a = f(a, data[l++]); }
            if (r & 1) { propagate(--r), b = f(data[r], b); }
        }
        return f(a, b);
    }
};
#define lazysegtree_decl(T, U, name, n, f, g, h, zero_t, zero_u) lazy_segment_tree<T, U, decltype(f), decltype(g), decltype(h), decltype(zero_t), decltype(zero_u)> name(n, f, g, h, zero_t, zero_u)
