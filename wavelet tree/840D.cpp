// https://codeforces.com/contest/840/problem/D
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
const int N = 3e5 + 5;
int n, q, id[N], cnt;
struct IT{
    struct node{
        int l, r, sum;
    }st[40*N];
    void add(int x, int pre, int &cur, int l = 1, int r = n){
        st[cur = ++cnt] = st[pre];
        st[cur].sum++;
        if(l == r)return;
        int mid = l + r >> 1;
        if(x <= mid)add(x, st[pre].l, st[cur].l, l, mid);
        else add(x, st[pre].r, st[cur].r, mid+1, r);
    }
    int get(int x, int L, int R, int l = 1, int r = n){
        if(st[R].sum - st[L].sum <= x)return -1;
        if(l == r)return l;
        int mid = l + r >> 1;
        int k = get(x, st[L].l, st[R].l, l, mid);
        return k != -1 ? k : get(x, st[L].r, st[R].r, mid+1, r);
    }
}seg;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    if(fopen("c.inp", "r")){
        freopen("c.inp", "r", stdin);
    //        freopen("c.out", "w", stdout);
    }
    cin >> n >> q;
    FOR(i, 1, n){
        int x; cin >> x;
        seg.add(x, id[i-1], id[i]);
    }
    while(q--){
        int l, r, k;
        cin >> l >> r >> k;
        cout << seg.get((r-l+1)/k, id[l-1], id[r]) << endl;
    }
}
