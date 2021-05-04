#include<bits/stdc++.h>
using namespace::std;

void setIO(string problemname, bool input = true, bool output = true){
	string in = problemname + ".in";
	string out = problemname + ".out";
	if(input) freopen(in.c_str(), "r", stdin);
	if(output) freopen(out.c_str(), "w", stdout);
}

int main(){
	setIO("paint");
	int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	printf("%d\n", b - a + d - c - max(0, min(b, d) - max(c, a)));
	return 0;
}
