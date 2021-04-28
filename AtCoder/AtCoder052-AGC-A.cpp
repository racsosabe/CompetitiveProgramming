#include<bits/stdc++.h>
using namespace::std;

const int N = 400000 + 5;

int n;
char s[3][N];

string get(char a, char b, char c){
	string res = "";
	for(int i = 0; i < n; i++) res.push_back(a);
	for(int i = 0; i < n; i++) res.push_back(c);
	res.push_back(b);
	return res;
}

bool subsequence(int id, string x){
	int len = 4 * n;
	int pos = 0;
	for(int i = 0; i < len; i++){
		if(s[id][i] == x[pos]) pos += 1;
		if(pos == x.size()) return true;
	}
	return false;
}

bool valid(string s){
	for(int i = 0; i < 3; i++){
		if(not subsequence(i, s)) return false;
	}
	return true;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < 3; i++){
			scanf("%s", s[i]);
			for(int j = 2 * n; j < 4 * n; j++) s[i][j] = s[i][j - 2 * n];
		}
		for(int mask = 0; mask < 8; mask++){
			char a = '0' + ((mask & 1) > 0);
			char b = '0' + ((mask & 2) > 0);
			char c = '0' + ((mask & 4) > 0);
			string s = get(a, b, c);
			if(valid(s)){
				printf("%s\n", s.c_str());
				break;
			}
		}
	}
	return 0;
}
