#include<bits/stdc++.h>
using namespace::std;

const int MAX = 3000 + 5;

int n;
int m;
int k;
vector<int> D;
int memo[MAX];
bool vis[MAX];
map<int, int> pos;

void getDivisors(){
	for(int i = 1; i * i <= m; i++){
		if(m % i == 0){
			D.emplace_back(i);
			if(i * i != m) D.emplace_back(m / i);
		}
	}
	sort(D.begin(), D.end());
	for(int i = 0; i < D.size(); i++){
		pos[D[i]] = i;
	}
}

int DP(int at){
	if(D[at] < k) return 0;
	if(vis[at]) return memo[at];
	int val = D[at];
	int win = 0;
	for(int i = 1; i * i <= val; i++){
		if(val % i == 0){
			int parts = val / i;
			if(parts > 1 and i >= k){
				if(parts & 1){
					if(!DP(pos[i])) win = 1;
				}
				else win = 1;
			}
			if(i > 1 and parts >= k){
				if(i & 1){
					if(!DP(pos[parts])) win = 1;
				}
				else win = 1;
			}
		}
	}
	vis[at] = true;
	return memo[at] = win;
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	getDivisors();
	if(n & 1) puts(DP(pos[m]) ? "Timur" :  "Marsel");
	else puts("Marsel");
	return 0;
}
