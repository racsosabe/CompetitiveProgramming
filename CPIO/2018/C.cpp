#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int p[N];
int k[N];

int main(){
	scanf("%d", &n);
	int max_extra = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &p[i], &k[i]);
		max_extra = max(max_extra, p[i] - k[i]);
	}
	int total = accumulate(p + 1, p + n + 1, 0);
	int iron = accumulate(k + 1, k + n + 1, 0);
	puts(2 * (iron + max_extra) > total ? "Puede" : "No puede");
	return 0;
}
