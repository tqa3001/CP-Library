#pragma GCC optimize("Ofast")
#pragma GCC optimization("unroll-loops, no-stack-protector")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define gcd __gcd
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, n) for (int i=0; i<(n); i++)
#define rep1(i, n) for (int i=1; i<=(n); i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl "\n"

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned uint;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool>> vvb;
template<typename T, typename cmp = less<T>>
using ordered_set=tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update> pref_trie;

//C++17 when

constexpr int N = 50005, M = 100005;
constexpr int Q = 100005, T = 444;

int n, m;

int u[M], v[M], w[M];
vector<int> idx;

auto comp = [](int x, int y) {
    return mp(w[x], x) > mp(w[y], y);
};

int cur_w[M];
bool changed[M];
bool tmp_vis[N];

int d[N];

//fwd-star
constexpr int MX = 2000;
int lst[N];
int to[MX], edge[MX], nxt[MX];
int sz = 0;

void add_edge(int u, int v, int i) {
    nxt[++sz] = lst[u];
    to[sz] = v;
    edge[sz] = i;
    lst[u] = sz;
}

int find(int x) {return d[x] < 0 ? x : d[x] = find(d[x]);}

void join(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return;
    if(d[x] > d[y]) swap(x, y);
    d[x] += d[y]; d[y] = x;
}

int comp_sz(int x) {
    return -d[find(x)];
}

struct query {
    int t, u, w;
    query(int t, int u, int w): t(t), u(u), w(w) {}
    bool operator < (const query& oth) {return w > oth.w;}
};

struct update {
    int t, id, w;
    update(int t, int id, int w): t(t), id(id), w(w) {}
};

vi merge(const vi& a, const vi& b) {
    vi ans; ans.reserve(m);
    int ptra = 0, ptrb = 0;
    while(ptra < a.size() || ptrb < b.size()) {
        if(ptra < a.size() && (ptrb == b.size() || comp(a[ptra], b[ptrb]))) ans.pb(a[ptra++]);
        else ans.pb(b[ptrb++]);
    }
    return ans;
}

void process_queries(const vector<update>& upd, vector<query> qry) {
    sort(all(qry));
    vector<int> updated;
    memset(changed, 0, m * sizeof(bool));
    memset(d, -1, n * sizeof(int));
    memset(tmp_vis, 0, n * sizeof(bool));
    memset(lst, 0, n * sizeof(int));
    sz = 0;
    for(auto& u: upd) if(!changed[u.id]) {
        updated.pb(u.id);
        idx.erase(lower_bound(all(idx), u.id, comp));
        //idx.erase(find(all(idx), u.id));
        changed[u.id] = 1;
    }
    vector<pii> ans;
    int ptr = 0;
    for(auto& q: qry) {
        //cout << "processing " << q.t << ' ' << q.u << ' ' << q.w << endl;
        while(ptr < idx.size() && w[idx[ptr]] >= q.w) {
            //if(!changed[idx[ptr]]) cout << "joining " << idx[ptr] << ' ' << u[idx[ptr]] << ' ' << v[idx[ptr]] << endl;
            join(u[idx[ptr]], v[idx[ptr]]);
            ptr++;
        }
        sz = 0;
        for(int id: updated) {
            lst[find(u[id])] = 0;
            lst[find(v[id])] = 0;
            cur_w[id] = w[id];
        }
        for(int i = 0; i < upd.size() && upd[i].t <= q.t; i++) {
            cur_w[upd[i].id] = upd[i].w;
        }
        for(int id: updated) {
            int x = find(u[id]), y = find(v[id]);
            //cout << "insert edge " << id << ' ' << x << ' ' << y << ' ' << cur_w[id] << endl;
            add_edge(x, y, id);
            add_edge(y, x, id);
        }
        int res = 0;
        for(int id: updated) {
            tmp_vis[find(u[id])] = 0;
            tmp_vis[find(v[id])] = 0;
        }
        q.u = find(q.u);
        function<void(int)> dfs = [&](int u) -> void {
            tmp_vis[u] = 1;
            res += comp_sz(u);
            for(int id = lst[u]; id; id = nxt[id]) {
                int v = to[id], i = edge[id];
                if(cur_w[i] >= q.w && !tmp_vis[v]) dfs(v);
            }
        };
        dfs(q.u);
        ans.eb(q.t, res);
    }
    for(auto& u: upd) w[u.id] = u.w;
    vi erased_idx;
    for(int x: updated) erased_idx.pb(x);
    sort(all(erased_idx), comp);
    idx = merge(idx, erased_idx);
    sort(all(ans));
    for(auto& T: ans) cout << T.second << endl;
    //cout << "end block\n";
    //rep(i, m) cout << w[i] << ' '; cout << endl;
    //rep(i, m) cout << idx[i] << ' '; cout << endl;
}

int32_t main() {
    freopen("input.txt", "r", stdin); 
    freopen("modal.txt", "w", stdout); 
    fastio;
    int _; cin >> _;
    cin >> n >> m;
    rep(i, m) {
        cin >> u[i] >> v[i] >> w[i];
        --u[i], --v[i];
    }
    idx.resize(m);
    iota(all(idx), 0);
    sort(all(idx), comp);
    int q; cin >> q;
    for(int i = 0; i < q; i += T) {
        vector<query> queries;
        vector<update> updates;
        for(int j = i; j < min(i + T, q); j++) {
            int T; cin >> T;
            if(T == 1) {
                int x, w; cin >> x >> w; --x;
                updates.eb(j, x, w);
            }
            else {
                int u, w; cin >> u >> w; --u;
                queries.eb(j, u, w);
            }
        }
        process_queries(updates, queries);
    }
//    cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
}
