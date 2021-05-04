#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int inf = 1e9 + 10;
const int SUML = 100 + 5;
const int E = 26;

int n;
char a[N];
char s[SUML];
int sum[SUML];
int suf[SUML];
int nodes = 1;
int go[SUML][E];
bool vis[N][SUML];
int memo[N][SUML];

void insert(int val){
	int pos = 0;
	for(int i = 0; s[i]; i++){
		int nxt = s[i] - 'a';
		if(go[pos][nxt] == 0){
			go[pos][nxt] = nodes++;
		}
		pos = go[pos][nxt];
	}
	sum[pos] += val;
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		sum[u] += sum[suf[u]];
		for(int i = 0; i < E; i++){
			if(go[u][i]){
				int v = go[u][i];
				suf[v] = u == 0 ? 0 : go[suf[u]][i];
				Q.emplace(v);
			}
			else{
				go[u][i] = u == 0 ? 0 : go[suf[u]][i];
			}
		}
	}
}

void buildAutomaton(int npat){
	for(int i = npat - 1; i >= 0; i--){
		int val = 2 * i - 1;
		scanf("%s", s);
		insert(val);
	}
	BFS(0);
}

int DP(int pos, int state){
	if(pos == n) return 0;
	if(vis[pos][state]) return memo[pos][state];
	int ans = -inf;
	if(a[pos] == '*'){
		for(int i = 0; i < E; i++){
			int nstate = go[state][i];
			ans = max(ans, DP(pos + 1, nstate) + sum[nstate]);
		}
	}
	else{
		int nstate = go[state][a[pos] - 'a'];
		ans = DP(pos + 1, nstate) + sum[nstate];
	}
	vis[pos][state] = true;
	return memo[pos][state] = ans;
}

int main(){
	scanf("%s", a);
	n = strlen(a);
	buildAutomaton(2);
	printf("%d\n", DP(0, 0));
	return 0;
}
