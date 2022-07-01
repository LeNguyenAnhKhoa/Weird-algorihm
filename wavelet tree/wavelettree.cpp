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
