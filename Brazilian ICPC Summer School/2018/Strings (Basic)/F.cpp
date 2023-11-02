#include<bits/stdc++.h>
using namespace::std;


string join(string a, string b){
	vector<int> pi(b.size(), 0);
	int k = 0;
	for(int i = 1; i < b.size(); i++){
		while(k > 0 and b[i] != b[k]) k = pi[k - 1];
		if(b[i] == b[k]) k++;
		pi[i] = k;
	}
	k = 0;
	for(int i = 0; i < a.size(); i++){
		while(k > 0 and (k == b.size() or a[i] != b[k])) k = pi[k - 1];
		if(a[i] == b[k]) k++;
	}
	string res = a.substr(0, a.size() - k) + b;
	return res;
}

string get_minimal_period(string &s){
	vector<int> z(s.size(), 0);
	int l = 0, r = 0;
	for(int i = 1; i < s.size(); i++){
		z[i] = min(r - i + 1, z[i - l]);
		if(z[i] < 0) z[i] = 0;
		while(i + z[i] < s.size() and s[i + z[i]] == s[z[i]]) z[i]++;
		if(r < i + z[i] - 1){
			l = i;
			r = i + z[i] - 1;
		}
	}
	for(int l = 1; l <= s.size(); l++){
		if(z[l] + l >= s.size()) return s.substr(0, l);
	}
	return "";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	string a, b;
	while(t--){
		cin >> a >> b;
		string u = join(a, b);
		string ru = get_minimal_period(u);
		string v = join(b, a);
		string rv = get_minimal_period(v);
		if(ru.size() < rv.size()) cout << ru.size() << endl << ru << endl;
		else cout << rv.size() << endl << rv << endl;
		if(t) cout << endl;
	}
	return 0;
}
