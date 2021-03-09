#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int v[N];
vector< pair<int, int> > S[2];

void insert(int x){
	if(S[0].empty()) S[0].emplace_back(make_pair(x, x));
	else S[0].emplace_back(make_pair(max(S[0].back().first, x), x));
}

void remove(){
	if(S[1].empty()){
		while(!S[0].empty()){
			int val = S[0].back().second;
			S[0].pop_back();
			if(S[1].empty()) S[1].emplace_back(make_pair(val, val));
			else S[1].emplace_back(make_pair(max(S[1].back().first, val), val));
		}
	}
	S[1].pop_back();
}

int getMax(){
	return max(S[0].empty() ? -1 : S[0].back().first, S[1].empty() ? -1 : S[1].back().first);
}

int main(){
	int a, s, c, m, k;
	scanf("%d %d %d %d %d %d", &a, &s, &c, &n, &m, &k);
	for(int i = 0; i < 2; i++) S[i].reserve(k);
	for(int i = 1; i <= n; i++){
		v[i] = s = (1ll * a * s + c) % m;
	}
	for(int i = 1; i < k; i++) insert(v[i]);
	for(int i = k; i <= n; i++){
		if(i - k >= 1) remove();
		insert(v[i]);
		printf("%d%c", getMax(), " \n"[i == n]);
	}
	return 0;
}
