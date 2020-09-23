---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/geometry.hpp
    title: "\u5E7E\u4F55"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=jp
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=jp
  bundledCode: "#line 1 \"test/AOJ/CGL/Convex-Hull-0.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=jp\"\n#line\
    \ 1 \"geometry/geometry.hpp\"\n#include <cmath>\n#include <utility>\n#include\
    \ <vector>\n#include <algorithm>\n\nstruct point {\n    double x, y;\n    point()\
    \ : x(0), y(0) {};\n    point(double x, double y) : x(x), y(y) {}\n    static\
    \ point polar(double r, double th) { return {r * cos(th), r * sin(th)}; }\n  \
    \  point &operator+=(const point &rhs) {\n        x += rhs.x, y += rhs.y;\n  \
    \      return *this;\n    }\n    point &operator-=(const point &rhs) {\n     \
    \   x -= rhs.x, y -= rhs.y;\n        return *this;\n    }\n    point &operator*=(double\
    \ rhs) {\n        x *= rhs, y *= rhs;\n        return *this;\n    }\n    point\
    \ &operator/=(double rhs) {\n        x /= rhs, y /= rhs;\n        return *this;\n\
    \    }\n    point operator+() const { return *this; }\n    point operator-() const\
    \ { return {-x, -y}; }\n    point operator+(const point &rhs) const { return point(*this)\
    \ += rhs; }\n    point operator-(const point &rhs) const { return point(*this)\
    \ -= rhs; }\n    point operator*(double rhs) const { return point(*this) *= rhs;\
    \ }\n    point operator/(double rhs) const { return point(*this) /= rhs; }\n};\n\
    constexpr double EPSQ = 1e-16;\ndouble dot(const point &a, const point &b) { return\
    \ a.x * b.x + a.y * b.y; }\ndouble det(const point &a, const point &b) { return\
    \ a.x * b.y - a.y * b.x; }\ndouble norm(const point &a) { return dot(a, a); }\n\
    double abs(const point &a) { return sqrt(norm(a)); }\ndouble arg(const point &a)\
    \ { return atan2(a.y, a.x); }\nbool operator==(const point &a, const point &b)\
    \ { return norm(a - b) < EPSQ; }\nbool operator!=(const point &a, const point\
    \ &b) { return std::rel_ops::operator!=(a, b); }\npoint revolved(const point &a,\
    \ double th) { return {a.x * cos(th) - a.y * sin(th), a.x * sin(th) + a.y * cos(th)};\
    \ }\nint ccw(point a, point b, point c) {\n    b -= a, c -= a;\n    if (det(b,\
    \ c) > EPSQ) { return 1; }\n    if (det(b, c) < -EPSQ) { return -1; }\n    if\
    \ (dot(b, c) < 0) { return 2; }\n    if (norm(b) < norm(c)) { return -2; }\n \
    \   return 0;\n}\nstd::vector<point> convex_hull(std::vector<point> ps) {\n  \
    \  std::sort(ps.begin(), ps.end(),\n              [](const point &a, const point\
    \ &b) -> bool { return a.x < b.x || a.x == b.x && a.y < b.y; });\n    int n =\
    \ ps.size(), k = 0;\n    std::vector<point> qs(n * 2);\n    for (int i = 0; i\
    \ < n; qs[k++] = ps[i++]) {\n        while (k > 1 && det(qs[k - 1] - qs[k - 2],\
    \ ps[i] - qs[k - 1]) < -EPSQ) { k--; }\n    }\n    for (int i = n - 2, t = k;\
    \ i >= 0; qs[k++] = ps[i--]) {\n        while (k > t && det(qs[k - 1] - qs[k -\
    \ 2], ps[i] - qs[k - 1]) < -EPSQ) { k--; }\n    }\n    qs.resize(k - 1);\n   \
    \ return qs;\n}\n#line 3 \"test/AOJ/CGL/Convex-Hull-0.test.cpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nint main() {\n    int n;\n    cin >> n;\n    vector<point>\
    \ ps(n);\n    for (int i = 0; i < n; i++) { cin >> ps[i].y >> ps[i].x; }\n   \
    \ vector<point> ch = convex_hull(ps);\n    rotate(ch.begin(), ch.begin() + 1,\
    \ ch.end()), reverse(ch.begin(), ch.end());\n    cout << ch.size() << endl;\n\
    \    for (int i = 0; i < ch.size(); i++) { cout << (int) ch[i].y << \" \" << (int)\
    \ ch[i].x << endl; }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=jp\"\
    \n#include \"../../../geometry/geometry.hpp\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\n\nint main() {\n    int n;\n    cin >> n;\n    vector<point>\
    \ ps(n);\n    for (int i = 0; i < n; i++) { cin >> ps[i].y >> ps[i].x; }\n   \
    \ vector<point> ch = convex_hull(ps);\n    rotate(ch.begin(), ch.begin() + 1,\
    \ ch.end()), reverse(ch.begin(), ch.end());\n    cout << ch.size() << endl;\n\
    \    for (int i = 0; i < ch.size(); i++) { cout << (int) ch[i].y << \" \" << (int)\
    \ ch[i].x << endl; }\n}"
  dependsOn:
  - geometry/geometry.hpp
  isVerificationFile: true
  path: test/AOJ/CGL/Convex-Hull-0.test.cpp
  requiredBy: []
  timestamp: '2020-09-23 16:37:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/AOJ/CGL/Convex-Hull-0.test.cpp
layout: document
redirect_from:
- /verify/test/AOJ/CGL/Convex-Hull-0.test.cpp
- /verify/test/AOJ/CGL/Convex-Hull-0.test.cpp.html
title: test/AOJ/CGL/Convex-Hull-0.test.cpp
---