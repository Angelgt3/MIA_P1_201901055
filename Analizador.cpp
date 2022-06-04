
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include<bits/stdc++.h>

#include <stdio.h>

using namespace std;

class analizar
{
public:
    analizar();
    void SE_linea(string linea);
    void leer();
    void Comandos(string comand,string para[],string valor[]);
    void para_dato(string datos[]);
};

analizar::analizar(){
    leer();
}

void analizar::Comandos(string comand,string para[], string valor[]){
    
    //OPCIONES
    
    if(comand!="")
    {    
        cout<<"comando: "+comand<<endl;
        if (comand=="mkdisk"){ //mkdisk
            for(size_t i=1; i <20;i++){      
                if (para[i]=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (para[i]=="$size"){

                }
                else if (para[i]=="$path"){
                    
                }
                else if (para[i]=="$name"){
                    
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+para[i]<<endl;
                //cout<<"valor: "+valor[i]<<endl;
            }
        }else if(comand=="rmdisk"){ //rmdisk
            for(size_t i=1; i <20;i++){      
                if (para[i]=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (para[i]=="$path"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+para[i]<<endl;
                //cout<<"valor: "+valor[i]<<endl;
            } 
        }else if (comand=="fdisk"){ //fdisk
            for(size_t i=1; i <20;i++){      
                if (para[i]=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (para[i]=="$size"){

                }
                else if (para[i]=="@unit"){
                    
                }
                else if (para[i]=="$path"){
                    
                }
                else if (para[i]=="@type"){
                    
                }
                else if (para[i]=="@fit"){
                    
                }
                else if (para[i]=="@delete"){
                    
                }
                else if (para[i]=="$name"){
                    
                }
                else if (para[i]=="@add"){
                    
                }
                else if (para[i]=="@mov"){
                    
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+para[i]<<endl;
                //cout<<"valor: "+valor[i]<<endl;
            }
        }else if(comand=="mount"){ //mount
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$path"){

                    }
                    else if (para[i]=="$name"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="unmount"){ //unmount
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id#"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="mkfs"){ //mkfs
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id"){

                    }
                    else if (para[i]=="@type"){

                    }
                    else if (para[i]=="@add"){

                    }
                    else if (para[i]=="@unit"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="mkfile"){ //mkfile
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id"){

                    }
                    else if (para[i]=="$path"){

                    }
                    else if (para[i]=="@p"){

                    }
                    else if (para[i]=="@size"){

                    }
                    else if (para[i]=="@cont"){

                    }
                    else if (para[i]=="$fileid"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    cout<<"parametro: "+para[i]<<endl;
                    cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="exec"){ //exec
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$path"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="rm"){ //rm
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id"){

                    }
                    else if (para[i]=="$fileid"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="mkdir"){ //mkdir
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id"){

                    }
                    else if (para[i]=="$path"){

                    }
                    else if (para[i]=="@p"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    cout<<"parametro: "+para[i]<<endl;
                    cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="cp"){ //cp
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id"){

                    }
                    else if (para[i]=="$path"){

                    }
                    else if (para[i]=="$dest"){

                    }
                    else if (para[i]=="$iddest"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                } 
        }else if(comand=="ls"){ //ls
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id"){

                    }
                    else if (para[i]=="$path"){

                    }
                    else if (para[i]=="$Order"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                }
        }
        else if(comand=="pause"){ //pause

        }
        else if(comand=="loss"){ //loss
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$id"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                }
        }
        else if(comand=="rep"){ //rep
                for(size_t i=1; i <20;i++){      
                    if (para[i]=="") //se sale si ya no viene mas atributos u.u
                        break;
                    else if (para[i]=="$name"){

                    }
                    else if (para[i]=="$path"){

                    }
                    else if (para[i]=="$id"){

                    }
                    else
                        cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                    //cout<<"parametro: "+para[i]<<endl;
                    //cout<<"valor: "+valor[i]<<endl;
                }
        }
        else
            cout<<"COMANDO NO RECONOCIDO"<<endl;
    }


    //cout<<"fin de una linea"<<endl;    
}


//separo parametros y valores en diferentes arrays (una linea)
void analizar::para_dato(string datos[]){
    string parametros[20];
    string valores[20];
    for(size_t i=1; i <20;i++){
        if (datos[i]=="") //se sale si ya no viene mas atributos u.u
            break;
        else{
            int pos=0;
            //cout<<datos[i]<<endl;
            pos=datos[i].find("=>"); 
            parametros[i]=datos[i].substr(0,pos);
            valores[i]=datos[i].substr(pos+2,datos[i].length());
            //cout<<"parametro:" +parametros[i]<<endl;
            //cout<<"valor: "+valores[i]<<endl;
            }
    }   
    Comandos(datos[0],parametros,valores);
}

//separo las lineas por espacios
void analizar::SE_linea(string linea){
    string datos[20];
    string palabra;
    int cont=0;
    stringstream nline(linea);
    while (getline(nline, palabra, ' ')){
        //cout << palabra << endl; //separadas en palabras
        datos[cont]=palabra;
        cont+=1;
    }
    para_dato(datos);
}

//separo el archivo en lineas
void analizar::leer(){

    ifstream archivo_entrada("entrada.txt");
    string linea;
    while(getline(archivo_entrada, linea)) {
        //lo comvierte todo a minuscula
        transform(linea.begin(), linea.end(), linea.begin(), ::tolower);
        //cout << linea << endl; //separadas por linea
        SE_linea(linea);
    }

}
