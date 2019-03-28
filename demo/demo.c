#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
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
void Assign_date(int array[8]);
int diff(int username[MAXSIZE],int name[MAXSIZE]);
int diff_date(int date1[8],int date2[8]);
int Check(Account *account,int name[MAXSIZE],int pwd[MAXSIZE]);
void printDate(int date[8]);
void Inquire(Userlog *userlog[20],int date[8],int chmod,Userlog *front);
void Add(Userlog *userlog[20],int chmod);
void Delete(Userlog *userlog[20],int chmod,Userlog *front);
void Modify(Userlog *userlog[20],int chmod, Userlog *front);
void Operation(Userlog *userlog[20],int chmod);
void Login(Account *account,Userlog *userlog[20]);
void Registered(Account *account);
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
int readId(FILE *fp,int *temp,Userlog *userlog)
{
	int id=0;
	while(temp!=10)
	{
		if(*temp<=57&&*temp>=48)
		{
			id=id*10+numSiwtch(temp);
		}
	}
	return id;
}
void readDate(Userlog *userlog,int *temp)
{
	int date[8];
	int count=0;
	while(temp!=10)
	{
		if(*temp<=57&&*temp>=48)
		{
			date[count++]=numSiwtch(temp);
		}
		if(count==8)
		{
			reDate(userlog->date,date);
		}
	}
}

void readLog(Userlog *userlog[20])
{
	FILE *fp=fopen("log.txt","r");
	int *temp;
	*temp=fgetc(fp);
	int id=readId(fp,temp);
	userlog[id]=init_userlog();
	readDate();
	readEx();
	readRe();
}

int main(int argc, char const *argv[])
{
	Account *account;
	Userlog *userlog[20];
	account=init_account();
	readAccount(account);
	printf("Welcome\n");
	printf("Login(0) or Registered(1)?\n");
	int tag=Choose();
	if(tag==0)
	{
		Login(account,userlog);
	}
	else
	{
		Registered(account);
		Login(account,userlog);
	}
	return 0;
}
void Inquire(Userlog *userlog[20],int date[8],int usrId,Userlog *front)
{
	int result=0;
	while(userlog[usrId]!=NULL)
	{
		front=userlog[usrId];
		result=diff_date(userlog[usrId]->date,date);
		if(result==1)
		{
			printDate(date);
			printf("expenses : %d\n",userlog[usrId]->expenses);
			printf("revenue :  %d\n",userlog[usrId]->revenue );
			break;
		}
		userlog[usrId]=userlog[usrId]->next;
	}
	if(result==0)
	{
		printf("Sorry,nothing can be founded!\n");
		Operation(userlog,usrId);
	}
}
void Add(Userlog *userlog[20],int chmod)
{
	FILE *fp=fopen("log.txt","a+");
	userlog[chmod]=init_userlog();
	fprintf(fp, "%s:%d\n","UserId",chmod );
	printf("Please input the date\n");
	Assign_date(userlog[chmod]->date);
	putDate(fp,userlog[chmod]->date);
	printf("Please input the expenses\n");
	scanf("%d",&userlog[chmod]->expenses);
	fprintf(fp, "Expenses=%d#",userlog[chmod]->expenses);
	printf("Please input the revenue\n");
	scanf("%d",&userlog[chmod]->revenue);
	fprintf(fp, "Revenue=%d\n",userlog[chmod]->revenue );
	fclose(fp);
	userlog[chmod]=userlog[chmod]->next;
	printf("Add Successfully!\n");
}
void Delete(Userlog *userlog[20],int chmod,Userlog *front)
{
	if(chmod==-1)
	{
		front->next=front->next->next;
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
	if(chmod!=-2)
	{

	}
	if(chmod==-2)
	{
		printf("Sorry ,you don't have permisson to this operate\n");		
	}

}
void Operation(Userlog *userlog[20],int chmod)//-1 for admin ,-2 for none,else for user 
{
	Userlog *front;
	// front=init_userlog();
	if(chmod != -2)
	{
		if(chmod==-1)
		{
			int usrId=0;
			int choice=0;
			int date[8];
			printf("Dear backstage administrator,Welcome you\n");
			printf("Please input the UserId you want to operate\n");
			scanf("%d",&usrId);
			printf("Please input date you want to operation\n");
			Assign_date(date);
			Inquire(userlog,date,usrId,front); 
			printf("1.add    \t2.delete \t3.modify \t4.inquire\n");
			scanf("%d",&choice);
		}
		else
		{
			printf("Welcome to you \n");
			int choice=0;
			printf("What do you want to do?\n");
			printf("1.inquire\t2.add\n");
			scanf("%d",&choice);
			if(choice==1)
			{
				int date[8];
				printf("Please input date you want to operation\n");
				Assign_date(date);
				Inquire(userlog,date,chmod,front); 
			}
			if(choice==2)
			{
				Add(userlog,chmod);
			}
			if(choice!=1 && choice!=2)
			{
				printf("Your choice is wrong,please input again\n");
				Operation(userlog,chmod);
			}
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
	Assign(pwd);
	int chmod=Check(account,name,pwd);//-1 for admin ,-2 for none,else for user 
	Operation(userlog,chmod);
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
void Registered(Account *account)
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
void arrToSt(FILE *fp,Account *account)
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