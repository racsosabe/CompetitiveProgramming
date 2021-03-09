#include<bits/stdc++.h>
using namespace::std;

const int LOG = 40;

int q;
vector<int> add;
vector<int> limit;
bool vis[LOG][3][3][2];
long long memo[LOG][3][3][2];

long long DP(int pos, int carry1, int carry2, int tipo){
	if(pos == LOG){
		if((carry1 & 1) == (carry2 & 1)) return tipo;
		return 0;
	}
	if(vis[pos][carry1][carry2][tipo]) return memo[pos][carry1][carry2][tipo];
	int d = limit[pos];
	long long ans = 0;
	int digit1 = carry1;
	int digit2 = carry2 + add[pos];
	for(int dx = 0; dx < 3; dx++){
		int ntipo;
		if(tipo == 1){
			// prefix is <= 
			if(dx <= d) ntipo = 1;
			else ntipo = 0;
		}
		else{
			if(dx < d) ntipo = 1;
			else ntipo = 0;
		}
		int d1 = (digit1 + dx) % 3;
		int d2 = (digit2 + dx) % 3;
		int nxtcarry1 = (digit1 + dx) / 3;
		int nxtcarry2 = (digit2 + dx) / 3;
		if((d1 & 1) == (d2 & 1)){
			ans += DP(pos + 1, nxtcarry1, nxtcarry2, ntipo);
		}
	}
	vis[pos][carry1][carry2][tipo] = true;
	return memo[pos][carry1][carry2][tipo] = ans;
}

long long query(long long a, long long b){
	if(a > b) swap(a, b);
	if(a < 0) return 0;
	long long d = b - a;
	add.clear();
	while(d > 0){
		add.emplace_back(d % 3);
		d /= 3;
	}
	memset(vis, 0, sizeof vis);
	limit.clear();
	while(a > 0){
		limit.emplace_back(a % 3);
		a /= 3;
	}
	while(add.size() < LOG) add.emplace_back(0);
	while(limit.size() < LOG) limit.emplace_back(0);
	return DP(0, 0, 0, 1);
}

int main(){
	scanf("%d", &q);
	while(q--){
		long long x, y, d;
		scanf("%lld %lld %lld", &d, &x, &y);
		long long ans = query(x + d, y + d) - query(x - 1, y - 1);
		printf("%lld\n", ans);
	}
	return 0;
}
