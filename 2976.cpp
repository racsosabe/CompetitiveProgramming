#include<cstdio>
#include<algorithm>
using namespace::std;

const int N = 100000 + 5;

int n;
int k;
int a[N];
long double mini[N];

bool can(long double val){
	long double prefix = 0;
	for(int i = 1; i <= n; i++){
		prefix += a[i] - val;
		int limit = max(0, i - k);
		if(prefix - mini[limit] > 1e-10){
			return true;
		}
		mini[i] = min(mini[i - 1], prefix);
	}
	return false;
}

int main(){
	while(scanf("%d %d", &n, &k) == 2){
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		long double lo = 1, hi = 2000;
		for(int i = 0; i < 20; i++){
			long double mi = (lo + hi) / 2.0;
			if(can(mi)) lo = mi;
			else hi = mi;
		}
		printf("%.3Lf\n", lo);
	}
	return 0;
}
