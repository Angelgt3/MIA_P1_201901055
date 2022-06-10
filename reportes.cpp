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
    void mbr(string path,string id);
    ~reportes();
};

//opciones de reportes
reportes::reportes(string name,string path, string id ){
    
    if(name=="disk"){
        disk(path,id);
    }
    else if(name=="mbr"){
        mbr(path,id);
    }
}

//Crear el reporte de mbr
void reportes::mbr(string path,string id){
    FILE *archivo;  // Se abre el archivo para leer mbr
    archivo=fopen((path+id).c_str(),"r");
    MBR mbr;
    fseek(archivo,0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo); // Guarda el mbr del archivo en "mbr"
    fclose(archivo); // Se cierra el archivo
    string contenido="digraph { \n\t labelloc=\"t\" \n\t label=\"REPORTE MBR\" \n\t rankdir=LR"; 
    contenido+="\n\t node[ shape=record style=\"filled\" ]";
    
    //escribir ebrs
    for (size_t i = 0; i < 4; i++){ //recorro las particiones
        if(mbr.particiones[i].part_type=='e'){ //hay extendida
            int k;    
            FILE *archivo;
            archivo=fopen((path+id).c_str(),"r");
            EBR ebr;
            fseek(archivo,sizeof(MBR),SEEK_SET);
            fread(&ebr, sizeof(ebr), 1, archivo); // Guarda el ebr del archivo en "ebr"
            fclose(archivo);
            if (ebr.part_next==0){ //si no hay ebr es 0
                archivo=fopen((path+id).c_str(),"r+");
                fseek(archivo,sizeof(MBR), SEEK_SET);
                fread(&ebr, sizeof(EBR), 1, archivo); // lo guardo en el archivo
                fclose(archivo);
                contenido+="\n\t ebr"+to_string(k)+"[ \n\t\t label= \"EBR";
                contenido+="|part_fit: ";
                contenido+=char(ebr.part_fit);
                contenido+="|part_start: ";
                contenido+=to_string(ebr.part_start);
                contenido+="|part_size: ";
                contenido+=to_string(ebr.part_size);
                contenido+="|part_next: ";
                contenido+=to_string(ebr.part_next);
                contenido+="|part_name: ";
                contenido+=ebr.part_name;
                contenido+="\"\n\t];\n";
                k++;
                /*
                cout<<"---------------------"+to_string(sizeof(MBR))<<endl;
                cout<<ebr.part_fit<<endl;
                cout<<ebr.part_name<<endl;
                cout<<ebr.part_next<<endl;
                cout<<ebr.part_size<<endl;
                cout<<ebr.part_start<<endl;
                */
                

            }
            else{
                int pos=sizeof(MBR);
                do{
                    pos+=sizeof(EBR);
                    contenido+="\n\t ebr"+to_string(k)+"[ \n\t\t label= \"EBR";
                    contenido+="|part_fit: ";
                    contenido+=char(ebr.part_fit);
                    contenido+="|part_start: ";
                    contenido+=to_string(ebr.part_start);
                    contenido+="|part_size: ";
                    contenido+=to_string(ebr.part_size);
                    contenido+="|part_next: ";
                    contenido+=to_string(ebr.part_next);
                    contenido+="|part_name: ";
                    contenido+=ebr.part_name;
                    contenido+="\"\n\t];\n";
                    
                    k++;
                    if (ebr.part_next==1){
                        contenido+="ebr"+to_string(k-1)+" -> ebr"+to_string(k);
                    }
                    /*
                    cout<<"---------------------"+to_string(pos)<<endl;
                    cout<<ebr.part_fit<<endl;
                    cout<<ebr.part_name<<endl;
                    cout<<ebr.part_next<<endl;
                    cout<<ebr.part_size<<endl;
                    cout<<ebr.part_start<<endl;
                    */
                    
                    FILE *arch2;
                    arch2=fopen((path+id).c_str(),"r");
                    EBR ebr2;
                    fseek(arch2,pos,SEEK_SET);
                    fread(&ebr2, sizeof(ebr2), 1, arch2); // Guarda el ebr del archivo en "ebr"
                    fclose(arch2);
                    ebr=ebr2;
                }while (ebr.part_next==1);

                }
        }
    }
    contenido+="\n\t mbr[ \n\t\t label= \"MBR|mbr_tamaño: "+to_string(mbr.tamanio)+" |mbr_creacion: "+to_string(time_t(mbr.fecha_creacion))+ " |mbr_disk_signature: "+to_string(mbr.disk_signature);
    for (size_t i = 0; i < 4; i++){ //escribir mbr
        contenido+="|PARTICION "+to_string(i+1);
        char temp='0';
        if (mbr.particiones[i].part_status=='m')
            temp='1';
        contenido+="|part_status: ";
        contenido+=temp;
        contenido+="|part_type: ";
        contenido+=char(mbr.particiones[i].part_type);
        contenido+="|part_fit: ";
        contenido+=char(mbr.particiones[i].part_fit);
        contenido+="|part_start: ";
        contenido+=to_string(mbr.particiones[i].part_start);
        contenido+="|part_size: ";
        contenido+=to_string(mbr.particiones[i].part_size);
        contenido+="|part_name: ";
        contenido+=mbr.particiones[i].part_name;

        /*
        cout<<"partition-------------------------"<<endl;
        cout<<temp<<endl;
        cout<<mbr.particiones[i].part_type<<endl;
        cout<<mbr.particiones[i].part_fit<<endl;
        cout<<mbr.particiones[i].part_start<<endl;
        cout<<mbr.particiones[i].part_size<<endl;
        cout<<mbr.particiones[i].part_name<<endl;
        */

    }
    contenido+="\"\n\t];\n";
    
    contenido+="\n}\n";
    ofstream file;
    file.open(path+"rep_mbr.dot");
    file << contenido;
    file.close();
    //string comand="dot -Tpng rep_disk.dot -o rep_disk.svg";
    //system(comand.c_str());

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
        else if(mbr.particiones[i].part_type=='e' or mbr.particiones[i].part_type=='a'){
            contenido+="|{EXTENDIDA|{";
            
            FILE *archivo;
            archivo=fopen((path+id).c_str(),"r");
            EBR ebr;
            fseek(archivo,sizeof(MBR),SEEK_SET);
            fread(&ebr, sizeof(ebr), 1, archivo); // Guarda el ebr del archivo en "ebr"
            fclose(archivo);

            if (ebr.part_next==0){ //si no hay ebr es 0
                archivo=fopen((path+id).c_str(),"r+");
                fseek(archivo,sizeof(MBR), SEEK_SET);
                fread(&ebr, sizeof(EBR), 1, archivo); // lo guardo en el archivo
                fclose(archivo);
                
                contenido+="EBR|LIBRE|";
                
                /*
                cout<<"---------------------"+to_string(sizeof(MBR))<<endl;
                cout<<ebr.part_fit<<endl;
                cout<<ebr.part_name<<endl;
                cout<<ebr.part_next<<endl;
                cout<<ebr.part_size<<endl;
                cout<<ebr.part_start<<endl;
                */

            }
            else{
                int pos=sizeof(MBR);
                do{
                    pos+=sizeof(EBR);
                    if (ebr.part_size>0)
                        contenido+="EBR|LOGICA|";
                    else
                        contenido+="EBR|LIBRE|";
                    /*
                    cout<<"---------------------"+to_string(pos)<<endl;
                    cout<<ebr.part_fit<<endl;
                    cout<<ebr.part_name<<endl;
                    cout<<ebr.part_next<<endl;
                    cout<<ebr.part_size<<endl;
                    cout<<ebr.part_start<<endl;
                    */
                    FILE *arch2;
                    arch2=fopen((path+id).c_str(),"r");
                    EBR ebr2;
                    fseek(arch2,pos,SEEK_SET);
                    fread(&ebr2, sizeof(ebr2), 1, arch2); // Guarda el ebr del archivo en "ebr"
                    fclose(arch2);
                    ebr=ebr2;

                }while (ebr.part_next==1);
                }
           
            contenido+="}}";
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