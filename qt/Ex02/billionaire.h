#ifndef BILLIONAIRE_H
#define BILLIONAIRE_H
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

class Billionaire
{

public:
    Billionaire();
    //vector <string> info;
    string name;
    string fortune;
    string country;

   friend istream& operator >>(istream& in, Billionaire &Destination) {
        char info[512];
        in.getline(info,512,'\t');
        Destination.name=info;
        in.getline(info,512,'\t');
        Destination.fortune=info;
        in.getline(info,512,'\n');
        Destination.country=info;
        //copy(istream_iterator<string>(test),istream_iterator<string>(),back_inserter(Destination.info));
       /*in>>Destination.first_name;
       */
       return in;
    }
    friend ostream& operator <<(ostream& out, vector<Billionaire>::iterator Source) {

        string space(" ");
        //out<<Source.info<<"\n";
        out<<Source->name <<space<<Source->fortune<<space<<Source->country<<endl;
        return out;
    }

    friend ostream& operator <<( vector<Billionaire>::iterator Source,ostream& out) {

        string space(" ");
        //out<<Source.info<<"\n";
        out<<Source->name <<space<<Source->fortune<<space<<Source->country<<endl;
        return out;
    }

    friend ostream& operator <<(ostream& out, Billionaire Source) {

        string space(" ");
        //out<<Source.info<<"\n";
        out<<Source.name <<space<<Source.fortune<<space<<Source.country<<endl;
        return out;
    }

};

#endif // BILLIONAIRE_H