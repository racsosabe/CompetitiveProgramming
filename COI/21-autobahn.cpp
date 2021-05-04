#include<bits/stdc++.h>
using namespace::std;

const int N = 400000 + 5;

int n;
int k;
int x;
int len;
int t[N];
int L[N];
int R[N];
int val[N];
int people[N];
long long ac[N];
long long suma[N];

void compress(){
	set<int> S;
	S.emplace(1);
	S.emplace(2e9 + 10);
	for(int i = 0; i < n; i++){
		S.emplace(L[i]);
		S.emplace(R[i] + 1);
		S.emplace(min(L[i] + t[i], R[i] + 1));
	}
	map<int, int> id;
	for(auto x : S){
		val[len] = x;
		id[x] = len++;
	}
	for(int i = 0; i < n; i++){
		int l = id[L[i]];
		int r = id[R[i] + 1];
		people[l] += 1;
		people[r] -= 1;
		l = id[min(L[i] + t[i], R[i] + 1)];
		suma[l] += 1;
		suma[r] -= 1;
	}
	for(int i = 1; i < len; i++){
		people[i] += people[i - 1];
		suma[i] += suma[i - 1];
	}
	for(int i = 0; i < len; i++){
		if(people[i] < k) suma[i] = 0;
	}
	for(int i = 0; i < len; i++){
		ac[i] = suma[i];
		if(i > 0) ac[i] += ac[i - 1];
	}
}

long long solve(){
	long long ans = 0;
	int pos = 0;
	long long cur = 0;
	for(int i = 0; i + 1 < len; i++){
		while(pos < len and val[pos + 1] - val[i] <= x){
			cur += 1ll * (val[pos + 1] - val[pos]) * suma[pos];
			pos += 1;
		}
		if(val[pos] - val[i] < x){
			long long cand = cur + (x - val[pos] + val[i]) * suma[pos];
			ans = max(ans, cand);
		}
		else{
			ans = max(ans, cur);
		}
		cur -= 1ll * (val[i + 1] - val[i]) * suma[i];
	}
	pos = len - 1;
	cur = 0;
	for(int i = len - 1; i > 0; i--){
		int at = val[i] - 1;
		while(pos > 0 and (at - val[pos - 1] + 1 <= x)){
			cur += 1ll * (val[pos] - val[pos - 1]) * suma[pos - 1];
			pos -= 1;
		}
		if(at - val[pos] + 1 < x){
			long long cand = cur + 1ll * (x - (at - val[pos] + 1)) * suma[pos - 1];
			ans = max(ans, cand);
		}
		else{
			ans = max(ans, cur);
		}
		cur -= 1ll * (val[i] - val[i - 1]) * suma[i - 1];
	}
	return ans;
}

int main(){
	scanf("%d %d %d", &n, &k, &x);
	for(int i = 0; i < n; i++){
		scanf("%d %d %d", L + i, t + i, R + i);
	}
	compress();
	printf("%lld\n", solve());
	return 0;
}
