#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
// #include <utility>

// #include <string_view>
using namespace std;
using std::vector;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

typedef struct line {
  void setup(ll x0, ll y0, ll x1, ll y1) {
    A = y1 - y0;
    B = -(x1 - x0);
    C = y0 * x1 - x0 * y1;
  }

  ll A, B, C;
} line;

typedef struct point {
  void setup(ll xx, ll yy) {
    x = xx;
    y = yy;
  }

  ll x, y;
} point;

typedef struct circle {
  void setup(ll x, ll y, ll r) {
    cent.x = x;
    cent.y = y;
    rad = r;
  }
  bool unstrightly_contains(point point) {
    return (cent.x - point.x) * (cent.x - point.x) +
    (cent.y - point.y) * (cent.y - point.y) < rad * rad;
  }
  bool strightly_contains(point point) {
    return (cent.x - point.x) * (cent.x - point.x) +
    (cent.y - point.y) * (cent.y - point.y) <= rad * rad;
  }

  point cent;
  ll rad;
} circle;

typedef struct half_plain {
  void setup(ll x0, ll y0, ll x1, ll y1) {
    ll a = x1 - x0, b = y1 - y0, x2 = x0 - b, y2 = y0 + a;
    base_line.setup(x0, y0, x2, y2);
    base_x = x1;
    base_y = y1;
  }
  bool unstrightly_contains(point point) {
    return (base_line.A * base_x + base_line.B * base_y + base_line.C) *
    (base_line.A * point.x + base_line.B * point.y + base_line.C) >= 0;
  }

  line base_line;
  ll base_x, base_y;
} half_plain;

bool line_and_circle_strightly_intersects(line line, circle circ) {
  return (line.A * circ.cent.x + line.B * circ.cent.y + line.C) *
   (line.A * circ.cent.x + line.B * circ.cent.y + line.C) <
   circ.rad * circ.rad * (line.A * line.A + line.B * line.B);
}

int main() {
  ll x0, y0, x1, y1;
  scanf("%lld %lld %lld %lld", &x0, &y0, &x1, &y1);

  line line;
  line.setup(x0, y0, x1, y1);
  point ray_beg; ray_beg.setup(x0, y0);
  // printf("%lld %lld %lld\n", line.A, line.B, line.C);

  half_plain half_plain;
  half_plain.setup(x0, y0, x1, y1);
  // printf("%lld %lld %lld %lld %lld\n", half_plain.base_line.A, half_plain.base_line.B, half_plain.base_line.C,
  //  half_plain.base_x, half_plain.base_y);

   // printf("%d %d", hp.strightly_in(3, 4), hp.strightly_in(-2, -4));
   size_t n;
   scanf("%d", &n);
   circle circle;
   point point;
   ll x, y, r;
   for (size_t i = 0; i < n; i++) {
     scanf("%lld %lld %lld", &x, &y, &r);
     point.setup(x, y);
     circle.setup(x, y, r);

     if (half_plain.unstrightly_contains(point)) {
       if (line_and_circle_strightly_intersects(line, circle))
        printf("%zu\n", i + 1);
     }
     else {
       if (circle.strightly_contains(ray_beg))
        printf("%zu\n", i + 1);
     }
   }
}
