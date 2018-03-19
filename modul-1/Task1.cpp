#include <iostream>
#include<vector>
using namespace std;
main()
{
int n;
cin>>n;
vector<int>a(n);
for (int i=0;i<n;i++)cin>>a[i];
for(int i=n-1;i>=0;i--)cout<<a[i]<<' ';
}
