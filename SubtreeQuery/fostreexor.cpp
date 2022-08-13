/// https://www.lqdoj.edu.vn/problem/fostreexor
/// Do the solution on the paper
#include <bits/stdc++.h>
using namespace std;
template <class T> inline bool minn(T &A,T B){return A > B ? A = B, 1 : 0;}
template <class T> inline bool maxx(T &A,T B){return A < B ? A = B, 1 : 0;}
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
//const int dx[4] = {-1, 0, 0, 1};
//const int dy[4] = {0, -1, 1, 0};
//const int base = 311;
//const int mod = 1e9 + 7;
const int N = 1e5 + 5;
int n, a[N], l, r, d[N], sz[N], in[N], cnt, out[N], pos[N];
long long ans;
vector<int> g[N];
struct trie{
    struct node{
        int nx[2], cnt;
        node(){
            nx[0] = nx[1] = cnt = 0;
        }
    };
    vector<node> a;
    trie() { a.pb(node()); }
    void add(int x, int val){
        int cur = 0;
        FOD(i, 29, 0){
            bool b = x >> i & 1;
            if(!a[cur].nx[b]){
                a[cur].nx[b] = SZ(a);
                a.pb(node());
            }
            cur = a[cur].nx[b];
            a[cur].cnt += val;
        }
    }
    int cal(int lim, int x){
        int cur = 0, res = 0;
        FOD(i, 29, 0){
            bool b = x >> i & 1;
            if(lim>>i&1){
                res += a[a[cur].nx[b]].cnt;
                cur = a[cur].nx[b^1];
            }
            else cur = a[cur].nx[b];
            if(!cur)break;
        }
        res += a[cur].cnt;
        return res;
    }
}t;
void dfs(int u, int p){
    d[u] ^= a[u];
    sz[u] = 1;
    in[u] = ++cnt;
    pos[cnt] = u;
    for(auto v : g[u])if(v != p)
        d[v] = d[u], dfs(v, u), sz[u] += sz[v];
    out[u] = cnt;
}
void updNode(int u, int x){
    t.add(d[u], x);
}
void updSub(int u, int x){
    FOR(i, in[u], out[u])
        updNode(pos[i], x);
}
void DFS(int u, int p){
    int best = 0;
    for(auto v : g[u])if(v != p && sz[v] > sz[best])best = v;
    if(!best){
        updNode(u, 1);
        return;
    }
    for(auto v : g[u])if(v != p && v != best)
        DFS(v, u), updSub(v, -1);
    DFS(best, u);
    ans += t.cal(r, d[u]^a[u]) - t.cal(l - 1, d[u]^a[u]);
    updNode(u, 1);
    for(auto v : g[u])if(v != p && v != best){
        FOR(i, in[v], out[v])
            ans += t.cal(r, d[pos[i]] ^ a[u]) - t.cal(l - 1, d[pos[i]] ^ a[u]);
        updSub(v, 1);
    }
//    cout << u << ' ' << ans << endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    if(fopen("c.inp", "r")){
        freopen("c.inp", "r", stdin);
//        freopen("c.out", "w", stdout);
    }
    cin >> n >> l >> r;
    FOR(i, 1, n)cin >> a[i], ans += l <= a[i] && a[i] <= r;
    rep(i, n-1){
        int u, v; cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }
    dfs(1, 0);
    DFS(1, 0);
    cout << ans;
}
