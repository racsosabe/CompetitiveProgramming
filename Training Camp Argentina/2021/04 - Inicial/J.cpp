#include<bits/stdc++.h>
using namespace::std;

const int N = 500 + 5;

int n;
int m;
int k;
bool vis[N][N];
double memo[N][N];

double DP(int pos, int coffee){
	if(pos == n) return coffee >= m and n - coffee >= k;
	if(vis[pos][coffee]) return memo[pos][coffee];
	double ans = 0.5 * (DP(pos + 1, coffee + 1) + DP(pos + 1, coffee));
	vis[pos][coffee] = true;
	return memo[pos][coffee] = ans;
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	printf("%.10lf\n", DP(0, 0));
	return 0;
}
