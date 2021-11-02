#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
using namespace std;

class Customer{
    private:
        int options;
        int innerOptions;
        int genreSize = 0;
        string *genreList;
        string customerName;
        string contactNumber;
        string emailAdresss;
        string address;
        string purType;
        int collUserInfo = 0;
    public:
        Customer();
        void draw();
        void displayOptions();
        void get_movie();
        void purchase_ops(int *c,string mn,string gn);
        int write_recepit(string mn,string gn, string purType);
        void store_PINFO();
        int price(string purType);
};