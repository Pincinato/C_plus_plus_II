#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <map>
#include "billionaire.h"
using namespace std;

void ex2_a(void);
void ex2_b(void);
void ex3(void);

int main()
{
    //ex2_a();
    //ex2_b();
    ex3();
    return 0;
}

void ex2_a(){

 vector <pair < string , string >> vec
        { make_pair ("Homer", " 1111 "),
         make_pair ("Marge", " 2222 "),
         make_pair ("Lisa", " 3333 "),
         make_pair ("Magy", " 4444 "),
         make_pair ("Bart", " 5555 ")};

 unordered_map <string,string> book(vec.begin(),vec.end());
 cout<<"Enter name (or Exit ): "<<endl;
 string input;
 cin>>input;
 auto it= book.find(input);
 if(it != book.cend()){
     cout<<" Phone number : "<<it->second<<endl;
 }
 else { cout<<"Name not in directory ."<<endl;}

}


void ex2_b(){

    vector <pair < string , string >> vec
           { make_pair ("Homer", " 1111 "),
            make_pair ("Homer", " 11122 "),
            make_pair ("Homer", " 11133 "),
            make_pair ("Marge", " 2222 "),
            make_pair ("Lisa", " 3333 "),
            make_pair ("Magy", " 4444 "),
            make_pair ("Bart", " 5555 ")};
    multimap <string,string> book(vec.begin(),vec.end());
    cout<<"Enter name (or Exit ): "<<endl;
    string input;
    cin>>input;
    auto it = book.equal_range(input);
    if(it.second != book.end()){
        cout<<"Number(s): ";
        for(auto i = it.first; i!= it.second; ++i ){
            cout<< i->second <<" ";
     }
     cout<<endl;
    }
    else { cout<<"Name not in directory ."<<endl;}
}

void ex3(void){

    ifstream in("Forbes2018.txt");
    cout<<"Exercise 3"<<endl;
    if (!in) cout << " WARNING : File not found !" << endl ;
    else{
        vector <Billionaire> billionaires ;
        copy(istream_iterator <Billionaire>(in), istream_iterator <Billionaire>(),back_inserter(billionaires));
        copy (billionaires.begin() ,billionaires.end(),ostream_iterator<Billionaire>(cout));
        //cout<<billionaires.size();
        cout<<endl<<"Second part "<<endl;
        map < string , pair < const Billionaire , size_t >> mymap;
        for(auto &it : billionaires){
           auto b= mymap.try_emplace(it.country,make_pair(it,1));
            if(b.second ==false){
                //b.first.;
                int abc;
                abc=0;
            }

        }
    }
}


