#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int l;
int r;
int len;
int a[N];
int ft[N];
int val[N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++) S.emplace(a[i]);
	map<int, int> id;
	len = 0;
	for(auto x : S){
		id[x] = len;
		val[len++] = x;
	}
	for(int i = 1; i <= n; i++) a[i] = id[a[i]];
}

void update(int pos, int val){
	pos++;
	while(pos <= len + 1){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int getSum(int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

int get(int L, int R){
	int res = 0;
	int lo = 0, hi = len - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(val[mi] < L) lo = mi;
		else hi = mi - 1;
	}
	if(val[lo] < L) res -= getSum(lo);
	hi = len - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(val[mi] <= R) lo = mi;
		else hi = mi - 1;
	}
	if(val[lo] <= R) res += getSum(lo);
	return res;
}

long long solve(){
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		ans += get(l - val[a[i]], r - val[a[i]]);
		update(a[i], 1);
	}
	return ans;
}

void clear(){
	for(int i = 0; i <= n + 1; i++) ft[i] = 0;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d", &n, &l, &r);
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		compress();
		printf("%lld\n", solve());
		if(t) clear();
	}
	return 0;
}
