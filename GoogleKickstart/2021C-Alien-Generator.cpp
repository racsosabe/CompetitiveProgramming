#include<bits/stdc++.h>
using namespace::std;

long long n;

int main(){
	int t;
	scanf("%d", &t);
	for(int caso = 1; caso <= t; caso++){
		scanf("%lld", &n);
		n <<= 1;
		int ans = 0;
		set<long long> Ls;
		for(int i = 1; 1ll * i * i <= n; i++){
			if(n % i == 0){
				long long a = i;
				long long b = n / i;
				if((a + b) % 2 == 1){
					long long r = (a + b - 1) / 2;
					long long l = r - a;
					Ls.emplace(l);
				}
			}
		}
		printf("Case #%d: %d\n", caso, (int)Ls.size());
	}
	return 0;
}
