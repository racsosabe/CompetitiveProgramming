#include<iostream>
#include<cstdio>
using namespace::std;

const int N = 100000 + 5;

int n;
int S;
int a[N];

int solve(){
	int res = 0;
	int l = 0, r = 0;
	int suma = 0;
	for(int l = 0; l < n; l++){
		while(r < n and suma <= S){
			suma += a[r];
			r++;
		}
		if(suma < S) break;
		if(res == 0 or res > r - l) res = r - l;
		suma -= a[l];		
	}
	return res;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &S);
		for(int i = 0; i < n; i++) scanf("%d", a + i);
		printf("%d\n", solve());
	}
	return 0;
}
