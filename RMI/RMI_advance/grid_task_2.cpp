#include <bits/stdc++.h>
using namespace std;
void check(int *robot_move,int r,int c)
{
	for(int i = 0;i<r;i++)
	{
		for(int j = 0;j<c;j++)
		{
			 if(*(robot_move + r*i + j)>9)
			 {
				cout<<"-1";
				exit(0);
			 	
			 }
		}
	}
}
int path_movement(int input_1,int input_2,int r, int c,int direction,int count,int *grid,int *robot_move,int w,int x,int y,int z)
{
		if((input_1==0&&input_2==0)||(input_1==0&&input_2==c-1)||(input_1==r-1&&input_2==0)||(input_1==r-1&&input_2==c-1))
		{
			return 0;
		}
		else
		{
			if(direction==1)
			{
			
				if(input_1<r-1&&*(grid + r*(input_1+direction) + input_2)==0)
				{
					(*(robot_move + r*(input_1+direction) + input_2))++;
					count = path_movement(input_1+direction,input_2,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else if(input_2<c-1&&*(grid + r*input_1 + input_2+direction)==0)
				{
					(*(robot_move + r*input_1 + input_2+direction))++;
					count = path_movement(input_1,input_2 + direction,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else
				{
					check(robot_move,r,c);
					direction = -1;
				}
				if(direction==-1)
				{
				
				if(input_1>-1&&*(grid + r*(input_1+direction) + input_2)==0)
				{
					(*(robot_move + r*(input_1+direction) + input_2))++;
					count = path_movement(input_1+direction,input_2,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else if(input_2>-1&&*(grid + r*input_1 + input_2+direction)==0)
				{
					(*(grid + r*input_1 + input_2+direction))++;
					count = path_movement(input_1,input_2 + direction,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else
				{
					cout<<"-1";
					exit(0);
				}
				}
				
			}
			else if(direction==-1)
			{
				
				if(input_1>-1&&*(grid + r*(input_1+direction) + input_2)==0)
				{
					(*(robot_move + r*(input_1+direction) + input_2))++;
					count = path_movement(input_1+direction,input_2,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else if(input_2>-1&&*(grid + r*input_1 + input_2+direction)==0)
				{
					(*(grid + r*input_1 + input_2+direction))++;
					count = path_movement(input_1,input_2 + direction,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else
				{
					check(robot_move,r,c);
					direction = 1;
				}
				if(direction==1)
				{
				
				if(input_1<r-1&&*(grid + r*(input_1+direction) + input_2)==0)
				{
					(*(robot_move + r*(input_1+direction) + input_2))++;
					count = path_movement(input_1+direction,input_2,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else if(input_2<c-1&&*(grid + r*input_1 + input_2+direction)==0)
				{
					(*(grid + r*input_1 + input_2+direction))++;
					count = path_movement(input_1,input_2 + direction,r,c,direction,count,grid,robot_move,w,x,y,z);
				}
				else
				{
					cout<<"-1";
					exit(0);
				}
				
				}
			}
			
		}
		count++;
		return count;
}

int main()
{
	
	int r,c;
	cin>>r>>c;
	int grid[r][c];
	int robot_move[r][c] = {0};
	
	for(int i = 0;i<r;i++)
	{
		for(int j = 0;j<c;j++)
		{
			cin>>grid[i][j];
		}
	}
	
	int direction = 1;
	int input_1,input_2;
	cin>>input_1>>input_2;
	int count = 0;
	int w,x,y,z;
	w = 1;
	x = 1;
	y = w;
	z = x;
	cout<<path_movement(input_1,input_2,r,c,direction,count,&grid[0][0],&robot_move[0][0],w,x,y,z);
	
	
}
