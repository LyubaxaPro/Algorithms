#include <iostream> 

using namespace std;

int rec(int n, int k)
{
	if (n == 1)
		return 1;
	else
		return 1 + (rec(n - 1, k) + k - 1) % n;
}
int main()
{
	int n, k;
	cin >> n >> k;
	cout << rec(n, k);
}
