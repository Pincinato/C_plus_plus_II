#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include "billionaire.h"
using namespace std;

void ex2_a(void);
void ex2_b(void);
void ex3(void);

int main()
{
    ex2_a();
    ex2_b();
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
            make_pair ("Magy", " 54545 "),
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
    cout<<endl<<"Exercise 3 "<<endl;
    if (!in) cout << " WARNING : File not found !" << endl ;
    else{
        vector <Billionaire> billionaires ;
        copy(istream_iterator <Billionaire>(in), istream_iterator <Billionaire>(),back_inserter(billionaires));
        copy_n(billionaires.begin() ,10,ostream_iterator<Billionaire>(cout,"\n"));
        map < string , pair < const Billionaire , size_t >> mymap;
        for(auto &it : billionaires){
           auto it_pair= mymap.emplace(it.country,make_pair(it,1));
            if(it_pair.second ==false){
                it_pair.first->second.second++;
            }
        }
        cout<<"....."<<endl;
        cout<<endl<<"My map - first 5 positions "<<endl;
        copy_n(mymap.begin(),6,ostream_iterator<pair<string,pair<const Billionaire,size_t>>>(cout,"\n"));
        vector <pair<string ,pair <Billionaire, size_t >>> vec(mymap.begin(),mymap.end());
        cout<<endl<<"The richest person - separated by Country"<<endl;
        sort(vec.begin(),vec.end(),[](pair<string ,pair < Billionaire, size_t >> &a,pair<string ,pair < Billionaire, size_t >> &b){return (stoi(a.second.first.fortune,nullptr,10)>stoi(b.second.first.fortune,nullptr,10));});
        copy_n(vec.begin(),6,ostream_iterator<pair<string,pair<const Billionaire,size_t>>>(cout,"\n"));
        cout<<endl<<"Country with the most billionaires"<<endl;
        sort(vec.begin(),vec.end(),[](pair<string ,pair < Billionaire, size_t >> &a,pair<string ,pair < Billionaire, size_t >> &b){return (a.second.second>b.second.second);});
        copy_n(vec.begin(),6,ostream_iterator<pair<string,pair<const Billionaire,size_t>>>(cout,"\n"));
    }
}

ostream& operator <<(ostream& out, const pair<string, pair<const Billionaire, size_t>> &Source) {
    out<<Source.second.first.country<<" : "<<Source.second.second<<" billionaires. Richest is "<<Source.second.first.name<<" with "<<Source.second.first.fortune<<" B$";
    return out;
}
