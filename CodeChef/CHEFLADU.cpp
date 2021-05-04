#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];
long long prefix[N];
long long suffix[N];

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		prefix[1] = a[1];
		int sgn = -1;
		for(int i = 2; i <= n; i++){
			prefix[i] = prefix[i - 1] + sgn * a[i];
			sgn = -sgn;
		}
		suffix[n + 1] = 0;
		suffix[n] = a[n];
		sgn = -1;
		for(int i = n - 1; i >= 1; i--){
			suffix[i] = suffix[i + 1] + sgn * a[i];
			sgn = -sgn;
		}
		int ans = -1;
		for(int i = 1; i <= n; i++){
			long long cur = prefix[i - 1] + ((n & 1) == (i & 1) ? suffix[i + 1] : -suffix[i + 1]);
			if(cur == 0){
				if(ans == -1 or ans < a[i]) ans = a[i];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
