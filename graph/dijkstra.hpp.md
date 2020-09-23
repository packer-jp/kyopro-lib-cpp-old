---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/GRL/Single-Source-Shortest-Path-0.test.cpp
    title: test/AOJ/GRL/Single-Source-Shortest-Path-0.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"graph/dijkstra.hpp\"\n#include <limits>\n#include <queue>\n\
    #include <vector>\n#include <cassert>\n\ntemplate<typename S>\nstruct dijkstra\
    \ {\n    using T = typename S::T;\n    using E = typename S::E;\n    std::vector<std::vector<int>>\
    \ adj;\n    std::vector<std::vector<E>> cost;\n    dijkstra(int n) : adj(n), cost(n)\
    \ {}\n    void add_edge(int from, int to, E cost) { adj[from].emplace_back(to),\
    \ this->cost[from].emplace_back(cost); }\n    std::vector<T> get_dist(int s) {\n\
    \        std::vector<T> ret(adj.size(), S::inf());\n        using P = std::pair<T,\
    \ int>;\n        auto c = [&](P a, P b) -> bool { return S::less(b.first, a.first);\
    \ };\n        std::priority_queue<P, std::vector<P>, decltype(c)> pq(c);\n   \
    \     ret[s] = S::zero();\n        pq.emplace(ret[s], s);\n        while (!pq.empty())\
    \ {\n            P p = pq.top();\n            pq.pop();\n            int v = p.second;\n\
    \            if (S::less(ret[v], p.first)) { continue; }\n            for (int\
    \ i = 0; i < adj[v].size(); i++) {\n                int u = adj[v][i];\n     \
    \           T dist = S::plus(ret[v], cost[v][i]);\n                if (S::less(dist,\
    \ ret[u])) { ret[u] = dist, pq.emplace(ret[u], u); }\n            }\n        }\n\
    \        return ret;\n    }\n};\n\nstruct int_dij {\n    using T = int;\n    using\
    \ E = int;\n    static T zero() { return 0; }\n    static T inf() { return std::numeric_limits<T>::max();\
    \ }\n    static T plus(const T &a, const E &b) { return a == inf() ? inf() : a\
    \ + b; }\n    static bool less(const T &a, const T &b) { return a < b; }\n};\n"
  code: "#include <limits>\n#include <queue>\n#include <vector>\n#include <cassert>\n\
    \ntemplate<typename S>\nstruct dijkstra {\n    using T = typename S::T;\n    using\
    \ E = typename S::E;\n    std::vector<std::vector<int>> adj;\n    std::vector<std::vector<E>>\
    \ cost;\n    dijkstra(int n) : adj(n), cost(n) {}\n    void add_edge(int from,\
    \ int to, E cost) { adj[from].emplace_back(to), this->cost[from].emplace_back(cost);\
    \ }\n    std::vector<T> get_dist(int s) {\n        std::vector<T> ret(adj.size(),\
    \ S::inf());\n        using P = std::pair<T, int>;\n        auto c = [&](P a,\
    \ P b) -> bool { return S::less(b.first, a.first); };\n        std::priority_queue<P,\
    \ std::vector<P>, decltype(c)> pq(c);\n        ret[s] = S::zero();\n        pq.emplace(ret[s],\
    \ s);\n        while (!pq.empty()) {\n            P p = pq.top();\n          \
    \  pq.pop();\n            int v = p.second;\n            if (S::less(ret[v], p.first))\
    \ { continue; }\n            for (int i = 0; i < adj[v].size(); i++) {\n     \
    \           int u = adj[v][i];\n                T dist = S::plus(ret[v], cost[v][i]);\n\
    \                if (S::less(dist, ret[u])) { ret[u] = dist, pq.emplace(ret[u],\
    \ u); }\n            }\n        }\n        return ret;\n    }\n};\n\nstruct int_dij\
    \ {\n    using T = int;\n    using E = int;\n    static T zero() { return 0; }\n\
    \    static T inf() { return std::numeric_limits<T>::max(); }\n    static T plus(const\
    \ T &a, const E &b) { return a == inf() ? inf() : a + b; }\n    static bool less(const\
    \ T &a, const T &b) { return a < b; }\n};"
  dependsOn: []
  isVerificationFile: false
  path: graph/dijkstra.hpp
  requiredBy: []
  timestamp: '2020-09-23 16:37:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/AOJ/GRL/Single-Source-Shortest-Path-0.test.cpp
documentation_of: graph/dijkstra.hpp
layout: document
title: "Dijkstra \u6CD5"
---

## 概要
辺のコストが非負なグラフの単一始点最短距離を頂点数$N$、辺数$M$に対し$O((N+M)\log N)$で求める。

## テンプレートパラメータ
- `typename T`  
距離のデータ型。

## `<typename T>dijkstra<T>`

## 引数
- `std::vector<std::vector<int>> adj`  
隣接リスト。

- `std::vector<std::vector<E>> cost`  
コストのリスト (隣接リストと同じ構造) 。

- `int s`  
始点。

- `F f`  
距離とコストを受けとり、距離を返す二項演算。

- `G g`  
距離`a, b`を受けとり、`a > b`を返す二項演算。`g(a, f(a, x))`を要請する。

- `ID id`  
距離の`f`に関する単位元。

- `AB ab`  
距離の`f`に関する吸収元。`g(ab, y)`を要請する。