#include<bits/stdc++.h>
using namespace::std;

const int N = 200 + 5;

const int a[] = {1, 2, 5, 10, 20, 50, 100, 200};

bool vis[9][N];
long long memo[9][N];

long long DP(int pos, int left){
	if(pos == 8) return left == 0 ? 1 : 0;
	if(vis[pos][left]) return memo[pos][left];
	long long ans = DP(pos + 1, left);
	if(left >= a[pos]) ans += DP(pos, left - a[pos]);
	vis[pos][left] = true;
	return memo[pos][left] = ans;
}

int main(){
	printf("%lld\n", DP(0, 200));
	return 0;
}
