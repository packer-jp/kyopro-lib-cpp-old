---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data-structure/splay-tree.hpp
    title: "Splay \u6728"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508
  bundledCode: "#line 1 \"test/AOJ/Volume15/RMQ-0.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508\"\
    \n#line 1 \"data-structure/splay-tree.hpp\"\n#include <vector>\n\ntemplate<typename\
    \ M>\nstruct splay_tree {\n    using T = typename M::T;\n    struct node {\n \
    \       node *left, *right, *par;\n        int size;\n        T val, res;\n  \
    \      node(T val) : left(nullptr), right(nullptr), par(nullptr), size(1), val(val),\
    \ res(val) {}\n        void rotate() {\n            node *p, *pp, *c;\n      \
    \      p = par, pp = p->par;\n            if (p->left == this) { c = right, right\
    \ = p, p->left = c; }\n            else { c = left, left = p, p->right = c; }\n\
    \            if (pp) {\n                if (pp->left == p) { pp->left = this;\
    \ }\n                else { pp->right = this; }\n            }\n            if\
    \ (c) { c->par = p; }\n            par = pp, p->par = this;\n            p->update();\n\
    \            update();\n        }\n        int state() {\n            if (!par)\
    \ { return 0; }\n            if (par->left == this) { return 1; }\n          \
    \  else { return -1; }\n        }\n        void splay() {\n            while (state()\
    \ != 0) {\n                if (par->state() == 0) { rotate(); }\n            \
    \    else if (state() == par->state()) { par->rotate(), rotate(); }\n        \
    \        else { rotate(), rotate(); }\n            }\n        }\n        void\
    \ update() {\n            size = 1, res = val;\n            if (left) { size +=\
    \ left->size, res = M::op(left->res, res); }\n            if (right) { size +=\
    \ right->size, res = M::op(res, right->res); }\n        }\n    };\n    node *root;\n\
    \    splay_tree(node *root = nullptr) : root(root) {}\n    int size() { return\
    \ root ? root->size : 0; }\n    node *get_node(int idx) {\n        node *cur =\
    \ root;\n        while (true) {\n            int size_l = cur->left ? cur->left->size\
    \ : 0;\n            if (idx < size_l) { cur = cur->left; }\n            if (idx\
    \ == size_l) {\n                cur->splay();\n                return root = cur;\n\
    \            }\n            if (idx > size_l) { cur = cur->right, idx -= size_l\
    \ + 1; }\n        }\n    }\n    T get(int idx) { return get_node(idx)->val; }\n\
    \    int lower_bound(T x) {\n        if (!root) { return 0; }\n        node *cur\
    \ = root;\n        int ret = -1;\n        while (true) {\n            if (cur->state()\
    \ < 1) { ret += cur->left ? cur->left->size + 1 : 1; }\n            else { ret\
    \ -= cur->right ? cur->right->size + 1 : 1; }\n            if (M::gr(x, cur->val))\
    \ {\n                if (cur->right) { cur = cur->right; }\n                else\
    \ {\n                    cur->splay(), root = cur;\n                    return\
    \ ret + 1;\n                }\n            } else {\n                if (cur->left)\
    \ { cur = cur->left; }\n                else {\n                    cur->splay(),\
    \ root = cur;\n                    return ret;\n                }\n          \
    \  }\n        }\n    }\n    splay_tree split(int size_left) {\n        if (size_left\
    \ == 0) {\n            node *root_r = root;\n            root = nullptr;\n   \
    \         return root_r;\n        }\n        if (size_left == root->size) { return\
    \ nullptr; }\n        node *root_r = get_node(size_left);\n        root = root_r->left;\n\
    \        root_r->left = nullptr, root->par = nullptr;\n        root_r->update();\n\
    \        return root_r;\n    }\n    void merge(splay_tree right) {\n        if\
    \ (!root) {\n            root = right.root;\n            return;\n        }\n\
    \        if (!right.root) { return; }\n        get_node(root->size - 1);\n   \
    \     root->right = right.root, right.root->par = root;\n        root->update();\n\
    \    }\n    void insert(int idx, T x) {\n        splay_tree xt = new node(x),\
    \ right = split(idx);\n        merge(xt), merge(right);\n    }\n    void erase(int\
    \ idx) {\n        splay_tree xt = split(idx);\n        splay_tree right = xt.split(1);\n\
    \        delete xt.root;\n        merge(right);\n    }\n    T get_sum(int l, int\
    \ r) {\n        splay_tree mid = split(l);\n        splay_tree right = mid.split(r\
    \ - l);\n        T ret = mid.root->res;\n        merge(mid), merge(right);\n \
    \       return ret;\n    }\n};\n\nstruct int_st {\n    using T = int;\n    static\
    \ T op(T a, T b) { return std::min(a, b); }\n    static bool gr(const T &a, const\
    \ T &b) { return a > b; }\n};\n#line 3 \"test/AOJ/Volume15/RMQ-0.test.cpp\"\n\n\
    #include <bits/stdc++.h>\nusing namespace std;\n\nint main() {\n    int n, q;\n\
    \    cin >> n >> q;\n    splay_tree<int_st> st;\n    for (int i = 0; i < n; i++)\
    \ {\n        int a;\n        cin >> a;\n        st.insert(i, a);\n    }\n    while\
    \ (q--) {\n        int x, y, z;\n        cin >> x >> y >> z;\n        if (x ==\
    \ 0) {\n            splay_tree<int_st> mid0 = st.split(y);\n            splay_tree<int_st>\
    \ mid1 = mid0.split(z - y);\n            splay_tree<int_st> right = mid1.split(1);\n\
    \            st.merge(mid1), st.merge(mid0), st.merge(right);\n        }\n   \
    \     if (x == 1) {\n            cout << st.get_sum(y, z + 1) << endl;\n     \
    \   }\n        if (x == 2) {\n            st.erase(y);\n            st.insert(y,\
    \ z);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508\"\
    \n#include \"../../../data-structure/splay-tree.hpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    splay_tree<int_st>\
    \ st;\n    for (int i = 0; i < n; i++) {\n        int a;\n        cin >> a;\n\
    \        st.insert(i, a);\n    }\n    while (q--) {\n        int x, y, z;\n  \
    \      cin >> x >> y >> z;\n        if (x == 0) {\n            splay_tree<int_st>\
    \ mid0 = st.split(y);\n            splay_tree<int_st> mid1 = mid0.split(z - y);\n\
    \            splay_tree<int_st> right = mid1.split(1);\n            st.merge(mid1),\
    \ st.merge(mid0), st.merge(right);\n        }\n        if (x == 1) {\n       \
    \     cout << st.get_sum(y, z + 1) << endl;\n        }\n        if (x == 2) {\n\
    \            st.erase(y);\n            st.insert(y, z);\n        }\n    }\n}"
  dependsOn:
  - data-structure/splay-tree.hpp
  isVerificationFile: true
  path: test/AOJ/Volume15/RMQ-0.test.cpp
  requiredBy: []
  timestamp: '2020-09-23 16:37:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/AOJ/Volume15/RMQ-0.test.cpp
layout: document
redirect_from:
- /verify/test/AOJ/Volume15/RMQ-0.test.cpp
- /verify/test/AOJ/Volume15/RMQ-0.test.cpp.html
title: test/AOJ/Volume15/RMQ-0.test.cpp
---