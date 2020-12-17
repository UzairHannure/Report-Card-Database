#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
class student
{
    int rollno;
    char name[100];
    int pmarks,cmarks,mmarks,emarks,csmarks;
    float per;
    char grade;
    int std;
    void calculate()
    {
	textcolor(6);
	per=(pmarks+cmarks+mmarks+emarks+csmarks)/5.0;
	if(per>=71)
	    grade='A';
	else if(per>=51 && per<71)
	    grade='B';
	else if(per>=41 && per<51)
	    grade='C';
	else
	    grade='F';
    }
public:
    student()
    {
	textcolor(6);
	rollno=0;
	pmarks=0;
	cmarks=0;
	mmarks=0;
	csmarks=0;
	per=0.0;
	std=0;
    }
    void getdata()
    {
	textcolor(6);
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	gets(name);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>pmarks;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>cmarks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>mmarks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>emarks;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>csmarks;
	calculate();
    }

    void showdata()
    {
	textcolor(6);
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<pmarks;
	cout<<"\nMarks in Chemistry : "<<cmarks;
	cout<<"\nMarks in Maths : "<<mmarks;
	cout<<"\nMarks in English : "<<emarks;
	cout<<"\nMarks in Computer Science :"<<csmarks;
	cout<<"\nPercentage of student is  :"<<setprecision(2)<<per;
	cout<<"\nGrade of student is :"<<grade;
    }

    void show_tabular()
    {
	textcolor(6);
	cout<<rollno<<setw(12)<<name<<setw(10)<<pmarks<<setw(3)<<cmarks<<setw(3)<<mmarks<<setw(3)<<emarks<<setw(3)<<csmarks<<setw(6)<<setprecision(3)<<per<<"     "<<grade<<endl;
    }
    int  retrollno()
    {
	textcolor(6);
	return rollno;
    }
};
fstream fp;
student st;
void write_student()
{
    textcolor(6);
    fp.open("student.dat",ios::out|ios::app);
    st.getdata();
    fp.write((char*)&st,sizeof(student));
    fp.close();
    cout<<"\n\nstudent record Has Been Created ";
    getch();
}
void display_all()
{
    textcolor(6);
    clrscr();
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD \n\n";
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
	textcolor(6);
	st.showdata();
	cout<<"\n\n************************************\n";
	getch();
	textcolor(6);
    }
    fp.close();
    getch();
    textcolor(6);
}
void display_sp(int n)
{
    textcolor(6);
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
    textcolor(6);
	if(st.retrollno()==n)
	{
	    clrscr();
	    st.showdata();
	    flag=1;
	}
    }
    fp.close();
    if(flag==0)
	cout<<"\n\nrecord not exist";
    getch();
}
void modify_student()
{
    textcolor(6);
    int no,found=0;
    clrscr();
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The roll number of student";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
	if(st.retrollno()==no)
	{
	    st.showdata();
	    cout<<"\nPlease Enter The New Details of student"<<endl;
	    st.getdata();
	    int pos=-1*sizeof(st);
	    fp.seekp(pos,ios::cur);
	    fp.write((char*)&st,sizeof(student));
	    cout<<"\n\n\t Record Updated";
	    found=1;
	}
    }
    fp.close();
    if(found==0)
	cout<<"\n\n Record Not Found ";
    getch();
}
void delete_student()
{
    textcolor(6);
    int no;
    clrscr();
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The roll number of student You Want To Delete";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
    {
	if(st.retrollno()!=no)
	{
	    fp2.write((char*)&st,sizeof(student));
	}
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}
void class_result()
{
    textcolor(6);
    clrscr();
    fp.open("student.dat",ios::in);
    if(!fp)
    {
	cout<<"ERROR FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
	cout<<"\n\n\n Program is closing ....";
	getch();
	exit(0);
    }

    cout<<"\n\n\t\tCLASS RESULT \n\n";
    cout<<"****************************************************\n";
    cout<<"Roll No. Name          P  C  M  E  CS   %    Grade\n";
    cout<<"****************************************************\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
	st.show_tabular();
    }
    fp.close();
    getch();
}

void result()
{
    textcolor(6);
    int ans,rno;
    char ch;
    clrscr();
    cout<<"\n\n\nRESULT MENU";
    cout<<"\n\n\n1. Class Result\n\n2. Student Report Card\n\n3.Back to Main Menu";
    cout<<"\n\n\nEnter Choice 1/2 ";
    cin>>ans;
    switch(ans)
    {
    case 1 :
	class_result();
	break;
    case 2 :
    {
    char ans='y';
	do
	{
	    clrscr();
	    cout<<"\n\nEnter Roll Number Of Student : ";
	    cin>>rno;
	    display_sp(rno);
	    cout<<"\n\nDo you want to See More Result y/n";
	    cin>>ans;
	}
	while(ans=='y'||ans=='Y');

	break;
    }
    case 3:
	break;
    default:
	cout<<"\a";
    }
}
void intro()
{
    textcolor(6);
    clrscr();
    cout<<endl<<endl<<endl;
    cout<<"\n\n\n\n\n\n\t\t\t            CLASS";
    cout<<"\n\t\t\t         REPORT CARD";
    cout<<"\n\t\t\t         DATA SYSTEM";
    cout<<"\n\t\t\t           PROJECT";
    cout<<"\n\n\n\n\t\t\t  MADE BY : UZAIR HANNURE ";
    cout<<"\n\t\t\t          CLASS 12-A      ";
    getch();

}
void entry_menu()
{
    textcolor(6);
    clrscr();
    char ch2;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
  //  cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t2.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t3.MODIFY STUDENT RECORD";
    cout<<"\n\n\t4.DELETE STUDENT RECORD";
    cout<<"\n\n\t5.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice ";
    ch2=getche();
    switch(ch2)
    {
    case '1':
	clrscr();
	write_student();
	break;
  /*  case '2':
	display_all();
	break;*/
    case '2':
	int num;
	clrscr();
	cout<<"\n\n\tPlease Enter The roll number ";
	cin>>num;
	display_sp(num);
	break;
    case '3':
	modify_student();
	break;
    case '4':
	delete_student();
	break;
    case '5':
	break;
    default:
	cout<<"\a";
	entry_menu();
    }
}
void main()
{
    textcolor(6);
    char ch;
    intro();
    do
    {
	clrscr();
	cout<<"\n\n\n\tMAIN MENU";
	cout<<"\n\n\t1. RESULTS MENU";
	cout<<"\n\n\t2. ADD/MODIFY MENU";
	cout<<"\n\n\t3. EXIT";
	cout<<"\n\n\tPlease Select Your Option 1,2,3 ";
	ch=getch();
	switch(ch)
	{
	case '1':
	    clrscr();
	    result();
	    break;
	case '2':
	    entry_menu();
	    break;
	case '3':
	    exit(0);
	default :
	    cout<<"\a";
	}
    }
    while(ch!='3');
}