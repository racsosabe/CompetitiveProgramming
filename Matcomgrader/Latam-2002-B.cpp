#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

int n;
int cnt[N];
int par[N];
bool vis[N];
int sizes[N];

int get(int x){
	return par[x] == x ? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
	cnt[b] += cnt[a];
}

bool check(){
	for(int i = 1; i <= n; i++){
		if(get(2 * i) == get(2 * i - 1)) return false;
	}
	return true;
}

int solve(){
	for(int i = 1; i <= 2 * n; i++) vis[i] = false;
	int ans = 0;
	for(int i = 1; i <= n; i++){
		int at1 = get(2 * i - 1);
		int at2 = get(2 * i);
		if(vis[at1] or vis[at2]) continue;
		vis[at1] = vis[at2] = true;
		ans += max(sizes[at1] - cnt[at1], cnt[at1]);
	}
	return ans;
}

int main(){
	while(scanf("%d", &n) == 1 and n){
		for(int i = 1; i <= 2 * n; i++){
			par[i] = i;
			sizes[i] = 1;
			cnt[i] = i & 1;
		}
		for(int i = 1; i <= n; i++){
			int v;
			char s[20];
			scanf("%s %d", s, &v);
			scanf("%s", s);
			scanf("%s", s);
			if(s[0] == 'f'){
				join(2 * i - 1, 2 * v);
				join(2 * i, 2 * v - 1);
			}
			else{
				join(2 * i, 2 * v);
				join(2 * i - 1, 2 * v - 1);
			}
		}
		if(not check()) puts("Inconsistent");
		else printf("%d\n", solve());
	}
	return 0;
}
