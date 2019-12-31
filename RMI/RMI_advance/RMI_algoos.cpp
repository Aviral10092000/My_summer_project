#include <bits/stdc++.h>
#include <vector>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[3][(n)*(n-1)];
	int b[n+1];
	for(int j = 0;j<(n)*(n-1);j++)
	{
		cin>>a[0][j]>>a[1][j]>>a[2][j];
	}
	for(int k = 0;k<n;k++)
	{
		b[k] = k+1;
	}
	b[n] = 1;
	int minDistance = INT_MAX;
	do
	{
		int sum = 0;
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<n*(n-1);j++)
			{
				if(b[i]==a[0][j]&&b[i+1]==a[1][j])
				{
					sum = sum + a[2][j];
				}
			}
		}
		if(sum<minDistance)
		{
			minDistance = sum;
		}
	}
	while(next_permutation(b+1,b+n));
	cout<<'\n'<<minDistance<<'\n';
}
