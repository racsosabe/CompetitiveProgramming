#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
char s[N];

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int lone = -1, rone = -1;
	int lzero = -1, rzero = -1;
	for(int i = 1; i <= n; i++){
		if(s[i] == '0'){
			if(lzero == -1) lzero = i;
			rzero = i;
		}
		else{
			if(lone == -1) lone = i;
			rone = i;
		}
	}
	if(rzero - lzero < rone - lone){
		printf("%d %d %d %d\n", lone, rone - 1, lone + 1, rone);
	}
	else{
		printf("%d %d %d %d\n", lzero, rzero - 1, lzero + 1, rzero);
	}
	return 0;
}
