
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>

#include "mkfile.cpp"
#include "mkdisk.cpp"

#include <stdio.h>

using namespace std;

class analizar
{
public:
    analizar();
    void SE_linea(string linea);
    void Comandos(string comand,string para[]);
    void leer();
};

analizar::analizar(){
    leer();
}



void analizar::Comandos(string comand,string para[]){
    
    //OPCIONES
    
    if(comand!="")
    {    
        //cout<<"comando: "+comand<<endl;
        if (comand=="mkdisk"){ //mkdisk
            int size;
            string path,name;
            for(size_t i=1; i <20;i++){      
                if(para[i]=="")
                    break;
                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$size"){
                    size=stoi(valor);
                }
                else if (parametro=="$path"){
                    path=valor.substr(1,valor.length()-2);
                }
                else if (parametro=="$name"){
                    name=valor;
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                cout<<"parametro: "+parametro<<endl;
                cout<<"valor: "+valor<<endl;
            }
            mkdisk *mkd=new mkdisk();
            mkd->crear(size,path,name);
        }else if(comand=="rmdisk"){ //rmdisk
            for(size_t i=1; i <20;i++){     

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$path"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if (comand=="fdisk"){ //fdisk
            for(size_t i=1; i <20;i++){   

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$size"){

                }
                else if (parametro=="@unit"){
                    
                }
                else if (parametro=="$path"){
                    
                }
                else if (parametro=="@type"){
                    
                }
                else if (parametro=="@fit"){
                    
                }
                else if (parametro=="@delete"){
                    
                }
                else if (parametro=="$name"){
                    
                }
                else if (parametro=="@add"){
                    
                }
                else if (parametro=="@mov"){
                    
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
        }else if(comand=="mount"){ //mount
            for(size_t i=1; i <20;i++){    

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$path"){

                }
                else if (parametro=="$name"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="unmount"){ //unmount
            for(size_t i=1; i <20;i++){      

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id#"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="mkfs"){ //mkfs
            for(size_t i=1; i <20;i++){    

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="@type"){

                }
                else if (parametro=="@add"){

                }
                else if (parametro=="@unit"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="mkfile"){ //mkfile
            string path;
            for(size_t i=1; i <20;i++){    

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){
                    path=valor;
                }
                else if (parametro=="@p"){

                }
                else if (parametro=="@size"){

                }
                else if (parametro=="@cont"){

                }
                else if (parametro=="$fileid"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
            mkfile *mkf= new mkfile();
            mkf->crear(path);
        }else if(comand=="exec"){ //exec
            for(size_t i=1; i <20;i++){     

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$path"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="rm"){ //rm
            for(size_t i=1; i <20;i++){      

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());
                
                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$fileid"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="mkdir"){ //mkdir
            for(size_t i=1; i <20;i++){ 

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="@p"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                cout<<"parametro: "+parametro<<endl;
                cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="cp"){ //cp
            for(size_t i=1; i <20;i++){    

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="$dest"){

                }
                else if (parametro=="$iddest"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="ls"){ //ls
            for(size_t i=1; i <20;i++){      

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());
                
                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="$Order"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
        }
        else if(comand=="pause"){ //pause

        }
        else if(comand=="loss"){ //loss
            for(size_t i=1; i <20;i++){      

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
        }
        else if(comand=="rep"){ //rep
            for(size_t i=1; i <20;i++){     

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$name"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="$id"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
        }
        else
            cout<<"COMANDO NO RECONOCIDO"<<endl;
    }


    //cout<<"fin de una linea"<<endl;    
}

//separo las lineas por espacios
void analizar::SE_linea(string linea){
    string comand="",palabra,parametros[20];
    stringstream nline(linea);
    int cont=0;
    while (getline(nline, palabra,' ')){
        if (comand!=""){
            parametros[cont]=palabra;
            cont++;
        }
        else
            comand=palabra;
    }
    Comandos(comand,parametros);
}

//separo el archivo en lineas
void analizar::leer(){

    ifstream archivo_entrada("entrada.txt");
    string linea;
    while(getline(archivo_entrada, linea)) {
        //lo comvierte todo a minuscula
        transform(linea.begin(), linea.end(), linea.begin(), ::tolower);
        //cout << linea << endl; //separadas por linea
        if(linea.substr(0,2)!="//")
            SE_linea(linea);
        
        
    }

}
