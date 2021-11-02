#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <stdio.h>
#include <cstring>
#define EQUAL 0
#define SMALLER -1
#define BIGGER 1
using namespace std;

struct Genre{
    string name;
    struct Genre *last;
    struct Genre *next;
};

struct MovieDetail{
    // for insert data into tree
    string name;
    string type;
    string plot;
    string rate;
    string metaScore;
    string Direc_name;
    string Stars;
    string release_date;
    string run_time;
    string counteries;
    string langs;
    string Budget;
    string Box_office;
    struct MovieDetail *left;
    struct MovieDetail *right;
};

struct MovieDetailBS{
    // for binary search, delete, update data
    string name;
    string type;
    string plot;
    string rate;
    string metaScore;
    string Direc_name;
    string Stars;
    string release_date;
    string run_time;
    string counteries;
    string langs;
    string Budget;
    string Box_office;
    struct MovieDetailBS *next;
};

class Manager{
    private:
        struct MovieDetail *head = NULL; // for tree saving
        struct MovieDetailBS *headNFR = NULL; // for reading file
        struct MovieDetailBS *headSBS; // for sorted binary search
        // movie itmes
        string genreName;
        string name;
        string type;
        string plot;
        string rate;
        string metaScore;
        string Direc_name;
        string Stars;
        string release_date;
        string run_time;
        string counteries;
        string langs;
        string Budget;
        string Box_office;
        vector<string> MovieNames;
        int ind = 0;
    public:
        void createFile();
        void set_genre_data(string gn);
        void set_movie_data();
        void insertDataIntoTree(); // using BTS, insert data into tree
        void insertDataIntoFile(struct MovieDetail *head, string FN); // using BTS, insert data into text file using tree
        void readFromFile(string gn); // used linked list
        struct Genre *readGenreList(); // used linked list
        int get_genre_list_size(); // used linked list
        void insertIntoChild(struct MovieDetail *head, string name,struct MovieDetail *node);
        void updateData(struct MovieDetailBS *head,string mn, int typeInd,int mInd); // linked list
        void saveUpdate(struct MovieDetailBS *head,string gn); // linked list
        int getMovieIndex(struct MovieDetailBS *head, string mn); // for update data
        void deleteGenre(string gn); // used linked list
        void deleteGenreFile(string fileName, string tp, string mn); // used binary search
        bool checkExistence(string name); // used linked list
        bool checkUpperCase(string sc1, string sc2);
        bool checkLowerCase(string sc1, string sc2);
        string *getGenreList();
        int compareNodeData(string n1, string n2);
        struct MovieDetail *getMovieDetailNode();
        struct MovieDetailBS *getMovieDetailNodeFR();
        struct MovieDetailBS *getMovieDetailNodeFBS();
        string getGFN(string gn);
        vector<string> getMovieName(struct MovieDetailBS *head); // used linkedlist
        int RDFG(struct MovieDetailBS *head,string mn); // used binary search
        void sortMD(struct MovieDetailBS *head); // insertion sort
        struct MovieDetailBS *sortedInsert(struct MovieDetailBS * sorted_head, struct MovieDetailBS * new_node);
        int binarySearch(struct MovieDetailBS **n, int s, int e, string mn);
        void re_write_movie_data(struct MovieDetailBS *n, string gn);
        void setConfig(string tp, string con, string data);
        string getConfig(string tp);
        void displayMD(struct MovieDetailBS *head, string mn);
        void setUserDetails();
        void generateUR();
};