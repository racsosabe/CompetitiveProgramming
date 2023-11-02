#include<bits/stdc++.h>
using namespace::std;

int match(string s){
	int ans = 0;
	for(int i = 0; i + 3 < s.size(); i++){
		if(s.substr(i, 4) == "haha") ans += 1;
	}
	return ans;
}

struct token{
	long long len;
	long long matches;
	string suffix;
	string prefix;
	token(){};

	token(string s){
		len = s.size();
		matches = match(s);
		prefix = s.substr(0, 3);
		suffix = s.substr(max(0, (int)s.size() - 3));
	}
};

token merge(token a, token b){
	token ans;
	ans.len = a.len + b.len;
	ans.matches = a.matches + b.matches + match(a.suffix + b.prefix);
	ans.prefix = a.prefix;
	if(a.len < 3) ans.prefix += b.prefix;
	ans.suffix = b.suffix;
	if(b.len < 3) ans.suffix = a.suffix + ans.suffix;
	ans.prefix = ans.prefix.substr(0, 3);
	ans.suffix = ans.suffix.substr(max(0, (int)ans.suffix.size() - 3));
	return ans;
}

int main(){
	int t;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		map<string, token> variables;
		string last = "";
		for(int i = 1; i <= n; i++){
			string name, op, val1, val2;
			cin >> name;
			last = name;
			cin >> op;
			if(op[0] == ':'){
				cin >> val1;
				variables[name] = token(val1);
			}
			else{
				cin >> val1 >> op >> val2;
				variables[name] = merge(variables[val1], variables[val2]); 
			}
		}
		cout << variables[last].matches << endl;
	}
	return 0;
}
