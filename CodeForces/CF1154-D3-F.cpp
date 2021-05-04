#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;
const int K = 2000 + 5;

int n;
int m;
int k;
int a[N];
int x[N];
int y[N];
long long ac[N];
long long memo[K];

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	for(int i = 1; i <= m; i++){
		scanf("%d %d", x + i, y + i);
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) ac[i] = ac[i - 1] + a[i];
	for(int i = 1; i <= k; i++){
		memo[i] = a[i] + memo[i - 1];
		for(int j = 1; j <= m; j++){
			if(x[j] <= i){
				int len = x[j] - y[j];
				long long cand = ac[i] - ac[i - len] + memo[i - x[j]];
				if(memo[i] > cand) memo[i] = cand;
			}
		}
	}
	printf("%lld\n", memo[k]);
	return 0;
}
