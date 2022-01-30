#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<iostream.h>
#include <stdlib.h>

void deposit(void);
void addrecord();
void delrecord();
void modrecord();
void disprecord();
void dispall();
void withdraw();
float w,z;

class account
{
int accountno,cls;
char name[30];
float deposit,withdraw;
public:
account()
{
deposit=withdraw=0;
}
int giveaccountno()
{
return accountno;
}
void getdata(int mrno)
{
accountno=mrno+1;
cout<<"ACCOUNT NUMBER        ::  ";
cout<<accountno<<endl;
cout<<"ENTER YOUR NAME       ::  ";
gets(name);
cout<<"ENTER INITIAL AMOUNT  ::Rs  ";
cin>>deposit;
}
void withdrawal(int m)
{
cout<<"\nAMOUNT BEFORE WITHDRAWING::Rs  "<<deposit<<"\t";
deposit=deposit-m;
cout<<"\nAMOUNT AFTER WITHDRAWING::Rs  "<<deposit;
}
void deposital(int m)
{
cout<<"\nAMOUNT BEFORE DEPOSIT::Rs  "<<deposit<<"\t";
deposit=deposit+m;
cout<<"\nAMOUNT AFTER DEPOSIT ::Rs  "<<deposit;
}
void dispdata()
{
int scrnt=0;
if(scrnt==1)
{
clrscr();
cout<<"DISPLAY ALL MENU";
scrnt=0;
}
cout<<"\nACCOUNT NUMBER              ::";
cout<<accountno;
cout<<"\nNAME OF DEPOSITER           ::";
cout<<name;
cout<<"\nBALANCE                     ::Rs  ";
cout<<deposit;
scrnt++;
}
};
void main()
{
int menuch;
do
{
clrscr();
cout<<"\nMAIN MENU";
cout<<"\n1.CREATING A NEW ACCOUNT     ";
cout<<"\n2.CLOSING AN ACCOUNT ";
cout<<"\n3.MODIFYING AN ACCOUNT  ";
cout<<"\n4.DISPLAYING AN ACCOUNT ";
cout<<"\n5.DISPLAYING ALL RECORDS ";
cout<<"\n6.WITHDRAWING AMOUNT";
cout<<"\n7.DEPOSITING AMOUNT";
cout<<"\n8.EXIT     ";
cout<<"\nENTER YOUR CHOICE  ";
cin>>menuch;

switch(menuch)
{
case 1:addrecord();break;
case 2:delrecord();break;
case 3:modrecord();break;
case 4:disprecord();break;
case 5:dispall();break;
case 6:withdraw();break;
case 7:deposit();break;
case 8:cout<<"THANK YOU......";
       getch();
       exit(0);
       break;
default:cout<<"WRONG CHOICE........ENTER AGAIN";getch();
}

}
while(menuch!=8);
}
void addrecord()
{
account obj_1,obj_2;
fstream fout;
fout.open("PGHM",ios::in|ios::binary);
int recsize=sizeof(account);
fout.seekg(0,ios::end);
fout.seekg(-1*recsize,ios::cur);
fout.read((char*)&obj_1,recsize);
int mrno=obj_1.giveaccountno();
fout.close();
clrscr();
cout<<"ADD MENU\n";
obj_2.getdata(mrno);
fout.open("PGHM",ios::app|ios::binary);
fout.write((char*)&obj_2,recsize);
cout<<"RECORD ADDED TO DATABASE\n";
cout<<"Press any key tocontinue...\n ";
getch();
fout.close();
}
void dispall()
{
account obj_3;
fstream fout;
int recsize=sizeof(account);
int countrec=0;
clrscr();
cout<<"DISPLAY ALL MENU \n";
fout.open("PGHM",ios::in);
if(!fout)
{
cout<<"FILE OPEN ERROR  ";getch();return;}
while(fout.read((char*)&obj_3,recsize))
{
obj_3.dispdata();
countrec++;
cout<<"\nPRESS ANY KEY FOR NEXT....\n";
getch();
}
clrscr();
cout<<"END OF FILE......"<<endl<<"TOTALNUMBER OF RECORDS..."<<countrec<<endl;
cout<<"Press any key......";
getch();
fout.close();}
void disprecord()
{
account obj_4;
fstream fout;
int mrno,flag=0;
int recsize=sizeof(account);
clrscr();      cout<<"DISPLAY A RECORD MENU\n";
fout.open("PGHM",ios::in);
if(!fout)
{
cout<<"FILE OPEN ERROR  ";getch();return;}
cout<<"ENTER  THE ACCOUNT NUMBER  ";cin>>mrno;
while(fout.read((char*)&obj_4,recsize))
{
if (obj_4.giveaccountno()==mrno)
{
obj_4.dispdata();
cout<<"\nPress any key.....\n";
flag=1;break;
}
}
if(flag==0)
{
cout<<"NO SUCH ACCOUNT EXIST \n ";
cout<<"Press any key......\n";
}
getch();
fout.close();
}
void delrecord()
{
account obj_5;
fstream fout,temp;
int mrno,flag;
int recsize=sizeof(account);
clrscr();
cout<<"CLOSING ACCOUNT MENU\n";
fout.open("PGHM",ios::in);
temp.open("temp",ios::app|ios::binary);
cout<<"ENTER THE ACCOUNT NUMBER ";
cin>>mrno;
while(fout.read((char*)&obj_5,recsize))
{
if(obj_5.giveaccountno()==mrno)
{
obj_5.dispdata();
char confirm;
cout<<"\nARE YOU SURE TO DELETE IT(Y/N)..";cin>>confirm;
if(confirm=='Y'||confirm=='y')
{
fout.read((char*)&obj_5,recsize);
cout<<"RECORD DELETED FORM DATABASE\n";
cout<<"press any key....\n";
flag=1;
if(!fout)
break;
}
flag=1;
}
temp.write((char*)&obj_5,recsize);}
fout.close();
temp.close();
remove("PGHM");
rename("temp","PGHM");
if(flag==0)
{
cout<<"NO SUCH ACCOUNT EXIST";
cout<<"Press any key.....";
}
getch();
}
void modrecord()
{
account obj_6;
fstream fout;
int mrno,flag=0;
int recsize=sizeof(account);
clrscr();
cout<<"MODIFYING RECORD MENU\n";
fout.open("PGHM",ios::in|ios::out|ios::binary);
fout.seekg(ios::beg);
cout<<"ENTER RECORD NUMBER  \n";
cin>>mrno;
while(fout.read((char*)&obj_6,recsize))
{
if(obj_6.giveaccountno()==mrno)
{
clrscr();
cout<<"MODIFY MENU\n";
obj_6.dispdata();
int tmprno=obj_6.giveaccountno()-1;
account obj_7;
cout<<"\nENTER NEW DATA\n";
obj_7.getdata(tmprno);
char confirm;
cout<<"ARE YOU SURE(Y/N)";
cin>>confirm;
if(confirm=='Y'||confirm=='y')
{
fout.seekg(-1*recsize,ios::cur);
fout.write((char*)&obj_7,recsize);
cout<<"RECORD MODIFIED\n";
cout<<"Press any key.....";
flag=1;
}
}
if(flag==0)
{
cout<<"NO SUCH RECORD EXIST";
cout<<"Press any key.....";
}
}
fout.close();
getch();
}
void withdraw()
{
account obj_9;
fstream fout;
int mrno=0;
int recsize=sizeof(account);
clrscr();
cout<<"WITHDRAWAL MENU\n";
fout.open("PGHM",ios::in|ios::out|ios::binary);
fout.seekg(ios::beg);
cout<<"ENTER ACCOUNT NUMBER  ";
cin>>mrno;
while(fout.read((char*)&obj_9,recsize))
{
if(obj_9.giveaccountno()==mrno)
{
clrscr();
cout<<"\nENTER THE AMOUNT TO BE WITHDRAWN::Rs ";
cin>>w;
obj_9.withdrawal(w);
fout.seekg(-1*recsize,ios::cur);
fout.write((char*)&obj_9,recsize);
}
}
fout.close();
getch();
}
void deposit(void)
{
account obj_10;
fstream fout;
int mrno=0;
int recsize=sizeof(account);
clrscr();
cout<<"DEPOSITAL MENU\n";
fout.open("PGHM",ios::in|ios::out|ios::binary);
fout.seekg(ios::beg);
cout<<"ENTER ACCOUNT NUMBER  ";
cin>>mrno;
while(fout.read((char*)&obj_10,recsize))
{
if(obj_10.giveaccountno()==mrno)
{
clrscr();
cout<<"ENTER THE AMOUNT TO BE DEPOSITED ::Rs ";
cin>>w;
obj_10.deposital(w);
fout.seekg(-1*recsize,ios::cur);
fout.write((char*)&obj_10,recsize);
}
}
fout.close();
getch();
}
