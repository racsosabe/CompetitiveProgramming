#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that we can consider the "pair" (l, rev(r)), where l would be the string

	  prefix and rev(r) the reverse of the string suffix.

	- Now, both components must have a common prefix, in particular, one of them is prefix

	  of the other, so we can "ignore" that common prefix and consider this as an 

	  state in a graph.

	- In this new graph, we want to get the length of the shortest path to the state ("", "")

	  since that would mean that the string is a palindrome.

	  
	- Complexity: O(n^2 * m^2 * log(nm)), where m = 20, n <= 50.
	
*/

const int N = 50 + 5;
const int L = 20 + 5;
const long long inf = 1e18;

int n;
int c[N];
int len[N];
char s[N][L];
map<string, long long> D;

void parse(string &val, string &l, string &r){
	l = "";
	r = "";
	bool first = true;
	for(int i = 0; i < val.size(); i++){
		if(val[i] == '#'){
			first = false;
			continue;
		}
		if(first) l += val[i];
		else r += val[i];
	}
}

void split(int i, int le, string &l, string &r){
	l = "";
	r = "";
	for(int j = le - 1; j >= 0; j--){
		l += s[i][j];
	}
	for(int j = le; j < len[i]; j++){
		r += s[i][j];
	}
}

bool check(string &l, string &r){
	if(l.size() > r.size()){
		if(l.substr(0, r.size()) != r) return false;
		l = l.substr(r.size());
		r = "";
	}
	else{
		if(r.substr(0, l.size()) != l) return false;
		r = r.substr(l.size());
		l = "";
	}
	return true;
}

long long solve(){
	priority_queue< pair<long long, string> > Q;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= len[i]; j++){
			string l, r;
			split(i, j, l, r);
			string l1 = l, r1 = r;
			if(check(l1, r1)){
				string cur = l1 + "#" + r1;
				if(!D.count(cur) or D[cur] > c[i]){
					D[cur] = c[i];
					Q.emplace(make_pair(-c[i], cur));
				}
			}
			if(l.size()){
				l1 = l.substr(1);
				r1 = r;
				if(check(l1, r1)){
					string cur = l1 + "#" + r1;
					if(!D.count(cur) or D[cur] > c[i]){
						D[cur] = c[i];
						Q.emplace(make_pair(-c[i], cur));
					}
				}
			}
			if(r.size()){
				l1 = l;
				r1 = r.substr(1);
				if(check(l1, r1)){
					string cur = l1 + "#" + r1;
					if(!D.count(cur) or D[cur] > c[i]){
						D[cur] = c[i];
						Q.emplace(make_pair(-c[i], cur));
					}
				}
			}
		}
	}
	while(!Q.empty()){
		long long dis = -Q.top().first;
		string cur = Q.top().second;
		Q.pop();
		if(D[cur] < dis) continue;
		string l, r;
		parse(cur, l, r);
		for(int i = 1; i <= n; i++){
			string new_l = l;
			string new_r = r;
			if(l.size()){
				for(int j = 0; j < len[i]; j++){
					new_r += s[i][j];
				}
			}
			else{
				for(int j = len[i] - 1; j >= 0; j--){
					new_l += s[i][j];
				}
			}
			if(check(new_l, new_r)){
				string nxt = new_l + "#" + new_r;
				if(!D.count(nxt) or D[nxt] > dis + c[i]){
					D[nxt] = dis + c[i];
					Q.emplace(make_pair(-D[nxt], nxt));
				}
			}
		}
	}
	return D.count("#")? D["#"] : -1;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%s %d", s[i], c + i);
		len[i] = strlen(s[i]);
	}
	printf("%lld\n", solve());
	return 0;
}

