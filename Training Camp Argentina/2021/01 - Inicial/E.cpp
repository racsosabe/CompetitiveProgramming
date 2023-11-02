#include<bits/stdc++.h>
using namespace::std;

const int N = 5000 + 5;

int n;
int a[N];

int ask(int i, int j){
	printf("? %d %d\n", i, j);
	fflush(stdout);
	int r;
	scanf("%d", &r);
	return r;
}

void solve(){
	int x1 = ask(1, 2);
	int x2 = ask(2, 3);
	int x3 = ask(1, 3);
	a[1] = (x1 - x2 + x3) / 2;
	a[2] = x1 - a[1];
	a[3] = x3 - a[1];
	for(int i = 4; i <= n; i++){
		a[i] = ask(1, i) - a[1];
	}
}

void answer(){
	printf("!");
	for(int i = 1; i <= n; i++) printf(" %d", a[i]);
	puts("");
	fflush(stdout);
}

int main(){
	scanf("%d", &n);
	solve();
	answer();
	return 0;
}
