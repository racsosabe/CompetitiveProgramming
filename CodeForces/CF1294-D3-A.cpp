#include<bits/stdc++.h>
using namespace::std;

int n;
int a;
int b;
int c;

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d %d", &a, &b, &c, &n);
		int suma = a + b + c + n;
		if(suma % 3){
			puts("NO");
			continue;
		}
		int x = suma / 3;
		puts(max({a, b, c}) <= x ? "YES" : "NO");
	}
	return 0;
}
