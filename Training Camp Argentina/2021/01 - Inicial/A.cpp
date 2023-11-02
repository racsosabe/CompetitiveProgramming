#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int k;
int q;
int a[2];
int st[2][4 * N];

void update(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[id][pos] = min(a[id], st[id][pos] + y);
		return;
	}
	int mi = (l + r) / 2;
	if(x <= mi) update(id, x, y, 2 * pos, l, mi);
	else update(id, x, y, 2 * pos + 1, mi + 1, r);
	st[id][pos] = st[id][2 * pos] + st[id][2 * pos + 1];
}

int query(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[id][pos];
	int mi = (l + r) / 2;
	return query(id, x, y, 2 * pos, l, mi) + query(id, x, y, 2 * pos + 1, mi + 1, r);
}

int solve(int pos){
	int ans = query(0, 1, pos - 1) + query(1, pos + k, n);
	return ans;
}

int main(){
	scanf("%d %d %d %d %d", &n, &k, &a[1], &a[0], &q);
	while(q--){
		int op, l, x;
		scanf("%d", &op);
		if(op == 1){
			scanf("%d %d", &l, &x);
			update(0, l, x);
			update(1, l, x);
		}
		else{
			scanf("%d", &l);
			printf("%d\n", solve(l));
		}
	}
	return 0;
}
