#include<iostream>
#include <stdlib.h>
#include <stdio.h>

#include "estructuras.h"

using namespace std;

class unmount
{
public:
    unmount();
    void desmontar(string path, string name);    
    ~unmount();
};

unmount::unmount(){}

void unmount::desmontar(string path,string name){
    FILE *archivo;  // Se abre el archivo para leer mbr
    archivo=fopen(path.c_str(),"r");
    MBR mbr;
    fseek(archivo,0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo); // Guarda el mbr del archivo en "mbr"
    fclose(archivo); // Se cierra el archivo

    for(size_t i=0; i <4;i++){  //recorrer las particiones del mbr
        if(mbr.particiones[i].part_name == name){ //se encontro la particion
            mbr.particiones[i].part_status='o'; //se coloca el nuevo valor
        }
    }
    archivo=fopen(path.c_str(),"r+"); //se abre el archivo para escribir
    fseek(archivo,0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, archivo); 
    fclose(archivo);
}

unmount::~unmount(){}