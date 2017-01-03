#include<dos.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
union REGS i,o;
struct mospos
{
	int x,y,button;
}m;
struct board
{
	char property[20];
	int number;
	struct board *next;
}*h,*t,*r,*p;
struct simpleprop
{
	char name[20],owner[15], condition[15],color[15];
	int prize,rent,h1,h2,h3,h4,office,mot,coh,coo,noh;
	struct simpleprop *ptra;
}*temp1,*q1,*p1;
struct property
{
	char color[15];
	int total,current;
	struct simpleprop *right;
	struct property *down;
}*temp2,*q2,*p2;
struct splprop1
{
	char name[20],owner[20],condition[15];
	int prize,rent,mot;
	struct splprop1 *ptrb;
}*temp3,*q3,*p3;
struct splprop2
{
	char name[20],owner[20],condition[15];
	int prize,mot;
	struct splprop2 *ptrc;
}*temp4,*q4,*p4;
struct bankprop1
{
	char msg[100];
	int index;
	struct bankprop1 *ptrd;
}*temp5,*q5;
struct bankprop2
{
	char msg[100];
	int index;
	struct bankprop2 *ptre;
}*temp6,*q6;
struct bankprop3
{
	char name[20];
	int rent;
	struct bankprop3 *ptrf;
}*temp7,*q7;
struct bank
{
	char sp1[25],sp2[25],bp1[10],bp2[10];
	int tsp1,csp1,tsp2,csp2;
	struct property *ptr1;
	struct splprop1 *ptr2;
	struct splprop2 *ptr3;
	struct bankprop1 *ptr4;
	struct bankprop2 *ptr5;
	struct bankprop3 *ptr6;
}*head;
struct generaluse
{
	char sp1[25],sp2[25];
	int tsp1,csp1,tsp2,csp2;
	struct property *pt1;
	struct splprop1 *pt2;
	struct splprop2 *pt3;
}*head1;
struct userdetail
{
	char username[20];
	int money,csp1,csp2,gojf,jail,jailchance,cp,pno;
	struct property *nxt1;
	struct splprop1 *nxt2;
	struct splprop2 *nxt3;
	struct userdetail *u;
}*hu,*chance,*tempu,*qu;
struct dieroll
{
	int d1,d2;
}d;
struct piecepos
{
	int m,n;
}crd;
int die,poly[10],fp,ptype,nop;
char edition[20];
void welscreen();
void usernames();        	//
void extboarddisplay();
void arena();           	//
void mousecontrol();    	//
void getmouseposition();
void property(FILE*,FILE*,FILE*,FILE*);     //
void boardtext(FILE*);          //
void boardwrite();
void colorchoice1(char*);
int boardclick();               //
void intboarddisplay();
void detailsdisplay();
void cardcolor1(char*);
void polydraw(int,int,int,int);
char* printing1(int,char*);
char* printing2(int,char*);
char* printing3(int,char*);
void userdetails(int);          //
void userdetailsdisplay();
void extrabuttons();
void dienumgen();               //
void placepieces();             //
void piecemovement();           //
void pieceposition(int);        //
void piececolor();              //
void display();
void yourchance();
void conditioncheck();          //
void buyprop();                 //
void structcopy(FILE*,FILE*);
void msgdisp1(char*,int);
void msgdisp2(int,char*);
void msgdisp3();
//void msgdisp4();
void msgbox();
void usercomplete(FILE*,FILE*); //
void transaction(char*,int);
void transanimation();
int rentcheck1();               //
int rentcheck2();
int rentcheck3();
void dieanimation();
void housing();
void balance();
void gorule();
void gotojail();
void boardcards1();
void boardcards2();
void quit();
void extrarental();
void quitbox();
void main()
{
	int i=0,j,k,driver=DETECT,mode,f,cc=0;
	char msg[20];
	nop=4;
	initgraph(&driver,&mode,"c:\\turboc3\\bgi");
	srand(time(0));
	//welscreen();
	usernames();
	mousecontrol();
	arena();
	chance=hu;
	while(i<4)
	{
		die=0;
		display();
		yourchance();
		display();
		intboarddisplay();
		while(die==0)
		{
			f=boardclick();
			if(f==0 && die==0)
			{
				display();
				detailsdisplay();
			}
			else if(f==1)
				userdetailsdisplay();
			else if(f==2)
			{
				quitbox();
				goto c15;
			}
			if(die==1)
			{
				if(chance->jail==1)
				{
					dienumgen();
					scanf("%d",&d.d1);
					scanf("%d",&d.d2);
					dieanimation();
					if(d.d1==d.d2)
					{
						chance->jail=0;
						goto c10;
					}
					else
					{
						(chance->jailchance)++;
						sprintf(msg,"Bank");
						msgdisp2(50,msg);
					}
					if(chance->jailchance==3)
						chance->jail=0;
				}
				else
				{
					dienumgen();
					scanf("%d",&d.d1);
					scanf("%d",&d.d2);
					dieanimation();
					c10:
					if(chance->cp+d.d1+d.d2<40)
						fp=chance->cp+d.d1+d.d2;
					else
						fp=chance->cp+d.d1+d.d2-40;
					piecemovement();
					if(d.d1==d.d2 && cc==2)
						gotojail();
					intboarddisplay();
					if(fp==30)
					{
						delay(200);
						gotojail();
					}
					delay(1250);
					conditioncheck();
				}
			}
		}
		if(d.d1!=d.d2 || cc==2)
		{
			//chance=chance->u;
			cc=0;
		}
		if(d.d1==d.d2)
			cc++;
		i++;
		c15:
	}
	getch();
	closegraph();
}
void welscreen()
{
	cleardevice();
	settextstyle(0,0,3);
	outtextxy(230,100,"Welcome");
	outtextxy(240,150,"To The");
	outtextxy(110,200,"World Of Monopoly");
	delay(3000);
}
void usernames()
{
	int i,j,k,t,n;
	char str[2];
	c3:
	cleardevice();
	settextstyle(3,0,2);
	outtextxy(150,getmaxy()/2-50,"Enter the number of users : ");
	i=getch()-'0';
	if(i>4 || i<1)
		goto c3;
	itoa(i,str,10);
	outtextxy(450,getmaxy()/2-50,str);
	getch();
	userdetails(i);
	cleardevice();
	settextstyle(3,0,3);
	outtextxy(50,50,"Enter the details of the users");
	k=getmaxy()+50;
	if(i==1)
		k=k/2;
	if(i==2)
		k=k/3;
	if(i==3)
		k=k/4;
	if(i==4)
		k=k/5;
	settextstyle(3,0,2);
	qu=hu;
	for(j=0;j<i;j++)
	{
		outtextxy(100,k*(j+1),"User ");
		itoa(j+1,str,10);
		outtextxy(150,k*(j+1),str);
		outtextxy(170,k*(j+1),":");
		t=0;
		n=0;
		do
		{
			str[0]=getch();
			outtextxy(200+t,k*(j+1),str);
			if(str[0]=='i' || str[0]=='l' || str[0]=='I' || str[0]=='j' || str[0]=='t' || str[0]=='f')
				t=t+4;
			else if(str[0]=='W' || str[0]=='M' || str[0]=='w')
				t=t+15;
			else if(str[0]=='m')
				t=t+16;
			else if(str[0]=='Q' || str[0]=='U' || str[0]=='N' || str[0]=='C')
				t=t+12;
			else if(str[0]=='r')
				t=t+8;
			else
				t=t+10;
			if(str[0]!='\r')
			{
				qu->username[n]=str[0];
				n++;
			}
		}while(str[0]!='\r');
		qu->username[n]='\0';
		if(i==2)
			qu=qu->u->u;
		else if(i==3 || i==4)
			qu=qu->u;
	}
}
void userdetails(int i)
{
	int j,k;
	k=1;
	hu=NULL;
	for(j=0;j<4;j++)
	{
		tempu=(struct userdetail*)malloc(sizeof(struct userdetail));
		if(tempu==NULL)
		{
			printf("Memory not Allocated");
			getch();
			exit(1);
		}
		else
		{
			tempu->nxt1=NULL;
			tempu->nxt2=NULL;
			tempu->nxt3=NULL;
			tempu->u=hu;
			switch(i)
			{
				case 1:
					if(j!=0)
					{
						sprintf(tempu->username,"Comp%d",k);
						k++;
					}
					break;
				case 2:
					if(j%2==1)
					{
						sprintf(tempu->username,"Comp%d",k);
						k++;
					}
					break;
				case 3:
					if(j==3)
					{
						sprintf(tempu->username,"Comp%d",k);
						k++;
					}
					break;
			}
			tempu->money=1500;
			tempu->csp1=0;
			tempu->csp2=0;
			tempu->gojf=0;
			tempu->cp=0;
			tempu->jail=0;
			tempu->pno=j;
			if(hu==NULL)
				hu=tempu;
			else
				qu->u=tempu;
			qu=tempu;
		}
	}
}
void usercomplete(FILE *x, FILE *z)
{

	int i,j;
	qu=hu;
	do
	{
		rewind(x);
		rewind(z);
		for(i=0;i<8;i++)
		{
			temp2=(struct property*)malloc(sizeof(struct property));
			if(temp2==NULL)
			{
				printf("Memory not alloted");
				getch();
				exit(1);
			}
			else
			{
				temp2->right=NULL;
				temp2->down=NULL;
				fscanf(x,"%s",temp2->color);
				for(j=0;temp2->color[j]!='\0';j++)
				if(temp2->color[j]=='-')
					temp2->color[j]=' ';
				fscanf(z,"%d",&temp2->total);
				temp2->current=0;
				if(qu->nxt1==NULL)
					qu->nxt1=temp2;
				else
				{
					q2=qu->nxt1;
					while(q2->down!=NULL)
						q2=q2->down;
					q2->down=temp2;
				}
			}
		}
		qu=qu->u;
	}while(qu!=hu);
}
void mousecontrol()
{
	i.x.ax=0;
	int86(0X33,&i,&o);
	if(o.x.ax!=0)
	{
		i.x.ax=1;
		int86(0X33,&i,&o);
	}
}
void getmouseposition()
{
	do
	{
		i.x.ax=3;
		int86(0X33, &i, &o);
		m.button=o.x.bx;
		m.x=o.x.cx;
		m.y=o.x.dx;
	}while(!kbhit() && m.button==0);
}
void extboarddisplay()
{
	int i;
	cleardevice();
	for(i=0;i<2;i++)
		polydraw(10+i*103,30+i*80,getmaxx()-10-i*102,getmaxy()-10-i*80);
	for(i=0;i<10;i++)
	{
		line(10,110+i*31,113,110+i*31);
		line(527,110+i*31,629,110+i*31);
		line(113+i*46,30,113+i*46,110);
		line(113+i*46,390,113+i*46,469);
	}
}
void arena()
{
	int i,j;
	FILE *x,*y,*z,*a,*b;
	cleardevice();
	settextstyle(4,0,4);
	outtextxy(178,50,"Choose your Edition");
	for(i=0;i<3;i++)
		rectangle(getmaxx()/2-100,130+i*100,getmaxx()/2+100,220+i*100);
	settextstyle(3,0,4);
	outtextxy(getmaxx()/2-35,150,".com");
	outtextxy(getmaxx()/2-35,250,"WWE");
	outtextxy(getmaxx()/2-75,350,"Las Vegas");
	c1:
	getmouseposition();
	if(m.button==1)
	{
		m.button=-1;
		if((m.x>getmaxx()/2-100 && m.x<getmaxx()/2+100) && (m.y>130 && m.y<220))
		{
			strcpy(edition,".com edition");
			x=fopen("coms.txt","r+");
			y=fopen("combd.txt","r+");
			z=fopen("comsp.txt","r+");
			a=fopen("Download.txt","r+");
			b=fopen("EMail.txt","r+");
		}
		else if((m.x>getmaxx()/2-100 && m.x<getmaxx()/2+100) && (m.y>230 && m.y<320))
		{
			x=fopen("wwe.txt","r+");
			y=fopen("wwebd.txt","r+");
		}
		else if((m.x>getmaxx()/2-100 && m.x<getmaxx()/2+100) && (m.y>320 && m.y<420))
		{
			x=fopen("lasveg.txt","r+");
			y=fopen("lasvegbd.txt","r+");
		}
		else
			goto c1;
	}
	else
		goto c1;
	property(x,z,a,b);
	fseek(x,0,SEEK_SET);
	fseek(z,0,SEEK_SET);
	structcopy(x,z);
	usercomplete(x,z);
	boardtext(y);
	fclose(x);
	fclose(y);
	fclose(z);
	fclose(a);
	fclose(b);
}
void structcopy(FILE *x,FILE *z)
{
	int i=0,j;
	head1=(struct generaluse*)malloc(sizeof(struct generaluse));
	head1->pt1=NULL;
	head1->pt2=NULL;
	head1->pt3=NULL;
	for(i=0;i<8;i++)
	{
		temp2=(struct property*)malloc(sizeof(struct property));
		if(temp2==NULL)
		{
			printf("Memory not alloted");
			getch();
			exit(1);
		}
		else
		{
			temp2->right=NULL;
			temp2->down=NULL;
			fscanf(x,"%s",temp2->color);
			for(j=0;temp2->color[j]!='\0';j++)
				if(temp2->color[j]=='-')
					temp2->color[j]=' ';
			fscanf(z,"%d",&temp2->total);
			temp2->current=temp2->total;
			if(head1->pt1==NULL)
				head1->pt1=temp2;
			else
			{
				q2=head1->pt1;
				while(q2->down!=NULL)
					q2=q2->down;
				q2->down=temp2;
			}
		}
	}
	i=0;
	do
	{
		temp1=(struct simpleprop*)malloc(sizeof(struct simpleprop));
		if(temp1==NULL)
		{
			printf("Memory not alloted");
			getch();
			exit(1);
		}
		else
		{
			temp1->ptra=NULL;
			fscanf(x,"%s",temp1->name);
			for(j=0;temp1->name[j]!='\0';j++)
				if(temp1->name[j]=='-')
					temp1->name[j]=' ';
			fscanf(x,"%s",temp1->color);
			for(j=0;temp1->color[j]!='\0';j++)
				if(temp1->color[j]=='-')
					temp1->color[j]=' ';
			strcpy(temp1->owner,"Bank");
			strcpy(temp1->condition,"Active");
			fscanf(z,"%d",&temp1->prize);
			fscanf(z,"%d",&temp1->rent);
			fscanf(z,"%d",&temp1->h1);
			fscanf(z,"%d",&temp1->h2);
			fscanf(z,"%d",&temp1->h3);
			fscanf(z,"%d",&temp1->h4);
			fscanf(z,"%d",&temp1->office);
			fscanf(z,"%d",&temp1->mot);
			fscanf(z,"%d",&temp1->coh);
			fscanf(z,"%d",&temp1->coo);
			temp1->noh=0;
			fflush(z);
			q2=head1->pt1;
			while(q2!=NULL)
			{
				if(strcmp(q2->color,temp1->color)==0)
				{
					if(q2->right==NULL)
						q2->right=temp1;
					else
					{
						q1=q2->right;
						while(q1->ptra!=NULL)
							q1=q1->ptra;
						q1->ptra=temp1;
					}
					break;
				}
				q2=q2->down;
			}
			i++;
		}
	}while(i<22);
	fscanf(x,"%s",head1->sp1);
	for(j=0;head1->sp1[j]!='\0';j++)
		if(head1->sp1[j]=='-')
			head1->sp1[j]=' ';
	fscanf(z,"%d",&head1->tsp1);
	head1->csp1=head1->tsp1;
	i=0;
	while(i<4)
	{
		temp3=(struct splprop1*)malloc(sizeof(struct splprop1));
		if(temp3==NULL)
		{
			printf("Memory Not Alloted");
			getch();
			exit(0);
		}
		else
		{
			temp3->ptrb=NULL;
			fscanf(x,"%s",temp3->name);
			for(j=0;temp3->name[j]!='\0';j++)
				if(temp3->name[j]=='-')
					temp3->name[j]=' ';
			fflush(x);
			fscanf(z,"%d",&temp3->prize);
			fscanf(z,"%d",&temp3->rent);
			fscanf(z,"%d",&temp3->mot);
			strcpy(temp3->owner,"Bank");
			strcpy(temp3->condition,"Active");
			fflush(z);
			if(head1->pt2==NULL)
				head1->pt2=temp3;
			else
			{
				q3=head1->pt2;
				while(q3->ptrb!=NULL)
					q3=q3->ptrb;
				q3->ptrb=temp3;
			}
			i++;
		}
	}
	fscanf(x,"%s",head1->sp2);
	for(j=0;head1->sp2[j]!='\0';j++)
		if(head1->sp2[j]=='-')
			head1->sp2[j]=' ';
	fscanf(z,"%d",&head1->tsp2);
	head1->csp2=head1->tsp2;
	for(i=0;i<2;i++)
	{
		temp4=(struct splprop2*)malloc(sizeof(struct splprop2));
		if(temp4==NULL)
		{
			printf("Memory Not Alloted");
			getch();
			exit(1);
		}
		else
		{
			temp4->ptrc=NULL;
			fscanf(x,"%s",temp4->name);
			for(j=0;temp4->name[j]!='\0';j++)
				if(temp4->name[j]=='-')
					temp4->name[j]=' ';
			fflush(x);
			fscanf(z,"%d",&temp4->prize);
			fscanf(z,"%d",&temp4->mot);
			strcpy(temp4->owner,"Bank");
			strcpy(temp4->condition,"Active");
			if(head1->pt3==NULL)
				head1->pt3=temp4;
			else
				q4->ptrc=temp4;
			q4=temp4;
		}
	}
}
void property(FILE* x,FILE *z,FILE *a,FILE *b)
{
	int i=0,j;
	head=(struct bank*)malloc(sizeof(struct bank));
	head->ptr1=NULL;
	head->ptr2=NULL;
	head->ptr3=NULL;
	head->ptr4=NULL;
	head->ptr5=NULL;
	head->ptr6=NULL;
	for(i=0;i<8;i++)
	{
		temp2=(struct property*)malloc(sizeof(struct property));
		if(temp2==NULL)
		{
			printf("Memory not alloted");
			getch();
			exit(1);
		}
		else
		{
			temp2->right=NULL;
			temp2->down=NULL;
			fscanf(x,"%s",temp2->color);
			for(j=0;temp2->color[j]!='\0';j++)
				if(temp2->color[j]=='-')
					temp2->color[j]=' ';
			fscanf(z,"%d",&temp2->total);
			temp2->current=temp2->total;
			if(head->ptr1==NULL)
				head->ptr1=temp2;
			else
			{
				q2=head->ptr1;
				while(q2->down!=NULL)
					q2=q2->down;
				q2->down=temp2;
			}
		}
	}
	i=0;
	do
	{
		temp1=(struct simpleprop*)malloc(sizeof(struct simpleprop));
		if(temp1==NULL)
		{
			printf("Memory not alloted");
			getch();
			exit(1);
		}
		else
		{
			temp1->ptra=NULL;
			fscanf(x,"%s",temp1->name);
			for(j=0;temp1->name[j]!='\0';j++)
				if(temp1->name[j]=='-')
					temp1->name[j]=' ';
			fscanf(x,"%s",temp1->color);
			for(j=0;temp1->color[j]!='\0';j++)
				if(temp1->color[j]=='-')
					temp1->color[j]=' ';
			strcpy(temp1->owner,"Bank");
			strcpy(temp1->condition,"Active");
			fscanf(z,"%d",&temp1->prize);
			fscanf(z,"%d",&temp1->rent);
			fscanf(z,"%d",&temp1->h1);
			fscanf(z,"%d",&temp1->h2);
			fscanf(z,"%d",&temp1->h3);
			fscanf(z,"%d",&temp1->h4);
			fscanf(z,"%d",&temp1->office);
			fscanf(z,"%d",&temp1->mot);
			fscanf(z,"%d",&temp1->coh);
			fscanf(z,"%d",&temp1->coo);
			temp1->noh=0;
			fflush(z);
			q2=head->ptr1;
			while(q2!=NULL)
			{
				if(strcmp(q2->color,temp1->color)==0)
				{
					if(q2->right==NULL)
						q2->right=temp1;
					else
					{
						q1=q2->right;
						while(q1->ptra!=NULL)
							q1=q1->ptra;
						q1->ptra=temp1;
					}
					break;
				}
				q2=q2->down;
			}
			i++;
		}
	}while(i<22);
	fscanf(x,"%s",head->sp1);
	for(j=0;head->sp1[j]!='\0';j++)
		if(head->sp1[j]=='-')
			head->sp1[j]=' ';
	fscanf(z,"%d",&head->tsp1);
	head->csp1=head->tsp1;
	i=0;
	cleardevice();
	while(i<4)
	{
		temp3=(struct splprop1*)malloc(sizeof(struct splprop1));
		if(temp3==NULL)
		{
			printf("Memory Not Alloted");
			getch();
			exit(0);
		}
		else
		{
			temp3->ptrb=NULL;
			fscanf(x,"%s",temp3->name);
			for(j=0;temp3->name[j]!='\0';j++)
				if(temp3->name[j]=='-')
					temp3->name[j]=' ';
			fflush(x);
			fscanf(z,"%d",&temp3->prize);
			fscanf(z,"%d",&temp3->rent);
			fscanf(z,"%d",&temp3->mot);
			strcpy(temp3->owner,"Bank");
			strcpy(temp3->condition,"Active");
			fflush(z);
			if(head->ptr2==NULL)
				head->ptr2=temp3;
			else
			{
				q3=head->ptr2;
				while(q3->ptrb!=NULL)
					q3=q3->ptrb;
				q3->ptrb=temp3;
			}
			i++;
		}
	}
	fscanf(x,"%s",head->sp2);
	for(j=0;head->sp2[j]!='\0';j++)
		if(head->sp2[j]=='-')
			head->sp2[j]=' ';
	fscanf(z,"%d",&head->tsp2);
	head->csp2=head->tsp2;
	for(i=0;i<2;i++)
	{
		temp4=(struct splprop2*)malloc(sizeof(struct splprop2));
		if(temp4==NULL)
		{
			printf("Memory Not Alloted");
			getch();
			exit(1);
		}
		else
		{
			temp4->ptrc=NULL;
			fscanf(x,"%s",temp4->name);
			for(j=0;temp4->name[j]!='\0';j++)
				if(temp4->name[j]=='-')
					temp4->name[j]=' ';
			fflush(x);
			fscanf(z,"%d",&temp4->prize);
			fscanf(z,"%d",&temp4->mot);
			strcpy(temp4->owner,"Bank");
			strcpy(temp4->condition,"Active");
			if(head->ptr3==NULL)
				head->ptr3=temp4;
			else
				q4->ptrc=temp4;
			q4=temp4;
		}
	}
	fscanf(a,"%s",head->bp1);
	for(j=0;head->bp1[j]!='\0';j++)
		if(head->bp1[j]=='-')
			head->bp1[j]=' ';
	for(i=0;i<14;i++)
	{
		temp5=(struct bankprop1*)malloc(sizeof(struct bankprop1));
		temp5->ptrd=head->ptr4;
		fscanf(a,"%s",temp5->msg);
		for(j=0;temp5->msg[j]!='\0';j++)
			if(temp5->msg[j]=='-')
				temp5->msg[j]=' ';
		temp5->index=i;
		if(head->ptr4==NULL)
			head->ptr4=temp5;
		else
			q5->ptrd=temp5;
		q5=temp5;
	}
	j=rand()%14;
	for(i=0;i<j;i++)
		head->ptr4=head->ptr4->ptrd;
	fscanf(b,"%s",head->bp2);
	for(j=0;head->bp2[j]!='\0';j++)
		if(head->bp2[j]=='-')
			head->bp2[j]=' ';
	for(i=0;i<14;i++)
	{
		temp6=(struct bankprop2*)malloc(sizeof(struct bankprop2));
		temp6->ptre=head->ptr5;
		fscanf(b,"%s",temp6->msg);
		for(j=0;temp6->msg[j]!='\0';j++)
			if(temp6->msg[j]=='-')
				temp6->msg[j]=' ';
		temp6->index=i;
		if(head->ptr5==NULL)
			head->ptr5=temp6;
		else
			q6->ptre=temp6;
		q6=temp6;
	}
	j=rand()%14;
	for(i=0;i<j;i++)
		head->ptr5=head->ptr5->ptre;
	cleardevice();
	for(i=0;i<2;i++)
	{
		temp7=(struct bankprop3*)malloc(sizeof(struct bankprop3));
		temp7->ptrf=NULL;
		fscanf(x,"%s",temp7->name);
		printf("%s",temp7->name);
		for(j=0;temp7->name[j]!='\0';j++)
			if(temp7->name[j]=='-')
				temp7->name[j]=' ';
		fscanf(z,"%d",&temp7->rent);
		printf("%d",temp7->rent);
		if(head->ptr6==NULL)
			head->ptr6=temp7;
		else
			q7->ptrf=temp7;
		q7=temp7;
	}
	getch();
}
void boardtext(FILE *y)
{
	int i=0,j;
	h=NULL;
	while(!feof(y))
	{
		t=(struct board*)malloc(sizeof(struct board));
		t->next=h;
		flushall();
		fscanf(y,"%s",t->property);
			for(j=0;t->property[j]!='\0';j++)
				if(t->property[j]=='-')
					t->property[j]=' ';
		t->number=i;
		if(h==NULL)
			h=t;
		else
			r->next=t;
		r=t;
		i++;
	}
}
void boardwrite()
{
	int i,j,k;
	r=h;
	settextjustify(1,1);
	settextstyle(2,1,4);
	for(i=9;i>=0;i--)
	{
		colorchoice1(r->property);
		if(i==9)
		{
			settextstyle(2,0,5);
			outtextxy(136+i*49,429,r->property);
			settextstyle(2,1,4);
		}
		else
			outtextxy(136+i*46,429,r->property);
		r=r->next;
	}
	settextstyle(2,0,5);
	for(i=9;i>=0;i--)
	{
		colorchoice1(r->property);
		if(i==9)
			outtextxy(62,122+i*34,r->property);
		else
			outtextxy(62,122+i*31,r->property);
		r=r->next;
	}
	settextstyle(2,1,4);
	for(i=0;i<10;i++)
	{
		colorchoice1(r->property);
		if(i==0)
		{
			settextstyle(2,0,5);
			outtextxy(62,70,r->property);
			settextstyle(2,1,4);
		}
		else
			outtextxy(89+i*46,70,r->property);
		r=r->next;
	}
	settextstyle(2,0,5);
	for(i=0;i<10;i++)
	{
		colorchoice1(r->property);
		if(i==0)
			outtextxy(581,70,r->property);
		else
			outtextxy(581,91+i*31,r->property);
		r=r->next;
	}
	setcolor(WHITE);
}
void colorchoice1(char* str)
{
	if(strcmp(str,"SportsLine")==0 || strcmp(str,"Fox Sports")==0)
		setcolor(LIGHTRED);
	else if(strcmp(str,"Y! Geocities")==0 || strcmp(str,"Oxygen")==0 || strcmp(str,"IVillage")==0)
		setcolor(LIGHTBLUE);
	else if(strcmp(str,"Shockwave")==0 || strcmp(str,"Games")==0 || strcmp(str,"E! Online")==0)
		setcolor(LIGHTMAGENTA);
	else if(strcmp(str,"Priceline")==0 || strcmp(str,"Expedia")==0 || strcmp(str,"eBAY")==0)
		setcolor(BROWN);
	else if(strcmp(str,"Weather")==0 || strcmp(str,"About")==0 || strcmp(str,"CNET")==0)
		setcolor(RED);
	else if(strcmp(str,"E*Trade")==0 || strcmp(str,"Monster")==0 || strcmp(str,"CBS M.Watch")==0)
		setcolor(YELLOW);
	else if(strcmp(str,"Ask Jeeves")==0 || strcmp(str,"Alta Vista")==0 || strcmp(str,"Lycos")==0)
		setcolor(GREEN);
	else if(strcmp(str,"Yahoo!")==0 || strcmp(str,"Excite@Home")==0)
		setcolor(BLUE);
	else
		setcolor(WHITE);
}
int boardclick()
{
	int i=0,j,k=0;
	c2:
	p=h;
	getmouseposition();
	if(m.button==1)
	{
		m.button=-1;
		if(m.y>389 && m.y<469 && m.x>113 && m.x<527)
		{
			if(m.x>481 && m.x<527)
				i=1;
			if(m.x>435 && m.x<481)
				i=2;
			if(m.x>389 && m.x<435)
				i=3;
			if(m.x>343 && m.x<389)
				i=4;
			if(m.x>297 && m.x<343)
				i=5;
			if(m.x>251 && m.x<297)
				i=6;
			if(m.x>205 && m.x<251)
				i=7;
			if(m.x>159 && m.x<205)
				i=8;
			if(m.x>113 && m.x<159)
				i=9;
		}
		else if(m.y>30 && m.y<110 && m.x>113 && m.x<527)
		{
			if(m.x>481 && m.x<527)
				i=29;
			if(m.x>435 && m.x<481)
				i=28;
			if(m.x>389 && m.x<435)
				i=27;
			if(m.x>343 && m.x<389)
				i=26;
			if(m.x>297 && m.x<343)
				i=25;
			if(m.x>251 && m.x<297)
				i=24;
			if(m.x>205 && m.x<251)
				i=23;
			if(m.x>159 && m.x<205)
				i=22;
			if(m.x>113 && m.x<159)
				i=21;
		}
		else if(m.x>10 && m.x<113 && m.y>110 && m.y<389)
		{
			if(m.y>358 && m.y<389)
				i=11;
			if(m.y>327 && m.y<358)
				i=12;
			if(m.y>296 && m.y<327)
				i=13;
			if(m.y>265 && m.y<296)
				i=14;
			if(m.y>234 && m.y<265)
				i=15;
			if(m.y>203 && m.y<234)
				i=16;
			if(m.y>172 && m.y<203)
				i=17;
			if(m.y>141 && m.y<172)
				i=18;
			if(m.y>110 && m.y<141)
				i=19;
		}
		else if(m.x>527 && m.x<629 && m.y>110 && m.y<389)
		{
			if(m.y>358 && m.y<389)
				i=39;
			if(m.y>327 && m.y<358)
				i=38;
			if(m.y>296 && m.y<327)
				i=37;
			if(m.y>265 && m.y<296)
				i=36;
			if(m.y>234 && m.y<265)
				i=35;
			if(m.y>203 && m.y<234)
				i=34;
			if(m.y>172 && m.y<203)
				i=33;
			if(m.y>141 && m.y<172)
				i=32;
			if(m.y>110 && m.y<141)
				i=31;
		}
		else if(m.x>10 && m.x<215 && m.y>1 && m.y<28)
			k=1;
		else if(m.x>424 && m.x<619 && m.y>1 && m.y<28)
			k=2;
		else if(m.x>(getmaxx()/2-25) && m.x<(getmaxx()/2+25) && m.y>120 && m.y<170)
			die=1;
		else
			goto c2;
	}
	else
		goto c2;
	for(j=0;j<i;j++)
		p=p->next;
	if(strcmp(edition,".com edition")==0)
		if(strcmp(p->property,"Download")==0 ||	strcmp(p->property,"Email")==0)
			goto c2;
	if(i!=0)
		k=0;
	return k;
}
void intboarddisplay()
{
	int i;
	settextjustify(1,1);
	settextstyle(3,0,4);
	outtextxy(getmaxx()/2,230,"MONOPOLY");
	settextstyle(3,0,1);
	outtextxy(getmaxx()/2,260,edition);
	for(i=0;i<2;i++)
	{
		polydraw(getmaxx()/2-196+i*324,180,getmaxx()/2-126+i*324,320);
		polydraw(getmaxx()/2-60+i*70,330,getmaxx()/2-10+i*70,380);
	}
	settextstyle(3,1,2);
	outtextxy(getmaxx()/2-171,250,head->bp1);
	outtextxy(getmaxx()/2+153,250,head->bp2);
	polydraw(getmaxx()/2+25,120,getmaxx()/2-25,170);
	setfillstyle(1,15);
	fillellipse(getmaxx()/2,145,5,5);
}
void detailsdisplay()
{
	int i,j;
	char msg[60];
	q2=head1->pt1;
	while(q2!=NULL)
	{
		q1=q2->right;
		while(q1!=NULL)
		{
			if(strcmp(q1->name,p->property)==0)
			{
				settextstyle(2,0,6);
				settextjustify(1,1);
				cardcolor1(p->property);
				polydraw(115,112,525,150);
				fillpoly(5,poly);
				outtextxy(320,128,q1->name);
				settextstyle(2,0,4);
				for(i=0;i<12;i++)
				{
					strcpy(msg,printing1(i,msg));
					outtextxy(200,170+i*15,msg);
				}
				settextjustify(1,1);
				settextstyle(2,0,6);
				if(q1->noh<5)
				{
					polydraw(370,getmaxy()/2+80,470,getmaxy()/2-20);
					itoa(q1->noh,msg,10);
					outtextxy(400,getmaxy()/2+30,msg);
					line(350,getmaxy()/2+80,490,getmaxy()/2+80);
					line(350,getmaxy()/2-20,490,getmaxy()/2-20);
					line(350,getmaxy()/2-20,420,getmaxy()/2-50);
					line(490,getmaxy()/2-20,420,getmaxy()/2-50);
				}
				break;
			}
			q1=q1->ptra;
		}
		q2=q2->down;
	}
	q3=head1->pt2;
	while(q3!=NULL)
	{
		if(strcmp(q3->name,p->property)==0)
		{
			settextstyle(2,0,6);
			settextjustify(1,1);
			outtextxy(320,128,q3->name);
			settextstyle(2,0,5);
			outtextxy(320,175,head->sp1);
			if(strcmp(edition,".com edition")==0)
			{
				line(230,160,400,160);
				line(230,195,400,195);
			}
			settextstyle(2,0,4);
			for(i=0;i<8;i++)
			{
				strcpy(msg,printing2(i,msg));
				outtextxy(320,210+i*15,msg);
			}
			break;
		}
		q3=q3->ptrb;
	}
	q4=head1->pt3;
	while(q4!=NULL)
	{
		if(strcmp(q4->name,p->property)==0)
		{
			settextstyle(2,0,6);
			settextjustify(1,1);
			outtextxy(320,128,q4->name);
			settextstyle(2,0,5);
			outtextxy(320,175,head->sp2);
			if(strcmp(edition,".com edition")==0)
			{
				line(290,160,345,160);
				line(290,195,345,195);
			}
			settextstyle(2,0,4);
			for(i=0;i<6;i++)
			{
				strcpy(msg,printing3(i,msg));
				outtextxy(320,210+i*15,msg);
			}
			break;
		}
		q4=q4->ptrc;
	}
	settextstyle(2,0,4);
	outtextxy(492,364,"Exit");
	polydraw(517,379,467,349);
	c3:
	getmouseposition();
	if(m.x>467 && m.x<517 && m.y>349 && m.y<379 && m.button==1)
	{
		display();
		intboarddisplay();
	}
	else
		goto c3;
}
void cardcolor1(char* str)
{
	if(strcmp(str,"SportsLine")==0 || strcmp(str,"Fox Sports")==0)
		setfillstyle(1,12);
	else if(strcmp(str,"Y! Geocities")==0 || strcmp(str,"Oxygen")==0 || strcmp(str,"IVillage")==0)
		setfillstyle(1,9);
	else if(strcmp(str,"Shockwave")==0 || strcmp(str,"Games")==0 || strcmp(str,"E! Online")==0)
		setfillstyle(1,13);
	else if(strcmp(str,"Priceline")==0 || strcmp(str,"Expedia")==0 || strcmp(str,"eBAY")==0)
		setfillstyle(1,6);
	else if(strcmp(str,"Weather")==0 || strcmp(str,"About")==0 || strcmp(str,"CNET")==0)
		setfillstyle(1,4);
	else if(strcmp(str,"E*Trade")==0 || strcmp(str,"Monster")==0 || strcmp(str,"CBS M.Watch")==0)
		setfillstyle(1,14);
	else if(strcmp(str,"Ask Jeeves")==0 || strcmp(str,"Alta Vista")==0 || strcmp(str,"Lycos")==0)
		setfillstyle(1,2);
	else if(strcmp(str,"Yahoo!")==0 || strcmp(str,"Excite@Home")==0)
		setfillstyle(1,1);
	else
		setfillstyle(1,15);
}
void polydraw(int a,int b,int c,int d)
{
	poly[0]=a;
	poly[1]=b;
	poly[2]=c;
	poly[3]=b;
	poly[4]=c;
	poly[5]=d;
	poly[6]=a;
	poly[7]=d;
	poly[8]=a;
	poly[9]=b;
	drawpoly(5,poly);
}
char* printing1(int i,char* msg)
{
	char value[6],str[15],str1[15];
	switch(i)
	{
		case 0:
			strcpy(str,"Owner");
			strcpy(str1,q1->owner);
			sprintf(msg,"%s : %s",str,str1);
			return msg;
		case 1:
			itoa(q1->prize,value,10);
			strcpy(str,"Prize");
			break;
		case 2:
			itoa(q1->rent,value,10);
			strcpy(str,"Rent");
			break;
		case 3:
			itoa(q1->h1,value,10);
			strcpy(str,"1 House Rent");
			break;
		case 4:
			itoa(q1->h2,value,10);
			strcpy(str,"2 House Rent");
			break;
		case 5:
			itoa(q1->h3,value,10);
			strcpy(str,"3 House Rent");
			break;
		case 6:
			itoa(q1->h4,value,10);
			strcpy(str,"4 House Rent");
			break;
		case 7:
			itoa(q1->office,value,10);
			strcpy(str,"Office Rent");
			break;
		case 8:
			itoa(q1->mot,value,10);
			strcpy(str,"Mortgage");
			break;
		case 9:
			itoa(q1->coh,value,10);
			strcpy(str,"Cost of House");
			break;
		case 10:
			itoa(q1->coo,value,10);
			strcpy(str,"Cost of Office");
			break;
		case 11:
			strcpy(str,"Condition");
			strcpy(str1,q1->condition);
			sprintf(msg,"%s : %s",str,str1);
			return msg;
	}
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"%s : $ %s Million",str,value);
	return msg;
}
char* printing2(int i,char* msg)
{
	char value[6],str[40],str1[15];
	switch(i)
	{
		case 0:
			strcpy(str,"Owner");
			strcpy(str1,q3->owner);
			sprintf(msg,"%s : %s",str,str1);
			return msg;
		case 1:
			itoa(q3->prize,value,10);
			strcpy(str,"Prize");
			break;
		case 2:
			itoa(q3->rent,value,10);
			sprintf(str,"If 1 %s is Owned",head->sp1);
			break;
		case 3:
			itoa(q3->rent*2,value,10);
			sprintf(str,"If 2 %ss is Owned",head->sp1);
			break;
		case 4:
			itoa(q3->rent*4,value,10);
			sprintf(str,"If 3 %ss is Owned",head->sp1);
			break;
		case 5:
			itoa(q3->rent*8,value,10);
			sprintf(str,"If 4 %ss is Owned",head->sp1);
			break;
		case 6:
			itoa(q3->mot,value,10);
			strcpy(str,"Modgage");
			break;
		case 7:
			strcpy(str,"Condition");
			strcpy(str1,q3->condition);
			sprintf(msg,"%s : %s",str,str1);
			return msg;
	}
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"%s : $ %s Million",str,value);
	return msg;
}
char* printing3(int i,char* msg)
{
	char value[6],str[40],str1[35];
	switch(i)
	{
		case 0:
			strcpy(str,"Owner");
			strcpy(str1,q4->owner);
			break;
		case 1:
			itoa(q4->prize,value,10);
			strcpy(str,"Prize");
			sprintf(msg,"%s : $ %s Million",str,value);
			return msg;
		case 2:
			sprintf(str,"If 1 %s is Owned",head->sp2);
			sprintf(str1,"4 times the amount shown on die");
			break;
		case 3:
			sprintf(str,"If 2 %s is Owned",head->sp2);
			sprintf(str1,"10 times the amount shown on die");
			break;
		case 4:
			itoa(q4->mot,value,10);
			strcpy(str,"Modgage");
			sprintf(msg,"%s : $ %s Million",str,value);
			return msg;
		case 5:
			strcpy(str,"Condition");
			strcpy(str1,q4->condition);
			sprintf(msg,"%s : %s",str,str1);
			return msg;
	}
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"%s : %s",str,str1);
	return msg;
}
void extrabuttons()
{
	int i;
	char msg[30];
	settextstyle(2,0,4);
	settextjustify(1,1);
	for(i=0;i<3;i=i+2)
	{
		polydraw(10+i*207,1,215+i*207,28);
		if(i==0)
			sprintf(msg,"User Detail");
		else
			sprintf(msg,"Quit");
		outtextxy(112+i*207,14,msg);
	}
}
void userdetailsdisplay()
{
	int i,j;
	char msg[10];
	cleardevice();
	polydraw(10,10,getmaxx()-10,getmaxy()-10);
	line(getmaxx()/2,10,getmaxx()/2,getmaxy()-10);
	settextstyle(3,0,4);
	settextjustify(1,1);
	outtextxy((getmaxx()+20)/4,30,"My Details");
	settextstyle(2,0,4);
	outtextxy(getmaxx()-45,getmaxy()-35,"Exit");
	polydraw(getmaxx()-20,getmaxy()-20,getmaxx()-70,getmaxy()-50);
	settextstyle(3,0,3);
	for(i=0;i<3;i++)
	{
		polydraw(30,100+i*110,getmaxx()/2-20,200+i*110);
		switch(i)
		{
			case 0:
				sprintf(msg,"Properties");
				break;
			case 1:
				sprintf(msg,"Money");
				break;
			case 2:
				sprintf(msg,"Houses");
				break;
		}
		outtextxy((getmaxx()+20)/4,150+i*110,msg);
	}
	qu=chance->u;
	for(i=0;i<3;i++)
	{
		polydraw(getmaxx()/2+20,100+i*110,getmaxx()-30,200+i*110);
		outtextxy((3*getmaxx()-20)/4,150+i*110,qu->username);
		qu=qu->u;
	}
	c3:
	getmouseposition();
	if(m.x>getmaxx()-70 && m.x<getmaxx()-20 && m.y>getmaxy()-50 && m.y<getmaxy()-20 && m.button==1)
	{
		display();
		intboarddisplay();
	}
	else
		goto c3;
}
void dienumgen()
{
	d.d1=(rand()%60)/10+1;
	d.d2=(rand()%60)/10+1;
}
void placepieces()
{
	qu=hu;
	do
	{
		pieceposition(qu->cp);
		piececolor();
		fillellipse(crd.m,crd.n,5,5);
		qu=qu->u;
	}while(qu!=hu);
	setcolor(WHITE);
	setfillstyle(1,WHITE);
}
void pieceposition(int i)
{
	if(i>0 && i<10)
	{
		switch(qu->pno)
		{
			case 0:
				crd.n=402;
				break;
			case 1:
				crd.n=420;
				break;
			case 2:
				crd.n=438;
				break;
			case 3:
				crd.n=456;
				break;
		}
		switch(i)
		{
			case 1:
				crd.m=517;
				break;
			case 2:
				crd.m=471;
				break;
			case 3:
				crd.m=425;
				break;
			case 4:
				crd.m=379;
				break;
			case 5:
				crd.m=333;
				break;
			case 6:
				crd.m=287;
				break;
			case 7:
				crd.m=241;
				break;
			case 8:
				crd.m=195;
				break;
			case 9:
				crd.m=149;
				break;
		}
	}
	if(i>10 && i<20)
	{
		switch(qu->pno)
		{
			case 0:
				crd.m=25;
				break;
			case 1:
				crd.m=75;
				break;
			case 2:
				crd.m=50;
				break;
			case 3:
				crd.m=100;
				break;
		}
		switch(i)
		{
			case 11:
				crd.n=379;
				break;
			case 12:
				crd.n=348;
				break;
			case 13:
				crd.n=317;
				break;
			case 14:
				crd.n=286;
				break;
			case 15:
				crd.n=255;
				break;
			case 16:
				crd.n=224;
				break;
			case 17:
				crd.n=193;
				break;
			case 18:
				crd.n=162;
				break;
			case 19:
				crd.n=131;
				break;
		}
	}
	if(i>20 && i<30)
	{
		switch(qu->pno)
		{
			case 0:
				crd.n=45;
				break;
			case 1:
				crd.n=63;
				break;
			case 2:
				crd.n=81;
				break;
			case 3:
				crd.n=99;
				break;
		}
		switch(i)
		{
			case 21:
				crd.m=123;
				break;
			case 22:
				crd.m=169;
				break;
			case 23:
				crd.m=215;
				break;
			case 24:
				crd.m=261;
				break;
			case 25:
				crd.m=307;
				break;
			case 26:
				crd.m=353;
				break;
			case 27:
				crd.m=399;
				break;
			case 28:
				crd.m=445;
				break;
			case 29:
				crd.m=491;
				break;
		}
	}
	if(i>30 && i<40)
	{
		switch(qu->pno)
		{
			case 0:
				crd.m=542;
				break;
			case 1:
				crd.m=592;
				break;
			case 2:
				crd.m=567;
				break;
			case 3:
				crd.m=617;
				break;
		}
		switch(i)
		{
			case 31:
				crd.n=120;
				break;
			case 32:
				crd.n=151;
				break;
			case 33:
				crd.n=182;
				break;
			case 34:
				crd.n=213;
				break;
			case 35:
				crd.n=244;
				break;
			case 36:
				crd.n=275;
				break;
			case 37:
				crd.n=306;
				break;
			case 38:
				crd.n=337;
				break;
			case 39:
				crd.n=368;
				break;
		}
	}
	if(i%10==0)
	{
		switch(i)
		{
			case 0:
				if(qu->pno==0)
				{
					crd.m=542;
					crd.n=402;
				}
				if(qu->pno==1)
				{
					crd.m=592;
					crd.n=420;
				}
				if(qu->pno==2)
				{
					crd.m=567;
					crd.n=438;
				}
				if(qu->pno==3)
				{
					crd.m=617;
					crd.n=456;
				}
				break;
			case 10:
				if(qu->pno==0)
				{
					crd.m=25;
					crd.n=402;
				}
				if(qu->pno==1)
				{
					crd.m=75;
					crd.n=420;
				}
				if(qu->pno==2)
				{
					crd.m=50;
					crd.n=438;
				}
				if(qu->pno==3)
				{
					crd.m=100;
					crd.n=456;
				}
				break;
			case 20:
				if(qu->pno==0)
				{
					crd.m=25;
					crd.n=45;
				}
				if(qu->pno==1)
				{
					crd.m=75;
					crd.n=63;
				}
				if(qu->pno==2)
				{
					crd.m=50;
					crd.n=81;
				}
				if(qu->pno==3)
				{
					crd.m=100;
					crd.n=99;
				}
				break;
			case 30:
				if(qu->pno==0)
				{
					crd.m=542;
					crd.n=45;
				}
				if(qu->pno==1)
				{
					crd.m=592;
					crd.n=63;
				}
				if(qu->pno==2)
				{
					crd.m=567;
					crd.n=81;
				}
				if(qu->pno==3)
				{
					crd.m=617;
					crd.n=99;
				}
				break;
		}
	}
}
void piecemovement()
{
	int i,ix,iy,j,jx,jy,k;
	qu=chance;
	piececolor();
	j=chance->cp;
	pieceposition(j);
	jx=crd.m;
	jy=crd.n;
	i=j;
	do
	{
		++i;
		if(i==40)
		{
			i=0;
			k=1;
		}
		pieceposition(i);
		ix=crd.m;
		iy=crd.n;
		do
		{
			fillellipse(jx,jy,5,5);
			if(j>=0 && j<10)
				jx--;
			else if(j>=10 && j<20)
				jy--;
			else if(j>=20 && j<30)
				jx++;
			else if(j>=30 && j<40)
				jy++;
			delay(10);
		}while(jx!=ix || jy!=iy);
		if(i==0)
			j=0;
		else
			j++;
	}while(i!=fp);
	chance->cp=fp;
	setcolor(WHITE);
	delay(100);
	display();
	intboarddisplay();
	delay(100);
	if(k==1)
		gorule();
	if(fp==2 || fp==17 || fp==33)
		boardcards1();
	if(fp==7 || fp==22 || fp==36)
		boardcards2();
	if(fp==2 || fp==38)
		extrarental();
	display();
}
void piececolor()
{
	switch(qu->pno)
	{
		case 0:
			setfillstyle(1,1);
			setcolor(1);
			break;
		case 1:
			setfillstyle(1,2);
			setcolor(2);
			break;
		case 2:
			setfillstyle(1,14);
			setcolor(14);
			break;
		case 3:
			setfillstyle(1,4);
			setcolor(4);
			break;
	}
}
void yourchance()
{
	char msg[50];
	settextjustify(1,1);
	settextstyle(3,0,4);
	if(strcmp(chance->username,"Comp1")==0 || strcmp(chance->username,"Comp2")==0 || strcmp(chance->username,"Comp3")==0)
		sprintf(msg,"%s's Chance",chance->username);
	else
		sprintf(msg,"%s - Your Chance",chance->username);
	outtextxy(getmaxx()/2,230,msg);
	settextstyle(2,0,5);
	setcolor(WHITE);
	outtextxy(getmaxx()/2,350,"Press enter to Continue");
	getch();
	setcolor(15);
}
void display()
{
	extboarddisplay();
	boardwrite();
	extrabuttons();
	placepieces();
}
void msgbox()
{
	polydraw(123,140,517,360);
	setfillstyle(1,BLACK);
	fillpoly(5,poly);
}
void conditioncheck()
{
	int i,rent;
	p=h;
	for(i=0;i<chance->cp;i++)
		p=p->next;
	q2=head1->pt1;
	while(q2!=NULL)
	{
		q1=q2->right;
		while(q1!=NULL)
		{
			if(strcmp(q1->name,p->property)==0)
			{
				ptype=0;
				if(strcmp(q1->owner,"Bank")==0)
					msgdisp1(q1->owner,q1->prize);
				else if(strcmp(q1->owner,chance->username)==0)
					housing();
				else
				{
					rent=rentcheck1();
					msgdisp2(rent,q1->owner);
				}
			}
			q1=q1->ptra;
		}
		q2=q2->down;
	}
	q3=head1->pt2;
	while(q3!=NULL)
	{
		if(strcmp(q3->name,p->property)==0)
		{
			ptype=1;
			if(strcmp(q3->owner,"Bank")==0)
				msgdisp1(q3->owner,q3->prize);
			else if(strcmp(q3->owner,chance->username)!=0)
			{
				rent=rentcheck2();
				msgdisp2(rent,q3->owner);
			}
		}
		q3=q3->ptrb;
	}
	q4=head1->pt3;
	while(q4!=NULL)
	{
		if(strcmp(q4->name,p->property)==0)
		{
			ptype=2;
			if(strcmp(q4->owner,"Bank")==0)
				msgdisp1(q4->owner,q4->prize);
			else if(strcmp(q4->owner,chance->username)!=0)
			{
				rent=rentcheck3();
				msgdisp2(rent,q4->owner);
			}
		}
		q4=q4->ptrc;
	}
}
void msgdisp1(char* own,int prz)
{
	char msg[50];
	settextjustify(1,1);
	settextstyle(2,0,7);
	msgbox();
	outtextxy(getmaxx()/2,170,"Buy Property");
	line(getmaxx()/2-70,185,getmaxx()/2+70,185);
	sprintf(msg,"Would You like to Buy %s",p->property);
	outtextxy(getmaxx()/2,230,msg);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Prize - $ %d Million",prz);
	settextstyle(2,0,5);
	outtextxy(getmaxx()/2,270,msg);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Your Balance - $ %d Million",chance->money);
	outtextxy(getmaxx()/2,300,msg);
	polydraw(143,320,193,350);
	polydraw(447,320,497,350);
	settextstyle(2,0,4);
	outtextxy(168,335,"Buy");
	outtextxy(472,335,"Cancel");
	c6:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>143 && m.x<193 && m.y>320 && m.y<350)
		{
			delay(100);
			transaction(own,prz);
		}
		if(m.x>447 && m.x<497 && m.y>320 && m.y<350)
		{
			display();
			intboarddisplay();
		}
		else
			goto c6;
	}
	else
		goto c6;
}
void transaction(char* own,int prz)
{
	char msg[50];
	settextjustify(1,1);
	settextstyle(2,0,7);
	msgbox();
	sprintf(msg,"Transaction");
	outtextxy(getmaxx()/2,170,msg);
	line(getmaxx()/2-65,185,getmaxx()/2+65,185);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Pay %s $ %d Million",own,prz);
	settextstyle(2,0,6);
	outtextxy(getmaxx()/2,230,msg);
	polydraw(143,320,193,350);
	settextstyle(2,0,4);
	outtextxy(168,335,"Pay");
	outtextxy(472,335,"Cancel");
	polydraw(447,320,497,350);
	c4:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>143 && m.x<193 && m.y>320 && m.y<350)
		{
			if(chance->money>=prz)
			{
				(chance->money)=(chance->money)-prz;
				buyprop();
				delay(100);
				transanimation();
				msgbox();
				balance();
			}
		}
		else if(m.x>447 && m.x<497 && m.y>320 && m.y<350)
		{
			display();
			intboarddisplay();
		}
		else
			goto c4;
	}
	else
		goto c4;
}
void transanimation()
{
	int i;
	char msg[50];
	settextjustify(1,1);
	settextstyle(2,0,7);
	msgbox();
	sprintf(msg,"Transacting");
	outtextxy(getmaxx()/2,200,msg);
	polydraw(getmaxx()/2-100,230,getmaxx()/2+100,240);
	i=-100;
	do
	{
		polydraw(getmaxx()/2-100,230,getmaxx()/2+i,240);
		setfillstyle(1,15);
		fillpoly(5,poly);
		i++;
		delay(10);
	}while(i!=100);
}
int rentcheck1()
{
	int rent;
	qu=hu;
	do
	{
		if(strcmp(tempu->username,q1->owner)==0)
			qu=tempu;
		tempu=tempu->u;
	}while(tempu!=hu);
	p2=qu->nxt1;
	while(p2!=NULL)
	{
		if(strcmp(p2->color,q1->color)==0)
		{
			p1=p2->right;
			if(strcmp(p1->name,q1->name)==0)
			{
				switch(p1->noh)
				{
					case 0:
						rent=p1->rent;
						break;
					case 1:
						rent=p1->h1;
						break;
					case 2:
						rent=p1->h2;
						break;
					case 3:
						rent=p1->h3;
						break;
					case 4:
						rent=p1->h4;
						break;
					case 5:
						rent=p1->office;
						break;
				}
			}
			p1=p1->ptra;
		}
		p2=p2->down;
	}
	return rent;
}
int rentcheck2()
{
	int rent;
	qu=hu;
	do
	{
		if(strcmp(tempu->username,q1->owner)==0)
			qu=tempu;
		tempu=tempu->u;
	}while(tempu!=hu);
	switch(qu->csp1)
	{
		case 1:
			rent=(q3->rent);
			break;
		case 2:
			rent=(q3->rent)*2;
			break;
		case 3:
			rent=(q3->rent)*4;
			break;
		case 4:
			rent=(q3->rent)*8;
			break;
	}
	return rent;
}
int rentcheck3()
{
	int rent;
	qu=hu;
	do
	{
		if(strcmp(tempu->username,q1->owner)==0)
			qu=tempu;
		tempu=tempu->u;
	}while(tempu!=hu);
	switch(qu->csp2)
	{
		case 1:
			rent=4*(d.d1+d.d2);
			break;
		case 2:
			rent=10*(d.d1+d.d2);
			break;
	}
	return rent;
}
void msgdisp2(int rent,char* own)
{
	char msg[50];
	settextjustify(1,1);
	settextstyle(2,0,7);
	msgbox();
	outtextxy(getmaxx()/2,170,"Pay Rent");
	line(getmaxx()/2-60,185,getmaxx()/2+60,185);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Pay $ %d Million to %s",rent,own);
	outtextxy(getmaxx()/2,230,msg);
	polydraw(getmaxx()/2-25,320,getmaxx()/2+25,350);
	settextstyle(2,0,4);
	outtextxy(getmaxx()/2,335,"Pay");
	c5:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x<(getmaxx()/2+25) && m.x>(getmaxx()/2-25) && m.y<350 && m.y>320)
		{
			delay(100);
			(chance->money)=(chance->money)-rent;
			if(strcmp(qu->username,chance->username)!=0 && strcmp(own,"Bank")==0)
				(qu->money)=(qu->money)+rent;
			transanimation();
			msgbox();
			settextstyle(2,0,6);
			balance();
		}
		else
			goto c5;
	}
	else
		goto c5;
}
void msgdisp3()
{
	char msg[50];
	settextjustify(1,1);
	settextstyle(2,0,7);
	msgbox();
	outtextxy(getmaxx()/2,170,"House Build");
	line(getmaxx()/2-70,185,getmaxx()/2+70,185);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Do you want a build a house");
	outtextxy(getmaxx()/2,230,msg);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Cost : $ %d Million", q1->coh);
	settextstyle(2,0,5);
	outtextxy(getmaxx()/2,280,msg);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Your Balance - $ %d Million",chance->money);
	outtextxy(getmaxx()/2,300,msg);
	polydraw(143,320,193,350);
	polydraw(447,320,497,350);
	settextstyle(2,0,4);
	outtextxy(168,335,"Yes");
	outtextxy(472,335,"No");
	c6:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>143 && m.x<193 && m.y>320 && m.y<350)
		{
			(q1->noh)++;
			delay(100);
			(chance->money)=(chance->money)-(q1->coh);
			transanimation();
			msgbox();
			balance();
		}
		if(m.x>447 && m.x<497 && m.y>320 && m.y<350)
		{
			display();
			intboarddisplay();
		}
		else
			goto c6;
	}
	else
		goto c6;
}
void msgdisp4()
{
}
void buyprop()
{
	if(ptype==0)
	{
		p2=head->ptr1;
		while(p2!=NULL)
		{
			p1=p2->right;
			while(p1!=NULL)
			{
				if(strcmp(p1->name,p->property)==0)
				{
					if(p1==p2->right)
						p2->right=p1->ptra;
					else
					{
						temp1=p2->right;
						while(temp1->ptra!=p1)
							temp1=temp1->ptra;
						temp1->ptra=p1->ptra;
					}
					strcpy(p1->owner,chance->username);
					strcpy(q1->owner,chance->username);
					q1=p1;
				}
				p1=p1->ptra;
			}
			p2=p2->down;
		}
		temp2=chance->nxt1;
		while(temp2!=NULL)
		{
			if(strcmp(temp2->color,q1->color)==0)
			{
				if(temp2->right==NULL)
					temp2->right=q1;
				else
				{
					temp1=temp2->right;
					while(temp1->ptra!=NULL)
						temp1=temp1->ptra;
					temp1->ptra=q1;
				}
				q1->ptra=NULL;
				(temp2->current)++;
			}
			temp2=temp2->down;
		}
	}
	if(ptype==1)
	{
		p3=head->ptr2;
		while(p3!=NULL)
		{
			if(strcmp(p3->name,p->property)==0)
			{
				if(p3==head->ptr2)
					head->ptr2=p3->ptrb;
				else
				{
					temp3=head->ptr2;
					while(temp3->ptrb!=p3)
						temp3=temp3->ptrb;
					temp3->ptrb=p3->ptrb;
				}
				strcpy(p3->owner,chance->username);
				strcpy(q3->owner,chance->username);
				q3=p3;
			}
			p3=p3->ptrb;
		}
		if(chance->nxt2==NULL)
			chance->nxt2=q3;
		else
		{
			temp3=chance->nxt2;
			while(temp3->ptrb!=NULL)
				temp3=temp3->ptrb;
			temp3->ptrb=q3;
		}
		q3->ptrb=NULL;
		(chance->csp1)++;
	}
	if(ptype==2)
	{
		p4=head->ptr3;
		while(p4!=NULL)
		{
			if(strcmp(p4->name,p->property)==0)
			{
				if(p4==head->ptr3)
					head->ptr3=p4->ptrc;
				else
				{
					temp4=head->ptr3;
					while(temp4->ptrc!=p4)
						temp4=temp4->ptrc;
					temp4->ptrc=p4->ptrc;
				}
				strcpy(p4->owner,chance->username);
				strcpy(q4->owner,chance->username);
				q4=p4;
			}
			p4=p4->ptrc;
		}
		if(chance->nxt3==NULL)
			chance->nxt3=q4;
		else
		{
			temp4=chance->nxt3;
			while(temp4->ptrc!=NULL)
				temp4=temp4->ptrc;
			temp4->ptrc=q4;
		}
		q4->ptrc=NULL;
		(chance->csp2)++;
	}
}
void dieanimation()
{
	int s;
	char str[3];
	delay(100);
	settextstyle(2,0,6);
	settextjustify(1,1);
	s=rand()%2;
	if(s==0)
	{
		itoa(d.d1,str,10);
		outtextxy(getmaxx()/2-35,355,str);
		delay(rand()%500+20);
		itoa(d.d2,str,10);
		outtextxy(getmaxx()/2+35,355,str);
	}
	else
	{
		itoa(d.d2,str,10);
		outtextxy(getmaxx()/2+35,355,str);
		delay(rand()%500+20);
		itoa(d.d1,str,10);
		outtextxy(getmaxx()/2-35,355,str);
	}
	delay(100);
}
void housing()
{
	int t=6,k;
	if(q2->total==q2->current)
	{
		p1=q2->right;
		while(p1!=NULL)
		{
			if(p1->noh<t)
				t=p1->noh;
			p1=p1->ptra;
		}
		if(q1->noh==t)
			msgdisp3();
	}
}
void balance()
{
	char msg[50];
	settextstyle(2,0,6);
	sprintf(msg,"Transaction Complete");
		outtextxy(getmaxx()/2,200,msg);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Your Balance : $ %d Million",chance->money);
	settextstyle(2,0,5);
	outtextxy(getmaxx()/2,260,msg);
	polydraw(447,320,497,350);
	outtextxy(472,335,"Ok");
	c7:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>447 && m.x<497 && m.y>320 && m.y<350)
		{
			display();
			intboarddisplay();
		}
		else
			goto c7;
	}
	else
		goto c7;
}
void gorule()
{
	char msg[50];
	settextjustify(1,1);
	settextstyle(2,0,7);
	msgbox();
	outtextxy(getmaxx()/2,170,"You Pass Go");
	line(getmaxx()/2-70,185,getmaxx()/2+70,185);
	if(strcmp(edition,".com edition")==0)
		sprintf(msg,"Collect $ 200 Million");
	outtextxy(getmaxx()/2,230,msg);
	polydraw(getmaxx()/2+25,320,getmaxx()/2-25,350);
	settextstyle(2,0,4);
	outtextxy(getmaxx()/2,335,"Collect");
	c6:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>getmaxx()/2-25 && m.x<getmaxx()/2+25 && m.y>320 && m.y<350)
		{
			delay(100);
			(chance->money)=(chance->money)+200;
			transanimation();
			msgbox();
			balance();
		}
		else
			goto c6;
	}
	else
		goto c6;
}
void gotojail()
{
	int j,jx,jy,fpx,fpy;
	float s,c;
	fp=10;
	chance->jail=1;
	qu=chance;
	piececolor();
	j=chance->cp;
	pieceposition(j);
	jx=crd.m;
	jy=crd.n;
	pieceposition(fp);
	fpx=crd.m;
	fpy=crd.n;
	s=(fpy-jy);
	s=s/(fpx-jx);
	c=fpy-s*fpx;
	do
	{
		fillellipse(jx,jy,5,5);
		if(jx>fpx)
		{
			--jx;
			jy=s*jx+c;
		}
		else if(jy==fpy && jx!=fpx)
			--jx;
		else if(jx==fpx && jy!=fpy)
			++jy;
		delay(10);
	}while(jx!=fpx || jy!=fpy);
	chance->jailchance=0;
	chance->cp=fp;
	delay(100);
	setcolor(WHITE);
	display();
	intboarddisplay();
}
void boardcards1()
{
	int t;
	char msg1[100];
	c11:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>(getmaxx()/2-196) && m.x<(getmaxx()/2-146) && m.y>180 && m.y<320)
		{
			msgbox();
			settextstyle(2,0,7);
			sprintf(msg1,"%s",head->bp1);
			outtextxy(getmaxx()/2,170,msg1);
			line(getmaxx()/2-70,185,getmaxx()/2+70,185);
			sprintf(msg1,"%s",head->ptr4->msg);
			settextstyle(2,0,5);
			outtextxy(getmaxx()/2,230,msg1);
			polydraw(getmaxx()/2+25,320,getmaxx()/2-25,350);
			settextstyle(2,0,4);
			outtextxy(getmaxx()/2,335,"Ok");
			c6:
			getmouseposition();
			if(m.button==1)
			{
				if(m.x>getmaxx()/2-25 && m.x<getmaxx()/2+25 && m.y>320 && m.y<350)
				{
					display();
					intboarddisplay();
				}
				else
					goto c6;
			}
			else
				goto c6;
		}
		else
			goto c11;
	}
	else
		goto c11;
	if(strcmp(edition,".com edition")==0)
	{
		switch(head->ptr4->index)
		{
			case 0:
				(chance->money)=(chance->money)+20;
				break;
			case 1:
				(chance->money)=(chance->money)-150;
				break;
			case 2:
				(chance->money)=(chance->money)+50*nop;
				qu=hu;
				do
				{
					if(qu!=chance)
						(qu->money)=(qu->money)-50;
					qu=qu->u;
				}while(qu!=hu);
				break;
			case 3:
				(chance->money)=(chance->money)-50;
				break;
			case 4:
				chance->gojf=1;
				break;
			case 5:
				(chance->money)=(chance->money)+25;
				break;
			case 6:
				(chance->money)=(chance->money)+10;
				break;
			case 7:
				fp=0;
				piecemovement();
				break;
			case 8:
				(chance->money)=(chance->money)+100;
				break;
			case 9:
				t=0;
				q2=chance->nxt1;
				while(q2!=NULL)
				{
					q1=q2->right;
					while(q1!=NULL)
					{
						t=t+(q1->noh);
						q1=q1->ptra;
					}
					q2=q2->down;
				}
				msgbox();
				settextstyle(2,0,7);
				outtextxy(getmaxx()/2,170,"House Tax");
				settextstyle(2,0,4);
				sprintf(msg1,"No. Of Houses : %d",t);
				outtextxy(getmaxx()/2,220,msg1);
				sprintf(msg1,"Your Balnace : $ %d Milliom", chance->money);
				outtextxy(getmaxx()/2,220,msg1);
				sprintf(msg1,"Prize to be paid : $ %d Million",t*115);
				outtextxy(getmaxx()/2,220,msg1);
				polydraw(getmaxx()/2+25,320,getmaxx()/2-25,350);
				settextstyle(2,0,4);
				outtextxy(getmaxx()/2,335,"Ok");
				c12:
				getmouseposition();
				if(m.button==1)
				{
					if(m.x>getmaxx()/2-25 && m.x<getmaxx()/2+25 && m.y>320 && m.y<350)
					{
						delay(100);
						transanimation();
						msgbox();
						balance();
					}
					else
						goto c12;
				}
				else
				goto c12;
				(chance->money)=(chance->money)-115*t;
				break;
			case 10:
				gotojail();
				break;
			case 11:
				(chance->money)=(chance->money)+100;
				break;
			case 12:
				(chance->money)=(chance->money)+45;
				break;
			case 13:
				(chance->money)=(chance->money)+200;
				break;
		}
	}
	if(head->ptr4->index!=4 && head->ptr4->index!=10 && head->ptr4->index!=7)
	{
		transanimation();
		msgbox();
		balance();
	}
	head->ptr4=head->ptr4->ptrd;
}
void boardcards2()
{
	int t,k,n=0;
	char msg1[100];
	c11:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>(getmaxx()/2+128) && m.x<(getmaxx()/2+178) && m.y>180 && m.y<320)
		{
			msgbox();
			settextstyle(2,0,7);
			sprintf(msg1,"%s",head->bp2);
			outtextxy(getmaxx()/2,170,msg1);
			line(getmaxx()/2-70,185,getmaxx()/2+70,185);
			sprintf(msg1,"%s",head->ptr5->msg);
			settextstyle(2,0,5);
			outtextxy(getmaxx()/2,230,msg1);
			polydraw(getmaxx()/2+25,320,getmaxx()/2-25,350);
			settextstyle(2,0,4);
			outtextxy(getmaxx()/2,335,"Ok");
			c6:
			getmouseposition();
			if(m.button==1)
			{
				if(m.x>getmaxx()/2-25 && m.x<getmaxx()/2+25 && m.y>320 && m.y<350)
				{
					display();
					intboarddisplay();
				}
				else
					goto c6;
			}
			else
				goto c6;
		}
		else
			goto c11;
	}
	else
		goto c11;
	if(strcmp(edition,".com edition")==0)
	{
		switch(head->ptr5->index)
		{
			case 0:
				fp=24;
				piecemovement();
				break;
			case 1:
				fp=39;
				piecemovement();
				break;
			case 2:
				t=0;
				k=0;
				q2=chance->nxt1;
				while(q2!=NULL)
				{
					q1=q2->right;
					while(q1!=NULL)
					{
						if(q1->noh<5)
							t=t+(q1->noh);
						if(q1->noh==5)
							k++;
						q1=q1->ptra;
					}
					q2=q2->down;
				}
				msgbox();
				settextstyle(2,0,7);
				outtextxy(getmaxx()/2,170,"House Tax");
				settextstyle(2,0,4);
				sprintf(msg1,"No. Of Houses : %d",t);
				outtextxy(getmaxx()/2,220,msg1);
				sprintf(msg1,"Your Balnace : $ %d Milliom", chance->money);
				outtextxy(getmaxx()/2,220,msg1);
				sprintf(msg1,"Prize to be paid : $ %d Million",t*25+k*40);
				outtextxy(getmaxx()/2,220,msg1);
				polydraw(getmaxx()/2+25,320,getmaxx()/2-25,350);
				settextstyle(2,0,4);
				outtextxy(getmaxx()/2,335,"Ok");
				c12:
				getmouseposition();
				if(m.button==1)
				{
					if(m.x>getmaxx()/2-25 && m.x<getmaxx()/2+25 && m.y>320 && m.y<350)
					{
						delay(100);
						transanimation();
						msgbox();
						balance();
					}
					else
						goto c12;
				}
				else
				goto c12;
				(chance->money)=(chance->money)-25*t-40*k;
				n=1;
				break;
			case 3:
				chance->gojf=1;
				break;
			case 4:
				if(chance->cp<12 || chance->cp>28)
					fp=12;
				else
					fp=28;
				piecemovement();
				break;
			case 5:
				(chance->money)=(chance->money)+50;
				n=1;
				break;
			case 6:
				fp=5;
				piecemovement();
				break;
			case 7:
				fp=0;
				piecemovement();
				break;
			case 8:
				(chance->money)=(chance->money)-15;
				n=1;
				break;
			case 9:
				(chance->money)=(chance->money)+150;
				n=1;
				break;
			case 10:
				if(chance->cp<5 || chance->cp>35)
					fp=5;
				else if(chance->cp>5 && chance->cp<15)
					fp=15;
				else if(chance->cp>15 && chance->cp<25)
					fp=25;
				else
					fp=35;
				piecemovement();
				break;
			case 11:
				fp=11;
				piecemovement();
				break;
			case 12:
				gotojail();
				break;
			case 13:
				(chance->money)=(chance->money)-50*nop;
				qu=hu;
				do
				{
					if(qu!=chance)
						(qu->money)=(qu->money)+50;
					qu=qu->u;
				}while(qu!=hu);
				n=1;
				break;
		}
	}
	if(n==1)
	{
		transanimation();
		msgbox();
		balance();
	}
	head->ptr5=head->ptr5->ptre;
}
void quitbox()
{
	char msg1[20];
	msgbox();
	settextstyle(2,0,7);
	sprintf(msg1,"Quit");
	outtextxy(getmaxx()/2,170,msg1);
	line(getmaxx()/2-30,185,getmaxx()/2+30,185);
	sprintf(msg1,"Are You Sure?");
	settextstyle(2,0,5);
	outtextxy(getmaxx()/2,230,msg1);
	polydraw(getmaxx()/2+25,320,getmaxx()/2-25,350);
	settextstyle(2,0,4);
	outtextxy(getmaxx()/2,335,"Yes");
	c6:
	getmouseposition();
	if(m.button==1)
	{
		if(m.x>getmaxx()/2-25 && m.x<getmaxx()/2+25 && m.y>320 && m.y<350)
		{
			quit();
			display();
			intboarddisplay();
		}
		else
			goto c6;
	}
	else
		goto c6;
}
void quit()
{
	q2=chance->nxt1;
	p2=head->ptr1;
	temp2=head1->pt1;
	while(q2!=NULL)
	{
		temp1=temp2->right;
		while(temp1!=NULL)
		{
			if(strcmp(temp1->owner,chance->username)==0)
				strcpy(temp1->owner,"Bank");
			temp1=temp1->ptra;
		}
		q1=q2->right;
		while(q1!=NULL)
		{
			strcpy(q1->owner,"Bank");
			q1->noh=0;
			q1=q1->ptra;
		}
		if(p2->right==NULL)
			p2->right=q2->right;
		else
		{
			p1=p2->right;
			while(p1->ptra!=NULL)
				p1=p1->ptra;
			p1->ptra=q2->right;
		}
		q2->right=NULL;
		q2->current=0;
		q2=q2->down;
		p2=p2->down;
		temp2=temp2->down;
	}
	q3=chance->nxt2;
	temp3=head1->pt2;
	while(temp3!=NULL)
	{
		if(strcmp(temp3->owner,chance->username)==0)
			strcpy(temp3->owner,"Bank");
		temp3=temp3->ptrb;
	}
	while(q3!=NULL)
	{
		strcpy(q3->owner,"Bank");
		q3=q3->ptrb;
	}
	chance->csp1=0;
	if(head->ptr2==NULL)
		head->ptr2=chance->nxt2;
	else
	{
		p3=head->ptr2;
		while(p3->ptrb!=NULL)
			p3=p3->ptrb;
		p3->ptrb=chance->nxt2;
	}
	chance->nxt2=NULL;
	q4=chance->nxt3;
	temp4=head1->pt3;
	while(temp4!=NULL)
	{
		if(strcmp(temp4->owner,chance->username)==0)
			strcpy(temp4->owner,"Bank");
		temp4=temp4->ptrc;
	}
	while(q4!=NULL)
	{
		strcpy(q4->owner,"Bank");
		q4=q4->ptrc;
	}
	chance->csp2=0;
	if(head->ptr3==NULL)
		head->ptr3=chance->nxt3;
	else
	{
		p4=head->ptr3;
		while(p4->ptrc!=NULL)
			p4=p4->ptrc;
		p4->ptrc=chance->nxt3;
	}
	chance->nxt3=NULL;
	qu=hu;
	do
	{
		if(qu->u==chance)
		{
			qu->u=chance->u;
			if(chance==hu)
				hu=chance->u;
			tempu=qu;
		}
		qu=qu->u;
	}while(qu!=hu);
	free(chance);
	chance=tempu->u;
}
void extrarental()
{
	int rent;
	char msg[10];
	if(fp==2)
		rent=head->ptr6->rent;
	else
		rent=head->ptr6->ptrf->rent;
	printf("%d",rent);
	getch();
	sprintf(msg,"Bank");
	msgdisp2(rent,msg);
}