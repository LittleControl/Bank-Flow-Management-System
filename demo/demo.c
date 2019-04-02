#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#define MAXSIZE 6
typedef struct admin
{
	int username[MAXSIZE];
	int password[MAXSIZE];
}Admin;
typedef struct user
{
	int username[MAXSIZE];
	int password[MAXSIZE];
}User;
typedef struct account
{
	int usernum;
	Admin *admin;
	User *user[20];
}Account;
typedef struct userlog
{
	int expenses;
	int revenue;
	int date[8];
	struct userlog *next;
}Userlog;
Admin* init_admin();
Account* init_account();
void Assign(int array[MAXSIZE]);
void Assign_pwd(int array[MAXSIZE]);
void Assign_date(int array[8]);
int diff(int username[MAXSIZE],int name[MAXSIZE]);
int diff_date(int date1[8],int date2[8]);
int Check(Account *account,int name[MAXSIZE],int pwd[MAXSIZE]);
void printDate(int date[8]);
void Add(Userlog *userlog[20],int chmod);
void Delete(Userlog *userlog[20],int chmod,Userlog *front);
void Modify(Userlog *userlog[20],int chmod, Userlog *front);
void Operation(Account *account,Userlog *userlog[20],int chmod);
void Login(Account *account,Userlog *userlog[20]);
void Registered(Account *account,Userlog *userlog[20]);
int Choose();
void putArray(FILE *fp,int array[MAXSIZE]);
Userlog* init_userlog();
User* init_user();
void putDate(FILE *fp,int date[8]);
int numSiwtch(int *temp);
void reArray(int arr1[MAXSIZE],int arr2[MAXSIZE]);
void reDate(int date1[8],int date2[8]);
int readWhile(FILE *fp,int *temp,int array[MAXSIZE]);
void arrToSt(FILE *fp,Account *account);
void readAccount(Account *account);
void seeStrc(Userlog *userlog);
int readId(FILE *fp,int *temp);
void readDate(FILE *fp,Userlog *userlog,int *temp);
void readEx(FILE *fp, Userlog *userlog,int *temp);
void readRe(FILE *fp, Userlog *userlog,int *temp);
void init_array(int array[20]);
void readLog(Userlog *userlog[20]);
int max(int a,int b);
void loopMain(Account *account,Userlog *userlog[20],int userId,int chmod,Userlog *front);
void CheckExDate(Userlog *userlog,int maxEx);
void CheckReDate(Userlog *userlog,int maxRe);
void Statistics(Userlog *userlog);
void Inquire(Account *account,Userlog *userlog[20],int date[8],int userId,Userlog *front);
void loopUser(Account *account,Userlog *userlog[20],int chmod,Userlog *front);
void loopMain(Account *account,Userlog *userlog[20],int userId,int chmod,Userlog *front);
void putFile(Account *account,Userlog *userlog[20]);


int main(int argc, char const *argv[])
{
	Account *account;
	Userlog *userlog[20];
	account=init_account();
	printf("Reloading the date,please wait ...\n");
	readAccount(account);
	readLog(userlog);
	
	printf("Welcome\n");
	printf("Login(0) or Registered(1)?\n");
	int tag=Choose();
	if(tag==0)
	{
		Login(account,userlog);
	}
	else
	{
		Registered(account,userlog);
		Login(account,userlog);
	}
	return 0;
}
void seeStrc(Userlog *userlog)
{
	Userlog *p;
	p=userlog->next;
	while(p!=NULL)
	{
		printf("Expenses=%d\t",p->expenses );
		printf("Revenue=%d\t",p->revenue );
		printDate(p->date);
		p=p->next;
	}
}
int readId(FILE *fp,int *temp)
{
	int id=0;
	while(*temp!=10)
	{
		if(*temp<=57&&*temp>=48)
		{
			id=id*10+numSiwtch(temp);
		}
		*temp=fgetc(fp);
	}
	*temp=fgetc(fp);
	return id;
}
void readDate(FILE *fp,Userlog *userlog,int *temp)
{
	int date[8];
	int count=0;
	while(*temp!=10)
	{
		if(*temp<=57&&*temp>=48)
		{
			date[count++]=numSiwtch(temp);
		}
		if(count==8)
		{
			reDate(userlog->date,date);
			// printDate(userlog->date);	
		}
		*temp=fgetc(fp);
	}
	*temp=fgetc(fp);
}
void readEx(FILE *fp, Userlog *userlog,int *temp)
{
	int Ex[20];
	int count=0;
	while(*temp!=35)
	{
		if(*temp<=57&&*temp>=48)
		{
			Ex[count++]=numSiwtch(temp);
		}
		*temp=fgetc(fp);
	}
	*temp=fgetc(fp);
	int sum=0;
	for(int i=0;i<count;i++)
	{
		sum=sum+Ex[i]*pow(10,count-1-i);
	}
	userlog->expenses=sum;
	// printf("exsum=%d\n",sum );
}
void readRe(FILE *fp, Userlog *userlog,int *temp)
{
	int Re[20];
	int count=0;
	while(*temp!=10)
	{	
		if(*temp<=57&&*temp>=48)
		{
			Re[count++]=numSiwtch(temp);
		}
		*temp=fgetc(fp);
	}
	*temp=fgetc(fp);
	int sum=0;
	for(int i=0;i<count;i++)
	{
		sum=sum+Re[i]*pow(10,count-1-i);
	}
	userlog->revenue=sum;
	// printf("resum=%d\n",sum );
}
void init_array(int array[20])
{
	for (int i = 0; i < 20; ++i)
	{
		array[i]=0;
	}
}
void idCount(int idArray[20],int id)
{
	for(int i=0;i<20;i++)
	{
		if(id==i)
		{
			idArray[i]++;
		}
	}
}
void readLog(Userlog *userlog[20])
{
	FILE *fp=fopen("log.txt","r");
	int *temp;
	temp=(int*)malloc(sizeof(int));
	*temp=fgetc(fp);
	int idArray[20];
	init_array(idArray);
	while(*temp!=-1)
	{
		Userlog *head;
		head=init_userlog();
		int id=readId(fp,temp);
		idCount(idArray,id);
		if(idArray[id]==1)
		{
			userlog[id]=init_userlog();
		}
		readDate(fp,head,temp);
		readEx(fp,head,temp);
		readRe(fp,head,temp);
		head->next=userlog[id]->next;
		userlog[id]->next=head;
		// seeStrc(userlog[id]);
	}
	// seeStrc(userlog[0]);
}
void CheckExDate(Userlog *userlog,int maxEx)
{
	Userlog *p;
	p=userlog->next;
	while(p!=NULL)
	{
		if(p->expenses==maxEx)
		{
			printDate(p->date);
			break;
		}
		p=p->next;
	}
}
void CheckReDate(Userlog *userlog,int maxRe)
{
	Userlog *p;
	p=userlog->next;
	while(p!=NULL)
	{
		if(p->revenue==maxRe)
		{
			printDate(p->date);
			break;
		}
		p=p->next;
	}
}
void Statistics(Userlog *userlog)
{
	Userlog *p;
	p=userlog->next;
//	p=init_userlog();
	int sumEx=0;
	int sumRe=0;
	int maxEx=p->expenses;
	int maxRe=p->revenue;
	int label=0;
	while(p->next!=NULL)
	{
		maxEx=max(p->expenses,p->next->expenses);
		maxRe=max(p->revenue,p->next->revenue);
		sumEx+=p->expenses;
		sumRe+=p->revenue;
		p=p->next;
		label=1;
	}
	if(label==1)
	{
		sumEx+=p->expenses;
		sumRe+=p->revenue;
		printf("The max of expenses is %d ",maxEx);
		CheckExDate(userlog,maxEx);
		printf("The max of revenue is %d ",maxRe);
		CheckReDate(userlog,maxRe);
		printf("Your cumulative expenditure is %d\n",sumEx );
		printf("Your cumulative revenue is %d\n",sumRe );
	}
//	free(p);
}
void Inquire(Account *account,Userlog *userlog[20],int date[8],int userId,Userlog *front)
{
	printf("userId=%d\n",userId );
	int result=0;
	Userlog *p;
	front=userlog[userId];
	printf("front->next->revenue=%d\n",front->next->revenue );
	if(userlog[userId]==NULL)
	{
		p=NULL;
	}
	else
	{
		p=userlog[userId]->next;
	}
	while(p!=NULL)
	{
		result=diff_date(p->date,date);
		if(result==1)
		{
			printDate(date);
			printf("expenses : %d\n",p->expenses);
			printf("revenue :  %d\n",p->revenue );
			break;
		}
		front=p;
		p=p->next;
	}
	printf("front->revenue=%d\n",front->revenue );
	if(result==0)
	{
		printf("Sorry,nothing can be founded!\n");
		Operation(account,userlog,userId);
	}
}
void Add(Userlog *userlog[20],int chmod)
{
	printf("chmod=%d\n",chmod );
	// FILE *fp=fopen("log.txt","a+");
	// userlog[chmod]=init_userlog();
	Userlog *p;
	p=init_userlog();
	// fprintf(fp, "%s:%d\n","UserId",chmod );
	printf("Please input the date\n");
	Assign_date(p->date);
	// putDate(fp,p->date);
	printf("Please input the expenses\n");
	scanf("%d",&p->expenses);
	// fprintf(fp, "Expenses=%d#",p->expenses);
	printf("Please input the revenue\n");
	scanf("%d",&p->revenue);
	// fprintf(fp, "Revenue=%d\n",p->revenue );
	// fclose(fp);
	p->next=userlog[chmod]->next;
	userlog[chmod]->next=p;
	// printf("userlog[chmod]->next->expenses=%d\n",userlog[chmod]->next->expenses );
	printDate(userlog[chmod]->next->date);
	// seeStrc(userlog[chmod]);
	printf("Add Successfully!\n");
}
void Delete(Userlog *userlog[20],int chmod,Userlog *front)
{
	if(chmod==-1)
	{
		if(front->next!=NULL&&front->next->next!=NULL)
		{
			front->next=front->next->next;
		}
		else
		{
			front->next=NULL;
		}
		printf("Delete Successfully!\n");
	}
	else
	{
		printf("Sorry ,you don't have permisson to this operate\n");
	}
}
void Modify(Userlog *userlog[20],int chmod, Userlog *front)
{
	if(chmod==-1)
	{
		printf("Please input the expenses you want to modify \n");
		scanf("%d",&front->next->expenses);
		printf("Please input the revenue you want to modify\n");
		scanf("%d",&front->next->revenue);
		printf("Please input the date you want to modify\n");
		Assign_date(front->next->date);
		printf("Modify Successfully!\n");
	}
	else
	{
		printf("Sorry ,you don't have permisson to this operate\n");
	}

}
void loopMain(Account *account,Userlog *userlog[20],int userId,int chmod,Userlog *front)
{
	int choice=0;
	int date[8];
	seeStrc(userlog[userId]);
	Statistics(userlog[userId]);
	printf("Please input date you want to operation\n");
	Assign_date(date);
	Inquire(account,userlog,date,userId,front); 
	printf("front->expenses=%d\n",front->expenses );
	printf("1.add    \t2.delete \t3.modify \t4.inquire\t5.quit   \n");
	scanf("%d",&choice);
	if(choice==1)
	{
		Add(userlog,userId);
		loopMain(account,userlog,userId,chmod,front);
	}
	if(choice==2)
	{
		Delete(userlog,chmod,front);
		loopMain(account,userlog,userId, chmod,front);
	}
	if(choice==3)
	{
		Modify(userlog,chmod,front);
		loopMain(account,userlog,userId, chmod,front);
	}
	if(choice==4)
	{
		Statistics(userlog[userId]);
		Inquire(account,userlog,date,chmod,front);
		loopMain(account,userlog,userId, chmod,front);
	}
	if(choice==5)
	{
		putFile(account,userlog);
		exit(1);
	}
	if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=4)
	{
		printf("Your input is wrong!\n");
		loopMain(account,userlog,userId, chmod,front);
	}
}
void loopUser(Account *account,Userlog *userlog[20],int chmod,Userlog *front)
{
	int choice=0;
	int date[8];
	printf("What do you want to do?\n");
	printf("1.inquire\t2.add    \t3.quit    \n");
	scanf("%d",&choice);
	if(choice==1)
	{
		Statistics(userlog[chmod]);
		printf("Please input date you want to operation\n");
		Assign_date(date);
		Inquire(account,userlog,date,chmod,front); 
		loopUser(account,userlog,chmod,front);
	}
	if(choice==2)
	{
		Add(userlog,chmod);
		loopUser(account,userlog,chmod,front);
	}
	if(choice==3)
	{
		putFile(account,userlog);
		exit(0);
	}
	if(choice!=1 && choice!=2 &&choice!=3)
	{
		printf("Your choice is wrong,please input again\n");
		loopUser(account,userlog,chmod,front);
	}
}
void Operation(Account *account,Userlog *userlog[20],int chmod)//-1 for admin ,-2 for none,else for user 
{
	Userlog *front;
	// front=init_userlog();
	if(chmod != -2)
	{
		if(chmod==-1)
		{
			int userId=0;
			
			printf("Dear backstage administrator,Welcome you\n");
			printf("Please input the UserId you want to operate\n");
			scanf("%d",&userId);
			loopMain(account,userlog,userId,chmod,front);
		}
		else
		{
			printf("Welcome to you \n");
			loopUser(account,userlog,chmod,front);
		}
	}
	else
	{
		printf("Sorry,username or password isn't right!\n");
	}	
}
void Login(Account *account,Userlog *userlog[20])
{
	int name[6];
	int pwd[6];
	printf("Please input your username\n");
	Assign(name);
	printf("Please input your password\n");
	Assign_pwd(pwd);
	int chmod=Check(account,name,pwd);//-1 for admin ,-2 for none,else for user 
	Operation(account,userlog,chmod);
}
void printDate(int date[8])
{
	printf("Date:");
	for (int i = 0; i < 8; ++i)
	{
		printf("%d",date[i]);
	}
	printf("\n");
}
void Registered(Account *account,Userlog *userlog[20])
{
	account->user[account->usernum]=init_user();
	FILE *fp=fopen("user.txt","a+");
	printf("Please input the username you want to registered\n");
	Assign(account->user[account->usernum]->username);
	fputs("Username:  ",fp);
	putArray(fp,account->user[account->usernum]->username);
	fputs("Password:  ",fp);
	printf("Please input the password you want to registered\n");
	Assign(account->user[account->usernum]->password);
	putArray(fp,account->user[account->usernum]->password);
	fclose(fp);
	userlog[account->usernum]=init_userlog();
	account->usernum++;
	printf("Registered Successfully!\n");
	printf("Transferring to the login screen...\n");
}
int Choose()
{
	int tag=0;
	scanf("%d",&tag);
	if(tag!=1&&tag!=0)
	{
		tag=Choose();
	}
	return tag;
}
void putArray(FILE *fp,int array[MAXSIZE])
{
	for (int i = 0; i < MAXSIZE; ++i)
	{
		fprintf(fp, "%d",array[i]);
	}
	fprintf(fp,"\n");
}
void putDate(FILE *fp,int date[8])
{
	fprintf(fp, "%s","Date:" );
	for (int i = 0; i < 8; ++i)
	{
		fprintf(fp, "%d", date[i]);
	}
	fprintf(fp, "\n" );
}
Admin* init_admin()
{
	Admin *admin;
	admin=(Admin*)malloc(sizeof(Admin));
	int name[MAXSIZE]={1,7,2,8,2,0};
	int pwd[MAXSIZE]={0,0,0,3,2,3};
	FILE *fp=fopen("admin.txt","w+");
	fputs("Username:  ",fp);
	putArray(fp,name);
	fputs("Password:  ",fp);
	putArray(fp,pwd);
	for(int i=0;i<MAXSIZE;i++)
	{
		admin->username[i]=name[i];
		admin->password[i]=pwd[i];
	}
	fclose(fp);
	return admin;
}
User* init_user()
{
	User *user;
	user=(User*)malloc(sizeof(User));
	return user;
}
Account* init_account()
{
	Account *account;
	account=(Account*)malloc(sizeof(Account));
	account->admin=init_admin();
	account->usernum=0;
	return account;
}
void Assign(int array[MAXSIZE])
{
	for(int i=0;i<MAXSIZE;i++)
	{
		scanf("%d",&array[i]);
	}
}
void Assign_pwd(int array[MAXSIZE])
{
	for(int i=0;i<MAXSIZE;i++)
	{
		scanf("%d",&array[i]);
		// printf("\b");
		// printf("*");
	}
}
void Assign_date(int array[8])
{
	for(int i=0;i<8;i++)
	{
		scanf("%d",&array[i]);
	}
}
int diff(int username[MAXSIZE],int name[MAXSIZE])
{
	int label=1;
	for(int i=0;i<MAXSIZE;i++)
	{
		if(username[i]!=name[i])
		{
			label=-1;
			break;
		}
	}
	return label;
}
int diff_date(int date1[8],int date2[8])
{
	int label=1;
	for(int i=0;i<8;i++)
	{
		if(date1[i]!=date2[i])
		{
			label=0;
			break;
		}
	}
	return label;
}
int Check(Account *account,int name[MAXSIZE],int pwd[MAXSIZE])
{
	int chmod=-2;
	int isadmin=diff(account->admin->username,name)+diff(account->admin->password,pwd);
	if(isadmin==2)
	{
		chmod=-1;
	}
	if(isadmin!=2)
	{
		for(int i=0;i<account->usernum;i++)
		{
			chmod=diff(account->user[i]->username,name)+diff(account->user[i]->password,pwd);
			if(chmod==2)
			{
				chmod=i;
				break;
			}
		}
	}
	return chmod;
}
Userlog* init_userlog()
{
	Userlog *userlog;
	userlog=(Userlog*)malloc(sizeof(Userlog));
	userlog->next=NULL;
	return userlog;
}
int numSiwtch(int *temp)
{
	int result=0;
	if(*temp==48)
		result=0;
	if(*temp==49)
		result=1;
	if(*temp==50)
		result=2;
	if(*temp==51)
		result=3;
	if(*temp==52)
		result=4;
	if(*temp==53)
		result=5;
	if(*temp==54)
		result=6;
	if(*temp==55)
		result=7;	
	if(*temp==56)
		result=8;							
	if(*temp==57)
		result=9;
	return result;
}
int readWhile(FILE *fp,int *temp,int array[MAXSIZE])
{
	int tag=0;
	int count=0;
	while(*temp!=-1)
	{
		if(*temp<=57&&*temp>=48)
		{
			array[count]=numSiwtch(temp);
			count++;
		}
		if(count==6)
		{
			tag=1;
			break;
		}
		*temp=fgetc(fp);
	}
	*temp=fgetc(fp);
	return tag;
}
void arrToSt(FILE *fp,Account *account)//
{
	int array[MAXSIZE];
	int *temp;
	temp=(int*)malloc(sizeof(int));
	*temp=fgetc(fp);
	while(*temp!=-1)
	{
		int tag=readWhile(fp,temp,array);	
		if(tag==1)
		{
			account->user[account->usernum]=(User*)malloc(sizeof(User));
			reArray(account->user[account->usernum]->username,array);
			tag=readWhile(fp,temp,array);
			reArray(account->user[account->usernum]->password,array);
			account->usernum++;
		}
		*temp=fgetc(fp);
	}
}
void readAccount(Account *account)
{
	FILE *fp=fopen("user.txt","r");
	rewind(fp);
	arrToSt(fp,account);
}
void reArray(int arr1[MAXSIZE],int arr2[MAXSIZE])
{
	for(int i=0;i<MAXSIZE;i++)
	{
		arr1[i]=arr2[i];
	}
}
void reDate(int date1[8],int date2[8])
{
	for(int i=0;i<8;i++)
	{
		date1[i]=date2[i];
	}
}
int max(int a,int b)
{
	return a>b?a:b;
}
void putFile(Account *account,Userlog *userlog[20])
{
	FILE *fp=fopen("log.txt","w+");
	for(int i=0;i<account->usernum;i++)
	{
		userlog[i]=userlog[i]->next;
		while(userlog[i]!=NULL)
		{
			fprintf(fp, "%s:%d\n","UserId",i );
			putDate(fp,userlog[i]->date);
			fprintf(fp, "Expenses=%d#",userlog[i]->expenses);
			// printf("expenses=%d\n",userlog[i]->expenses);
			fprintf(fp, "Revenue=%d\n",userlog[i]->revenue );
			userlog[i]=userlog[i]->next;
		}
	}
	fclose(fp);
}
