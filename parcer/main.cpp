#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

int aFuncion (vector <string> &sentencia, string oracionSql){
    int func=0;
    string str2 = oracionSql.substr (0,4);  
    string createTable="CREA";
    string createTable1="Crea";
    string insert="INSE";
    string insert1="Inse";
    string select="SELE";
    string select1="Sele";
    string update="UPDA";
    string update1="Upda";
    string remove="REMO";
    string remove1="Remo";
    string values="Values";
    string values1="VALUES";

    if( str2==createTable || str2==createTable1){
        func=1;
        oracionSql.erase(0,12);
    }

    else if( str2==insert|| str2==insert1){
        func=2;
        oracionSql.erase(0,11);
    }

    else if( str2==select|| str2==select1){
        func=3;
        oracionSql.erase(0,6);
    }

    else if( str2==update|| str2==update){
        func=4;
        oracionSql.erase(0,6);
    }

    else if( str2==remove|| str2==remove1){
        func=5;
        oracionSql.erase(0,6);
    }

    string tmp;

    for(int i=0;i<oracionSql.length();i++){
        char e=oracionSql.at(i);
        if(oracionSql.at(i)=='('|| oracionSql.at(i)==')'|| oracionSql.at(i)==' ' ||oracionSql.at(i)==','||oracionSql.at(i)==';'){
            if(tmp!= " "  && tmp!="VALUES" && tmp!="Values" && tmp!="\0") sentencia.push_back(tmp);
            tmp.clear();
        }
        else {
            tmp.push_back(oracionSql.at(i));
        }
    }
    return func;
} 
void removerEspacios(vector<string>&sentencia){
    vector<string> tmp;
    for(int i=0; i<sentencia.size();i++){
        if (sentencia[i]!="\0") tmp.push_back(sentencia[i]);
    }
    sentencia=tmp;
}

int main(){
    
    string sql;

     getline(cin, sql);

    vector<string> bla;
    bool a=aFuncion(bla,sql);
    if (a == 0) {
        cout<<"ERROR"<<endl;
    }
    
    else {
       removerEspacios(bla);
       
        for ( int i=0; i< bla.size()-1 ;i++){
            cout<<bla[i];
        }
        cout<<bla[bla.size()-1]<<endl;
    }
    
    return 0;

}