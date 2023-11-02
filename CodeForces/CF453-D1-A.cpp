#include<bits/stdc++.h>
using namespace::std;

int n;
int m;

long double f(int x){
	return 1.0 - powl(1.0 * (x - 1) / m, n);
}

long double solve(){
	long double ans = 0;
	for(int i = 1; i <= m; i++){
		ans += i * (f(i) - f(i + 1));
	}
	return ans;
}

int main(){
	scanf("%d %d", &m, &n);
	printf("%.10Lf\n", solve());
	return 0;
}
