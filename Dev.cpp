//Dev.cpp
#include "Headers/Dev.hpp"
#include "DataManager.cpp"
class CheckDataBase{
    // check database to find out existing (used only for genre)
    private:
        string type;
        string name;
        Manager manager;
    public:
        CheckDataBase(string type, string name){
            this->type = type;
            this->name = name;
        }
        bool check_data(){
            if (type == "genre"){
                return manager.checkExistence(name);
            }
            return false;
        }
};

Developer::Developer(){
    draw();
    displayOptions();
    get_options();
}

void Developer::draw(){
    cout << "\t###################################################" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t#"<<"          **Movie Menagement System**"         <<"\t\t  #" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t###################################################" << endl;
}

void Developer::displayOptions(){
    cout << "[~]0.Set Config"<< endl;
    cout << "[~]1.Add"<< endl;
    cout << "[~]2.Delete" << endl;
    cout << "[~]3.Update" << endl;
    cout << "[~]4.Exit" << endl;
}


void Developer::get_options(){  
    int run = 1;
    while(run){
        cout <<"->->-> "; 
        cin >> options;
        if(cin.good()){
            if(options == 4){
                exit(1);
            }
            else if(options==0){
                config_options();
            }
            else if(options == 1){
                add_options();
            }
            else if(options == 2){
                delete_options();
            }
            else if(options == 3){
                update_options();
            }
            else{
                cout << "Enter proper option!" << endl;
            }
        }
        else{
            cout << "error -Invalid input!";
            run = 0;
        }
    }
}


void Developer::add_options(){
    Manager insert;
    string *genreList = insert.getGenreList();
    int size = insert.get_genre_list_size();
    cout <<" 1.Add Genre" << endl;
    cout <<" 2.Add movie into Genre" << endl;
    cout <<" 3.Exit" << endl;
    int run = 1;
    string name;
    string gList = "";
    bool status;
    bool found = false;
    try{
        do{
            cout <<"->-> ";
            cin >> innerOptions;
            if(!cin.good()){
                throw innerOptions;
            }
            switch (innerOptions){
                case 1:
                    if(size != 0){
                        cout << "Available Genre -> ";
                        for(int i =0;i<size;i++){
                            gList += *(genreList+i) + ",";
                        }
                        gList.pop_back();
                        cout << gList;
                    }
                    else{
                        cout << "Available Genre -> 0";
                    }
                    cout << endl;
                    cout << "Enter Genre Name (null/n to Exit) -> ";
                    cin >> name;
                    if(name == "null" || name == "n" || name == "NULL" || name == "null"){
                        run = 0;
                        add_options();
                    }
                    else{
                        status = warnings("genre", name);
                        if (status != true){
                            // if genre not exists in the database the insert new
                            insert.set_genre_data(name);
                            cout <<"*Genre created!*" << endl;
                            run = 0;
                            add_options();
                        }
                        else{
                            // if exits ask to enter different one
                            cout << "Genre exists in the database!" << endl;
                        }
                    }
                    break;
                case 2:
                    if(size != 0){
                        cout << "Available Genre -> ";
                        for(int i =0;i<size;i++){
                            gList += *(genreList+i) + ",";
                        }
                        gList.pop_back();
                        cout << gList;
                        found = true;
                    }
                    else{
                        // if no genre available
                        cout << "Available Genre -> 0" << endl;
                        cout <<"  1.Create a new Genre" << endl;
                        cout <<"  2.Exit" << endl;
                        cout <<"->-> ";
                        cin >> innerOptions;
                        if(innerOptions == 1){
                            cout << "Enter Genre Name (null/n to Exit) -> ";
                            cin >> name;
                            if(name == "null" || name == "n" || name == "NULL" || name == "null"){
                                run = 0;
                                add_options();
                            }
                            else{
                                insert.set_genre_data(name);
                                status = warnings("genre", name);
                                cout <<"*Genre created!*" << endl;
                                run = 0;
                                add_options();
                            }
                        }
                        else{
                            system("cls"); // clear the terminal and recall options
                            draw();
                            displayOptions();
                            get_options();
                            run = 0; 
                        }
                    }
                    cout << endl;
                    if(found){
                        int c = 1;
                        while(c){
                            cout << "Enter Genre Name to insert movie Data (null/n to Exit) -> ";
                            cin >> name;
                            if(name == "null" || name == "n" || name == "NULL" || name == "null"){
                                c = 0;
                                run = 0;
                                add_options();
                            }
                            else{
                                status = warnings("genre", name);
                                if (status == true){
                                    // if genre exists in the database , can insert movie data
                                    int c2 = 1;
                                    string con;
                                    do{    
                                        // call data insert func  
                                        insert.set_movie_data();
                                        insert.insertDataIntoTree();
                                        cout << "~Data Inserted" << endl;                  
                                        cout << "Do you want to insert more movie data of--"<< name<<"--genre (Yes/y to CONTINUE | No/no/n to EXIT) -> ";
                                        cin >> con;
                                        if(con == "No" || con == "No" || con == "n"){
                                            insert.insertDataIntoFile(insert.getMovieDetailNode(), insert.getGFN(name));
                                            c2 = 0;
                                            c = 0;
                                            run = 0;
                                            add_options();
                                        }
                                    } while(c2);
                                }
                                else{
                                    cout << "Genre doesn't exist in the database!" << endl;
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    system("cls"); // clear the terminal and recall options
                    draw();
                    displayOptions();
                    get_options();
                    run = 0;
                    break;
                default:
                    cout << "Enter proper option" << endl;
            }
        }while (run);
    }
    catch(...){
        run = 0;
    }
}
void Developer::delete_options(){
    Manager del;
    string *genreList = del.getGenreList();
    int size = del.get_genre_list_size();
    int run = 1;
    int innerOptions;
    string name, mn;
    string gList = "";
    string allMvName = "";
    bool status;
    bool found = false;
    vector<string> names;
    int c = 1;
    int c1 = 1;
    int mIndex;
    int totalMovies = 0;
    cout <<" 1.Delete Genre" << endl;
    cout <<" 2.Delete movie into of a Genre" << endl;
    cout <<" 3.Exit" << endl;
    while (run){
        try{
            cout <<"->-> ";
            cin >> innerOptions;
            if(!cin.good()){
                throw innerOptions;
            }
            switch(innerOptions){
                case 1:
                    if(size != 0){
                            cout << "Available Genre -> ";
                            for(int i =0;i<size;i++){
                                gList += *(genreList+i) + ",";
                            }
                            gList.pop_back();
                            cout << gList;
                        }
                        else{
                            cout << "Available Genre -> 0";
                        }
                        cout << endl;
                        while(c){
                            cout << "Enter Genre Name (null/n to Exit) -> ";
                            cin >> name;
                            if(name == "null" || name == "n" || name == "NULL" || name == "null"){
                                c1 = 0;
                                run = 0;
                                delete_options();
                            }
                            else{
                                status = warnings("genre", name);
                                if (status == true){
                                    // if genre not exists in the database the insert new
                                    del.deleteGenre(name);
                                    cout <<"*Genre Deleted!*" << endl;
                                    c1 = 0;
                                    run = 0;
                                    delete_options();
                                }
                                else{
                                    // if exits ask to enter different one
                                    cout << "Genre does't exists in the database!" << endl;
                                }
                            }
                        }
                    break;
                case 2:
                    if(size != 0){
                            cout << "Available Genre -> ";
                            for(int i =0;i<size;i++){
                                gList += *(genreList+i) + ",";
                            }
                            gList.pop_back();
                            cout << gList;
                        }
                    else{
                        cout << "Available Genre -> 0";
                    }
                    cout << endl;
                    while(c){
                        cout << "Enter Genre Name (null/n to Exit) -> ";
                        cin >> name;
                        if(name == "null" || name == "n" || name == "NULL" || name == "null"){
                            c = 0;
                            run = 0;
                            delete_options();
                        }
                        else{
                            status = warnings("genre", name);
                            if(status == true){
                                int c2 = 1;
                                string mn;
                                // if genre not exists in the database the insert new
                                del.readFromFile(name);
                                names = del.getMovieName(del.getMovieDetailNodeFR());
                                sort(names.begin(), names.end());
                                del.sortMD(del.getMovieDetailNodeFR());
                                while(c2){
                                    if(names.size() != 0){
                                        totalMovies = 0;
                                        cout << "Available Movies -> ";
                                        for(auto i = names.cbegin();i!=names.cend();i++){
                                            cout << totalMovies<<"." << *i << " ";
                                            if (totalMovies >= 10){
                                                cout << endl;
                                            }
                                            totalMovies++;
                                        }
                                    }
                                    else{
                                        cout << "Available Movies -> 0";
                                    }
                                    cout << endl;
                                    try{
                                        cout << "Enter Movie Number to delete(-1 to EXIT) -> ";
                                        cin >> mIndex;
                                        if(!cin.good()){
                                            throw mIndex;
                                        }
                                        if(mIndex == -1){
                                            c2 = 0;
                                            c = 0;
                                            run = 0;
                                            del.re_write_movie_data(del.getMovieDetailNodeFBS(), name);
                                            delete_options();
                                        }
                                        else{
                                            if(!names.empty() && mIndex < totalMovies){
                                                mn = names[mIndex];
                                                names.erase(remove(names.begin(), names.end(), mn), names.end());
                                                int n = del.RDFG(del.getMovieDetailNodeFBS(),mn);
                                                if(n != -1){
                                                    cout << "Movie not found" << endl;
                                                    cout <<"*"<<mn <<" Deleted!*" << endl;
                                                }
                                                else{
                                                    cout << "Movie not found" << endl;
                                                }
                                            }
                                            else{
                                                cout << "Movie not found" << endl;
                                            }
                                        }
                                    }
                                    catch(...){
                                        cout << "error -Invalid input!";
                                        exit(1);
                                    }
                                }
                            }
                            else{
                                // if exits ask to enter different one
                                cout << "Genre does't exists in the database!" << endl;
                            }
                        }
                    }
                    break;
                case 3:
                    system("cls"); // clear the terminal and recall options
                    draw();
                    displayOptions();
                    get_options();
                    run = 0;
                    break;
                default:
                    cout << "Enter proper option" << endl;
            }
           
        }
        catch(...){
            cout << "error -Invalid input!";
            exit(1);
        }
         
    }

}  
void Developer::update_options(){
    Manager update;
    string *genreList = update.getGenreList();
    int size = update.get_genre_list_size();
    int run = 1;
    int choice, mIndex, type;
    string gList, name;
    bool status;
    vector<string> names;
    int totalMovies = 0;
    bool updated = false;
    string types[] = {"Name","Type","Plot","Rate","MetaScore","Director name","Stars","Release Date","Run Time",
                    "Counteries","Languages","Budget","Box Office"};
    cout <<" 1.Update movie" << endl;
    cout <<" 2.Exit" << endl;
    while(run){
        try{
            cout <<"->-> ";
            cin >> choice;
            if(!cin.good()){
                throw choice;
            }
            switch (choice){
                case 1:
                if(size != 0){
                    cout << "Available Genre -> ";
                    for(int i =0;i<size;i++){
                        gList += *(genreList+i) + ",";
                    }
                    gList.pop_back();
                    cout << gList;
                }
                else{
                    cout << "Available Genre -> 0";
                }
                cout << endl;
                cout << "Enter Genre Name (null/n to Exit) -> ";
                cin >> name;
                if(name == "null" || name == "n" || name == "NULL" || name == "null"){
                    run = 0;
                    add_options();
                }
                else{
                    status = warnings("genre", name);
                    if(status == true){
                        int c2 = 1;
                        string mn;
                        update.readFromFile(name);
                        names = update.getMovieName(update.getMovieDetailNodeFR());
                        sort(names.begin(), names.end());
                        update.sortMD(update.getMovieDetailNodeFR());
                        while(c2){
                            if(names.size() != 0){
                                cout << "Available Movies -> ";
                                totalMovies = 0;
                                for(auto i = names.cbegin();i!=names.cend();i++){
                                    cout << totalMovies<<"." << *i << " ";
                                    if (totalMovies >= 10){
                                        cout << endl;
                                    }
                                    totalMovies++;
                                }
                            }
                            else{
                                cout << "Available Movies -> 0";
                            }
                            cout << endl;
                            try{
                                cout << "Enter Movie Number to update(-1 to EXIT) -> ";
                                cin >> mIndex;
                                if(!cin.good()){
                                    throw mIndex;
                                }
                                if(mIndex == -1){
                                    c2 = 0;
                                    run = 0;
                                    update_options();
                                }
                                else{
                                    int c3 = 1;
                                    if(!names.empty() && mIndex < totalMovies){
                                        mn = names[mIndex];
                                        int mInd = update.getMovieIndex(update.getMovieDetailNodeFBS(), mn);
                                        while(c3){
                                            for (int i = 0; i < 13; i++){
                                                cout << i <<"." << types[i] << " ";
                                            }
                                            cout << endl;       
                                            mn = names[mIndex];
                                            cout << "Enter type(-1 to EXIT) -> ";
                                            cin >> type;
                                            if(type == -1){
                                                if(updated){
                                                    update.saveUpdate(update.getMovieDetailNodeFBS(), update.getGFN(name));
                                                }
                                                c3 = 0;
                                                c2 = 0;
                                                run = 0;
                                                update_options();
                                            }
                                            else if(type  >=0 && type < 13){ 
                                                updated = true; 
                                                update.updateData(update.getMovieDetailNodeFBS(), mn, type, mInd);
                                                cout <<"*"<<types[type] <<" Updated!*" << endl;   
                                            }
                                            else{
                                                cout << "Enter proper number!" << endl;
                                            }
                                        }
                                    }
                                    else{
                                        cout << "Movie not found" << endl;
                                    }
                                }
                            }
                            catch(...){
                                cout << "error -Invalid input!";
                                exit(1);
                            }
                        }
                    }
                    else{
                        // if exits ask to enter different one
                        cout << "Genre exists in the database!" << endl;
                    }
                }
                    break;
                case 2:
                    system("cls"); // clear the terminal and recall options
                    draw();
                    displayOptions();
                    get_options();
                    run = 0;
                    break;
                default:
                    cout << "Enter proper option" << endl;
            }
        }
        catch (...){
            cout << "error -Invalid input!";
            exit(1);
        }
    }  
}

void Developer::config_options(){
    Manager conf;
    int run = 1;
    int choice;
    string passwd, ch;
    string data = conf.getConfig("passwd");
    string con = data.substr(0, data.find("/"));
    if(con == "NULL"){
        cout <<" 1.Set password" << endl;
    }
    else if(con == "1") {
        cout <<" 1.Reset password" << endl;
    }
    cout <<" 2.None" << endl;
    cout <<" 3.Exit" << endl;
    while(run){
        try{
            cout <<"->-> ";
            cin >> choice;
            if(!cin.good()){
                throw choice;
            }
            switch (choice){
                case 1:
                    if(con == "NULL"){
                        cout << "Enter Password ->";
                        cin >> passwd;
                        conf.setConfig("passwd","1",passwd);
                        cout << "*Password Created!" << endl;
                    }
                    else if(con == "1") {
                        cout <<" 1.Reset password" << endl;
                        cout <<" 2.Turn off password" << endl;
                        cout <<"-> ";
                        cin >> ch;
                        if(ch == "1"){
                            cout << "Enter Password ->";
                            cin >> passwd;
                            conf.setConfig("passwd","1",passwd);
                            cout << "*Password Changed!" << endl;
                        }
                        else if(ch == "2"){
                            conf.setConfig("passwd","NULL","NULL");
                            cout << "*Password Turned off!" << endl;
                        }
                        else{
                            cout << "Enter proper option" << endl;
                        }
                    }
                    break;
                case 2:
                    break;
                case 3:
                    system("cls"); // clear the terminal and recall options
                    draw();
                    displayOptions();
                    get_options();
                    run = 0;
                    break;
                default:
                    cout << "Enter proper option" << endl;
            }
        }
        catch (...){
            cout << "error -Invalid input!";
            exit(1);
        }
    }
}

bool Developer::warnings(string type ,string n){
    CheckDataBase ck(type,n);
    return ck.check_data();
}
