#include<bits/stdc++.h>
using namespace::std;

const int MAX = 100 + 5;

map<vector<int>, int> memo[MAX][2];

int DP(vector<int> a, int last, int turn){
	if(a.empty()) return turn ^ 1;
	if(memo[last][turn].count(a)) return memo[last][turn][a];
	int maximo = *max_element(a.begin(), a.end());
	int ans = turn ^ 1;
	for(int i = last; i <= maximo; i += last){
		for(int j = 0; j < a.size(); j++){
			if(a[j] >= i){
				vector<int> nxta;
				for(int k = 0; k < a.size(); k++){
					int x = j == k ? a[k] - i : a[k];
					if(x >= i) nxta.emplace_back(x);
				}
				int wins = DP(nxta, i, turn ^ 1);
				if(wins == turn) ans = turn;
			}
		}
	}
	return memo[last][turn][a] = ans;
}

int getCount(int val, vector<int> &a){
	int res = 0;
	for(int x : a){
		res += x / val;
	}
	return res;
}

int solve(vector<int> a){
	int ans = 0;
	for(int i = 0; i < a.size(); i++){
		for(int j = 1; j <= a[i]; j++){
			a[i] -= j;
			int r = DP(a, j, 1);
			if(r == 0){
				ans += 1;
				int cnt = getCount(j, a);
				assert(cnt % 2 == 0);
				cout << i + 1 << " " << j << " " << cnt << endl;
			}
			a[i] += j;
		}
	}
	return ans;
}

int main(){
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	printf("%d\n", solve(a));
	return 0;
}
