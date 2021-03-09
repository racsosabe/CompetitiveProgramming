#include<bits/stdc++.h>
using namespace::std;

const int N = 500 + 5;

string years[] = {"Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"};

int type(string s){
	for(int i = 0; i < 12; i++){
		if(years[i] == s) return i;
	}
	assert(false);
}

int n;
int Y[N];
int to[N];
int prv[N];
int who[N];
int tipo[N];
bool vis[N];
int nodes = 0;
vector<int> G[N];
map<string, int> id;

void adjust(int i){
	int a = who[i];
	int b = to[i];
	int Ta = tipo[a];
	int Tb = tipo[b];
	if(vis[a]){
		if(prv[i]){
			int dif = Tb - Ta;
			if(dif <= 0) dif += 12;
			Y[b] = Y[a] - dif;
		}
		else{
			int dif = Tb - Ta;
			if(dif >= 0) dif -= 12;
			Y[b] = Y[a] + dif;
		}
	}
	else{
		if(prv[i]){
			int dif = Tb - Ta;
			if(dif <= 0) dif += 12;
			Y[a] = Y[b] - dif;
		}
		else{
			int dif = Tb - Ta;
			if(dif >= 0) dif -= 12;
			Y[a] = Y[b] - dif;
		}
	}
}

void BFS(int src){
	vis[src] = true;
	tipo[src] = 0;
	Y[src] = 0;
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int i : G[u]){
			int a = who[i];
			int b = to[i];
			if(a == u and !vis[b]){
				adjust(i);
				Q.emplace(b);
				vis[b] = true;
			}
			if(b == u and !vis[a]){
				adjust(i);
				Q.emplace(a);
				vis[a] = true;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		string u, s, y, carry, v;
		cin >> u;
		cin >> carry >> carry >> s;
		if(!id.count(u)){
			id[u] = nodes++;
		}
		int previous = s == "previous";
		int idu = id[u];
		cin >> y;
		cin >> carry >> carry >> v;
		if(!id.count(v)){
			id[v] = nodes++;
		}
		int idv = id[v];
		int T = type(y);
		who[i] = idu;
		to[i] = idv;
		prv[i] = previous;
		tipo[idu] = T;
		G[idu].emplace_back(i);
		G[idv].emplace_back(i);
	}
	int src = id["Bessie"];
	BFS(src);
	printf("%d\n", abs(Y[id["Elsie"]]));
	return 0;
}
