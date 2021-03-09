#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

int getMinute(int day, int hour, int minute){
	return (day - 11) * 1440 + hour * 60 + minute;
}

int main(){
	setIO("ctiming", 1, 1);
	int D, H, M;
	scanf("%d %d %d", &D, &H, &M);
	int ans = getMinute(D, H, M) - getMinute(11, 11, 11);
	if(ans < 0) ans = -1;
	printf("%d\n", ans);
	return 0;
}
