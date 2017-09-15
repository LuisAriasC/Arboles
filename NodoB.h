//
//  Nodo.h
//  ArbolB
//
//  Created by JJ Santos on 9/13/17.
//  Copyright © 2017 JJ Santos. All rights reserved.
//

#ifndef Nodo_h
#define Nodo_h

using namespace std;
template <class T>
struct Nodo {
    
    int llave = NULL;
    int espaciosUsados = 0;
    int padre = NULL;
    bool leaf = false;
    T *info;
    int *hijos;
    
    
    
    Nodo(int);
    Nodo(int,int,fstream &);
    virtual ~Nodo();
    
    bool checkFull(int);
    
    
    void printInfo();
    void print(int);
    
};

template <class T>
void Nodo<T>::printInfo(){
    for(int i = 0; i < espaciosUsados;i++){
        cout << info[i] << " ";
    }
}




template <class T>
bool Nodo<T>::checkFull(int orden){
    return espaciosUsados==orden*2-1;
}


template <class T>
Nodo<T>::Nodo(int orden){
    info = new T[2*orden-1];
    hijos = new int[2*orden+1];
}

template <class T>
void Nodo<T>::print(int orden){
    cout << "Nodo: ";
    cout << llave << endl;
    cout << "Padre: ";
    cout << padre << endl;
    
    cout << "Info: ";
    printInfo();
    cout << endl;
    if(!leaf){
        cout << "Hijos: ";
        for(int i = 0; i < espaciosUsados+1;i++){
            cout << hijos[i] << " ";
        }
        cout << endl;
    }
    else{
        cout << "Leaf" << endl;
    }
    
    cout << endl;
}



template <class T>
Nodo<T>::~Nodo(){
}
#endif /* Nodo_h */
