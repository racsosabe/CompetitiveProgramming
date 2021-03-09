#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 1000 + 5;

int n;
int a[N];
char s[N];
int ac[N];
int memo[N][N];

int solve(){
	for(int i = 1; i <= n; i++){
		a[i] = s[i] == '(' ? 1 : -1;
		ac[i] = ac[i - 1] + a[i];
	}
	memo[0][0] = 1;
	for(int i = 0; i < n; i++){
		for(int prefix = 0; prefix <= i; prefix++){
			int p2 = ac[i] - prefix;
			if(p2 + a[i + 1] >= 0){
				memo[i + 1][prefix] += memo[i][prefix];
				if(memo[i + 1][prefix] >= 2012) memo[i + 1][prefix] -= 2012;
			}
			if(prefix + a[i + 1] >= 0){
				memo[i + 1][prefix + a[i + 1]] += memo[i][prefix];
				if(memo[i + 1][prefix + a[i + 1]] >= 2012) memo[i + 1][prefix + a[i + 1]] -= 2012;
			}
		}
	}
	return memo[n][0];
}

int main(){
	setIO("bbreeds", 1, 1);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	printf("%d\n", solve());
	return 0;
}
