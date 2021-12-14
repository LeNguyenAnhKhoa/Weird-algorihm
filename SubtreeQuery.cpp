/// https://codeforces.com/contest/375/problem/D
/// Do the solution on the paper first
#include <bits/stdc++.h>
using namespace std;
//template <class T> inline bool minn(T &A,T B){return A > B ? (A = B,1) : 0;}
//template <class T> inline bool maxx(T &A,T B){return A < B ? (A = B,1) : 0;}
//#define int long long
#define rep(i, n) for(int i = 0;i < n;++i)
#define FOR(i, l, r) for(int i = l;i <= r;++i)
#define FOD(i, r, l) for(int i = r;i >= l;--i)
#define dem(x) __builtin_popcount(x)
#define endl '\n'
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define SZ(x) (int)((x).size())
#define fi first
#define se second
typedef pair<int,int> ii;
//const int dx[4] = {-1, 0, 1, 0};
//const int dy[4] = {0, -1, 0, 1};
//const int base = 311;
//const int mod = 1e9 + 7;
const int N = 1e5 + 5;
int n, m, in[N], out[N], node[N], j, sz[N], c[N], ans[N], cnt[N];
vector<int> a[N];
vector<ii> q[N];
void dfs(int u, int p){
    node[++j] = u;
    in[u] = j;
    sz[u] = 1;
    for(auto v : a[u])if(v != p)
        dfs(v, u), sz[u] += sz[v];
    out[u] = j;
}
struct BIT{
    int bit[N];
    void add(int i, int x){
        for(;i <= n;i += i&-i)
            bit[i] += x;
    }
    int get(int i){
        int res = 0;
        for(;i > 0;i ^= i&-i)
            res += bit[i];
        return res;
    }
    int get(int l, int r){
        return get(r) - get(l-1);
    }
}bit;
void updNode(int u, int x){
    int &num = cnt[c[u]];
    if(num)bit.add(num, -1);
    num += x;
    if(num)bit.add(num, 1);
//    cout << num << endl;
}
void updSub(int u, int x){
    FOR(i, in[u], out[u])
        updNode(node[i], x);
}
void DFS(int u, int p){
    int best = -1;
    for(auto v : a[u])if(v != p)
        if(best < 0 or sz[best] < sz[v])best = v;
    if(best != -1){
        for(auto v : a[u])if(v != best && v != p)
            DFS(v, u), updSub(v, -1);
        DFS(best, u);
        for(auto v : a[u])if(v != p && v != best)updSub(v, 1);
    }
    updNode(u, 1);
    for(auto i : q[u])ans[i.se] = bit.get(i.fi, n);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
//    freopen("c.inp", "r", stdin);
    cin >> n >> m;
    FOR(i, 1, n)cin >> c[i];
    rep(i, n-1){
        int u, v; cin >> u >> v;
        a[u].pb(v), a[v].pb(u);
    }
    FOR(i, 1, m){
        int v, k; cin >> v >> k;
        if(k > n)continue;
        q[v].pb({k, i});
    }
    dfs(1, 0), DFS(1, 0);
    FOR(i, 1, m)cout << ans[i] << endl;
}
