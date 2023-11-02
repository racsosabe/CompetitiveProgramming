#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int q;
int maxi[4 * N];
int mini[4 * N];
long long st[4 * N];
int lazy_color[4 * N];
long long lazy_val[4 * N];

void build(int pos = 1, int l = 1, int r = n){
    if(l == r){
        st[pos] = 0;
        mini[pos] = maxi[pos] = l;
        return;
    }
    int mi = (l + r) / 2;
    build(2 * pos, l, mi);
    build(2 * pos + 1, mi + 1, r);
    mini[pos] = min(mini[2 * pos], mini[2 * pos + 1]);
    maxi[pos] = max(maxi[2 * pos], maxi[2 * pos + 1]);
}

void push(int pos, int l, int r){
    if(lazy_color[pos] or lazy_val[pos]){
        st[pos] += 1ll * (r - l + 1) * lazy_val[pos];
        if(lazy_color[pos]) mini[pos] = maxi[pos] = lazy_color[pos];
        if(l < r){
            lazy_val[2 * pos] += lazy_val[pos];
            lazy_val[2 * pos + 1] += lazy_val[pos];
            if(lazy_color[pos]){
                lazy_color[2 * pos] = lazy_color[pos];
                lazy_color[2 * pos + 1] = lazy_color[pos];
            }
        }
        lazy_color[pos] = 0;
        lazy_val[pos] = 0;
    }
}

void update(int x, int y, int z, int pos = 1, int l = 1, int r = n){
    push(pos, l, r);
    if(y < l or r < x or x > y) return;
    if(x <= l and r <= y and maxi[pos] == mini[pos]){
        lazy_color[pos] = z;
        lazy_val[pos] += abs(maxi[pos] - z);
        push(pos, l, r);
        return;
    }
    int mi = (l + r) / 2;
    update(x, y, z, 2 * pos, l, mi);
    update(x, y, z, 2 * pos + 1, mi + 1, r);
    st[pos] = st[2 * pos] + st[2 * pos + 1];
    mini[pos] = min(mini[2 * pos], mini[2 * pos + 1]);
    maxi[pos] = max(maxi[2 * pos], maxi[2 * pos + 1]);
}

long long query(int x, int y, int pos = 1, int l = 1, int r = n){
    push(pos, l, r);
    if(y < l or r < x or x > y) return 0;
    if(x <= l and r <= y) return st[pos];
    int mi = (l + r) / 2;
    return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

int main(){
    scanf("%d %d", &n, &q);
    build();
    while(q--){
        int op, l, r, x;
        scanf("%d", &op);
        if(op == 1){
            scanf("%d %d %d", &l, &r, &x);
            update(l, r, x);
        }
        else{
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(l, r));
        }
    }
    return 0;
}
