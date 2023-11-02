#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int m;
char a[N];
char b[N];
int key[N];

int get(char c){ return c - 'a';}

int main(){
	scanf("%s %s %d", a, b, &m);
	n = strlen(b);
	for(int i = 0; i < n; i++){
		key[i] = (get(b[i]) - get(a[i]) + 26) % 26;
	}
	for(int i = 0; i + m < n; i++){
		if(key[i] != key[i + m]){
			puts("-1");
			return 0;
		}
	}
	for(int i = 0; i < m; i++) putchar('a' + key[i]);
	puts("");
	return 0;
}
