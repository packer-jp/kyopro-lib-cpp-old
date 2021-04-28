---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/low-link.hpp
    title: Low Link
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja
  bundledCode: "#line 1 \"test/AOJ/GRL/Bridges-0.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja\"\
    \n#line 1 \"graph/low-link.hpp\"\n#include <vector>\n#include <algorithm>\n\n\
    struct low_link {\n    struct edge {\n        int to, idx;\n        edge(int to,\
    \ int idx) : to(to), idx(idx) {}\n    };\n    int m = 0;\n    std::vector<std::vector<edge>>\
    \ adj;\n    low_link(int n) : adj(n) {}\n    int add_edge(int u, int v) {\n  \
    \      adj[u].emplace_back(v, m), adj[v].emplace_back(u, m);\n        return m++;\n\
    \    }\n    std::pair<std::vector<int>, std::vector<int>> get() {\n        int\
    \ n = adj.size();\n        std::vector<int> ord(n), low(n), articulations, bridges;\n\
    \        std::vector<bool> visited(n);\n        int k = 0;\n        auto dfs =\
    \ [&](auto &&dfs, int cur, int par) -> void {\n            visited[cur] = true;\n\
    \            ord[cur] = k++;\n            low[cur] = ord[cur];\n            int\
    \ cnt = 0;\n            bool is_articulation = false;\n            for (auto[to,\
    \ idx] : adj[cur]) {\n                if (!visited[to]) {\n                  \
    \  cnt++;\n                    dfs(dfs, to, cur);\n                    low[cur]\
    \ = std::min(low[cur], low[to]);\n                    is_articulation |= ord[cur]\
    \ <= low[to];\n                    if (ord[cur] < low[to]) { bridges.emplace_back(idx);\
    \ }\n                } else if (to != par) { low[cur] = std::min(low[cur], ord[to]);\
    \ }\n            }\n            if (par == -1) { is_articulation = cnt >= 2; }\n\
    \            if (is_articulation) { articulations.emplace_back(cur); }\n     \
    \   };\n        dfs(dfs, 0, -1);\n        return {articulations, bridges};\n \
    \   }\n};\n#line 3 \"test/AOJ/GRL/Bridges-0.test.cpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nint main() {\n    int V, E;\n    cin >> V >> E;\n    low_link\
    \ ll(V);\n    vector<int> s(E), t(E);\n    for (int i = 0; i < E; i++) {\n   \
    \     cin >> s[i] >> t[i];\n        if (s[i] > t[i]) { swap(s[i], t[i]); }\n \
    \       ll.add_edge(s[i], t[i]);\n    }\n    vector<pair<int, int>> ans;\n   \
    \ for (int i:ll.get().second) { ans.emplace_back(s[i], t[i]); }\n    sort(ans.begin(),\
    \ ans.end());\n    for (auto p:ans) { cout << p.first << \" \" << p.second <<\
    \ endl; }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja\"\
    \n#include \"../../../graph/low-link.hpp\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\n\nint main() {\n    int V, E;\n    cin >> V >> E;\n    low_link\
    \ ll(V);\n    vector<int> s(E), t(E);\n    for (int i = 0; i < E; i++) {\n   \
    \     cin >> s[i] >> t[i];\n        if (s[i] > t[i]) { swap(s[i], t[i]); }\n \
    \       ll.add_edge(s[i], t[i]);\n    }\n    vector<pair<int, int>> ans;\n   \
    \ for (int i:ll.get().second) { ans.emplace_back(s[i], t[i]); }\n    sort(ans.begin(),\
    \ ans.end());\n    for (auto p:ans) { cout << p.first << \" \" << p.second <<\
    \ endl; }\n}"
  dependsOn:
  - graph/low-link.hpp
  isVerificationFile: true
  path: test/AOJ/GRL/Bridges-0.test.cpp
  requiredBy: []
  timestamp: '2020-10-13 20:30:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/AOJ/GRL/Bridges-0.test.cpp
layout: document
redirect_from:
- /verify/test/AOJ/GRL/Bridges-0.test.cpp
- /verify/test/AOJ/GRL/Bridges-0.test.cpp.html
title: test/AOJ/GRL/Bridges-0.test.cpp
---