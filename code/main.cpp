#include <iostream>
#include <algorithm>
#include <chrono>
#include <string.h>
#include <fstream>
#include "distance.h"
#include <sstream>

using namespace std;

//PARA TOMAR EL TIEMPO
template <typename Func>
long long execution_time_ms(Func function, string tarea, int id_dataset) 
{
  auto start_time = std::chrono::high_resolution_clock::now();
  
  function(tarea, id_dataset);

  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

// PROCESOS
//1 - Ejecución clásica - Gutenberg vs Gutenberg
void distancia_clasica_g_vs_g(int id_dataset)
{
    //Lectura de archivo 1 en string 1
    stringstream strStream1;
    ifstream file1;
    string filename1 = "datasets/input/g_vs_g/alicia" + to_string(id_dataset) + ".txt";
    file1.open(filename1);
    if(!file1.is_open()){
        cout << "ERROR!!! el archivo " << filename1 << " no se pudo abrir\n";
        return;
    }
    strStream1 << file1.rdbuf();
    string string1 = strStream1.str(); 

    //Lectura de archivo 2 en string 2
    stringstream strStream2;
    ifstream file2; //ARCHIVO DE ENTRADA 2
    string filename2 = "datasets/input/g_vs_g/metamorfosis" + to_string(id_dataset) + ".txt";
    file2.open(filename2);
    if(!file2.is_open()){
        cout << "ERROR!!! el archivo " << filename2 << " no se pudo abrir\n";
        return;
    }
    strStream2 << file2.rdbuf();
    string string2 = strStream2.str(); 

    //Calcula distancia entre strings
    cout << clasica(string1,string2) << endl;

    return;
}

//2 - Ejecución adaptiva
void distancia_adaptiva_g_vs_g(int id_dataset)
{
    //Lectura de archivo 1 en string 1
    stringstream strStream1;
    ifstream file1; //ARCHIVO DE ENTRADA 1
    string filename1 = "datasets/input/g_vs_g/alicia" + to_string(id_dataset) + ".txt";
    file1.open(filename1);
    if(!file1.is_open()){
        cout << "ERROR!!! el archivo " << filename1 << " no se pudo abrir\n";
        return;
    }
    strStream1 << file1.rdbuf();
    string string1 = strStream1.str(); 

    //Lectura de archivo 2 en string 2
    stringstream strStream2;
    ifstream file2; //ARCHIVO DE ENTRADA 2
    string filename2 = "datasets/input/g_vs_g/metamorfosis" + to_string(id_dataset) + ".txt";
    file2.open(filename2);
    if(!file2.is_open()){
        cout << "ERROR!!! el archivo " << filename2 << " no se pudo abrir\n";
        return;
    }
    strStream2 << file2.rdbuf();
    string string2 = strStream2.str(); 

    //Calcula distancia entre strings
    cout << adaptiva(string1,string2) << endl;

    return;
}


//3 - Ejecución clásica - Gutenberg Vs Alterado Gutenberg
void distancia_clasica_g_vs_ag(int id_dataset)
{

    //Lectura de archivo 1 en string 1
    stringstream strStream1;
    ifstream file1;
    string filename1 = "datasets/input/g_vs_ag/alicia_base.txt";
    file1.open(filename1);
    if(!file1.is_open()){
        cout << "ERROR!!! el archivo " << filename1 << " no se pudo abrir\n";
        return;
    }
    strStream1 << file1.rdbuf();
    string string1 = strStream1.str(); 

    //Lectura de archivo 2 en string 2
    stringstream strStream2;
    ifstream file2; //ARCHIVO DE ENTRADA 2
    string filename2 = "datasets/input/g_vs_ag/alicia" + to_string(id_dataset) + ".txt";
    file2.open(filename2);
    if(!file2.is_open()){
        cout << "ERROR!!! el archivo " << filename2 << " no se pudo abrir\n";
        return;
    }
    strStream2 << file2.rdbuf();
    string string2 = strStream2.str(); 

    //Calcula distancia entre strings
    cout << clasica(string1,string2) << endl;

    return;
}

//4 - Ejecución adaptiva
void distancia_adaptiva_g_vs_ag(int id_dataset)
{
    //Lectura de archivo 1 en string 1
    stringstream strStream1;
    ifstream file1;
    string filename1 = "datasets/input/g_vs_ag/alicia_base.txt";
    file1.open(filename1);
    if(!file1.is_open()){
        cout << "ERROR!!! el archivo " << filename1 << " no se pudo abrir\n";
        return;
    }
    strStream1 << file1.rdbuf();
    string string1 = strStream1.str(); 

    //Lectura de archivo 2 en string 2
    stringstream strStream2;
    ifstream file2;
    string filename2 = "datasets/input/g_vs_ag/alicia" + to_string(id_dataset) + ".txt";
    file2.open(filename2);
    if(!file2.is_open()){
        cout << "ERROR!!! el archivo " << filename2 << " no se pudo abrir\n";
        return;
    }
    strStream2 << file2.rdbuf();
    string string2 = strStream2.str(); 

    //Calcula distancia entre strings
    cout << adaptiva(string1,string2) << endl;

    return;
}


//CENTRO DE LLAMADA DE FUNCIONES
void centro_tareas(string tarea, int id_dataset)
{
    if (tarea=="distancia-clasica-g-vs-g") {return distancia_clasica_g_vs_g(id_dataset); } 
    if (tarea=="distancia-adaptiva-g-vs-g") {return distancia_adaptiva_g_vs_g(id_dataset); } 
    if (tarea=="distancia-clasica-g-vs-ag") {return distancia_clasica_g_vs_ag(id_dataset); } 
    if (tarea=="distancia-adaptiva-g-vs-ag") {return distancia_adaptiva_g_vs_ag(id_dataset); } 
}

//BLOQUE PRINCIPAL
int main(int argv, char* argc[]) {
  srand(time(NULL)); 

  int n; //tamaño muestras
  int id_proceso;

  int numero_de_experimentos;
  string dir_csv;
  string tarea_seleccionada;
  string nombre_archivo_salida;

  dir_csv = "csv/";

  cout<<"INICIO"<<endl;

  //TAREAS DE ACUERDO A PARÁMETRO ENVIADO AL PROGRAMA
  id_proceso=atoi(argc[1]);
  switch(id_proceso){

    case 1: tarea_seleccionada = "distancia-clasica-g-vs-g"; break;
    case 2: tarea_seleccionada = "distancia-adaptiva-g-vs-g"; break;
    case 3: tarea_seleccionada = "distancia-clasica-g-vs-ag"; break;
    case 4: tarea_seleccionada = "distancia-adaptiva-g-vs-ag"; break;

    default: tarea_seleccionada = ""; break;
  }

  //SI ENTRA CON PARÁMETROS, REALIZA EL TEST
  if((argv > 2) && (strcmp(argc[2],"--test") == 0)){

    int id_dataset = atoi(argc[4]);
    switch(atoi(argc[4]))
    {
      case 1: n = 100; break;
      case 2: n = 200; break;
      case 3: n = 300; break;
      case 4: n = 400; break;
      case 5: n = 500; break;

      default: n = 0; break;
    }

    //SI SON PROCESOS DE DIFERENCIAS PEQUEÑAS
    if (
        (id_proceso==3 || id_proceso==4)
        )
    {
      switch(atoi(argc[4]))
      {
        case 1: n = 1; break;
        case 2: n = 2; break;
        case 3: n = 3; break;
        case 4: n = 4; break;
        case 5: n = 5; break;
        case 6: n = 6; break;
        case 7: n = 7; break;
        case 8: n = 8; break;
        case 9: n = 9; break;
        case 10: n = 10; break;
        case 11: n = 11; break;
        case 12: n = 12; break;
        case 13: n = 13; break;
        case 14: n = 14; break;
        case 15: n = 15; break;
        case 16: n = 16; break;
        case 17: n = 17; break;
        case 18: n = 18; break;
        case 19: n = 19; break;
        case 20: n = 20; break;

        default: n = 0; break;
      }
    }


    cout<<"Tarea seleccionada: "<< tarea_seleccionada<<endl;

    nombre_archivo_salida = dir_csv + tarea_seleccionada + "-results.csv";
    ofstream outfile(nombre_archivo_salida,std::ios::app);

    double mm_total_time = 0;
    int numero_de_experimentos=10;
    for(int j = 0; j < numero_de_experimentos; j++){ 

        long long single_execution_time = execution_time_ms(centro_tareas, tarea_seleccionada, id_dataset);
        mm_total_time += single_execution_time;
      
    }
    double mm_avg_time = mm_total_time / numero_de_experimentos;
    outfile << n << "," << mm_avg_time <<endl;
    outfile.close(); 
    
    return 0;
  }
  else
  //SINO CREA EL ENCABEZADO PARA GUARDAR EL CSV
  {
    nombre_archivo_salida = dir_csv + tarea_seleccionada + "-results.csv";
    ofstream outfile(nombre_archivo_salida);
    outfile << "Tamaño muestra,Tiempo[ms]\n";

    return 0;
  }


}

