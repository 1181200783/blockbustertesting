//DataManager.cpp
#include "Headers/DataManager.hpp"

void Manager::createFile(){
    ofstream Genrefile, genreList;
    genreList.open ("DB/genrelist.txt", ios::app);
    genreList << genreName << "," << endl;
    string path = "DB/" + genreName + ".txt";
    Genrefile.open(path);
    Genrefile.close();
    genreList.close();
}
void Manager::set_genre_data(string gn){
    genreName = gn;
    createFile();
}

void Manager::set_movie_data(){
    cout << "-----------------------------------" << endl;
    cout <<"-"<< " Symbol to avoid [|]" <<"             -"<<endl;
    cout <<"-"<<" Avoid inputing multi-line\n  at the same time" <<"                -"<<endl;
    cout << "-----------------------------------" << endl;
    try{
        cout << "Enter Name->";
        getline(cin >> ws, name);
        cout << "Enter Type->";
        getline(cin >> ws, type);
        cout << "Enter Plot->";
        getline(cin >> ws, plot);
        cout << "Enter Rate->";
        getline(cin >> ws, rate);
        cout << "Enter MetaScore->";
        getline(cin >> ws, metaScore);
        cout << "Enter Director name->";
        getline(cin >> ws, Direc_name);
        cout << "Enter Stars->";
        getline(cin >> ws, Stars);
        cout << "Enter Release Date->";
        getline(cin >> ws, release_date);
        cout << "Enter Run Time->";
        getline(cin >> ws, run_time);
        cout << "Enter Counteries->";
        getline(cin >> ws, counteries);
        cout << "Enter Language->";
        getline(cin >> ws, langs);
        cout << "Enter Budget->";
        getline(cin >> ws, Budget);
        cout << "Enter Box Office->";
        getline(cin >> ws, Box_office);
        if(!cin.good()){
            throw "Multi-line input not allowed!";
        }
    }
    catch(...){
        exit(1);
    }
}

struct Genre *Manager::readGenreList(){
    struct Genre *head = NULL;
    ifstream file("DB/genrelist.txt");
    string text;
    if(file.is_open() && file.peek() != ifstream::traits_type::eof()){
        // to chekc if file is open and not empty
        while (getline(file, text)){
            stringstream line(text);
            struct Genre *node = new struct Genre;
            getline(line, node->name, ',');
            node->next = NULL;
            node->last = NULL;
            if (head == NULL){
                head = node;
            }
            else{
                struct Genre *temp = head;
                while (temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = node;
                node->last = temp;
            }
        }
        file.close();
        return head;
    }
    return NULL;
}

int Manager::get_genre_list_size(){
    // get the size of genre list's item
    struct Genre *temp = readGenreList();
    int size = 0;
    if(temp){
        while(temp->next){
            size++;
            temp = temp->next;
        }
        if(temp->next == NULL){
            size++;
        }
    }
    return size;
}

bool Manager::checkExistence(string name){
    struct Genre *temp = readGenreList();
    if (temp){
        while(temp->next != NULL){
            if(checkUpperCase(temp->name, name) && checkLowerCase(temp->name, name)){
                return true;
            }
            temp = temp->next;
        }
        if(temp->next == NULL && (checkUpperCase(temp->name, name) && checkLowerCase(temp->name, name))){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}

bool Manager::checkUpperCase(string sc1, string sc2){
    //ASCII value of uppercase alphabets â€“ 65 to 92
    // make lowercase and check
    for(int i=0;i<sc1.length();i++){
        if(sc1[i]>=65 && sc1[i]<=92){
	        sc1[i]=sc1[i]+32;
        }
    }

    for(int j = 0;j<sc2.length();j++){
        if(sc2[j]>=65 && sc2[j]<=92)
        {
	        sc2[j]=sc2[j]+32;
        }
    }
    if(sc1==sc2){
        return true;
    }
    else{
        return false;
    }
}
bool Manager::checkLowerCase(string sc1, string sc2){
    //ASCII value of lowercase alphabets â€“ 97 to 122
    // make uppercase and check
    for(int i=0;i<sc1.length();i++){
        if(sc1[i] >= 97 && sc2[i] <= 122){
            sc1[i] = sc1[i]-32;
        }
    }

    for(int j = 0;j<sc2.length();j++){
        if(sc2[j] >= 97 && sc2[j] <= 122){
            sc2[j] = sc2[j]-32;
        }
    }
    if(sc1==sc2){
        return true;
    }
    else{
        return false;
    }
}

string *Manager::getGenreList(){
    string *genres = new string[get_genre_list_size()];
    struct Genre *temp = readGenreList();
    int index = 0;
    if(temp != NULL){
        while(temp->next){
            genres[index] = temp->name;
            temp = temp->next;
            index++;
        }
        if(temp->next == NULL){
            if(index == 0){
                genres[index] = temp->name;
            }
            else{
                genres[index] = temp->name;
            }
        }
    }

    return genres;
}

int Manager::compareNodeData(string n1, string n2){
    int res = n1.compare(n2);
    if(res == 0){
        return EQUAL;
    }
    else if(res < 0){
        return SMALLER;
    }
    else{
        return BIGGER;
    }
}

void Manager::insertDataIntoTree(){ 
    struct MovieDetail *node =  new struct MovieDetail;
    node->name = name;
    node->type = type;
    node->plot = plot;
    node->rate = rate;
    node->metaScore = metaScore;
    node->Direc_name = Direc_name;
    node->Stars = Stars;
    node->release_date = release_date;
    node->run_time = run_time;
    node->counteries = counteries;
    node->langs = langs;
    node->Budget = Budget;
    node->Box_office = Box_office;
    node->left = NULL;
    node->right = NULL;    
    if(head == NULL){
        head = node;
    }
    else{
        insertIntoChild(head, name, node);
    }
}

void Manager::insertIntoChild(struct MovieDetail *head, string name, struct MovieDetail *node){
    if(compareNodeData(name, head->name) < 0){
        if(head->left == NULL){
            head->left = node;
        }
        else{
            insertIntoChild(head->left, name, node);
            return;
        }
    }
    else if(compareNodeData(name, head->name) > 0){
        if(head->right == NULL){
            head->left = node;
        }
        else{
            insertIntoChild(head->right, name, node);
            return;
        }
    }
}
void Manager::insertDataIntoFile(struct MovieDetail *head, string FN){
    // read binary tree and store data into approprite file
    ofstream moviedata;
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
    string data;
    if(head != NULL){
        insertDataIntoFile(head->left, FN);
        name = head->name;
        type = head->type;
        plot = head->plot;
        rate = head->rate;
        metaScore = head->metaScore;
        Direc_name = head->Direc_name;
        Stars = head->Stars;
        release_date = head->release_date;
        run_time = head->run_time;
        counteries = head->counteries;
        langs = head->langs;
        Budget = head->Budget;
        Box_office = head->Box_office;
        data = name +"|"+type+"|"+plot+"|"+rate+"|"+metaScore+"|"+Direc_name+"|"+Stars+"|"+release_date+"|"+run_time+"|"+counteries+"|"+langs+"|"+Budget+"|"+Box_office;     
        moviedata.open(FN, ios::app);
        if(moviedata.is_open()){
            moviedata << data << endl;
        }
        else{
            exit(1);
        }
        insertDataIntoFile(head->right, FN);
    }
}

struct MovieDetail *Manager::getMovieDetailNode(){
    return head;
}
struct MovieDetailBS *Manager::getMovieDetailNodeFR(){
    return headNFR;
}

struct MovieDetailBS *Manager::getMovieDetailNodeFBS(){
    return headSBS;
}

string Manager::getGFN(string gn){
    // get folder name
    string s;
    string temp;
    string path;
    DIR *dir; 
    struct dirent *diread;
    dir = opendir("./DB");
    vector<string> pName;
    if(dir != NULL){
        while ((diread = readdir(dir)) != NULL){
            s = diread->d_name;
            pName.push_back(s);
        }
        closedir (dir);
    }
    else{
        cout << "No file found" << endl;
    }
    
    for (auto i = pName.cbegin(); i != pName.cend();i++){
        temp = (string)*i;
        if((checkUpperCase(temp.substr(0, temp.find(".")), gn) && checkLowerCase(temp.substr(0, temp.find(".")), gn))){
            break;
        }
    }
    path = "DB/" + temp;
    return path;
} 

void Manager::deleteGenre(string gn){
    struct Genre *temp = readGenreList();
    struct Genre *temp2 = readGenreList();
    struct Genre *temp3 = temp2;
    struct Genre *s;
    int index = 0;
    if(temp){
        //find genre index
        while(temp->next){
            if((checkUpperCase(temp->name, gn) && checkLowerCase(temp->name,gn))){
                break;
            }
            temp = temp->next;
            index++;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        }
        if(temp->next == NULL && index <= 0){
            if((checkUpperCase(temp->name, gn) && checkLowerCase(temp->name,gn))){
                index = 0;
            }
        }
        // delete genre by index
        if(index == 0){
           temp2 = temp2->next;
           if(temp2!=NULL){
                temp2->last = NULL;
           }
           temp3 = temp2;
        } 
        else{
            for(int i =0;i<index-1;i++){
                temp2 = temp2->next;
            }
            s = temp2->next;
            temp2->next = s->next;
            if(temp2->next != NULL){
                temp2->next->last = temp2;
            }
            else{
                free(s);  
            }
        }
    }
    if(temp3){
        // re write genre into file
        ofstream genreList;
        genreList.open ("DB/genrelist.txt",ios::out | ios::trunc);
        while(temp3->next){
            genreList << temp3->name << "," << endl;
            temp3 = temp3->next;
        }
        if(temp3->next == NULL){
            genreList << temp3->name << "," << endl;
        }
        genreList.close();
    }
    else{
        ofstream genreList;
        genreList.open("DB/genrelist.txt", ios::out | ios::trunc);
        genreList.close();
    }
    deleteGenreFile(gn, "file","");
}

void Manager::deleteGenreFile(string fileName, string tp, string mn){
    // delete from system folder
    if (tp == "file"){
        string file = getGFN(fileName);
        char fp[file.length()+1];
        strcpy(fp,file.c_str());
        try{
            remove(fp);
        }
        catch(...){
           cout << "No file available";
        }
    }
}

void Manager::readFromFile(string gn){
    string file_path = getGFN(gn);
    string text;   
    string name;
    string type;
    string plot;
    string Direc_name;
    string Stars;
    string release_date;
    string run_time;
    string counteries;
    string langs;
    string Budget;
    string Box_office;
    string r,m;
    Manager::ind = 0;
    ifstream file(file_path);
    if(file.is_open() && file.peek() != ifstream::traits_type::eof()){
        while(getline(file, text)){
            stringstream line(text);
            getline(line,name, '|');
            getline(line,type, '|');
            getline(line, plot, '|');
            getline(line, r, '|');
            getline(line, m, '|');
            getline(line,Direc_name, '|');
            getline(line,Stars, '|');
            getline(line,release_date, '|');
            getline(line,run_time, '|');
            getline(line,counteries, '|');
            getline(line,langs, '|');
            getline(line,Budget, '|');
            getline(line,Box_office, '|');
            struct MovieDetailBS *node = new struct MovieDetailBS;
            node->name = name;
            node->type = type;
            node->plot = plot;
            node->rate = r;
            node->metaScore = m;
            node->Direc_name = Direc_name;
            node->Stars = Stars;
            node->release_date = release_date;
            node->run_time = run_time;
            node->counteries = counteries;
            node->langs = langs;
            node->Budget = Budget;
            node->Box_office = Box_office;
            node->next = NULL;
            if(headNFR == NULL){
                headNFR = node;
                Manager::ind++;
            }
            else{
                struct MovieDetailBS *temp = headNFR;
                while(temp->next){
                    temp = temp->next;
                }
                temp->next = node;
                Manager::ind++;
            }
        }
    }
    //file.close();
}

vector<string> Manager::getMovieName(struct MovieDetailBS *head){
    // get all movies name according to genre
    if(head){
        struct MovieDetailBS *temp = head;
        while(temp->next){
            MovieNames.push_back(temp->name);
            temp = temp->next;
        }
        if(temp->next == NULL){
            MovieNames.push_back(temp->name);
        }
    }
    return MovieNames;
}

int Manager::RDFG(struct MovieDetailBS *head, string mn){
    // get movie index pos wanted to remove from linked list
    int index = -1;
    int res;
    int c = 0;
    int size = Manager::ind;
    struct MovieDetailBS *container[size];
    struct MovieDetailBS *temp = headSBS;
    struct MovieDetailBS *s;
    if(temp){
        while(temp->next){
            container[c] = temp;
            temp = temp->next;
            c++;
        }
        if(temp->next == NULL){
            container[c] = temp;
        }
    }
    res = binarySearch(container, 0, size-1, mn);
    if(res != -1){
        index = 1; 
        Manager::ind--;
        if(res == 0){
            headSBS = headSBS->next;
        } 
        else{
            struct MovieDetailBS *temp3 = headSBS;
            for(int i =0;i<res-1;i++){
                temp3 = temp3->next;
            }
            s = temp3->next;
            temp3->next = s->next;
            free(s);  
        }
    }
    for (int i = 0; i < Manager::ind; i++){
        container[i] = NULL;
    }
    
    return index;
}

void Manager::re_write_movie_data(struct MovieDetailBS *n, string gn){
    string file_path = getGFN(gn);
    if(n!=NULL){
        ofstream genreList;
        genreList.open (file_path,ios::out | ios::trunc);
        while(n->next){
            genreList << n->name << "|";
            genreList << n->type << "|";
            genreList << n->plot << "|";
            genreList << n->rate << "|";
            genreList << n->metaScore << "|";
            genreList << n->Direc_name << "|";
            genreList << n->Stars << "|";
            genreList << n->release_date << "|";
            genreList << n->run_time << "|";
            genreList << n->counteries << "|";
            genreList << n->langs << "|";
            genreList << n->Budget << "|";
            genreList << n->Box_office << "|" << endl;
            n = n->next;
        }
        if(n->next == NULL){
            genreList << n->name << "|";
            genreList << n->type << "|";
            genreList << n->plot << "|";
            genreList << n->rate << "|";
            genreList << n->metaScore << "|";
            genreList << n->Direc_name << "|";
            genreList << n->Stars << "|";
            genreList << n->release_date << "|";
            genreList << n->run_time << "|";
            genreList << n->counteries << "|";
            genreList << n->langs << "|";
            genreList << n->Budget << "|";
            genreList << n->Box_office << "|" << endl;
        }
        genreList.close();
    }
    else{
        ofstream genreList;
        genreList.open(file_path, ios::out | ios::trunc);
        genreList.close();
    }
}

void Manager::sortMD(struct MovieDetailBS *head){
    struct MovieDetailBS *c = head;
    struct MovieDetailBS *sorted = NULL;
    while (c != NULL){
        struct MovieDetailBS *currNext = c->next;
        sorted = sortedInsert(sorted, c);
        c = currNext;
    }
    headSBS =  sorted; // store to new node
}

 struct MovieDetailBS *Manager::sortedInsert(struct MovieDetailBS *sorted, struct MovieDetailBS * new_node){
    if(sorted == NULL or sorted->name >= new_node->name){
        new_node->next = sorted;
        return new_node;
    }
    else{
        struct MovieDetailBS *curr = sorted;
        while(curr->next != NULL and curr->next->name < new_node->name){
                curr = curr->next;
            }
        new_node->next = curr->next;
        curr->next = new_node;
    }
    return sorted;
 }

int Manager::binarySearch(struct MovieDetailBS **n, int s, int e, string mn){
    int mid = (s+e)/2;
    int res = mn.compare(n[mid]->name);
    if(res == 0){
        return mid;
    }
    if(s >= e){
        return -1;
    }
    if(res < 0){
        return binarySearch(n, s, mid-1, mn);
    }
    else{
        return binarySearch(n, mid+1, e, mn);
    }  
}

void Manager::updateData(struct MovieDetailBS *head, string mn, int typeInd, int mInd){
    string types[] = {"Name","Type","Plot","Rate","MetaScore","Director name","Stars","Release Date","Run Time",
                    "Counteries","Languages","Budget","Box Office"};
    cout << "-----------------------------------" << endl;
    cout <<"-"<< " Symbol to avoid [|]" <<"             -"<<endl;
    cout <<"-"<<" Avoid inputing multi-line\n  at the same time" <<"                -"<<endl;
    cout << "-----------------------------------" << endl;
    try{
        string data;
        cout << "Enter "<<types[typeInd] << "->";
        getline(cin >> ws, data);
        if(!cin.good()){
            throw "Multi-line input not allowed!";
        }
        struct MovieDetailBS *temp = head;
        for(int i =0;i<mInd;i++){
            temp = temp->next;
        }
        if(temp){
            switch(typeInd){
                case 0:
                    temp->name = data;
                    break;
                case 1:
                    temp->type = data;
                    break;
                case 2:
                    temp->plot = data;
                    break;
                case 3:
                    temp->rate = data;
                    break;
                case 4:
                    temp->metaScore = data;
                    break;
                case 5:
                    temp->Direc_name = data;
                    break;
                case 6:
                    temp->Stars = data;
                    break;
                case 7:
                    temp->release_date = data;
                    break;
                case 8:
                    temp->run_time = data;
                    break;
                case 9:
                    temp->counteries = data;
                    break;
                case 10:
                    temp->langs = data;
                    break;
                case 11:
                    temp->Budget = data;
                    break;
                case 12:
                    temp->Box_office = data;
                    break;   
            }
        }
    }
    catch(...){
        exit(1);
    }
    
}

void Manager::saveUpdate(struct MovieDetailBS *head, string gn){
    ofstream moviedata;
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
    string data;
    moviedata.open(gn, ios::out | ios::trunc);
    while(head->next){
        name = head->name;
        type = head->type;
        plot = head->plot;
        rate = head->rate;
        metaScore = head->metaScore;
        Direc_name = head->Direc_name;
        Stars = head->Stars;
        release_date = head->release_date;
        run_time = head->run_time;
        counteries = head->counteries;
        langs = head->langs;
        Budget = head->Budget;
        Box_office = head->Box_office;
        data = name +"|"+type+"|"+plot+"|"+rate+"|"+metaScore+"|"+Direc_name+"|"+Stars+"|"+release_date+"|"+run_time+"|"+counteries+"|"+langs+"|"+Budget+"|"+Box_office;     
        if(moviedata.is_open()){
            moviedata << data << endl;
        }
        else{
            exit(1);
        }
        head = head->next;
    }
    if(head->next == NULL){
        name = head->name;
        type = head->type;
        plot = head->plot;
        rate = head->rate;
        metaScore = head->metaScore;
        Direc_name = head->Direc_name;
        Stars = head->Stars;
        release_date = head->release_date;
        run_time = head->run_time;
        counteries = head->counteries;
        langs = head->langs;
        Budget = head->Budget;
        Box_office = head->Box_office;
        data = name +"|"+type+"|"+plot+"|"+rate+"|"+metaScore+"|"+Direc_name+"|"+Stars+"|"+release_date+"|"+run_time+"|"+counteries+"|"+langs+"|"+Budget+"|"+Box_office;     
        if(moviedata.is_open()){
            moviedata << data << endl;
        }
        else{
            exit(1);
        }
    }
    moviedata.close();
}

int Manager::getMovieIndex(struct MovieDetailBS *head, string mn){
    int res;
    int c = 0;
    int size = Manager::ind;
    struct MovieDetailBS *container[size];
    struct MovieDetailBS *temp = headSBS;
    struct MovieDetailBS *s;
    if(temp){
        while(temp->next){
            container[c] = temp;
            temp = temp->next;
            c++;
        }
        if(temp->next == NULL){
            container[c] = temp;
        }
    }
    res = binarySearch(container, 0, size-1, mn);
    for (int i = 0; i < Manager::ind; i++){
        container[i] = NULL;
    }
    return res;
}

void Manager::displayMD(struct MovieDetailBS *head, string mn){
    int res;
    int c = 0;
    int size = Manager::ind;
    struct MovieDetailBS *container[size];
    struct MovieDetailBS *temp = headSBS;
    struct MovieDetailBS *s;
    if(temp){
        while(temp->next){
            container[c] = temp;
            temp = temp->next;
            c++;
        }
        if(temp->next == NULL){
            container[c] = temp;
        }
    }
    res = binarySearch(container, 0, size-1, mn);
    if(res!=-1){
        cout << "\t"<<container[res]->name << endl;
        cout << "Type         :" << container[res]->type << endl;
        cout << "Plot         :" << container[res]->plot << endl;
        cout << "Rate         :" << container[res]->rate << endl;
        cout << "MetaScore    :" << container[res]->metaScore << endl;
        cout << "Directed by  :" << container[res]->Direc_name << endl;
        cout << "Starring     :" << container[res]->Stars << endl;
        cout << "Release date :" << container[res]->release_date << endl;
        cout << "Running time :" << container[res]->run_time << endl;
        cout << "Country      :" << container[res]->counteries << endl;
        cout << "Language     :" << container[res]->langs << endl;
        cout << "Budget       :" << container[res]->Budget << endl;
        cout << "Box office   :" << container[res]->Box_office << endl;
    }

    for (int i = 0; i < Manager::ind; i++){
        container[i] = NULL;
    }
}

void Manager::setConfig(string tp, string con, string data){
    string *type = new string[5];
    string *condi = new string[5];
    string *val = new string[5];
    string tpS, conS, dataS, text;
    int index = 0;
    ifstream configRead;
    ofstream configSet, configSet2;
    configRead.open("config.txt");
    configSet.open("config.txt");
    if(configRead.is_open() && configRead.peek() != ifstream::traits_type::eof()){
        while(getline(configRead, text)){
            stringstream line(text);
            getline(line, tpS, ',');
            getline(line, conS, ',');
            getline(line, dataS);
            type[index] = tpS;
            condi[index] = conS;
            val[index] = dataS;
            index++;
        }
        configSet2.open("config.txt",ios::out | ios::trunc);
        if(configSet2.is_open()){
            for (int i = 0; i < index; i++){
                string finalData = type[i]+","+condi[i]+","+val[i];
                configSet2 << finalData;
            }
        }
    }
    else if(configSet.is_open() && configRead.peek() == ifstream::traits_type::eof()){
        string finalData = tp+","+con+","+data;
        configSet << finalData;
    }
    configRead.close();
    configSet.close();
    configSet2.close();
    //delete type, condi, val;
}

string Manager::getConfig(string tp){
    string data = "";
    string *type = new string[5];
    string *condi = new string[5];
    string *val = new string[5];
    string tpS, conS, dataS, text;
    int index = 0;
    int f;
    ifstream config;
    config.open("config.txt");
    if(config.is_open() && config.peek() != ifstream::traits_type::eof()){
        while (getline(config, text)){
            stringstream line(text);
            getline(line, tpS, ',');
            getline(line, conS, ',');
            getline(line, dataS);
            type[index] = tpS;
            condi[index] = conS;
            val[index] = dataS;
            index++;
        }

        for(int  i = 0; i < index; i++){
            if(tp == type[i]){
                f = i;
                break;
            }
        }
        data = condi[f]+"/"+val[f];
    }
    config.close();
    //delete type, condi, val;
    return data;
}
