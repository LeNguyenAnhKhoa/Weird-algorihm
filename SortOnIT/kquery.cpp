/// https://oj.vnoi.info/problem/kquery
/// Do the solution on the paper first
#include <bits/stdc++.h>
using namespace std;
template <class T> inline bool minn(T &A,T B){return A > B ? (A = B,1) : 0;}
template <class T> inline bool maxx(T &A,T B){return A < B ? (A = B,1) : 0;}
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
const int N = 3e4 + 5;
int n, a[N];
struct IT{
    vector<int> st[4*N];
    void build(int id = 1, int l = 1, int r = n){
        if(l == r){
            st[id].pb(a[l]);
            return;
        }
        int mid = l + r >> 1;
        build(id<<1, l, mid);
        build(id<<1|1, mid+1, r);
        merge(all(st[id<<1]), all(st[id<<1|1]), back_inserter(st[id]));
    }
    int get(int u, int v, int x, int id = 1, int l = 1, int r = n){
        if(l > v or r < u)return 0;
        if(u <= l && r <= v){
            int k = upper_bound(all(st[id]), x) - st[id].begin();
            return SZ(st[id]) - k;
        }
        int mid = l + r >> 1;
        return get(u, v, x, id<<1, l, mid) + get(u, v, x, id<<1|1, mid+1, r);
    }
}seg;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
//    freopen("c.inp", "r", stdin);
//    freopen("c.out", "w", stdout);
    cin >> n;
    FOR(i, 1, n)cin >> a[i];
    seg.build();
    int q; cin >> q;
    while(q--){
        int l, r, x;
        cin >> l >> r >> x;
        cout << seg.get(l, r, x) << endl;
    }
}
