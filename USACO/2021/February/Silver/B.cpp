#include<bits/stdc++.h>
using namespace::std;

const int N = 65536 + 5;

int n;
int k;
int a[N];

int query(int l, int r){
	int lo = 0, hi = n - 1;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(a[mi] < l) lo = mi + 1;
		else hi = mi;
	}
	if(a[lo] > r) return 0;
	int lower = lo;
	hi = n - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(a[mi] <= r) lo = mi;
		else hi = mi - 1;
	}
	return lo - lower + 1;
}

int solve(){
	vector<int> v;
	for(int i = 0; i < n; i++){
		v.emplace_back(12 * ((a[i] + 11) / 12));
		v.emplace_back(a[i] - a[i] % 12);
	}
	v.emplace_back(0);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	int ans = v.back();
	k -= 1;
	vector<int> dif;
	for(int i = 1; i < v.size(); i++){
		int cnt = query(v[i - 1], v[i]);
		if(cnt == 0) dif.emplace_back(v[i] - v[i - 1]);
	}
	sort(dif.begin(), dif.end(), greater<int>());
	k = min(k, (int)dif.size());
	for(int i = 0; i < k; i++){
		ans -= dif[i];
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	sort(a, a + n);
	printf("%d\n", solve());
	return 0;
}
