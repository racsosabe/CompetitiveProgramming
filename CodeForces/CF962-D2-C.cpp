#include<bits/stdc++.h>
using namespace::std;

int n;

int f(long long a, long long b){
	vector<int> v, w;
	while(a > 0){
		v.emplace_back(a % 10);
		a /= 10;
	}
	while(b > 0){
		w.emplace_back(b % 10);
		b /= 10;
	}
	int pos = 0;
	for(int i = 0; i < w.size(); i++){
		if(w[i] == v[pos]) pos += 1;
		if(pos == v.size()) return w.size() - v.size();
	}
	return -1;
}

int solve(){
	int ans = -1;
	for(int i = 1; 1ll * i * i <= n; i++){
		int cand = f(i * i, n);
		if(cand != -1){
			if(ans == -1 or ans > cand) ans = cand;
		}
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	printf("%d\n", solve());
	return 0;
}
