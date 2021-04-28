---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/ford-fulkerson.hpp
    title: "Ford-Fulkerson \u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja
  bundledCode: "#line 1 \"test/AOJ/GRL/Maximum-Flow-0.test.cpp\"\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja\"\
    \n#line 1 \"graph/ford-fulkerson.hpp\"\n#include <limits>\n#include <map>\n#include\
    \ <queue>\n#include <vector>\n\ntemplate<typename S>\nstruct ford_fulkerson {\n\
    \    using T = typename S::T;\n    struct edge {\n        int to, rev;\n     \
    \   T cap;\n        bool is_rev;\n    };\n    std::vector<std::vector<edge>> graph;\n\
    \    std::vector<int> used;\n    int timestamp;\n    void add_edge(int from, int\
    \ to, T cap) {\n        graph[from].push_back({to, (int) graph[to].size(), cap,\
    \ false});\n        graph[to].push_back({from, (int) graph[from].size() - 1, S::zero(),\
    \ true});\n    }\n    ford_fulkerson(int n) : graph(n), used(n) {}\n    T dfs(int\
    \ v, int t, T f) {\n        if (v == t) { return f; }\n        used[v] = timestamp;\n\
    \        for (int i = 0; i < graph[v].size(); i++) {\n            edge &e = graph[v][i];\n\
    \            if (used[e.to] != timestamp && S::less(S::zero(), e.cap)) {\n   \
    \             T d = dfs(e.to, t, S::less(e.cap, f) ? e.cap : f);\n           \
    \     if (S::is_zero(d)) { continue; }\n                e.cap = S::plus(e.cap,\
    \ S::minus(d));\n                graph[e.to][e.rev].cap = S::plus(graph[e.to][e.rev].cap,\
    \ d);\n                return d;\n            }\n        }\n        return S::zero();\n\
    \    }\n    T calc_max_flow(int s, int t, T lim) {\n        T ret = S::zero();\n\
    \        fill(used.begin(), used.end(), 0);\n        timestamp = 0;\n        while\
    \ (true) {\n            timestamp++;\n            T f = dfs(s, t, lim);\n    \
    \        if (S::is_zero(f)) { return ret; }\n            ret = S::plus(ret, f);\n\
    \            lim = S::plus(lim, S::minus(f));\n        }\n    }\n    T calc_max_flow(int\
    \ s, int t) { return calc_max_flow(s, t, S::inf()); }\n    std::map<std::pair<int,\
    \ int>, T> get_max_flow() {\n        std::map<std::pair<int, int>, T> ret;\n \
    \       for (int i = 0; i < graph.size(); i++) {\n            for (int j = 0;\
    \ j < graph[i].size(); j++) {\n                edge &e = graph[i][j];\n      \
    \          if (e.is_rev) { ret[{e.to, i}] = e.cap; }\n            }\n        }\n\
    \        return ret;\n    }\n    std::map<std::pair<int, int>, T> get_min_cut(int\
    \ s) {\n        std::map<std::pair<int, int>, T> ret;\n        std::vector<int>\
    \ visited(graph.size());\n        std::queue<int> que;\n        que.push(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop();\n            if (visited[v]) { continue; }\n            visited[v]\
    \ = true;\n            for (int i = 0; i < graph[v].size(); i++) {\n         \
    \       edge &e = graph[v][i];\n                if (!S::is_zero(e.cap)) { que.push(e.to);\
    \ }\n            }\n        }\n        for (int i = 0; i < graph.size(); i++)\
    \ {\n            if (visited[i]) { continue; }\n            for (int j = 0; j\
    \ < graph[i].size(); j++) {\n                edge &e = graph[i][j];\n        \
    \        if (e.is_rev && visited[e.to]) { ret[{e.to, i}] = e.cap; }\n        \
    \    }\n        }\n        return ret;\n    }\n};\n\nstruct int_ff {\n    using\
    \ T = int;\n    static T zero() { return 0; }\n    static T inf() { return std::numeric_limits<T>::max();\
    \ }\n    static T minus(const T &a) { return -a; }\n    static T plus(const T\
    \ &a, const T &b) { return a + b; }\n    static bool less(const T &a, const T\
    \ &b) { return a < b; }\n    static bool is_zero(const T &a) { return a == zero();\
    \ };\n};\n#line 3 \"test/AOJ/GRL/Maximum-Flow-0.test.cpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nint main() {\n    int V, E;\n    cin >> V >> E;\n    ford_fulkerson<int_ff>\
    \ ff(V);\n    for (int i = 0; i < E; i++) {\n        int u, v, c;\n        cin\
    \ >> u >> v >> c;\n        ff.add_edge(u, v, c);\n    }\n    int ans0 = ff.calc_max_flow(0,\
    \ V - 1);\n    map<pair<int, int>, int> flow = ff.get_max_flow();\n    int ans1\
    \ = 0;\n    for (auto p:flow) {\n        if (p.first.first == 0) { ans1 += p.second;\
    \ }\n    }\n    int ans2 = 0;\n    for (auto p:flow) {\n        if (p.first.second\
    \ == V - 1) { ans2 += p.second; }\n    }\n    map<pair<int, int>, int> cut = ff.get_min_cut(0);\n\
    \    int ans3 = 0;\n    for (auto p:cut) { ans3 += p.second; }\n    assert(ans0\
    \ == ans1);\n    assert(ans0 == ans2);\n    assert(ans0 == ans3);\n    cout <<\
    \ ans0 << endl;\n\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja\"\
    \n#include\"../../../graph/ford-fulkerson.hpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nint main() {\n    int V, E;\n    cin >> V >> E;\n    ford_fulkerson<int_ff>\
    \ ff(V);\n    for (int i = 0; i < E; i++) {\n        int u, v, c;\n        cin\
    \ >> u >> v >> c;\n        ff.add_edge(u, v, c);\n    }\n    int ans0 = ff.calc_max_flow(0,\
    \ V - 1);\n    map<pair<int, int>, int> flow = ff.get_max_flow();\n    int ans1\
    \ = 0;\n    for (auto p:flow) {\n        if (p.first.first == 0) { ans1 += p.second;\
    \ }\n    }\n    int ans2 = 0;\n    for (auto p:flow) {\n        if (p.first.second\
    \ == V - 1) { ans2 += p.second; }\n    }\n    map<pair<int, int>, int> cut = ff.get_min_cut(0);\n\
    \    int ans3 = 0;\n    for (auto p:cut) { ans3 += p.second; }\n    assert(ans0\
    \ == ans1);\n    assert(ans0 == ans2);\n    assert(ans0 == ans3);\n    cout <<\
    \ ans0 << endl;\n\n}"
  dependsOn:
  - graph/ford-fulkerson.hpp
  isVerificationFile: true
  path: test/AOJ/GRL/Maximum-Flow-0.test.cpp
  requiredBy: []
  timestamp: '2020-09-23 16:37:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/AOJ/GRL/Maximum-Flow-0.test.cpp
layout: document
redirect_from:
- /verify/test/AOJ/GRL/Maximum-Flow-0.test.cpp
- /verify/test/AOJ/GRL/Maximum-Flow-0.test.cpp.html
title: test/AOJ/GRL/Maximum-Flow-0.test.cpp
---