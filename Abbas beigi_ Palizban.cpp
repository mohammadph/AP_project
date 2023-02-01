#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
class Library{
    private:
        
    public:
      
        void search(string searchItem)
        {
            ifstream testFile("books.txt");    
            string line;
            smatch result;
            bool found = false;
                while(getline(testFile, line))
                {
                    regex expr("(?:"+searchItem+")");
                    regex_search(line, result, expr);
                    if (searchItem == result[0])
                    {
                        cout << line << endl;
                        found = true;
                    }
                }
                if(found == false)
                {
                    string searchItem;
                    cout << "not found" << endl;
                    char ans;
                    cout << "search again? (y/n)";
                    cin >> ans;
                    if (ans == 'y'){
                        cout << "search:";
                        cin >> searchItem;
                        search(searchItem);
                    }
                }
        }
        void give(string book,string userid){
            ifstream testFile; 
            testFile.open("books.txt");
            string line;
            smatch result;
            static string deleteline;
                while(getline(testFile, line))
                {
                    regex expr("(?:"+book+")");
                    regex_search(line, result, expr);
                   
                    if (book == result[0])
                    {
                        regex expr("(?:free)");
                        regex_search(line, result, expr);
                        if ("free"==result[0])
                        {
                            cout << "This book is free you Got it." << endl;
                            int index;
                            string sub_str="NUll "+userid;
                            deleteline=line;
                            index = line.find("free");
                            line.replace(index, sub_str.length(), sub_str);
                            testFile.close();
                            // delete the previos line
                            string line_new;
                            ifstream fin;
                            fin.open("books.txt");
                            ofstream temp;
                            temp.open("books_new.txt",ios::app);
                            temp << line << endl;
                        
                            //cout << deleteline;
                            while (getline(fin,line_new))
                            {
                                if (line_new != deleteline)
                                {
                                    temp << line_new << endl;
                                }
                            }
                            temp.close();
                            fin.close();
                            remove("books.txt");
                            rename("books_new.txt","books.txt");
                        }else{
                          
                            string searchItem;
                            string book;
                            cout << "This book is not free" << endl;
                            char ans;
                            cout << "search again? (y/n)";
                            cin >> ans;
                            if (ans == 'y'){
                                cout << "search:";
                                cin >> searchItem;
                                search(searchItem);
                                cout << "which one do you want to get?" << endl << "type here:";
                                cin >> book;
                                give(book,userid);
                            }
                        }
                    }
                
                            
                }
               
        }
        void returnbook(string book,string userid)
        {
            ifstream testFile; 
            testFile.open("books.txt");
            string line;
            smatch result;
            static string deleteline;
            while(getline(testFile, line))
            {
                regex expr("(?:"+book+")");
                regex_search(line, result, expr);
            
                if (book == result[0])
                {
                    regex expr("(?:"+userid+")");
                    regex_search(line, result, expr);
                
                    if (userid == result[0])
                    {
                        int index;
                        int p;
                        string sub_str="NUll";
                        string subi_str="NUll";
                        deleteline=line;
                        index = line.find("free");
                        p=line.find(userid);
                        line.replace(index, sub_str.length(), sub_str);
                        line.replace(p, subi_str.length(), subi_str);
                        
                    
                        testFile.close();
                        string line_new;
                        ifstream fin;
                        fin.open("books.txt");
                        ofstream temp;
                        temp.open("books_new.txt",ios::app);
                        temp << line << endl;
                        //cout << deleteline;
                        while (getline(fin,line_new))
                        {
                            if (line_new != deleteline)
                            {
                                temp << line_new << endl;
                            }
                        }
                    temp.close();
                    fin.close();
                    remove("books.txt");
                    rename("books_new.txt","books.txt");
                  
                    }
                    else
                    {
                        cout<<"You are Not the one who should Return this book!";
                    }
                    
                    
               
                }

                    
            }
                
                
                    
           
                
            
        }
    
};      
class personality
{
private:
      
public:

    void signup(){
        string userName;
        string password;
        string firstName;
        string lastName;
        string birth;

        cout << "Please give me your username:";
        cin >> userName;
        cout << endl << "Please give me your password:";
        cin >> password;
        cout  << endl << "What's your First Name:";
        cin >> firstName;
        cout << endl <<  "What's your Last Name:";
        cin >> lastName;
        cout << endl << "Date of birth YYYY/MM/DD:";
        cin >> birth;
        cout << endl;


        string accountinfo = "user"+userName + " pass" + password + " " + firstName + " " + lastName + " " + birth;
        fstream file;
        file.open ("users.txt", ios::app );
        file << accountinfo << endl;
        file.close();
    }
    bool login(string password, string username){
        fstream file;
        string input = "user"+username + " pass" + password + " " + ".+";
        file.open ("users.txt");
        string accountData = "";
        while(getline(file, accountData))
        { //read data from file object and put it into string.
            if (regex_match(accountData, regex(input))){
                return true;
            }
        }
        return false;
    } 
};  
int main(){
    personality person;
    Library L;
    string acc;
    string username;
    string password;
    string ans;
    string searchitem;
    bool loginsucess = false;
    do{//login
        cout << "Login or Signup? ";
        cin >> acc;
        if (acc == "Login"){
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            loginsucess =  person.login(password, username);
            if (loginsucess == false){
                cout << "The username or password is wrong. To try again type (a) and to signup type (s):";
                cin >> ans;
                if (ans == "s"){
                    person.signup();
                    loginsucess = true;
                }
            }
            else
            {
                cout<<"you are logged in"<<endl;
                
            }
            
        }
        else if (acc == "Signup"){
            person.signup();
            person.login(password,username);
        }
    }while (loginsucess == false);
    //if logged in
    if (person.login(password, username))
    {   
        string rg;
        bool runcode=true;
        cout<<"do You want to get(g) or return(r) a book:";
        cin>>rg;
        while (runcode)
        {
            if (rg=="g")
            {
                cout<<"Please Search your book: ";
                cin>>searchitem;
                L.search(searchitem);
                cout << "which one do you want to get?" << endl << "type here:";
                string book;
                cin >> book;
                L.give(book,username);
            }
            else if (rg=="r")
            {
                string book_give;
                cout <<"type the book name here:";
                cin >> book_give;
                L.returnbook(book_give,username);
            }
            
            cout<<"What do you want to do now get more books(g) or return any book(r)or nothing(n):";
            cin>>rg;
            if (rg=="n")
            {
                cout<<"Have Nice Day";
                runcode=false;
            }
            
        }
        
        
    }
    return 0;

}