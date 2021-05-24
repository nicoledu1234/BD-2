#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

int mo(int t, int m) {
  int mo = -1;
  if (t < 0)
	  return (t*mo >= m) ? (t - (t/m * m)) + m : t+ m;
  return (t >= m) ? t - (t/m * m) : t;
}
int generadorNumAleatorio(int maximo){
    srand(time(NULL));
    int aleatorio, DESDE=0, HASTA=maximo;
    aleatorio = mo(rand(),HASTA);
    return aleatorio;
}

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

    else if( str2==update|| str2==update1){
        func=4;
        oracionSql.erase(0,6);
    }

    else if( str2==remove|| str2==remove1){
        func=5;
        oracionSql.erase(0,6);
    }

    string tmp;

    for(int i=0;i<oracionSql.length();i++){
        if(oracionSql.at(i)=='('|| oracionSql.at(i)==')'|| oracionSql.at(i)==' ' ||oracionSql.at(i)==','||oracionSql.at(i)==';'){
            if(tmp!= " "  && tmp!="SET" && tmp!="WHERE" && tmp!="Where" && tmp!="AS" && tmp!="As"&& tmp!="Set" &&  tmp!="\0") sentencia.push_back(tmp);
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

struct Columna{
    
    string name;
    
    string type;
    
    Columna(){
        this->name="";
        this->type="";
    }
    
    Columna(string name,string tipo){
        this->name= name;
        this->type=tipo; 
    }
};

ofstream metadata;

ifstream metadata1;

struct Tabla{
    string nombre;
    
    vector<Columna*> atributos;
    
    int cantColumnas=0;
    
    int numFilas=0;
    
    ofstream tabla1;
    
    ifstream tabla2;
    
    string nombreTablaTXT;

    Tabla(string name, vector<Columna*> atr){

        nombre= name;
        
        atributos= atr;
        
        cantColumnas=atributos.size();
        
        string tmp=nombre;
        
        string t=".txt";
        
        tmp+=t;
        
        nombreTablaTXT=tmp;
        
        tabla1.open(tmp,ios::app);

        tabla2.open(tmp,ios::app);

        string metadataName="metadata";
        
        metadataName+=nombre;
        
        metadata1.open(metadataName);
        
        string copy;
        
        getline(metadata1,copy);
        
        if (copy!=nombre) {
            
            metadata1.clear();
            
            metadata.open(metadataName,ios::app);
            
            metadata<< name<<endl;
            
            metadata<<cantColumnas<<endl;
        
            for(int i=0; i<cantColumnas; i++ ){
                
                metadata<<atributos[i]->name << " , "<<atributos[i]->type <<endl;
            }
        }
        else {
            cout<<"La tabla " << nombre<< " ya existe."<<endl;
        }
    }
};

bool insert(Tabla *table, vector<string> registro){
    
    if(!table->tabla1.is_open()){
       
        table->tabla1.open(table->nombreTablaTXT,ios::app);
    }
    
    for(int i=0;i<table->cantColumnas;i++){
       
        table->tabla1<<registro[i]<< "/";
    }
    
    table->tabla1<<endl;
    
    table->numFilas++;
    
    return true; 
}

bool update(Tabla *table,string dato , string cambioD){
    ofstream temporal;
    ifstream entrada ;

    if(!table->tabla1.is_open()){
    
        table->tabla1.open(table->nombreTablaTXT,ios::app);
    }
    if(!table->tabla2.is_open()){
   
        table->tabla2.open(table->nombreTablaTXT,ios::app);
    }

    temporal.open("tmp.txt");
    bool s;
    string copy;
    int r=0;
    while(getline(table->tabla2,copy)){
        vector <string> reg;
        string tmp;
        int cont=0;
        int j=0;
        int r=0;
        for(int i=0;i<copy.length();i++){
            if(copy.at(i)!='/'){
                tmp.push_back(copy.at(i));
            }
            else {
                cont++;
                reg.push_back(tmp);
                tmp.clear();
            }
        }
        reg.push_back(tmp);

        for(int i=0; i<reg.size();i++){
            if( reg[i]== dato){
                temporal<< cambioD <<"/";
                s=true;
            }
            else temporal<< reg[i]<<"/";
        }
        temporal<<endl;
        r++;
    }
    table->tabla2.close();
    temporal.close();
    string tmp=table->nombreTablaTXT;
    const char * str2 = tmp.c_str();
    remove(str2);
    rename("tmp.txt",str2);

    return s;

}

bool remove(Tabla *table, string dato ){
    ofstream temporal;
    ifstream entrada ;
    if(!table->tabla1.is_open()){
        table->tabla1.open(table->nombreTablaTXT,ios::app);
    }
    if(!table->tabla2.is_open()){
        table->tabla2.open(table->nombreTablaTXT,ios::app);
    }
    
    temporal.open("tmp1.txt");

    string copy;
    bool s;
    int r=0;
    while(getline(table->tabla2,copy)){

        vector <string> reg;
        string tmp;
        for(int i=0;i<copy.length();i++){
            if(copy.at(i)!='/'){
                tmp.push_back(copy.at(i));
            }
            else {
                reg.push_back(tmp);
                tmp.clear();
            }
        }
        reg.push_back(tmp);
        
        for(int i=0; i<reg.size();i++){
            if( reg[i]== dato){
                reg.clear();
                s=true;
            }
        }
       for(int i=0; i<reg.size();i++){
            temporal<< reg[i]<<"/";
        }
        temporal<<endl;
    }

    table->tabla2.close();
    temporal.close();
    string tmp=table->nombreTablaTXT;
    const char * str2 = tmp.c_str();
    remove(str2);
    rename("tmp1.txt",str2);

    return s;

}
bool select(Tabla *table, vector<Columna*> columnasSelect){

    if(!table->tabla1.is_open()){
        table->tabla1.open(table->nombreTablaTXT,ios::app);
    }
    if(!table->tabla2.is_open()){
        table->tabla2.open(table->nombreTablaTXT,ios::app);
    }

    if(table->cantColumnas == columnasSelect.size()){
        string copy;
        while(!table->tabla2.eof()){

            getline(table->tabla2,copy,'\n');

            vector <string> reg;
            string tmp;
            int cont=0;
            int j=0;
            int r=0;
            for(int i=0;i<copy.length();i++){
                if(copy.at(i)!='/'){
                    tmp.push_back(copy.at(i));
                }
                else {
                    cont++;
                    reg.push_back(tmp);
                    tmp.clear();
                }
            }
            reg.push_back(tmp);
            for(int i=0; i<reg.size()-1;i++){
                cout<< reg[i]<<" ";
            }
            cout<< reg[reg.size()-1]<<endl;
        }
        cout<<"Select *"<<endl;
        table->tabla2.close();
        return true;
    }

vector<int> contS;
    int aux=0;
    for(int i=0; i<columnasSelect.size();i++){
        if(table->atributos[i]->name==columnasSelect[i]->name){
            aux++;
        }
        else {
            contS.push_back(aux);
        }
    }

    contS.push_back(aux);
    string copy;

    while(!table->tabla2.eof()){

        getline(table->tabla2,copy,'\n');
        vector <string> reg;
        string tmp;
        int cont=0;
        int j=0;
        int r=0;
        for(int i=0;i<copy.length();i++){
            if(!contS.empty()&& cont==contS[j]){
                for(int k=i;k<copy.length();k++){
                    if(copy.at(k)!='/'){
                        i++;
                    }
                    else { break;}
                } 
                j++;
            }

            if(copy.at(i)!='/'){
                tmp.push_back(copy.at(i));
            }
            else {
                cont++;
                reg.push_back(tmp);
                tmp.clear();
            }
        }
        reg.push_back(tmp);
        for(int i=0; i<reg.size()-1;i++){
            cout<< reg[i]<<" ";
        }
        cout<< reg[reg.size()-1]<<endl;
    }
    table->tabla2.close();
    return true;
}

int main(){
    vector<Columna*>colu;
    vector<Tabla*>tabs;

    Columna a("w","w"); Columna b("w","w"); Columna c("w","w");
    Columna d("w","w"); Columna e("w","w"); Columna f("w","w");
    Columna g("w","w"); Columna h("w","w"); Columna i("w","w");
    Columna j("w","w");
    colu.push_back(&a);colu.push_back(&b);colu.push_back(&c);
    colu.push_back(&d);colu.push_back(&e);colu.push_back(&f);
    colu.push_back(&g);colu.push_back(&h);colu.push_back(&i);
    colu.push_back(&j);

    cout<< "------ Manejador de Archivos -------"<<endl;
    string sql;
    cout<< "Comando sql a ejecutar "<<endl;
    getline(cin, sql);
    vector<string> bla;
    aFuncion(bla,sql);
    cout<<endl;
    ///CREAR TABLA
    int r=0;
    vector<Columna*> col;
    for(int i=1;i<bla.size(); ){ 
        colu[r]->name=bla[i];
        i++;
        colu[r]->type=bla[i];
        i++;
        col.push_back(colu[r]);
        r++;  
    }
    Tabla tab(bla[0],col);
    tabs.push_back(&tab);
    string sql1;
        getline(cin, sql1);
        string consulta="for(i =0 ; i<20000; i++ ) Insert Into Peruanos(DNI,nombre,apellido,edad,fecha) Values (11111111+i, Nombre+(11111111+i),Apellido+(11111111+i),RANDOM(1-100),RANDOMDATE(01/01/1970-31/12/1990));";
        string ert=consulta.substr(0,3);
        if (ert=="for"){
            int dni=11111111;
          for(int i =0 ; i<20000 ; i++ ) {
              vector<string> consul;
              dni++;
              string a1= to_string(dni);
              consul.push_back(a1);
              string n1="Nombre"+a1;
              consul.push_back(n1);
              string d1="Apellido"+a1;
              consul.push_back(d1);
              int ed=generadorNumAleatorio(100);
              string ed1=to_string(ed);
              consul.push_back(ed1);
              int di=generadorNumAleatorio(28);
              string di1=to_string(di);
              int me=generadorNumAleatorio(12);
              string me1=to_string(me);
              int ao=generadorNumAleatorio(20);
              ao+=1970;
              string ao1=to_string(ao);
              string date=di1+"-"+me1+"-"+ao1;
              consul.push_back(date);
              insert(&tab,consul);
          }
        }
    
    bool code=true;
    while(code){
        
        string sql1;
        getline(cin, sql1);
        vector<string> oracion;
        int b=aFuncion(oracion,sql1);
        switch(b){
            //Tabla tab ---Columnas col
            case 2:{
                /// INSERT
                Tabla *t;
                vector<string> ingreso;
                for(int i=0;i<tabs.size();i++){
                    if(oracion[0]== tabs[i]->nombre) {
                        t=tabs[i];
                        break;
                    }
                }
                for(int i=(oracion.size()/2)+1;i<oracion.size();i++){
                    if(oracion[i]== "Values" || oracion[i]== "VALUES") continue;
                    ingreso.push_back(oracion[i]);
                }
                bool q= insert(t,ingreso);
                if(q == true) cout<<"Dato ingresado correctamente"<<endl;
                else cout<<"Error en el ingreso"<<endl;
                break;
            }
            break;
            case 3:{
                ///Select
                vector<Columna*> colu10; vector<Columna*> colu20;
                vector<Columna*> colu30; vector<Columna*> colu40;
                vector<Columna*> colu50;
                vector<vector<Columna*> >vectCol;
                vectCol.push_back(colu10);vectCol.push_back(colu20);
                vectCol.push_back(colu30);vectCol.push_back(colu40);
                vectCol.push_back(colu50);
                Tabla *t1;
                if(oracion[0]=="*"){
                    for(int i=1;i<oracion.size();i++){
                        if(oracion[i]== "FROM" || oracion[i]== "From"){
                            for(int j=0;j<tabs.size();j++){
                                if(oracion[i+1]==tabs[j]->nombre){
                                    t1=tabs[j];
                                    break;
                                }
                            }
                        }
                    }
                    bool w=select(t1,t1->atributos);
                    if(w == true) cout<<"Seleccion Correcta"<<endl;
                    else cout<<"Error en la Seleccion"<<endl;
                }
                else {
                    for(int i=1;i<oracion.size();i++){
                        if(oracion[i]== "FROM" || oracion[i]== "From"){
                            for(int j=0;j<tabs.size();j++){
                                if(oracion[i+1]==tabs[j]->nombre){
                                    t1=tabs[j];
                                }
                            }
                        }
                    }
                    for(int i=0;i<oracion.size();i++){
                        for(int j=0;j<t1->atributos.size();j++){
                            //cout<<oracion[i]<<endl;
                            //cout<<t1->atributos[j]->name<<endl;
                            if(oracion[i]==t1->atributos[j]->name){
                                colu10.push_back(t1->atributos[j]);
                            }  
                        }
                    }

                    bool w=select(t1,colu10);
                    if(w == true) cout<<"Seleccion Correcta"<<endl;
                    else cout<<"Error en la Seleccion"<<endl;
                    colu10.clear();
                }
                colu.clear();

                break;
            }
            break;
            case 4: {
                //update
                cout<<"update"<<endl;
                vector<Columna*> colu10;
                Tabla *t2;
                vector<string> ingreso;
                for(int i=0;i<tabs.size();i++){
                    if(oracion[0]== tabs[i]->nombre) {
                        t2=tabs[i];
                        break;
                    }
                }
                
                bool w=update(t2,oracion[1],oracion[2]);
                if(w == true) cout<<"Dato Correctamente modificado"<<endl;
                else cout<<"Error en la modificacion"<<endl;
                break;
            }
            break;
            case 5: {
                //REMOVE
                Tabla *t3;
                for(int i=0;i<tabs.size();i++){
                    if(oracion[0]== tabs[i]->nombre) {
                        t3=tabs[i];
                        break;
                    }
                }
                
                bool w=remove(t3,oracion[1]);
                if(w == true) cout<<"Dato Correctamente eliminado"<<endl;
                else cout<<"Error en el borrado"<<endl;
                break;
                
            }
            break;
            case 0: {
                code=false ;
            }
            break;
        }
        oracion.clear();
    }
    return 0;
}
