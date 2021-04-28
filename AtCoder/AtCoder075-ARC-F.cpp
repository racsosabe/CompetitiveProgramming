#include<bits/stdc++.h>
using namespace::std;

const int N = 11;

long long gcd(long long a, long long b){ return b == 0 ? a : gcd(b, a % b);}

int n;
long long mcd[N];
long long pot[N];
long long coef[N];
map<int, int> memo[N];

void init(){
	pot[0] = 1;
	for(int i = 1; i < N; i++) pot[i] = 10 * pot[i - 1];
}

int DP(int pos, int left, int len){
	if(pos == len) return left == 0;
	if(left % mcd[pos]) return 0;
	if(memo[pos].count(left)) return memo[pos][left];
	int start = pos == 0 ? 1 : 0;
	int res = 0;
	for(int i = start; i < 10; i++){
		if(i * coef[pos] <= left){
			res += DP(pos + 1, left - i * coef[pos], len);
		}
	}
	return memo[pos][left] = res;
}

int solve(int len){
	for(int i = 0; i < len; i++){
		coef[i] = pot[i] - pot[len - 1 - i];
		memo[i].clear();
	}
	mcd[len - 1] = abs(coef[len - 1]);
	for(int i = len - 2; i >= 0; i--) mcd[i] = gcd(mcd[i + 1], abs(coef[i]));
	return DP(0, n, len);
}

int main(){
	scanf("%d", &n);
	int ans = 0;
	init();
	for(int len = 2; len <= 10; len++){
		ans += solve(len);
	}
	printf("%d\n", ans);
	return 0;
}
