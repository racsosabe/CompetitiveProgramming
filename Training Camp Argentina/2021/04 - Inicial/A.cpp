#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];
int b[N];
int c[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	for(int i = 1; i <= (n - 1) / 2; i++){
		int x = a[i];
		int y = a[n - i + 1];
		int s = (x + y);
		if(s & 1){
			puts("NO");
			return 0;
		}
		c[i] = c[n + 1 - i] = s / 2;
		b[i] = x - c[i];
		b[n + 1 - i] = -b[i];
	}
	b[(n + 1) / 2] = 0;
	c[(n + 1) / 2] = a[(n + 1) / 2];
	puts("YES");
	for(int i = 1; i <= n; i++){
		printf("%d%c", b[i], " \n"[i == n]);
	}
	for(int i = 1; i <= n; i++){
		printf("%d%c", c[i], " \n"[i == n]);
	}
	return 0;
}
