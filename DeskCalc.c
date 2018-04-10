#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int top=0;
struct item
{
	char val[5];
	int type;
};

void pop(struct item stack[])
{
	strcpy(stack[top].val,"x");
	stack[top].type=-1;
	--top;
}

void push(struct item stack[],char val[5])
{
	strcpy(stack[++top].val,val);
	if(val[0]=='+'||val[0]=='-'||val[0]=='*'||val[0]=='/'||val[0]=='$'||val[0]=='('||val[0]==')')
		stack[top].type=0;
	else
		stack[top].type=1;
}

int findprec(char a,char b)
{
	int pt[7][7];
	pt[0][0]=0,pt[0][1]=0,pt[0][2]=1,pt[0][3]=1,pt[0][4]=1,pt[0][5]=0,pt[0][6]=0;
	pt[1][0]=0,pt[1][1]=0,pt[1][2]=1,pt[1][3]=1,pt[1][4]=1,pt[1][5]=0,pt[1][6]=0;
	pt[2][0]=0,pt[2][1]=0,pt[2][2]=0,pt[2][3]=1,pt[2][4]=1,pt[2][5]=0,pt[2][6]=0;
	pt[3][0]=0,pt[3][1]=0,pt[3][2]=0,pt[3][3]=0,pt[3][4]=1,pt[3][5]=0,pt[3][6]=0;
	pt[4][0]=1,pt[4][1]=1,pt[4][2]=1,pt[4][3]=1,pt[4][4]=1,pt[4][5]=2,pt[4][6]=-9;
	pt[5][0]=0,pt[5][1]=0,pt[5][2]=0,pt[5][3]=0,pt[5][4]=-9,pt[5][5]=0,pt[5][6]=0;
	pt[6][0]=1,pt[6][1]=1,pt[6][2]=1,pt[6][3]=1,pt[6][4]=1,pt[6][5]=-9,pt[6][6]=-1;
	int x,y;
	if(a=='+')
		x=0;
	else if(a=='-')
		x=1;
	else if(a=='*')
		x=2;
	else if(a=='/')
		x=3;
	else if(a=='(')
		x=4;
	else if(a==')')
		x=5;
	else if(a=='$')
		x=6;	
	if(b=='+')
		y=0;
	else if(b=='-')
		y=1;
	else if(b=='*')
		y=2;
	else if(b=='/')
		y=3;
	else if(b=='(')
		y=4;
	else if(b==')')
		y=5;
	else if(b=='$')
		y=6;
	return pt[x][y];

}

int reduce(struct item stack[],char x,int opi)
{
	int up;
	int down;
	int res,i,j;
	char val[5];
	char chkneg[5];
	up=opi;
	down=opi; 
	while(stack[up].type!=1)//data bisara loike
		up++;
	while(stack[down].type!=1)
		down--;
	int num1,num2;
	num1=atoi(stack[up].val);
	num2=atoi(stack[down].val);
	printf("\nnum1=%d,num2=%d",num1,num2);
	if(x=='+')
		res=num1+num2;	
	if(x=='-')
		res=num2-num1;
	if(x=='*')
		res=num1*num2;
	else if(x=='/')
		res=num2/num1;
	while(top>=down)
	{
		pop(stack);
	}
	for(i=top;i>=0;i--)
		if(stack[i].type==0)
			break;
	opi=i;
	printf("\nopi is= %d",opi);
	printf("\nres=%d",res);
	sprintf(val,"%d",res);
	printf("\nval=%s",val);
	push(stack,val);
	if(val[0]=='-')
		stack[top].type=1;
	printf("\ntop=%d",top);
	for(j=0;j<20;j++)
	{
		if(j>top)
		{
			strcpy(stack[j].val,"x");
			stack[j].type=-1;
		}	
	}
	return opi;			
}

void result(struct item stack[])
{
	int i=top;
	while(i>=0)
	{
		if(stack[i].type==1)
		{
			printf("\nANS=%s\n",stack[i].val);
			exit(0);
		}
	}
}
int main()
{
	struct item stack[20];
	char exp[30];
	char input[5];
	int i=0; int k=0; int j=0;
	int num;
	int precedence=999;
	int opi=0;
	printf("Enter your expression:");
	scanf("%s",exp);
	while(exp[j]!='\0')
		j++;
	exp[j]='$';
	exp[++j]='\0';
	j=0;
	strcpy(stack[0].val,"$");
	stack[0].type=0;
	printf("exp=%s",exp);
	while(i<50)
	{
		printf("\ni=%d",i);
		if(exp[i]=='\0')
			break;
		else
			printf("\nGetting input\n");
		k=0;
		memset(input,0,sizeof(input));
		if(isdigit(exp[i])!=0)
		{
			printf("\nhello");			
			input[k]=exp[i];
			j=i+1;
			while(isdigit(exp[j])!=0)
			{
				input[++k]=exp[++i];
				j=i+1;	
			}
			input[++k]='\0';
			i++;
			push(stack,input);
			printf("\nopi=%d",opi);				
		}
		else if(exp[i]=='+'||exp[i]=='-'||exp[i]=='*'||exp[i]=='/'||exp[i]=='$'||exp[i]=='('||exp[i]==')')
		{
			printf("\nCHECK");
			printf("\nexp[i]=%c",exp[i]);//problem in accessing exp[i]
			printf("\nhey");			
			precedence = findprec(stack[opi].val[0],exp[i]);
			input[0]=exp[i];
			input[1]='\0';
			printf("\nprecedence = %d",precedence);
			if(precedence==-9)
			{
				printf("ERROR!");
				exit(1);
			}
			else if(precedence==2)
			{
				char temp[5];
				strcpy(temp,stack[top].val);
				top--;
				pop(stack);
				push(stack,temp);
				opi=top-1;
				printf("\ntop=%d and opi=%d",top,opi);
				i++;
			}
			else if(precedence==1)
			{	
				push(stack,input);
				opi=top;
				printf("\nopi=%d",opi);
				i++;
			}
			else if(precedence==0)
			{
				opi=reduce(stack,stack[opi].val[0],opi);
			}
			else if(precedence==-1)
			{
				result(stack);
			}
		}
		printf("\ninput=%s",input);
		
		for(j=0;j<20;j++)
		{
			if(j>top)
			{
				strcpy(stack[j].val,"x");
				stack[j].type=-1;
			}	
			printf("\nval=%s,type=%d",stack[j].val,stack[j].type);
		}
		printf("\n\n\n");
	}

	return 0;
}
