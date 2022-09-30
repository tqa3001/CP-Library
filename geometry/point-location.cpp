#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
 
struct Point {
    ll x, y; 
    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}  
    inline ll operator* (const Point &oth) const {
        return x * oth.y - y * oth.x; 
    }
    inline Point operator- (const Point &oth) const {
        return Point(x - oth.x, y - oth.y); 
    }
}; 
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; }
 
signed main() {
    int t; cin >> t; 
    while(t--) {
        Point a1, a2, a3; 
        cin >> a1 >> a2 >> a3; 
        ll cross = (a2 - a1) * (a3 - a1);  
        if(!cross) cout << "TOUCH\n"; 
        else cout << (cross < 0 ? "RIGHT" : "LEFT") << '\n'; 
    }
}
