#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>

#include "estructuras.h"

using namespace std;

class mount
{
public:
    mount();
    void escribir(string path,string name);
    Discos buscar(vector<Discos>tdisks,string path,string name,Discos dis);
    Discos montar(string path, string name,vector<Discos> tmisdisk);    
    ~mount();
};

mount::mount(){}

void mount::escribir(string path,string name){
    FILE *archivo;  // Se abre el archivo para leer mbr
    archivo=fopen(path.c_str(),"r");
    MBR mbr;
    fseek(archivo,0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo); // Guarda el mbr del archivo en "mbr"
    fclose(archivo); // Se cierra el archivo

    for(size_t i=0; i <4;i++){  //recorrer las particiones del mbr
        if(mbr.particiones[i].part_name == name){ //se encontro la particion
            mbr.particiones[i].part_status='m'; //se coloca el nuevo valor
        }
    }
    archivo=fopen(path.c_str(),"r+"); //se abre el archivo para escribir
    fseek(archivo,0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, archivo); 
    fclose(archivo);
}

Discos mount::buscar(vector<Discos>tdisks,string path,string name,Discos dis){
    string abc[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    string letra="";
    int num=1;
    for (size_t i = 0; i < tdisks.size(); i++){
        if (tdisks[i].path==path){ // es de este disco
            if (tdisks[i].name==name){ //esta particion ya esta montada
                letra = "err";
                break;
            }
            letra=abc[tdisks[i].no_letra]; //consigo la letra
            num+=1; //el numero 
        }
    }
    if(letra==""){//no se encontro el disco (no esta montado el disco)
        int cont=0;
        for (size_t i = 0; i < tdisks.size(); i++){
            if (tdisks[i].no_letra>=cont){ //conseguir la letra mas grande que no este usada
                cont=tdisks[i].no_letra+1;
                dis.no_letra=cont;
                letra=abc[cont];
            }
        }
        if (tdisks.size()==0){//si no hay nada montado 
            letra=abc[0];
        }
    }
    dis.id="vd"+letra+to_string(num);
    //cout<<"mount: "+ dis.id <<endl;
    return dis;
}

Discos mount::montar(string path, string name,vector<Discos>tmisdisk){
    FILE *archivo;
    archivo=fopen(path.c_str(),"r"); //abro el archivo para leer
    MBR mbr;
    fseek(archivo,0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo); // Guardo el mbr del archivo
    fclose(archivo);

    Discos dis; //creo una estructura Discos para guardar los valores 
    for(int i=0;i<4;i++){ //busco si existe la particion
        if(mbr.particiones[i].part_name == name){ //se encontro la particion
            dis.particion=mbr.particiones[i]; 
            dis.name=name;
            dis.path=path;
            Discos newd=buscar(tmisdisk,path,name,dis);//se busca la letra y el numero para el id
            escribir(path,name); //escribir que esta montada la particion
            return newd;
        }
    }
    dis.id="err1";
    return dis;
}

mount::~mount(){}