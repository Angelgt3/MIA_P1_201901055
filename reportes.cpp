#include<iostream>
#include <stdlib.h>
#include <stdio.h>

#include "estructuras.h"

using namespace std;

class reportes
{
public:
    reportes(string name,string path,string id);
    void disk(string path,string id);
    ~reportes();
};

//opciones de reportes
reportes::reportes(string name,string path, string id ){
    
    if(name=="disk"){
    
        disk(path,id);
    }
}

//Crear el reporte de disk
void reportes::disk(string path,string id){
    
    FILE *archivo;  // Se abre el archivo para leer mbr
    archivo=fopen((path+id).c_str(),"r");
    MBR mbr;
    fseek(archivo,0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo); // Guarda el mbr del archivo en "mbr"
    fclose(archivo); // Se cierra el archivo

    //contenido es el contenido del .dot
    string contenido="digraph { \n\t labelloc=\"t\" \n\t label=\"Disk\""; 
    contenido+="\n\t node[ shape=record style=\"filled\" ]";
    contenido+="\n\t struct[ \n\t\t label= \"MBR";
    for (size_t i = 0; i < 4; i++){ //recorro las particiones
        if(mbr.particiones[i].part_status=='l'){
            contenido+="|LIBRE";
        }
        else if(mbr.particiones[i].part_type=='p'){
            contenido+="|PRIMARIA";
        }
        else if(mbr.particiones[i].part_type=='e'){
            contenido+="|{EXTENDIDA|{EBR|A|EBR|B}";
            //ebrs
            contenido+="}";
        }
    }
    contenido+="\"\n\t];\n}";

    ofstream file;
    file.open(path+"rep_disk.dot");
    file << contenido;
    file.close();
    //string comand="dot -Tpng rep_disk.dot -o rep_disk.svg";
    //system(comand.c_str());
    
}


reportes::~reportes(){}