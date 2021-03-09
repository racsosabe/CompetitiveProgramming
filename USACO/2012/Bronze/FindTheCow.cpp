#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 50000 + 5;

char s[N];

int main(){
	setIO("cowfind", 1, 1);
	scanf("%s", s);
	int n = strlen(s);
	int ans = 0;
	int cnt = 0;
	for(int i = 1; i < n; i++){
		if(s[i - 1] == '(' and s[i] == '(') cnt += 1;
		if(s[i - 1] == ')' and s[i] == ')') ans += cnt;
	}
	printf("%d\n", ans);
	return 0;
}
