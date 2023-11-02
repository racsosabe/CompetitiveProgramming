#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int q;
int lazy[4 * N];
int add[2][4 * N];
int st[2][4 * N];

void push_add(int id, int pos, int l, int r) {
	if(add[id][pos]) {
		st[id][2 * pos] += add[id][pos];
		add[id][2 * pos] += add[id][pos];

		st[id][2 * pos + 1] += add[id][pos];
		add[id][2 * pos + 1] += add[id][pos];

		add[id][pos] = 0;
	}
}

void push(int pos, int l, int r) {
	push_add(0, pos, l, r);
	push_add(1, pos, l, r);
	if(lazy[pos]) {
		swap(st[0][2 * pos], st[1][2 * pos]);
		lazy[2 * pos] ^= 1;

		swap(st[0][2 * pos + 1], st[1][2 * pos + 1]);
		lazy[2 * pos + 1] ^= 1;

		lazy[pos] = 0;
	}
}

void update1(int id, int x, int y, int z, int pos = 1, int l = 0, int r = n - 1) {
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y) {
		st[id][pos] += z;
		add[id][pos] += z;
		return;
	}
	push(pos, l, r);
	int mi = (l + r) / 2;
	update1(id, x, y, z, 2 * pos, l, mi);
	update1(id, x, y, z, 2 * pos + 1, mi + 1, r);
	st[0][pos] = st[0][2 * pos] + st[0][2 * pos + 1];
	st[1][pos] = st[1][2 * pos] + st[1][2 * pos + 1];
}

void update2(int x, int y, int pos = 1, int l = 0, int r = n - 1) {
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y) {
		lazy[pos] ^= 1;
		swap(st[0][pos], st[1][pos]);
		return;
	}
	push(pos, l, r);
	int mi = (l + r) / 2;
	update2(x, y, 2 * pos, l, mi);
	update2(x, y, 2 * pos + 1, mi + 1, r);
	st[0][pos] = st[0][2 * pos] + st[0][2 * pos + 1];
	st[1][pos] = st[1][2 * pos] + st[1][2 * pos + 1];

}

int query(int id, int x, int y, int pos = 1, int l = 0, int r = n - 1) {
	if(y < l or r < x) return 0;
	if(x <= l and r <= y) return st[id][pos];
	push(pos, l, r);
	int mi = (l + r) / 2;
	return query(id, x, y, 2 * pos, l, mi) + query(id, x, y, 2 * pos + 1, mi + 1, r);
}

int main() {
	scanf("%d %d", &n, &q);
	while(q--) {
		int op;
		scanf("%d", &op);
		if(op == 0) {
			int id, l, r;
			scanf("%d %d %d", &id, &l, &r);
			printf("%d\n", query(id, l, r));
		}
		else if(op == 1) {
			int id, x, y;
			scanf("%d %d %d", &id, &x, &y);
			y -= query(id, x, x);
			update1(id, x, x, y);
		}
		else {
			int l, r;
			scanf("%d %d", &l, &r);
			update2(l, r);
		}
	}
	return 0;
}
