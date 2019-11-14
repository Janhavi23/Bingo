#include<iostream>
#include<new>
#include<cstdlib>
#include<ctime>
#include<string.h>
using namespace std;
int win=0;
class layout
{		
	protected:
	    int **matrix;
	public:
		char Name[40];
		int pos_row[5],pos_col[5],pos_dig[2];
		int count;
		int row[5],col[5],dig[2],size;
		layout( )
		{
			size = 5;
			matrix=new int*[size];
			for(int i=0; i<size; i++)
			{
				matrix[i]=new int[size];
			}
			count=0;     
		}                       //layout constructor
		~layout()
		{
			for(int i=0; i<size; i++)
			{
				delete [] matrix[i];
			}
			delete []matrix;
		}                       //destructor layout 
		void update(int);
		void display(); 
		void check_bingo();
		void check_zero();
}; 
void layout::check_bingo()           //check for winner
{
	int i;
	for(i=0; i<2; i++)
	{
		if(dig[i]==-1&& pos_dig[i]!=-1)
		{
		   pos_dig[i]=-1;
		   count++;
		}
	}
	for(i=0;i<size;i++)
	{
		if(row[i]==-1 && pos_row[i]!=-1)
		{
			pos_row[i]=-1;
			count++;
		}
		if(col[i]==-1 && pos_col[i]!=-1)
		{
			pos_col[i]=-1;
			count++;
		}		
	}
	if(count==5||count>5)
	{
		win=1;
		cout<<"\n"<<Name<<" is the winner!";
	}
}
void layout::update(int value)          //update the value
{
	int i,j;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(matrix[i][j]==value)
			matrix[i][j]=0;
		}
	}
	check_zero();
	check_bingo();	
}
void layout::display()                //display output
{
	int i,j;
	  for(i=0; i<size; i++)
		{ 
		  cout<<"\n";
		  for(j=0;j<size;j++)
		  {
			  if(matrix[i][j]/10==0)
			  cout<<matrix[i][j]<<"  ";	
			  else
			  cout<<matrix[i][j]<<" ";
		   }
		}
}
void layout::check_zero()             //check for number of zeros
{
	int i,j,c=0,rh,ch,dh,rpos,cpos,dpos,no;
	
	for(i=0;i<5;i++)
	{
		c=0;
		for(j=0;j<5;j++)
		{
			if(matrix[i][j]==0)
			++c;
		}
		if(c==5)
		{
			row[i]=-1;
		}
		else
		row[i]=c;
	}
	c=0;
	for(i=0;i<5;i++)
	{
		c=0;
		for(j=0;j<5;j++)
		{
			if(matrix[j][i]==0)
			++c;
		}
		if(c==5)
		{
			col[i]=-1;
		}
		else
		col[i]=c;
	}
	c=0;
	for(i=0;i<5;i++)
	{
		if(matrix[i][i]==0)
		++c;
	}
	if(c==5)
	{
		dig[0]=-1;
	}
	else
	dig[0]=c;
	c=0;
	for(i=0,j=4;i<5;i++,j--)
	{
		if(matrix[i][j]==0)
		++c;
	}
	if(c==5)
	{
		dig[1]=-1;
	}
	else
	dig[1]=c;
}
//CLASS COMPUTER
class computer:public layout
{
	public:
		computer()
		{
			int i;
			strcpy(Name,"Computer");
			for(i=0; i<5; i++)
			{
				row[i]=0;
				col[i]=0;
			}
			dig[0]=0;
			dig[1]=0;
		}
		void random();
		int computer_generate();
		int highest(int arr[],int n);
		int pos(int arr[],int h,int n);
		
				
};
void computer::random()     //Filling the computer board
{
	int i,j,k=0,r,arr[25],temp;
	srand(time(NULL));
	for(i=0; i<size*size; i++)
	{
		 arr[i]=i+1;
	}   
	for(i=size*size-1; i>0; i--)
	{
		r=rand()%i;
		temp=arr[i];
		arr[i]=arr[r];
		arr[r]=temp;
	}
	
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			matrix[i][j]=arr[k];
			k++;
		}
	}
}
int computer::highest(int arr[],int n)     
{
	int i,h;
	h=arr[0];
	for(i=0; i<n; i++)
	{
		if(arr[i]>h)
		h=arr[i];
	} 
	return h;
}
int computer::pos(int arr[],int h,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		
		if(arr[i]==h)
		return i;
	}
}
int computer:: computer_generate()            //computer's turn to generate a number
{
	int i,j,rh,ch,dh,rpos,cpos,dpos,no;
	
	rh=highest(row,5);
	ch=highest(col,5);
	dh=highest(dig,2);
	if(rh>=ch && rh>=dh)
	{
		rpos=pos(row,rh,5);
		for(j=0; j<5;j++)
		{
			
			if(matrix[rpos][j]!=0)
			{
				no=matrix[rpos][j];
				break;
			}			
		}
	}
	
	else if(ch>=rh && ch>=dh)
	{
		cpos=pos(col,ch,5);
		for(j=0; j<5; j++)
		{
			if(matrix[j][cpos]!=0)
			{
				no=matrix[j][cpos];
				break;
			}
			
		}

	}
	
	else
	{
		dpos=pos(dig,dh,2);
		if(dpos==0)
		{
			for(j=0;j<5;j++)
			{
				if(matrix[j][j]!=0)
				{
				no=matrix[j][j];
				break;	
				}
			}
		}
		else
		{
			for(i=0,j=4;i<5;i++,j--)
			{
				if(matrix[i][j]!=0)
				{
					no=matrix[i][j];
					break;
				}
			}
		}	
	}
	return no;
}
//CLASS PLAYER
class player: public layout
{
	char name[10];
	public:
		player(): layout()
		{
			int i;
			cout<<"Enter your name: ";
			   cin>>name;
			strcpy(Name,"player");
			cout<<"\nHello "<<name<<"! Welcome to the game!...\nHope you are already familiar with the game!";
			cout<<"\nDo not underestimate our computer ...It is also well versed with the game ,so best of luck;)";
			for(i=0;i<5;i++)
				{
					row[i]=0;
					col[i]=0;
				}
				dig[0]=0;
				dig[1]=0;			
		}                     //player constructor
		void input();         //takes input of the matrix			    		
};
void player::input()         //takes the input of matrix
{
	cout<<"\nEnter the matrix:\n";
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
		    cin>>matrix[i][j];			
		}
	}
	
}
int main()
{
	
	int number,x;
	cout<<"***********************************************************************************\n";
	cout<<"**************************WELCOME TO BINGO GAME************************************\n";
	cout<<"***********************************************************************************\n";
	player p;
	computer c;
	c.random();																							//Computer's board
	p.input();																							//Player's board
	p.display();																						//Displaying player's board
	do
	{
		cout<<"\n\nPlayer's turn:";                //Player enters a number
	    	cin>>number;
		p.update(number);                    
		c.update(number);
		cout<<"\n\nThe players board is:";
		p.display();
		if(win==1)
		break;
		x=c.computer_generate();                //Computer generates a number
		cout<<"\n\nComputer's turn: "<<x<<endl;
		p.update(x);
		c.update(x);
		cout<<"\n\nThe players board is:";
		p.display();
	}while(win==0);
	cout<<"\n\nThe computer's board is:";
	c.display();
	return 0;
}
