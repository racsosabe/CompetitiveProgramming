#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n, k, a, b, q;
int o[N];
int ft[2][N];

void update(int id, int pos, int val){
	pos++;
	while(pos <= n + 1){
		ft[id][pos] += val;
		pos += (-pos) & pos;
	}
}

int getSum(int id, int pos){
	int res = 0;
	pos++;
	while(pos > 0){
		res += ft[id][pos];
		pos &= pos - 1;
	}
	return res;
}

int query(int id, int l, int r){
	return getSum(id, r) - getSum(id, l - 1);
}

int main(){
	scanf("%d %d %d %d %d", &n, &k, &a, &b, &q);
	for(int i = 1; i <= q; i++){
		int op;
		scanf("%d", &op);
		if(op == 1){
			int l, x;
			scanf("%d %d", &l, &x);
			update(0, l, -min(o[l], b));
			update(1, l, -min(o[l], a));
			o[l] += x;
			update(0, l, min(o[l], b));
			update(1, l, min(o[l], a));
		}
		else{
			int p;
			scanf("%d", &p);
			printf("%d\n", query(0, 1, p - 1) + query(1, p + k, n));
		}
	}
	return 0;
}
