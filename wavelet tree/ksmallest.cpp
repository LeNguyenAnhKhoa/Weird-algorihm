// https://judge.yosupo.jp/problem/range_kth_smallest
/// Do the solution on the paper
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
//const int mod = 1e9 + 7; //
const int N = 2e5 + 5;
int n, cnt, q, id[N], a[N];
vector<int> b;
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
    int get1(int x, int L, int R, int l = 1, int r = n){
        if(x >= r)return st[R].sum - st[L].sum;
        int mid = l + r >> 1;
        int val = get1(x, st[L].l, st[R].l, l, mid);
        return x <= mid ? val : val + get1(x, st[L].r, st[R].r, mid+1, r);
    }
    int get2(int x, int L, int R, int l = 1, int r = n){
        if(l == r)return st[R].sum - st[L].sum;
        int mid = l + r >> 1;
        return x <= mid ? get2(x, st[L].l, st[R].l, l, mid) : get2(x, st[L].r, st[R].r, mid+1, r);
    }
    int get3(int k, int L, int R, int l = 1, int r = n){
        if(l == r)return l;
        int x = st[st[R].l].sum - st[st[L].l].sum;
        int mid = l + r >> 1;
        return x >= k ? get3(k, st[L].l, st[R].l, l, mid) : get3(k-x, st[L].r, st[R].r, mid+1, r);
    }
}seg;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    if(fopen("c.inp", "r")){
        freopen("c.inp", "r", stdin);
       // freopen("c.out", "w", stdout);
    }
    cin >> n >> q;
    FOR(i, 1, n)cin >> a[i], b.pb(a[i]);
    sort(all(b));
    b.resize(unique(all(b)) - b.begin());
    FOR(i, 1, n){
        a[i] = lower_bound(all(b), a[i]) - b.begin() + 1;
        seg.add(a[i], id[i-1], id[i]);
    }
    while(q--){
        int l, r, x;
        cin >> l >> r >> x;
        l++, x++;
        cout << b[seg.get3(x, id[l-1], id[r]) - 1] << endl;
    }
}

