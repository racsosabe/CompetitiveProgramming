#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int premin[2][N];
int premax[2][N];
int sufmin[2][N];
int sufmax[2][N];
pair<int, int> x[N];

void preprocess(int id){
	sort(x + 1, x + n + 1);
	premin[id][0] = INT_MAX;
	premax[id][0] = INT_MIN;
	for(int i = 1; i <= n; i++){
		int cur = id == 0 ? x[i].first : x[i].second;
		premin[id][i] = min(premin[id][i - 1], cur);
		premax[id][i] = max(premax[id][i - 1], cur);
	}
	sufmin[id][n + 1] = INT_MAX;
	sufmax[id][n + 1] = INT_MIN;
	for(int i = n; i >= 1; i--){
		int cur = id == 0 ? x[i].first : x[i].second;
		sufmin[id][i] = min(sufmin[id][i + 1], cur);
		sufmax[id][i] = max(sufmax[id][i + 1], cur);
	}
}

long long solve(){
	long long ans = LLONG_MAX;
	for(int i = 1; i <= n; i++){
		int minR = min(premin[0][i], sufmin[1][i + 1]);
		int maxR = max(premax[0][i], sufmax[1][i + 1]);
		int minB = min(premin[1][i], sufmin[0][i + 1]);
		int maxB = max(premax[1][i], sufmax[0][i + 1]);
		ans = min(ans, 1ll * (maxR - minR) * (maxB - minB));
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &x[i].first, &x[i].second);
		if(x[i].first > x[i].second) swap(x[i].first, x[i].second);
	}
	for(int i = 0; i < 2; i++) preprocess(i);
	printf("%lld\n", solve());
	return 0;
}
