#include <fstream>
#include <time.h>
#include <ctime>
#include <chrono>
#include "AVL.h"
#include "ArbolDosTres.h"
#include "ArbolB.h"

using namespace std;
using namespace std::chrono;

int main()
 {
     AVL<int> a;
     
     int n = 100000;
     int cienMil[n];
     ifstream fileCienMil("100000.txt");
     if(fileCienMil.is_open()){
         for(int i = 0; i < n; ++i){
             fileCienMil >> cienMil[i];
         }
     }
     fileCienMil.close();
     clock_t t;
     t = clock();
     for (int i = 0; i < n; i++) {
         a.insertar(cienMil[i]);
     }
     t = clock() - t;
     t = ((float)t)*1000;
     
     n = 10;
     int diez[n];
     ifstream fileDiez("10.txt");
     if (fileDiez.is_open()) {
         for (int i = 0; i < n; i++) {
             fileDiez >> diez[i];
         }
     }
     fileDiez.close();
     cout << "BUSQUEDA CON ARBOL AVL" << endl;
     for (int i = 0; i < n; i++) {
         cout << "Elemento a buscar: " << diez[i] << endl;
         t = clock();
         a.buscar(diez[i]);
         t = clock() - t;
         t = ((float)t)*1000;
         cout << (((float)t)/CLOCKS_PER_SEC) << " mili-segundos" << endl;
     }
     //printf("-Búsqueda de 10 elementos aleatorios: %f milisegundos.\n",((float)t)/CLOCKS_PER_SEC);
     
     //a.imprimir();
     //a.obtenerAltura(338800);
     //a.obtenerAltura(250);
     
     ArbolDosTres<int> nuevoArbol;
     int tam;
     ifstream archivo;
     
     archivo.open("100000.txt");
     archivo >> tam;
    
     for (int i=0; i<tam; i++)
     {
         int nuevoDato;
         archivo >> nuevoDato;
         nuevoArbol.insertar23(nuevoDato);
     }
     
     
     cout << endl << endl;
     cout <<"BUSQUEDA CON ARBOL 2-3" << endl;
     int aBuscar[] = {10, 99999, 34718, 666, 13000, 60000, 80570, 43263, 32055, 8729};
     high_resolution_clock::time_point t1;
     high_resolution_clock::time_point t2;
     duration<double> time_span;
     
     for(int i=0; i<10; i++)
     {
         cout << "Elemento a buscar: " << aBuscar[i] << endl;
         t1 = high_resolution_clock::now();
         nuevoArbol.buscar(aBuscar[i]);
         t2 = high_resolution_clock::now();
         time_span = (duration_cast<duration<double> >(t2-t1))*1000;
         cout << time_span.count() << " mili-segundos" << endl;
         
     }
     
     
     cout << endl << endl;
     cout << "BUSQUEDA CON ARBOL-B" << endl;
     int orden = 3;
     srand((int)time(NULL));
     
     ArbolB<int> * arbol = new ArbolB<int>(orden);
     
     for(int i = 0; i< 100000;i++){
         arbol->Insertar(rand()%10000);
     }
     
     for (int i = 0; i < 10;i++){
         t = clock();
         arbol->Buscar(rand() % 1000);
         t = clock() - t;
         t = ((float)t)*1000;
         cout << (((float)t)/ CLOCKS_PER_SEC) << " mili-segundos" << endl;
     }
     
     return 0;
 }

