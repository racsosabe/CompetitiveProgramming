#include<bits/stdc++.h>
using namespace::std;

int n;
vector<int> a;

vector<int> getMin(vector<int> b){
	int shift = 0;
	for(int i = 1; i < n; i++){
		for(int j = 0; j < n; j++){
			int pos = (i + j) % n;
			if(b[pos] == b[(j + shift) % n]) continue;
			if(b[pos] < b[(j + shift) % n]){
				shift = i;
			}
			else break;
		}
	}
	vector<int> res;
	for(int i = 0; i < n; i++) res.emplace_back(b[(shift + i) % n]);
	return res;
}

void solve(){
	vector<int> ans = a;
	for(int d = 0; d < 10; d++){
		vector<int> b(a.begin(), a.end());
		for(int i = 0; i < n; i++){
			b[i] = (b[i] + d) % 10;
		}
		ans = min(ans, getMin(b));
	}
	for(int i = 0; i < n; i++) putchar(ans[i] + '0');
	puts("");
}

int main(){
	scanf("%d", &n);
	a.resize(n);
	getchar();
	for(int i = 0; i < n; i++){
		char c = getchar();
		a[i] = c - '0';
	}
	solve();
	return 0;
}
