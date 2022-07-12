/// https://codeforces.com/contest/778/problem/C
/// Do the solution on the paper
#include <bits/stdc++.h>
using namespace std;
template <class T> inline bool minn(T &A,T B){return A > B ? (A = B,1) : 0;}
template <class T> inline bool maxx(T &A,T B){return A < B ? (A = B,1) : 0;}
//#define int long long
#define rep(i, n) for(int i = 0;i < n;++i)
#define FOR(i, l, r) for(int i = l; i <= r; ++i)
#define FOD(i, r, l) for(int i = r; i >= l; --i)
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
const int mod = 1e9 + 7; //
const int N = 3e5 + 5;
int n, d[N], a[26][2*N], best[N], sz[N], res[N];
int t, cnt, fl[2*N], b[26][2*N], val[N], res1 = 1e9, res2;
void dfs(int u){
    rep(i, 26)if(a[i][u]){
        int v = a[i][u];
        d[v] = d[u] + 1;
        dfs(v);
        sz[u] += sz[v];
        if(!best[u] || sz[best[u]] < sz[v])best[u] = v;
    }
    sz[u]++;
}
void gop(int u, int x, int node){
    if(fl[x] != node){
        fl[x] = node;
        rep(i, 26)b[i][x] = a[i][x];
    }
    rep(i, 26)if(a[i][u]){
        int v = a[i][u];
        if(!b[i][x])
            b[i][x] = ++t, cnt++;
        gop(v, b[i][x], node);
    }
}
void DFS(int u){
    rep(i, 26)if(a[i][u])
        DFS(a[i][u]);
    cnt = sz[best[u]], t = n;
    rep(i, 26)if(a[i][u]){
        int v = a[i][u];
        if(v == best[u])continue;
        gop(v, best[u], u);
    }
    val[u] = best[u] ? cnt - 1 : 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    if(fopen("c.inp", "r")){
        freopen("c.inp", "r", stdin);
       // freopen("c.out", "w", stdout);
    }
    cin >> n;
    rep(i, n-1){
        int u, v; char c;
        cin >> u >> v >> c;
        a[c-'a'][u] = v;
        res[i+1] = n;
    }
    dfs(1); DFS(1);
    FOR(i, 1, n){
        res[d[i]] -= sz[i];
        res[d[i]+1] += val[i];
    }
    FOR(i, 1, n-1)if(res1 > res[i])
        res1 = res[i], res2 = i;
    cout << res1 << endl << res2;
}
