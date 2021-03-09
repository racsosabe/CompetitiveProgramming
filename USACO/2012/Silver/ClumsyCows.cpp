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

int solve(){
	int ans = 0;
	int prefix = 0;
	for(int i = 0; i < n; i++){
		if(s[i] == ')'){
			if(prefix == 0){
				ans += 1;
				prefix += 1;
			}
			else prefix -= 1;
		}
		else{
			prefix += 1;
		}
	}
	return prefix / 2 + ans;
}

int main(){
	setIO("clumsy", 1, 1);
	scanf("%s", s);
	n = strlen(s);
	printf("%d\n", solve());
	return 0;
}
