/// https://www.codechef.com/problems/SEGPROD
#include <bits/stdc++.h>
using namespace std;
template <class T> inline bool minn(T &A,T B){return A > B ? (A = B,1) : 0;}
template <class T> inline bool maxx(T &A,T B){return A < B ? (A = B,1) : 0;}
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
//const int dx[4] = {-1, 0, 1, 0};
//const int dy[4] = {0, -1, 0, 1};
//const int base = 311;
//const int mod = 1e9 + 7;
const int N = 1e6 + 5;
int a[N], b[N], p, n, q, L[20][N], R[20][N], mask[N];
void go(int l, int r, int d){
    if(l == r)return;
    int mid = l + r >> 1;
    L[d][mid] = a[mid];
    R[d][mid+1] = a[mid+1];
    FOD(i, mid-1, l)L[d][i] = a[i] * L[d][i+1] % p;
    FOR(i, mid+2, r)R[d][i] = a[i] * R[d][i-1] % p;
    FOR(i, mid+1, r)mask[i] ^= 1 << d;
    go(l, mid, d+1);
    go(mid+1, r, d+1);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("c.inp","r",stdin);
    int t; cin >> t;
    while(t--){
        cin >> n >> p >> q;
        rep(i, n)cin >> a[i], mask[i] = 0;
        go(0, n-1, 0);
        rep(i, q/64+2)cin >> b[i];
        int l, r, x = 0;
        rep(i, q){
            if(i%64 == 0){
                l = (b[i/64] + x) % n;
                r = (b[i/64+1] + x) % n;
            }
            else{
                (l += x) %= n;
                (r += x) %= n;
            }
            if(l > r)swap(l, r);
            if(l == r)x = a[l]%p;
            else{
                int d = __builtin_ctz(mask[l] ^ mask[r]);
                x = L[d][l] * R[d][r] % p;
            }
            (x += 1) %= p;
        }
        cout << x << endl;
    }
}
