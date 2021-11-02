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
