#include<bits/stdc++.h>
using namespace::std;

const int N = 400 + 5;

int n;
int C[N][6];
map<long long, int> F;

long long get(int pos){
	long long res = 0;
	for(int i = 3; i >= 0; i--){
		res *= 1000;
		res += c[pos][i];
	}
	return res;
}

long long solve(){
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < 4; j++){
			scanf("%d", &c[i][j]);
		}
		F[get(i)] += 1;
	}
	printf("%lld\n", solve());
	return 0;
}
