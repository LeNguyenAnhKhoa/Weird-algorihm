const int N = 1e5 + 5;
int n, cnt;
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
