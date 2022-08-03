/// http://usaco.org/index.php?page=viewproblem2&cpid=213
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
const int N = 2e5 + 5;
int in[N], out[N], d[N], n, L, t, pos[N], sz[N], ans[N], id[N], bit[N];
vector<ii> a[N];
vector<int> b;
void dfs(int u){
    b.pb(d[u]);
    in[u] = ++t;
    pos[t] = u;
    sz[u] = 1;
    for(auto v : a[u])
        d[v.fi] = d[u] + v.se,
        dfs(v.fi),
        sz[u] += sz[v.fi];
    out[u] = t;
}
void add(int i, int x){
    if(i <= 0)return;
    for(; i <= n; i += i&-i)
        bit[i] += x;
}
int get(int i){
    int res = 0;
    for(; i > 0; i ^= i &-i)
        res += bit[i];
    return res;
}
void updNode(int u, int x){
    add(id[u], x);
}
void updSub(int u, int x){
    FOR(i, in[u], out[u])
        updNode(pos[i], x);
}
void DFS(int u){
    int best = 0;
    for(auto v : a[u])
        if(sz[best] < sz[v.fi])
            best = v.fi;
    if(!best){
        updNode(u, 1);
        ans[u] = 1;
        return;
    }
    for(auto v : a[u])if(v.fi != best)
        DFS(v.fi), updSub(v.fi, -1);
    DFS(best);
    for(auto v : a[u])
        if(v.fi != best)
            updSub(v.fi, 1);
    updNode(u, 1);
    int i = upper_bound(all(b), d[u] + L) - b.begin();
    ans[u] = get(i);
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("runaway.in","r",stdin);
    freopen("runaway.out","w",stdout);
    cin >> n >> L;
    FOR(i, 2, n){
        int p, c; cin >> p >> c;
        a[p].pb({i, c});
    }
    dfs(1);
    sort(all(b));
    b.resize(unique(all(b)) - b.begin());
    FOR(i, 1, n)id[i] = lower_bound(all(b), d[i]) - b.begin() + 1;
    DFS(1);
    FOR(i, 1, n)cout << ans[i] << endl;
}
