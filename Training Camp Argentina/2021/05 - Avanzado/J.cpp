#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
int c[N];
int d[N];
int t[N];
int s[N];
map<int, int> id;
bool used_shoe[N];
map<int, int> pos;
bool used_client[N];
vector<int> valid[N];
vector<pair<int, int>> matches;

bool have(int x){
	return pos.count(x) and !used_shoe[pos[x]];
}

long long solve(){
	vector<int> perm(m);
	iota(perm.begin(), perm.end(), 0);
	sort(perm.begin(), perm.end(), [&] (int i, int j){
		return t[i] < t[j];
	});
	long long ans = 0;
	for(int step = 0; step < 3; step++){
		for(int at = 0; at < m; at++){
			int i = perm[at];
			if(used_client[i]) continue;
			int val = t[i];
			int cnt = 0;
			if(have(val + 1) and c[pos[val + 1]] <= d[i]) cnt += 1;
			if(have(val) and c[pos[val]] <= d[i]) cnt += 1;
			if(cnt == 2) continue;
			used_client[i] = true;
			if(cnt == 0) continue;
			if(have(val + 1) and c[pos[val + 1]] <= d[i]){
				matches.emplace_back(make_pair(i, pos[val + 1]));
				used_shoe[pos[val + 1]] = true;
				ans += c[pos[val + 1]];
			}
			if(have(val) and c[pos[val]] <= d[i]){
				matches.emplace_back(make_pair(i, pos[val]));
				used_shoe[pos[val]] = true;
				ans += c[pos[val]];
			}
		}
	}
	int len = 0;
	vector<int> new_perm;
	for(int at = 0; at < m; at++){
		int i = perm[at];
		if(used_client[i]) continue;
		if(!id.count(t[i])) id[t[i]] = len++;
		valid[id[t[i]]].emplace_back(i);
		new_perm.emplace_back(i);
	}
	swap(perm, new_perm);
	int l = 0, r = 0;
	vector<pair<int, int>> sizes;
	while(l < perm.size()){
		while(r < perm.size() and t[perm[l]] == t[perm[r]]){
			r += 1;
		}
		sizes.emplace_back(make_pair(t[perm[l]], r - l));
		l = r;
	}
	l = 0;
	while(l < sizes.size()){
		r = l;
		int suma = sizes[l].second;
		while(r + 1 < sizes.size() and sizes[r].first - 1 == sizes[r + 1].first){
			suma += sizes[r + 1].second;
			r += 1;
		}
		int low = sizes[l].first + 1;
		int high = sizes[r].first;
		if(suma >= r - l + 2){
			// Puedo todos
			bool prv = true;
			for(int i = l; i <= r; i++){
				int val = sizes[i].first;
				if(sizes[i].second >= 2 and prv){
					ans += c[pos[val + 1]];
					matches.emplace_back(make_pair(valid[id[val]].back(), pos[val + 1]));
					valid[id[val]].pop_back();
					prv = false;
				}
				if(prv){
					ans += c[pos[val + 1]];
					matches.emplace_back(make_pair(valid[id[val]].back(), pos[val + 1]));
				}
				else{
					ans += c[pos[val]];
					matches.emplace_back(make_pair(valid[id[val]].back(), pos[val]));
				}
			}
		}
		else{
			int take = low;
			for(int i = l; i <= r; i++){
				if(c[pos[take]] > c[pos[sizes[i].first]]){
					take = sizes[i].first;
				}
			}
			bool prv = take != low;
			for(int i = l; i <= r; i++){
				int val = sizes[i].first;
				if(prv){
					ans += c[pos[val + 1]];
					matches.emplace_back(make_pair(valid[id[val]].back(), pos[val + 1]));
				}
				else{
					ans += c[pos[val]];
					matches.emplace_back(make_pair(valid[id[val]].back(), pos[val]));
				}
				if(sizes[i].first == take){
					prv = false;
				}
			}
		}
		l = r + 1;
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d %d", c + i, s + i);
		pos[s[i]] = i;
	}
	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		scanf("%d %d", d + i, t + i);
	}
	long long ans = solve();
	printf("%lld\n", ans);
	printf("%d\n", (int)matches.size());
	for(auto e : matches){
		printf("%d %d\n", e.first + 1, e.second + 1);
	}
	return 0;
}
