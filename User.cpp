//User.cpp
#include "Headers/User.hpp"

Customer::Customer(){
    draw();
    displayOptions();
    get_movie();
}

void Customer::draw(){
    cout << "\t###################################################" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t#"<<"          **Welcome To BlockBuster**"         <<"\t\t  #" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t#                                                 #" << endl;
    cout << "\t###################################################" << endl;
}

void Customer::displayOptions(){
    cout << "\t\t>>> The No.1 Best Buy For Movies <<<\n";
    if(collUserInfo <= 0){
        store_PINFO();
    }
    Manager manager;
    string *genreList = manager.getGenreList();
    int size = manager.get_genre_list_size();
    genreSize = size;
    this->genreList = genreList;
    cout << "=================" << endl;
    cout << "=  ===GENRE===  =" << endl;
    for(int i=0;i<size;i++){
        cout << "=  " <<i<<"."<<genreList[i] << "\t=" <<endl;
    }
    cout << "=================" << endl;
    collUserInfo++;
}
void Customer::get_movie(){
    Manager MD;
    int run = 1;
    int c1 = 1;
    int selectM;
    int genreType;
    vector<string> names;
    int totalMovies = 0;
    string gn;
    string mn;
    while(run){
        try{
            cout << "Choose Type of Genre(-1 to EXIT) -> ";
            cin >> genreType;
            if(!cin.good()){
                throw genreType;
            }
            if(genreType == -1){
                cout << "Thank You for using BlockBuster!!!" << endl;
                cout << "Come Back and Stay Safe";
                run = 0;
            }
            else if(genreType >=0 && genreType < genreSize){
                gn = genreList[genreType];
                MD.readFromFile(gn);
                names = MD.getMovieName(MD.getMovieDetailNodeFR());
                sort(names.begin(), names.end());
                MD.sortMD(MD.getMovieDetailNodeFR());
                while(c1){
                    if(names.size() != 0){
                        cout << "Available Movies" << endl;
                        cout <<"~~~~~~~~~~~~~~~~~~~~"<< endl;
                        totalMovies = 0;
                        for(auto i = names.cbegin();i!=names.cend();i++){
                            cout << totalMovies<<". " << *i << endl;
                            totalMovies++;
                        }
                        cout << endl;
                        try{
                            cout << "Enter Movie Number to view details(-1 to EXIT) -> ";
                            cin >> selectM;
                            if(!cin.good()){
                                throw selectM;
                            }
                            if(selectM == -1){
                                c1 = 0;
                                run = 0;
                                displayOptions();
                                get_movie();

                            }
                            else if(selectM >=0 &&  selectM < totalMovies){
                                mn = names[selectM];
                                MD.displayMD(MD.getMovieDetailNodeFBS(), mn);
                                purchase_ops(&c1, mn ,gn);
                            }
                            else{
                                cout << "Please Enter proper movie number!" << endl; 
                            }
                        }
                        catch(...){
                            cout << "error -Invalid input!";
                            exit(1);
                        }

                    }
                    else{
                        cout << "No movie available!" << endl;
                    }
                }
            }
            else{
                cout << "Please Enter proper genre number!" << endl;
            }
        }
        catch(...){
            cout << "error -Invalid input!";
            exit(1);
        }
        
    }
}

void Customer::purchase_ops(int *c, string mn,string gn){
    int ch;
    int type;
    int con;
    cout << "\t*Movie Purchase Option*" << endl;
    cout << "1.Buy" << endl;
    cout << "2.Rent" << endl;
    cout << "3.Exit" << endl;
    try{
        cout << "Please one purchase option -> ";
        cin >> ch;
        if(!cin.good()){
            throw ch;
        }
        switch (ch){
            case 1:
            	cout << "\nYou have choosen Buy Option\n";
                cout << "\t*Movie Purchase Type*" << endl;
                cout << "1.Physical" << endl;
                cout << "2.Digital" << endl;
                try{
                    cout << "Please select one purchase type -> ";
                    cin >> type;
                    if(!cin.good()){
                        throw type;
                    }
                    if(type == 1){
                        con = write_recepit(mn, gn, "phy");
                        if(con == -1){
                            c = 0;
                        }
                        else{
                            cout << "You have purchased " << mn << " movie" << endl;
                        }
                    }
                    else if(type == 2){
                        con = write_recepit(mn,gn, "digital");
                        if(con == -1){
                            c = 0;
                        }
                        else{
                            cout << "You have purchased " << mn << " movie" << endl;
                        }
                    }
                }
                catch(...){
                    cout << "error -Invalid input!";
                    exit(1);
                }
                break;
            case 2://suren
            	cout << "\nYou have choosen Rent Option\n\n";
            	int warrantyOption;
            	cout << ">>>> Warranty Duration Option <<<<\n";
            	cout << "\n\nWarranty Date for Rent";
        		cout << "\n[1] 20 Days";
        		cout << "\n[2] 50 Days";
        		cout << "\n[3] 70 Days";
        		cout << "\nChoose Warranty Option: ";
            	cin >> warrantyOption;
        
        switch(warrantyOption){
            case 1:
            
            cout << "\nYour Rent Warranty will be for 20 days.Please return it after 20 days";
            cout << "\n****Customer will be fined RM100 for not returning it on time****\n\n";
            
            break;
            case 2:
            cout << "\nYour Rent Warranty will be for 50 days.Please return it after 50 days";
            cout << "\n****Customer will be fined RM75 for not returning it on time****\n\n";
            
            
            break;
            case 3:
            cout << "\nYour Rent Warranty will be for 70 days.Please return it after 70 days";
            cout << "\n****Customer will be fined RM50 for not returning it on time****\n\n";
             
            break;
        }
            	
            	cout << "\t*Movie Purchase Type*" << endl;
                cout << "1.Physical" << endl;
                cout << "2.Digital" << endl;
                try{
                    cout << "Please select one purchase type -> ";
                    cin >> type;
                    if(!cin.good()){
                        throw type;
                    }
                    if(type == 1){
                        con = write_recepit(mn, gn, "phy");
                        if(con == -1){
                            c = 0;
                        }
                        else{
                            cout << "You have purchased " << mn << " movie" << endl;
                        }
                    }
                    else if(type == 2){
                        con = write_recepit(mn,gn, "digital");
                        if(con == -1){
                            c = 0;
                        }
                        else{
                            cout << "You have purchased " << mn << " movie" << endl;
                        }
                    }
                }
                catch(...){
                    cout << "error -Invalid input!";
                    exit(1);
                }
            	
            	
                break;
            case 3:
                c = 0;
                break;
            default:
                cout << "Please Enter proper number!" << endl; 
        }
    }
    catch(...){
        cout << "error -Invalid input!";
        exit(1);
    }
   
}

int Customer::write_recepit(string mn, string gn , string purType){
    int con;
    ofstream myFile;
    time_t now = time(0);
    char *dt = ctime(&now);
    string path = "Recepit/"+mn+"Recepit"+to_string(rand())+".txt";
    string version;
    if(purType == "phy"){
        con = price(purType);
        if (con!=-1){
            if(con == 15){
                version = "Normal Disc";
            }
            else if(con == 35){
                version = "Blue Ray";
            }
            else if(con == 150){
                version = "Collectors Edition";
            }
            else{
                version = "4K";
            }
            myFile.open(path, ios::out);//write
            if(myFile.is_open()){
                myFile << "\n========================================\n";
                myFile << "=           Customer Recipt            =";
                myFile << "\n========================================\n";
                myFile << "\nName           : " << customerName ;
                myFile << "\nContact Number : " << contactNumber;
                myFile << "\nHome Address   : " << address;
                myFile << "\nEmail Address  : " << emailAdresss;
                myFile << "\nDate Purchased : " << dt;
                myFile << "\nType of Genre  : "<<gn;
                myFile << "\nName of Movie  : "<<mn;
                myFile << "\nMovie Version  : "<<version;
                myFile << endl;
                myFile << "                  Movie price - " << to_string(con) << " RM" << endl;
                myFile << "                  Delivery Charge - 5 RM" << endl;
                myFile << "                  Total Amount - "<< to_string(con+5) <<" RM" << endl;
                myFile << "\n========================================\n";
                //suren
                
                myFile << "\n>>>>>>>>> Thank You and Stay Safe <<<<<<<<<";
            }
        }
        else{
            con = -1;
        }
    }
    else if(purType == "digital"){
        con = price(purType);
        if (con!=-1){
            if(con == 40){
                version = "HD";
            }
            else if(con == 100){
                version = "Collectors Edition";
            }
            else{
                version = "4K";
            }
            myFile.open(path, ios::out);//write
            string link = "https://"+mn+"123_fake.com";
            if(myFile.is_open()){
                myFile << "\n========================================\n";
                myFile << "=           Customer Recipt            =";
                myFile << "\n========================================\n";
                myFile << "\nName               : " << customerName ;
                myFile << "\nContact Number     : " << contactNumber;
                myFile << "\nHome Address       : " << address;
                myFile << "\nEmail Address      : " << emailAdresss;
                myFile << "\nDate Purchased     : " << dt;
                myFile << "\nType of Genre      : "<<gn;
                myFile << "\nName of Movie      : "<<mn;
                myFile << "\nMovie Version      : "<<version;
                myFile << "\nLink to Download   : " << link;
                myFile << endl;
                myFile << "                   Movie price - " << to_string(con) << " RM" << endl;
                myFile << "                   Total Amount - "<< to_string(con) <<" RM" << endl;
                myFile << "\n========================================\n";
                //suren
                
                myFile << "\n>>>>>>>>> Thank You and Stay Safe <<<<<<<<<";
            }
        }
        else{
            con = -1;
        }
    }
    myFile.close();
    return con;
}

int Customer::price(string purType){
    int price;
    int run = 1;
    char movieVersion;
    if(purType == "phy"){
        cout << "\n==============================";
        cout << "\n= [A]Normal Disc        [RM15]";
        cout << "\n= [B]Blue Ray           [RM35]";
        cout << "\n= [C]Collectors Edition [RM150]";
        cout << "\n= [D]4K                 [RM50]";
        cout << "\n= [E]Exit               [....]";
        cout << "\n==============================";
        while(run){
            cout << "\nChoose type of version -> ";
            cin >> movieVersion;
            switch (movieVersion){
                case 'A':
                    price = 15;
                    break;
                case 'B':
                    price = 35;
                    break;
                case 'C':
                    price = 150;
                    break;
                case 'D':
                    price = 50;
                    break;
                case 'E':
                    price = -1;
                default:
                    cout << "Please enter proper option!" << endl; 
            }
            return price;
        }
    }
    else if(purType == "digital"){
        cout << "\n==============================";
        cout << "\n= [A]HD                 [RM40]";
        cout << "\n= [B]Collectors Edition [RM100]";
        cout << "\n= [C]4K                 [RM60]";
        cout << "\n= [E]Exit               [....]";
        cout << "\n==============================";
        while(run){
            cout << "\nChoose type of version -> ";
            cin >> movieVersion;
            switch (movieVersion){
                case 'A':
                    price = 40;
                    break;
                case 'B':
                    price = 100;
                    break;
                case 'C':
                    price = 60;
                    break;
                case 'E':
                    price = -1;
                default:
                    cout << "Please enter proper option!" << endl; 
            }
            return price;
        }
    }

    return price; 
}

void Customer::store_PINFO(){
    cout << "***Your Information and Private Data will be safely secured with us at all times***" << endl;
    cout << "Please fill in Your Information for further clarification" << endl;  
    cout << "Enter Your Name            : ";
    getline(cin >> ws, customerName);
    cout << "Enter Your Contact Number  : ";
    getline(cin >> ws, contactNumber);
    cout << "Enter Email Address        : ";
    getline(cin >> ws, emailAdresss);
    cout << "Enter Address              : ";
    getline(cin >> ws, address);
}