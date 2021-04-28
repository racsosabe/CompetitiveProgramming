#include<bits/stdc++.h>
using namespace::std;

const int N = 19;

int ans;
long long pot[N];
vector<int> res(10);
vector<bool> vis(10, false);

int ask(long long x, int p){
	if(vis[p]) return res[p];
	printf("? %lld\n", x);
	fflush(stdout);
	int r;
	scanf("%d", &r);
	return res[p] = r;
}

void answer(long long x){
	printf("! %lld\n", x);
	fflush(stdout);
}

int main(){
	pot[0] = 1;
	for(int i = 1; i < N; i++) pot[i] = 10 * pot[i - 1];
	int len = 0;
	while(ask(pot[len + 1], 0)){
		vis[0] = false;
		len += 1;
	}
	long long ans = 0;
	bool special = false;
	for(int i = len; i >= 0; i--){
		int lo = i == len, hi = 9;
		vis.assign(10, false);
		while(lo < hi){
			int mi1 = lo + (hi - lo) / 3;
			int mi2 = hi - (hi - lo) / 3;
			if(ask(ans + mi1 * pot[i] + pot[i] - 1, mi1) > ask(ans + mi2 * pot[i] + pot[i] - 1, mi2)) lo = mi1;
			else hi = mi2;
		}
		cout << lo << " " << hi << endl;
		if(ask(ans + lo * pot[i] + pot[i] - 1, lo)){
			special = true;
			ans += pot[i] - 1;
			break;
		}
		ans += lo * pot[i];
	}
	if(special){
		
	}
	answer(ans);
	return 0;
}
