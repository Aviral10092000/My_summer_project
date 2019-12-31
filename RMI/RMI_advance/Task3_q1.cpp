#include <bits/stdc++.h>
using namespace std;
int main()
{
	char read_number;
	cin>>read_number;
	int sum = 0,count = 0,sum_store = 0;
	String number;
	while(read_number!='\n')
	{
		sum = sum + read_number - '0';
		cin>>read_number;
	}
	count++;
	do
	{
		sum_store = sum;
		sum = 0;
		while(sum_store)
		{
			sum = sum + sum_store%10;
			sum_store = (sum_store - sum_store%10)/10;
		}
		count++;
	}
	while(sum<=9)
	cout<<count;
}
