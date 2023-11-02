#include<bits/stdc++.h>
using namespace::std;

int n;
set<string> used;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		if(!used.count(s)){
			cout << i << endl;
			used.emplace(s);
		}
	}
	return 0;
}
