#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=ja"
#include"../../../data-structure/segment-tree.hpp"

#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    auto f = [](int a, int b) { return a + b; };
    auto id = []() { return 0; };
    segtree_decl(int, rsq, n + 1, f, id);
    for (int i = 0; i < q; i++) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) { rsq.set(x, rsq[x] + y); }
        else if (com == 1) { cout << rsq.get_sum(x, y + 1) << endl; }
    }
}