#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

int n;
char s[N];
bitset<N> in[N], out[N];

int solve(int i, int j){
	for(int k = 0; k < n; k++){
		if(i == k or j == k) continue;
		if(in[i][k] and out[j][k]) return k;
	}
	return -1;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", s);
		for(int j = 0; j < n; j++){
			if(s[j] == '1'){
				in[j].set(i, 1);
				out[i].set(j, 1);
			}
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j) continue;
			if(!out[i][j]) continue;
			if((in[i] & out[j]).count()){
				printf("%d %d %d\n", i + 1, j + 1, solve(i, j) + 1);
				return 0;
			}
		}
	}
	puts("-1");
	return 0;
}
