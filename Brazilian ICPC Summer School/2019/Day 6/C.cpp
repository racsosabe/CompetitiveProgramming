#include<bits/stdc++.h>
using namespace::std;

const int N = 60;

int n;
char s1[N];
char s2[N];
bool vis[N][2][2];
long long memo[N][2][2];

long long DP(int pos, int a, int b){
	if(pos == n) return a & b;
	if(vis[pos][a][b]) return memo[pos][a][b];
	long long ans = DP(pos + 1, a , b) + DP(pos + 1, a | (s1[pos] == '0'), b | (s2[pos] == '0'));
	vis[pos][a][b] = true;
	return memo[pos][a][b] = ans;
}

int main(){
	scanf("%s", s1);
	scanf("%s", s2);
	n = strlen(s1);
	printf("%lld\n", (1ll << n) - DP(0, 0, 0));
	return 0;
}
