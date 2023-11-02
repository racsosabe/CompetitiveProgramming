#include<bits/stdc++.h>
using namespace::std;

const int N = 400000 + 5;

int n;
int q;
int l;
int r;
int a[N];

int get(int x){
	return r - x + 1;
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = n; i >= 1; i--){
		scanf("%d", a + i);
	}
	l = 1; r = n;
	int op, x, y;
	while(q--){
		scanf("%d %d %d", &op, &x, &y);
		if(op == 1){
			int px = get(x);
			int py = get(y);
			swap(a[px], a[py]);
		}
		else if(op == 2){
			a[r + 1] = a[l];
			l++; r++;
		}
		else{
			int px = get(x);
			printf("%d\n", a[px]);
		}
	}
	return 0;
}
