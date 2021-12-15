/// https://codeforces.com/contest/893/problem/F
#include <bits/stdc++.h>
using namespace std;
template <class T> inline bool minn(T &A,T B){return A > B ? (A = B,1) : 0;}
template <class T> inline bool maxx(T &A,T B){return A < B ? (A = B,1) : 0;}
#define endl '\n'
#define pb push_back
#define SZ(x) (int)((x).size())
#define fi first
#define se second
typedef pair<int,int> ii;
struct IT{
    vector<ii> st[400005];
    void build(int id,int l,int r,ii b[]){
        if(l == r){
            st[id].pb(b[l]);
            return;
        }
        int mid = l + r >> 1;
        build(id<<1, l, mid, b);
        build(id<<1^1, mid+1, r, b);
        merge(st[id<<1].begin(), st[id<<1].end(), st[id<<1^1].begin(),
              st[id<<1^1].end(), back_inserter(st[id]));
        for(int i = 0;i < SZ(st[id])-1;++i)
            minn(st[id][i+1].se, st[id][i].se);
    }
    int query(int id,int l,int r,int u,int v,int d){
        if(l > v or r < u)return 1e9;
        if(u <= l && r <= v){
            int pos = upper_bound(st[id].begin(), st[id].end(),
                        ii(d, 1e9)) - st[id].begin();
            pos--;
            return pos < 0 ? 1e9 : st[id][pos].se;
        }
        int mid = l + r >> 1;
        return min(query(id<<1, l, mid, u, v, d),
                   query(id<<1|1, mid+1, r, u, v, d));
    }
}st;
int n, root, ans, in[100005], out[100005], c[100005], j, d[100005];
vector<int> a[100005];
ii b[100005];
void DFS(int u,int p){
    in[u] = ++j;
    b[j] = {d[u], c[u]};
    for(auto v : a[u])if(v != p){
        d[v] = d[u] + 1;
        DFS(v, u);
    }
    out[u] = j;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
//    freopen("c.inp","r",stdin);
    cin >> n >> root;
    for(int i = 1;i <= n;++i)cin >> c[i];
    for(int i = 1;i < n;++i){
        int u, v; cin >> u >> v;
        a[u].pb(v); a[v].pb(u);
    }
    DFS(root, root);
    st.build(1, 1, n, b);
    int q; cin >> q;
    while(q--){
        int p, q; cin >> p >> q;
        int i = (p + ans) % n + 1;
        int k = (q + ans) % n;
        ans = st.query(1, 1, n, in[i], out[i], d[i] + k);
        cout << ans << endl;
    }
}
