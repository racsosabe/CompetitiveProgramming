#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];

long long solveGreedy(){
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		if(x < 0) cnt ^= 1;
		a[i] = abs(x);
	}
	if(cnt){
		return accumulate(a + 1, a + n + 1, 0ll) - 2 * (*min_element(a + 1, a + n + 1));
	}
	else{
		return accumulate(a + 1, a + n + 1, 0ll);
	}
}

long long solveDP(){
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	// (pos, signo) signo = 0 -> 1, 1 -> -1
	// (1, 1)
	const long long inf = 1e18;
	vector< vector<long long> > memo(n + 1, vector<long long>(2, -inf));
	memo[n][0] = a[n];
	memo[n][1] = -a[n];
	for(int i = n - 1; i >= 1; i--){
		for(int sgn = 0; sgn < 2; sgn++){
			for(int choice = 0; choice < 2; choice++){
				int cur_sgn = sgn ^ choice;
				memo[i][sgn] = max(memo[i][sgn], memo[i + 1][choice] + (cur_sgn == 0 ? a[i] : -a[i]));
			}
		}
	}
	return memo[1][0];
}

int main(){
	scanf("%d", &n);
	printf("%lld\n", solveDP());
	return 0;
}
