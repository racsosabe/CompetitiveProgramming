#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 100000 + 5;

int n;
char s[N];
pair<int, int> a[N];
pair<int, int> prefix[N], suffix[N];

pair<int, int> merge(pair<int, int> a, pair<int, int> b){
	pair<int, int> res = make_pair(a.first + b.first, a.second + b.second);
	int take = min(a.first, b.second);
	res.first -= take;
	res.second -= take;
	return res;
}

int solve(){
	for(int i = 1; i <= n; i++) a[i] = s[i] == '(' ? make_pair(1, 0) : make_pair(0, 1);
	prefix[0] = make_pair(0, 0);
	for(int i = 1; i <= n; i++){
		prefix[i] = merge(prefix[i - 1], a[i]);
	}
	suffix[n + 1] = make_pair(0, 0);
	for(int i = n; i >= 1; i--){
		suffix[i] = merge(a[i], suffix[i + 1]);
	}
	int res = 0;
	for(int i = 1; i <= n; i++){
		pair<int, int> cur = merge(merge(prefix[i - 1], make_pair(a[i].second, a[i].first)), suffix[i + 1]);
		if(cur.first == cur.second and cur.first == 0){
			res += 1;
		}
	}
	return res;
}

int main(){
	setIO("typo", 1, 1);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	printf("%d\n", solve());
	return 0;
}
