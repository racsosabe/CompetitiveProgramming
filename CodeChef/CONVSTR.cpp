#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int E = 26;

int n;
char a[N];
char b[N];
int mini[E];
vector<int> pos[E];

void solve(){
	for(int i = 0; i < E; i++){
		pos[i].clear();
		mini[i] = 26;
	}
	for(int i = 0; i < n; i++){
		pos[b[i] - 'a'].emplace_back(i);
		mini[b[i] - 'a'] = min(mini[b[i] - 'a'], a[i] - 'a');
	}
	int cnt = 0;
	for(int i = 0; i < E; i++){
		if(pos[i].empty()) continue;
		cnt += 1;
		if(mini[i] != i){
			puts("-1");
			return;
		}
	}
	printf("%d\n", cnt);
	for(int i = 0; i < E; i++){
		if(pos[i].empty()) continue;
		for(int j = 0; j < pos[i].size(); j++){
			printf("%d%c", pos[i][j], " \n"[j + 1 == pos[i].size()]);
		}
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		scanf("%s %s", a, b);
		solve();
	}
	return 0;
}
