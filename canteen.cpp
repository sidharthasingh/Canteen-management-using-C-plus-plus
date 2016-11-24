#include<conio.h>
#include<stdlib.h>
#include<iomanip>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<windows.h>
#include<fstream>

void clrscr()
{
	system("cls");
}


using namespace std;
void gotoxy(int x,int y)
{
	static HANDLE h=NULL;
	if(!h)
	h=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c={x,y};
	SetConsoleCursorPosition(h,c);
}



class canteen
{
int sno,rate;
char item[100];
public:

void report();	//function to show data in tabular format

void input()
{
clrscr();
cout<<"\n\n\t ENTER SERIAL NO. , ITEM NAME , RATE\n\n\t ";
cin>>sno;
cout<<"\t";
gets(item);
cout<<"\t";
cin>>rate;
}
void output()
{
cout<<"\t"<<sno<<"\t"<<item<<"\t"<<rate;
}

int retsn()
{
return sno;
}
int retrate()
{
return rate;
}
char* retitem()
{
return item;
}

};
void canteen::report()
{
	cout<<sno<<"          "<<setw(15)<<item<<"      "<<setw(15)<<rate<<endl;
}

void select_items()
{
clrscr();
int code,add=0;
{
	canteen ac;
	ifstream fin("kevin.dat",ios::binary);
	cout<<"\n\n\t\tCANTEEN MENU LIST\n\n";
	cout<<"====================================================\n";
	cout<<"SERIAL NO.             ITEM                   RATE\n";
	cout<<"====================================================\n";
	while(fin.read((char *) &ac, sizeof(ac)))
	{
		ac.report();
	}
	fin.close();
}

cout<<"\n\n\tPLEASE SELECT ITEMS YOU WANT TO BUY";
cout<<"\n";
int m,x;
ifstream fin;
ofstream fout("menu.dat",ios::binary);
canteen s;
do
{
fin.open("kevin.dat",ios::binary);
cout<<"\n Enter serial no.of item you want to buy  ";
cin>>x;
fin.seekg(0,ios::beg);
int flag=0;
while(fin.read((char*)&s,sizeof(s)))
	{
		if (x==s.retsn())
		{
		flag=1;
		cout<<"\n\n\tENTERED DETAILS EXITS ";
		break;
		}
	}
fin.close();
if (flag==0)
   {
      cout<<"SERIAL NO. DOES NOT MATCH";

   }
else
fout.write((char*)&s,sizeof(s));
cout<<"\n\n\t IF SELECTION IS COMPLETE PRESS 1 ELSE 0 ";
cin>>m;
flag=0;
}
while(m!=1);

     fout.close();
      if(m==1)
	      {
	       ifstream fin("menu.dat",ios::binary);
	       canteen p;
cout<<"\n\n\t                      SELECTION MADE BY YOU ARE.......	";
cout<<"\n";
while(fin.read((char*)&p,sizeof(p)))
{
add=add+p.retrate();
cout<<"\n";
  p.output();
}
cout<<"\n";
cout<<"\n                     YOUR BILL IS   Rs " <<add;
cout<<"\n";
cout<<"\n***********************THANK YOU******************************";
getch();
}
}
//***************************************************************
// function to read all records from file
//****************************************************************

void display_all()
{
	canteen ac;
	ifstream fin("kevin.dat",ios::binary);
	cout<<"\n\n\t\tCANTEEN MENU LIST\n\n";
	cout<<"====================================================\n";
	cout<<"SERIAL NO.             ITEM                   RATE\n";
	cout<<"====================================================\n";
	while(fin.read((char *) &ac, sizeof(ac)))
	{
		ac.report();
	}
	fin.close();
}
//***************************************************************
// function to write in file
//****************************************************************


void write_product()
{
canteen s,t;
ifstream fin("kevin.dat",ios::binary);
int flag=1;
s.input();
// Validation for avoiding  dupication of record
	while(fin.read((char*)&t,sizeof(s)))
	{
		if (t.retsn()==s.retsn())
		{
		flag=0;
		cout<<"\n\n\tSERIAL NO. ALREADY OCCUPIED WITH AN ITEM";
		break;
		}
	}
fin.close();
if (flag==1)
{
ofstream fout("kevin.dat",ios::app|ios::binary);
fout.write((char*)&s,sizeof(s));
fout.close();
}
}

//***************************************************************
// function to search record from file
//***************************************************************
void search_product()
{
int flag=0;
ifstream fin("kevin.dat",ios::binary);
canteen s;
int sn;
cout<<"\n\n\n\tENTER THE SERIAL NO. OF ITEM  ";
cin>>sn;
while(fin.read((char*)&s,sizeof(s)))
{
if(s.retsn()==sn)
{
s.output();
flag=1;
cout<<"\n\n\n\t FOUND";
break;
} }
fin.close();

if(flag==0)
cout<<"\n\n\n\t NOT FOUND";
}
//***************************************************************
// function to delete record of file
//****************************************************************

void delete_product()
{
{
	canteen ac;
	ifstream fin("kevin.dat",ios::binary);
	cout<<"\n\n\t\tCANTEEN MENU LIST\n\n";
	cout<<"====================================================\n";
	cout<<"SERIAL NO.             ITEM                   RATE\n";
	cout<<"====================================================\n";
	while(fin.read((char *) &ac, sizeof(ac)))
	{
		ac.report();
	}
	fin.close();
}
ifstream fin("kevin.dat",ios::binary);
ofstream fout("kevout.dat",ios::binary);
canteen s;
int rn,flag=0;
cout<<"\n\nENTER SERIAL NUMBER YOU WANT TO MODIFY";
cin>>rn;
while(fin.read((char*)&s,sizeof(s)))
{
if(s.retsn()==rn)
{
s.output();
flag=1;
}
else fout.write((char*)&s,sizeof(s));
}
fin.close();
fout.close();
remove("kevin.dat");
rename("kevout.dat","kevin.dat");
if(flag==0)
cout<<"\n\n\n\tNOT FOUND";
}

//***************************************************************
// function to modify record of file
//****************************************************************

void modify_product()
{
ifstream fin("kevin.dat",ios::binary);
ofstream fout("kevout.dat",ios::binary);
canteen s;
int rn,flag=0;
cout<<"\n\nENTER SERIAL NUMBER YOU WANT TO MODIFY";
cin>>rn;
while(fin.read((char*)&s,sizeof(s)))
{
if(s.retsn()==rn)
{
s.output();
s.input();
flag=1;
}
fout.write((char*)&s,sizeof(s));
}
fin.close();
fout.close();
remove("kevin.dat");
rename("kevout.dat","kevin.dat");
if(flag==0)
cout<<"\n\n\n\tNOT FOUND";
}
//***************************************************************
// CUSTOMER MENU FUNCTION
//****************************************************************
void cust_menu()
{
clrscr();
char ch2;
cout<<"\n\n\n\n\tCUSTOMER MENU";
cout<<"\n\n\t1:DISPLAY ITEMS";
cout<<"\n\n\t2:SELECT ITEMS";
cout<<"\n\n\t3:EXIT";
cout<<"\n\n\tPLEASE ENTER YOUR CHOICE (1-3)";
cin>>ch2;
switch(ch2)
{
case '1': display_all();break;
case '2': select_items();break;
case '3': break;
default:cust_menu();
}
getch();
}
//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{
clrscr();
//************************************************************************
//                       FUNCTION FOR THE PASSWORD
//************************************************************************
	{
	clrscr();
	char pass[3200],t;
	int i=0,k,flag=0;
	cout<<"\n Please enter the password: ";
	randomize();//helps in generating random char everytime loops executes
	while(1)
		{
		k=getch();
		if(k==13)//code for 'enter'
			{
			break;
			}
		else
			{
			pass[i]=k;
			}
		t=random(58)+65;//to chose char within alphabet ascaii value
		cout<<t;        //alphabets lie between 65 and 122
		i++;
		}
	pass[i]='\0'; //to make it string
	if(strcmpi(pass,"hithisissid")==0)
		{
		cout<<"\n\n Access Granted.\n\n\n\n\n\t";


		flag=1;//to specify that password is true
		}
	else
		{
		cout<<"\n Access Denied.";
		}
	getch();
	if (flag==0)
	exit(0);
	}
char ch1;
cout<<"\n\n\n\n\n\tADMIN MENU";
cout<<"\n\n\t1.CREATE PRODUCT";
cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
cout<<"\n\n\t3.MODIFY PRODUCT";
cout<<"\n\n\t4.SEARCH PRODUCT";
cout<<"\n\n\t5.DELETE PRODUCT";
cout<<"\n\n\t6.EXIT";
cout<<"\n\n\tPLEASE ENTER YOUR CHOICE (1-6) ";
cin>>ch1;
switch(ch1)
{
case '1': write_product();break;
case '2': display_all();break;
case '3': modify_product();break;
case '4': search_product();break;
case '5': delete_product();break;
case '6': break;
default:admin_menu();
}
getch();
}

//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void welcome_note()
{
clrscr();
int ch;
gotoxy(18,26);
cout<<"\n\n\n\n\n\n\n\n\n\t\t\t     WELCOME TO CANTEEN      ";
gotoxy(20,36);
cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\tMADE BY : SiDHARtHA SINGH";
cout<<"\n\n\tSCHOOL : OXFORD SR. SEC. SCHOOL";
 getch();
 }
void biblio()
{
clrscr();
cout<<"\n\n\n\n\n\t\t\t  THANK YOU FOR THE VISIT";
}
void main()
{
welcome_note();
int ch;
clrscr();
do
{
clrscr();
cout<<"\n\n\n\t\t\t\tMAIN MENU";
cout<<"\n\n\n\n\n\t1.FOR CUSTOMERS";
cout<<"\n\n\t2.FOR MANAGEMENT";
cout<<"\n\n\t3.EXIT";
cout<<"\n\n\t\tENTER YOUR CHOICE(1-3)_";
cin>>ch;
switch(ch)
{

case 2:admin_menu();break;
case 1:cust_menu();break;
}
}
while(ch!=3);
biblio();
getch();
}


