#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int MOD = 1000000000 + 7;

int n;
int len;
int a[N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++) S.emplace(a[i]);
	map<int, int> id;
	for(auto x : S){
		id[x] = len++;
	}
	for(int i = 1; i <= n; i++) a[i] = id[a[i]];
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	compress();
	printf("%d\n", solve());
	return 0;
}
