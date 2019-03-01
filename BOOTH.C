#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#define w 30
#define l 10
#define o 8
#define dt 2
#define n 4
int acc[n],m[n],q[n];

//dt-->digit thickness

void makeBlock(int x,int y)
{
	//setfillstyle(SOLID_FILL,BLACK);
	//floodfill(x+1,y+1,WHITE);
	rectangle(x,y,x+w,y+w);
}

void makeReg(int bitlen,int x,int y)
{
	int i=0;
	for(i=0;i<bitlen;i++)
	{
		makeBlock(x,y);
		x+=w;
	}
}

void drawDig0(int x,int y)
{
	int i=0;
	//thickness of 0
	setcolor(GREEN);
	for(;i<dt;i++)
	{
		x+=i;
		y+=i;
		rectangle(x+w/2-l/2,y+w/2-l/2-o/2,x+w/2+l/2,y+w/2+l/2+o/2);
	}
}

void drawDig1(int x,int y)
{
	int i=0;
	setcolor(GREEN);
	for(;i<=dt;i++)
	{
		x+=i;
		line(x+w/2-dt/2,y+w/2-l/2-o/2,x+w/2-dt/2,y+w/2+o/2);
	}
	setcolor(WHITE);
}

void makeScreen(int bitlen,int x,int y)
{
	//Accumulator reg
	makeReg(bitlen,x,y);
	x+=(bitlen+1)*w;

	//Q(Multiplier) reg
	makeReg(bitlen,x,y);
	x+=(bitlen+1)*w;

	//M(Multiplicand) reg
	makeReg(bitlen,x,y);
	x+=(bitlen+1)*w;
}


void initScreen(int A[n],int Q[n],int M[n],int x,int y)
{
	int i=0;
	//A[0]=0,A[1]=0,A[2]=0,A[3]=0;
	//M[0]=0,M[1]=1,M[2]=0,M[3]=1;
	//Q[0]=1,Q[1]=1,Q[2]=0,Q[3]=1;

	makeScreen(n,x,y);
	for(i=n;i>0;i--)
	{
		if(A[i]==0)
			drawDig0(x,y);
		else
			drawDig1(x,y);
		x+=w;
	}

	x+=w;
	for(i=n;i>0;i--)
	{
		if(Q[i]==0)
			drawDig0(x,y);
		else
			drawDig1(x,y);
		x+=w;
	}

	x+=w;
	for(i=n;i>0;i--)
	{
		if(M[i]==0)
			drawDig0(x,y);
		else
			drawDig1(x,y);
		x+=w;
	}
}

int* twosComp(int* temp)
{
	int i=0,c=1;
	while(1)
	{
		if(temp[i]==-1)
			break;
		if(temp[i]==0)
		{
			temp[i]=1;
		}
		else
		{
			temp[i]=0;
		}

		i++;
	}
	i=0;
	while(1)
	{
		if(temp[i]==-1 && c==0)
			break;
		//if c==1
		temp[i]=(c+temp[i])%2;
		c=(c+temp[i])/2;
		i++;
	}
	return temp;
}

int* convert(int num)
{
	int *temp,i=0,sign;
	temp=(int*)malloc(sizeof(int)*n);
	sign=(num>=0)?0:1;
	num=abs(num);
	while(1)
	{
		temp[i]=num%2;
		num/=2;
		i++;

		if(num==0)
			break;
	}
	temp[i]=-1;
	if(sign==1)
	{
		temp=twosComp(temp);
	}
	return temp;
}
void twoComp(int *temp)
{
	int i=n-1;

	while(temp[i]!=1 && i>=0)
	{
		i--;
	}

	i=i-1;
	while(i>=0)
	{
		temp[i]=!temp[i];
		i--;
	}
}
void convert2(int num, int *temp)
{
	int i,sign;
	printf("%d converting..",num);
	printf("%x is add",temp);
       //	temp=(int *)malloc(sizeof(int)*n);
	i=n-1;
	sign=(num>=0)?0:1;

	num=abs(num);

	while(num>=0)
	{
		temp[i]=num%2;
		printf("%d\t",temp[i]);
		num/=2;
		i--;
	}

	while(i>=0)
	{
		temp[i]=0;
		i--;
	}

	if(sign)
		twoComp(temp);
       printf("COnverted\n");


}

void input()
{
	int multiplicand,multiplier,i=0;
	printf("Enter value of Multiplicand\n");
	scanf("%d",&multiplicand);
	printf("Enter value of Multiplier\n");
	scanf("%d",&multiplier);

	clrscr();
     //	printf("%x is add\n",m);
	convert2(multiplicand,m);
	convert2(multiplier,q);

      /*	printf("m:");
	while(m[i]!=-1)
		printf(" %d",m[i]);
		i++;
	printf("\nq:");
	while(q[i]!=-1)
		printf(" %d",q[i]);
		i++; */
	printf("\nM:\n");
	for(i=0;i<n;i++)
		printf("%d",m[i]);
	printf("\nQ:\n");
	for(i=0;i<n;i++)
		printf("%d",q[i]);
}

void main()
{
	int gd=DETECT,gm=0;
	int xi=50,yi=50,xtemp,ytemp,mul,mpr;
	int i=0;
	clrscr();

	detectgraph(&gd,&gm);
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	 printf("Enter m and q:");
	 scanf("%d%d",&mul,&mpr);
	 printf("\n %x is add..\n",m);
	 convert2(mul,&m[0]);
	 convert2(mpr,&q[0]);
       //	input();
	/*
	xtemp=xi,ytemp=yi;
	makeReg(4,xi,yi);
	for(;i<4;i++)
	{
		drawDig0(xtemp+=w,ytemp);
	}
	delay(20);
	xtemp=xi,ytemp=yi;
	makeReg(4,xi,yi);
	for(i=0;i<4;i++)
	{
		drawDig1(xtemp+=w,ytemp);
	} */
	//makeScreen(8,5,50);
	/*initScreen(acc,q,m,5,50);
	initScreen(acc,q,m,5,50+w+o);
	initScreen(acc,q,m,5,50+2*w+2*o);
	initScreen(acc,q,m,5,50+3*w+3*o);
	  */
	getch();
}