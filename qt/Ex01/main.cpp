#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <numeric> //iota
#include <iterator>
#include <fstream>
#include <algorithm> // sort, find
#include <string>

using namespace std;

void ex2_1(void);
void ex2_2(vector <string> &vec);
void ex2_3(char letter,vector <string> &vec);
void ex2_4(string predicate,vector <string> &vec);
void ex3(void);
bool readFile(const char * const path,vector<string> &vecOutput);

int main()
{
    vector<string> vec;
    vec.clear();
    ex2_1();
    if(readFile("cars.txt",vec)){
        ex2_2(vec);
        ex2_3('A',vec);
        ex2_4("ABCD",vec);
    }
    ex3();
    return 0;
}

void ex2_1(void){

    vector <char> vec(26,0);
    cout<<endl<<" Exercise 1-2 -letters a-z and z-a"<<endl;
    iota(vec.begin(),vec.end(),'a');
    copy(vec.begin(),vec.end(), ostream_iterator<char> (cout," "));
    cout<<endl;
    reverse_copy(vec.begin(),vec.end(), ostream_iterator<char> (cout," "));

}

bool readFile(const char * const path,vector<string> &vecOutput){

    ifstream in(path);
    istream_iterator<string> it(in);
    if(in && in.is_open()){
        copy(istream_iterator<string> (in),istream_iterator<string>(),back_inserter(vecOutput));
        in.close();
        sort(vecOutput.begin(),vecOutput.end());
        return 1;
    }
    else {
        cout <<endl<<"Unable to open" << endl;
        return 0;
    }

}

void ex2_2(vector <string> &vec){


    cout<<endl<<endl<<" Exercise 2-2 - read a list with names of car brands"<<endl;
    copy(vec.begin(),vec.end(), ostream_iterator<string> (cout," "));

}

void ex2_3(char letter,vector <string> &vec){

     cout<<endl<<endl<<" Exercise 2-3a - Ordinary Loop"<<endl;
     for( auto it=vec.cbegin();it<vec.cend();it++){
             if(it.operator->()->at(0) == letter){ cout<<*it<<" ";}
      }
      cout<<endl<<endl<<" Exercise 2-3b - range based for loop"<<endl;
      for (const auto& car : vec){
        if(car.at(0)== letter){cout<<car<<" ";}
         }
}


void ex2_4(string predicate,vector <string> &vec){

    cout<<endl<<endl<<" Exercise 2-4 pred = "<<predicate<<endl;
    copy_if(vec.cbegin(),vec.cend(),ostream_iterator<string> (cout," "),[predicate](string toCompare)
    {
        if(toCompare.find_first_of(predicate) == 0){ return 1;}
        return 0;
     });
}

void ex3(void){

    set <string> vec;
    vec.clear();
    cout<<endl<<endl<<" Exercise 3 "<<endl<<"Please enter some text: ";
    copy(istream_iterator<string>(cin),istream_iterator<string>(),inserter(vec,vec.end()));
    cout<<"The unique word list contains:"<<endl<<endl;
    unique_copy(vec.begin(),vec.end(),ostream_iterator<string>(cout," "));
    cout<<endl;
}
