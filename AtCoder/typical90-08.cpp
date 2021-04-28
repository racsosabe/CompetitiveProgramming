#include<bits/stdc++.h>
using namespace::std;

const string pattern = "atcoder";
const int MOD = 1000000000 + 7;
const int N = 100000 + 5;
const int M = 10;

int n;
char s[N];
int frec[M];

int find(char c){
	for(int i = 0; i < pattern.size(); i++){
		if(pattern[i] == c) return i;
	}
	return -1;
}

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	for(int i = 0; i < n; i++){
		int idx = find(s[i]);
		if(idx == -1) continue;
		if(idx == 0){
			frec[1] += 1;
			if(frec[1] >= MOD) frec[1] -= MOD;
		}
		else{
			frec[idx + 1] += frec[idx];
			if(frec[idx + 1] >= MOD) frec[idx + 1] -= MOD;
		}
	}
	printf("%d\n", frec[pattern.size()]);
	return 0;
}
