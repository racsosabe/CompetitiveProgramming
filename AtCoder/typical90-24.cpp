#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int k;
int a[N];
int b[N];

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < n; i++) scanf("%d", b + i);
	int need = 0;
	for(int i = 0; i < n; i++) need += abs(a[i] - b[i]);
	puts(need <= k and (need & 1) == (k & 1) ? "Yes" : "No");
	return 0;
}
