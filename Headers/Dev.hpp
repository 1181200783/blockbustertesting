#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Developer{
    private:
        int options;
        int innerOptions;
    public:
        Developer();
        void draw();
        void displayOptions();
        void get_options();
        void add_options();
        void delete_options();
        void update_options();
        void config_options();
        bool warnings(string type, string name);
};
