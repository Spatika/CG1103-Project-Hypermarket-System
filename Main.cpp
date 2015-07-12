#include <iostream>
#include <cctype>
#include <Windows.h>
#include <string> 
#include "Controller.h"
using namespace std;

/*

COLOR CODES:

1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE


0 = Black	8 = Gray
1 = Blue	9 = Light Blue
2 = Green	A/10 = Light Green
3 = Aqua	B/11 = Light Aqua
4 = Red	C/12 = Light Red
5 = Purple	D/13 = Light Purple
6 = Yellow	E/14 = Light Yellow
7 = White	F/15 = Bright White


*/

//made changes to UI and main so far....



void gotoxy ( short x, short y )
{
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

string getpass(const char *prompt, bool show_asterisk=true)
{
  const char BACKSPACE=8;
  const char RETURN=13;

  string password;
  unsigned char ch=0;

  cout <<prompt ;

  DWORD con_mode;
  DWORD dwRead;

  HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);

  GetConsoleMode( hIn, &con_mode );
  SetConsoleMode( hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  while(ReadConsoleA( hIn, &ch, 1, &dwRead, NULL) && ch !=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                     cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}


int main()
{
	
	
	controller control;
	
	int chance=0 ;
	int flag = 0 ;
    string username ;
	while(chance < 3)
	{
    system("cls") ;
	system("color 0a") ;

	gotoxy(20,8) ;


	cout << "Username: " ;
    cin >> username ; 
	gotoxy(20,10) ;

	const char *correct_password="CiCm5";

    string password=getpass("Password: ", true); // Show asterisks
	
	gotoxy(20, 12) ;	chance++ ; 

    
	if(password==correct_password)
	{
		system("cls") ;
        gotoxy(20,8) ;
		cout << "Welcome to CICMS, " << username << "." ;
		gotoxy(20,10) ;
		cout<<"Press enter to continue...";
		getchar() ;
		getchar();
		flag=1 ;
		control.initiate(username) ;
		break ;
	}
    

	 else if(chance < 3)
	 {
	
	  cout <<"Incorrect password. You have " << 3-chance << " try/tries remaining." ;
	  
	  getchar() ;
	  _getch();
	 }
	}
	 
	 if(chance == 3 && flag == 0)
	{
		HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hcon,12);
		gotoxy(20,14) ;
		cout << "You have exceeded the number of login tries." ;
		gotoxy(20,15) ;
		cout << "Please try again later." ; 
		gotoxy(20,16) ; //new 
		system("PAUSE") ; //new
	}


	getchar() ;

	return 0;
}
























