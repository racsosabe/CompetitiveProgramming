#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int q;
int a[N];
int L[N];
int R[N];
int ac[N];
int ft[N];
int ans[N];
vector<int> Q[N];

void preprocess(){
	for(int i = 1; i <= n; i++){
		ac[i] = ac[i - 1] ^ a[i];
	}
}

void update(int pos, int val){
	pos++;
	while(pos <= n + 1){
		ft[pos] ^= val;
		pos += (-pos) & pos;
	}
}

int getSum(int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res ^= ft[pos];
		pos &= pos - 1;
	}
	return res;
}

void solve(){
	map<int, int> last;
	for(int i = 1, l; i <= n; i++){
		if(!last.count(a[i])) l = 1;
		else l = last[a[i]] + 1;
		update(l, a[i]);
		update(i + 1, a[i]);
		last[a[i]] = i;
		for(int x : Q[i]){
			ans[x] = getSum(L[x]) ^ ac[R[x]] ^ ac[L[x] - 1];
		}
	}

}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	scanf("%d", &q);
	for(int i = 1; i <= q; i++){
		scanf("%d %d", L + i, R + i);
		Q[R[i]].emplace_back(i);
	}
	preprocess();
	solve();
	for(int i = 1; i <= q; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
