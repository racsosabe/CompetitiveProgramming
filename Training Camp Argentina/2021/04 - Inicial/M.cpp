#include<bits/stdc++.h>
using namespace::std;

int main(){
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	double ans = 1.0 * a / b / (1.0 - (1.0 - 1.0 * a / b) * (1.0 - 1.0 * c / d));
	cout << setprecision(8) << fixed << ans << endl;
	return 0;
}
