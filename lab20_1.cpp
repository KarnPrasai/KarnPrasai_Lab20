#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string& filename, vector<string>& names, vector<int>& scores, vector<char> &grades) {
    ifstream file;
    file.open(filename);
    string textline;
    while(getline(file,textline))
    {
        char format[] = "%[^:]: %d %d %d";
        char name[50];
        int a,b,c;
        sscanf(textline.c_str(),format,name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "NAME")
    {
        cin.ignore();
        getline(cin,key);
    }
    else if(toUpperStr(command) == "GRADE")
    {
        cin >> key;
    }
    else if(toUpperStr(command) == "EXIT")
    {
    
    }
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key) 
{
    bool namefounded = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0;i<names.size();i++)
    {
        string Name = toUpperStr(names.at(i));
        if(Name == key)
        {
            cout << names.at(i) << "'s score = " << scores.at(i) << endl;
            cout << names.at(i) <<"'s grade = " << grades.at(i) << endl;
            namefounded = true;
            break;
        }
    }
    if(!namefounded)
    {
     cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key) 
{
    char Grade[2];
    bool founded = false;
    cout << "---------------------------------\n";
    for(unsigned int i =0;i<grades.size();i++)
    {
        Grade[0] = grades.at(i);;
        Grade[1] = '\0';
        if(key == Grade)
        {
            cout << names.at(i) << " (" << scores.at(i) << ")" << endl;
            founded = true;
        }
    }
    if(!founded)
    {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}