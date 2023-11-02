#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

int n;
int q;
int st[4 * N];
int lazy[4 * N];

void push(int pos, int l, int r){
	if(lazy[pos]){
		st[pos] = max(st[pos], lazy[pos]);
		if(l < r){
			lazy[2 * pos] = max(lazy[2 * pos], lazy[pos]);
			lazy[2 * pos + 1] = max(lazy[2 * pos + 1], lazy[pos]);
		}
		lazy[pos] = 0;
	}
}

void update(int x, int y, int z, int pos = 1, int l = 1, int r = n){
	push(pos, l, r);
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y){
		lazy[pos] = z;
		push(pos, l, r);
		return;
	}
	int mi = (l + r) / 2;
	update(x, y, z, 2 * pos, l, mi);
	update(x, y, z, 2 * pos + 1, mi + 1, r);
	st[pos] = max(st[2 * pos], st[2 * pos + 1]);
}

int query(int x, int y, int pos = 1, int l = 1, int r = n){
	push(pos, l, r);
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return max(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1, r));
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= q; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		int h = query(l, r) + 1;
		update(l, r, h);
		printf("%d\n", h);
	}
	return 0;
}
