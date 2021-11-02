//Main.cpp
#include <iostream>
#include <fstream>
#include "Dev.cpp"
#include "User.cpp"

using namespace std;
int main() {
    Manager mang;
    int t;
    int run = 1;
    int innerRun = 1;
    string data = mang.getConfig("passwd");
    string con = data.substr(0, data.find("/"));
    string p = data.substr(data.find("/")+1 ,data.length());
    string getPasswd;
    cout << "1.Developer" << endl;
    cout << "2.User" << endl;
    cout << "3.Exit" << endl;
    while(run){
        try{
            cout << "Enter Type:";
            cin >> t;
            if(!cin.good()){
                throw t;
            }
            if(t == 1){
                if(con != "NULL"){
                    while (innerRun){
                        cout << "Enter Password ->";
                        cin >> getPasswd;
                        if(getPasswd == p){
                            system("cls");
                            innerRun = 0;
                            run = 0;
                            Developer dev;
                        }
                        else{
                            cout << "Incorret password!" << endl;
                        }
                    }    
                }
                else{
                    system("cls");
                    Developer dev;
                }
            }
            else if(t == 2){
                system("cls");
                run = 0;
                Customer dev;
            }
            else if(t == 3){
                exit(1);
            }
            else{
                cout << "Enter currect option!" << endl;
            }
        }
        catch(...){
            cout << "error -Invalid input!";
            exit(1);
        };
    }
    return 0;
}
