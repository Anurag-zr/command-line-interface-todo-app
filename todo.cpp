#include <iostream>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
using namespace std;


//prototype of todo class
class Todo{
public:
void addtodo(string);
void deltodo(int);
void marktododone(int);
void listtodo();

};

//global declaration of variable

int count=0;           //to count pending todos
int done=0;           //to count todos  that are done
Todo t;               //Todo class object



string getDate(){

    SYSTEMTIME stime;
    string date,month,year,finalstr;
    GetSystemTime(&stime);

    stringstream sd,sm,sy;
    sd<<stime.wDay;
    sd>>date;
    sm<<stime.wMonth;
    sm>>month;

    sy<<stime.wYear;
    sy>>year;

    finalstr = year+"-"+month+"-"+date;

    return finalstr;
}


void Todo::addtodo(string s){

  cout<<"Added todo: "<<s<<endl;
  ofstream fout;
  fout.open("todo.txt",ios::app);
  fout<<s<<"\n";
  count++;
  fout.close();

}


void Todo::deltodo(int a){
    if(a>count){
        cout<<"Error: todo #"<<a<<" does not exist. Nothing deleted."<<endl;
    }else{
  cout<<"Deleted todo #"<<a<<endl;

   ofstream fout;
  ifstream fin;
     fin.open("todo.txt");
     fout.open("temp.txt");
     string s;

     for(int i=1;i<=count;i++){
        getline(fin,s);
        if(i==a){
            getline(fin,s);
            count--;
        }
        fout<<s<<endl;
     }

       fout.close();
       fin.close();
       remove("todo.txt");
       rename("temp.txt","todo.txt");
    }

    if(count==0){
        remove("todo.txt");
    }
}

void Todo::marktododone(int a){

 if(a>count){
        cout<<"Error: todo #"<<a<<" does not exist."<<endl;
    }else{
  cout<<"Marked todo #"<<a<<" as done."<<endl;

   ofstream fout;
  ifstream fin;
     fin.open("todo.txt");
     fout.open("temp.txt");
     string s;

     for(int i=1;i<=count;i++){
        getline(fin,s);
        if(i==a){
            ofstream fdone;
            fdone.open("done.txt",ios::app);
            fdone<<"x "<<getDate()<<" "<<s<<endl;
            count--;
            done++;
            fdone.close();
             getline(fin,s);
        }
        fout<<s<<endl;
     }

       fout.close();
       fin.close();
       remove("todo.txt");
       rename("temp.txt","todo.txt");
    }

    if(count==0){
        remove("todo.txt");
    }
}


void Todo::listtodo(){
  string s;
  ifstream fin;
   fin.open("todo.txt");
   fin.get();
   if(fin.eof()==1 || count==0)
     cout<<"No pending todos";
  else
    for(int i=count;i>0;i--){
    fin.seekg(0);
       for(int j=0;j<i;j++){
         getline(fin,s);
        }
        cout<<"["<<i<<"]"<<" "<<s<<endl;
    }
            fin.close();
}


int main(int argc, char* argv[])
{

 ofstream fout;
 ifstream fin;
 fin.open("record.txt");
 fin>>count;
 fin>>done;
 fin.close();


    if(argc==1 ||  strcmp(argv[1],"help")==0){
        cout<<"Usage :-"<<endl
            <<"$ todo add \"todo item\"  # Add a new todo"<<endl
            <<"$ todo ls               # Show remaining todos"<<endl
            <<"$ todo del NUMBER       # Delete a todo"<<endl
            <<"$ todo done NUMBER      # Complete a todo"<<endl
            <<"$ todo help             # Show usage"<<endl
            <<"$ todo report           # Statistics";

    }
    else if(argc==2){


           if(strcmp(argv[1],"report")==0){
            cout<<getDate()<<" "<<"Pending : "<<count<<"  "<<"Completed : "<<done;
            }

           if(strcmp(argv[1],"ls")==0){
               t.listtodo();
        }


         if(strcmp(argv[1],"add")==0){
            cout<<"Error : no todo listed";
         }

         if(strcmp(argv[1],"del")==0){
            cout<<"Error : insufficient argument";
         }

         if(strcmp(argv[1],"done")==0){
            cout<<"Error : insufficient argument";
          }
   }
   else if(argc==3){

          if(strcmp(argv[1],"add")==0){
            t.addtodo(argv[2]);
            }

          if(strcmp(argv[1],"del")==0){
            t.deltodo(atoi(argv[2]));
          }

          if(strcmp(argv[1],"done")==0){
            t.marktododone(atoi(argv[2]));
          }
   }


     else {

         if(strcmp(argv[1],"add")==0){
            for(int i=2;i<argc;i++)
                t.addtodo(argv[i]);
         }

            if(strcmp(argv[1],"del")==0){
              cout<<"Error : too many argument, Nothing deleted"<<endl;
              cout<<"Type: todo help    #for help"<<endl;
          }


     }


 fout.open("record.txt");
 fout<<count<<endl;
 fout<<done<<endl;
 fout.close();

    return 0;
}
