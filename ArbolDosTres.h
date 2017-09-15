#include "NodoDosTres.h"
#include <iomanip>
#include <queue>
#include <iostream>
#include <vector>
template <class T>
class ArbolDosTres {
    
protected:
    NodoDosTres<T> * raiz = nullptr;
    std::vector<T> nivelesHoja;
    
public:
    ArbolDosTres() { }
    ~ArbolDosTres();
    
    bool empty();
    
    void clear();
    void clear(NodoDosTres<T> * nodo);
    
    NodoDosTres<T> * getRaiz() const;
    void setRaiz(const T info);
    void setRaiz(NodoDosTres<T> * nodo);
    bool isRoot(NodoDosTres<T> * nodo);
    
    void insertar23(T info);
    void insertar23(NodoDosTres<T> * info);
    void insertar23(NodoDosTres<T> * padre, NodoDosTres<T> * info);
    void insertar23(NodoDosTres<T> * padre, T info);
    
    void printAsc(NodoDosTres<T> * nodo, int nivel);
    void printAsc();
    
    void printDesc(NodoDosTres<T> * nodo, int nivel);
    void printDesc();
    
    void asignarRaiz(NodoDosTres<T>* raiz);
    bool esDosTres ();
    bool esDosTres(NodoDosTres<T>* nodo);
    
    void redistribuirHijos(NodoDosTres<T>* contenedor, NodoDosTres<T>* nodo1, NodoDosTres<T>* nodo2);
    void dividir(NodoDosTres<T>* contenedor);
    bool checaNodoDos(NodoDosTres<T>* nodo);
    bool checaNodoTres(NodoDosTres<T>* nodo);
    bool hijosLibres(NodoDosTres<T>* nodo);
    
    NodoDosTres<T>* buscarNodo(const T info, NodoDosTres<T> * nodo);
    bool buscar(const T info);
    
    NodoDosTres<T>* encontrarNodoABorrar(NodoDosTres<T>*, T info);
    bool borrarNodo(NodoDosTres<T>* nodo);
    bool borrar(T info);
    void arreglar(NodoDosTres<T>* nodo);
    NodoDosTres<T>* getSucesorInorder(NodoDosTres<T>* nodo);
    
    void getNivelesHoja(NodoDosTres<T>* nodo);
    bool getLlavesNodo(NodoDosTres<T>* nodo);
    bool getHijosNodo(NodoDosTres<T>* nodo);
    bool encontrarNodo(NodoDosTres<T>*, T info);
    
    void esHoja() ;
    bool esHoja(NodoDosTres<T> * nodo) ;
    
    void ancestros(NodoDosTres<T> * nodo) const;
    
    int getAltura() const;
    int getAltura(NodoDosTres<T> * nodo) const ;
    
    int getProfundidad() const;
    int getProfundidad(NodoDosTres<T> * nodo) const;
    
    int getNivel() const;
    int getNivel(NodoDosTres<T> * nodo) const;
    
    void ordenar(T a[], int N);
    
};

template <class T>
ArbolDosTres<T>::~ArbolDosTres() {
    clear();
}

template <class T>
bool ArbolDosTres<T>::empty() {
    return raiz == nullptr;
}

template <class T>
void ArbolDosTres<T>::clear() {
    clear(raiz);
}

template <class T>
void ArbolDosTres<T>::clear(NodoDosTres<T> * nodo) {
    if (nodo) {
        clear(nodo->getIzquierdo());
        clear(nodo->getDerecho());
        delete nodo;
    }
}

template <class T>
NodoDosTres<T> * ArbolDosTres<T>::getRaiz() const {
    return raiz;
}

template <class T>
void ArbolDosTres<T>::setRaiz(const T info) {
    NodoDosTres<T> * nodo = new NodoDosTres<T>(info);
    setRaiz(nodo);
}

template <class T>
void ArbolDosTres<T>::setRaiz(NodoDosTres<T> * nodo) {
    if (!empty()) {
        nodo->setIzquierdo(raiz);
        raiz->setPadre(nodo);
        raiz = nodo;
    }
    else {
        raiz = nodo;
    }
}

template <class T>
bool ArbolDosTres<T>::isRoot(NodoDosTres<T> * nodo) {
    return nodo == this->raiz;
}

template <class T>
void ArbolDosTres<T>::insertar23(T info) {
    insertar23(this->raiz, info);
}

template <class T>
void ArbolDosTres<T>::insertar23(NodoDosTres<T> * info) {
    insertar23(this->raiz, info);
}

template <class T>
void ArbolDosTres<T>::asignarRaiz(NodoDosTres<T>* nodo) {
    raiz = nodo;
}

template <class T>
void ArbolDosTres<T>::redistribuirHijos(NodoDosTres<T>* contenedor, NodoDosTres<T>* nodo1, NodoDosTres<T>* nodo2) {
    nodo1->setIzquierdo(contenedor->getIzquierdo());
    nodo1->setDerecho(contenedor->getCentro());
    nodo2->setIzquierdo(contenedor->getTemp());
    nodo2->setDerecho(contenedor->getDerecho());
    nodo1->getIzquierdo()->setPadre(nodo1);
    nodo1->getDerecho()->setPadre(nodo1);
    nodo2->getIzquierdo()->setPadre(nodo2);
    nodo2->getDerecho()->setPadre(nodo2);
}

template <class T>
void ArbolDosTres<T>::dividir(NodoDosTres<T>* contenedor) {
    
    if(isRoot(contenedor)) {
        NodoDosTres<T>* newRoot = new NodoDosTres<T>(contenedor->getTempCentro());
        asignarRaiz(newRoot);
        NodoDosTres<T>* nodo1 = new NodoDosTres<T>(contenedor->getMenor());
        NodoDosTres<T>* nodo2 = new NodoDosTres<T>(contenedor->getMayor());
        if(contenedor->getTemp()!=nullptr)
            redistribuirHijos(contenedor, nodo1, nodo2);
        newRoot->setIzquierdo(nodo1);
        newRoot->setDerecho(nodo2);
        newRoot->getIzquierdo()->setPadre(newRoot);
        newRoot->getDerecho()->setPadre(newRoot);
        delete contenedor;
    }
    else if(contenedor->getPadre() != nullptr) {
        NodoDosTres<T>* padre = contenedor->getPadre();
        if(padre->isFull()) {
            padre->setInfoCentro(contenedor->getTempCentro());
            if(padre->getDerecho() == contenedor) {
                NodoDosTres<T>* nodo1 = new NodoDosTres<T>(contenedor->getMenor());
                NodoDosTres<T>* nodo2 = new NodoDosTres<T>(contenedor->getMayor());
                if(contenedor->getTemp()!=nullptr)
                    redistribuirHijos(contenedor, nodo1, nodo2);
                padre->setDerecho(nodo2);
                padre->setTemp(nodo1);
                padre->getDerecho()->setPadre(padre);
                padre->getTemp()->setPadre(padre);
                delete contenedor;
            }
            else if(padre->getIzquierdo() == contenedor) {
                NodoDosTres<T>* nodo1 = new NodoDosTres<T>(contenedor->getMenor());
                NodoDosTres<T>* nodo2 = new NodoDosTres<T>(contenedor->getMayor());
                if(contenedor->getTemp()!=nullptr)
                    redistribuirHijos(contenedor, nodo1, nodo2);
                padre->setIzquierdo(nodo1);
                padre->setTemp(padre->getCentro());
                padre->setCentro(nodo2);
                padre->getIzquierdo()->setPadre(padre);
                padre->getCentro()->setPadre(padre);
                padre->getTemp()->setPadre(padre);
                delete contenedor;
                
            }
            else {
                NodoDosTres<T>* nodo1 = new NodoDosTres<T>(contenedor->getMenor());
                NodoDosTres<T>* nodo2 = new NodoDosTres<T>(contenedor->getMayor());
                if(contenedor->getTemp()!=nullptr)
                    redistribuirHijos(contenedor, nodo1, nodo2);
                padre->setCentro(nodo1);
                padre->setTemp(nodo2);
                padre->getCentro()->setPadre(padre);
                padre->getTemp()->setPadre(padre);
                delete contenedor;
            }
            dividir(padre);
        }
        else {
            padre->setInfo(contenedor->getTempCentro());
            if(padre->getDerecho() == contenedor)
            {
                NodoDosTres<T>* nodo1 = new NodoDosTres<T>(contenedor->getMenor());
                NodoDosTres<T>* nodo2 = new NodoDosTres<T>(contenedor->getMayor());
                if(contenedor->getTemp()!=nullptr)
                    redistribuirHijos(contenedor, nodo1, nodo2);
                padre->setDerecho(nodo2);
                padre->setCentro(nodo1);
                padre->getDerecho()->setPadre(padre);
                padre->getCentro()->setPadre(padre);
                delete contenedor;
            }
            else if(padre->getIzquierdo() == contenedor) {
                NodoDosTres<T>* nodo1 = new NodoDosTres<T>(contenedor->getMenor());
                NodoDosTres<T>* nodo2 = new NodoDosTres<T>(contenedor->getMayor());
                if(contenedor->getTemp()!=nullptr)
                    redistribuirHijos(contenedor, nodo1, nodo2);
                padre->setIzquierdo(nodo1);
                padre->setCentro(nodo2);
                padre->getIzquierdo()->setPadre(padre);
                padre->getCentro()->setPadre(padre);
                delete contenedor;
            }
            if(padre->tieneTresLlaves())
                dividir(padre);
        }
    }
}

template <class T>
bool ArbolDosTres<T>:: checaNodoDos(NodoDosTres<T>* nodo) {
    if((nodo->hasLower() && !nodo->hasHigher()) || (!nodo->hasLower() && nodo->hasHigher()))
        return true;
    else
        return false;
}

template <class T>
bool ArbolDosTres<T>:: checaNodoTres(NodoDosTres<T>* nodo) {
    if(nodo->hasLower() && nodo->hasHigher())
        return true;
    else
        return false;
}

template <class T>
bool ArbolDosTres<T>::hijosLibres(NodoDosTres<T>* nodo) {
    if(nodo->getIzquierdo() == nullptr || nodo->getCentro() == nullptr || nodo->getDerecho() == nullptr)
        return true;
    else
        return false;
}

template <class T>
void ArbolDosTres<T>::insertar23(NodoDosTres<T> * padre, T info) {
    NodoDosTres<T>* contenedor = new NodoDosTres<T>();
    if(raiz == nullptr)
    {
        asignarRaiz(new NodoDosTres<T>(info));
        return;
    }
    contenedor = buscarNodo(info, raiz);
    if(checaNodoDos(contenedor))
    {
        contenedor->setInfo(info);
        contenedor->borrarTempCentro();
    }
    else if(checaNodoTres(contenedor))
    {
        contenedor->setInfoCentro(info);
        dividir(contenedor);
    }
}

template <class T>
bool ArbolDosTres<T>::buscar(const T info) {
    bool found;
    
    if (buscarNodo(info, raiz) != nullptr) {
        found = true;
    }
    else {
        found = false;
    }
    
    return found;
    
}

template <class T>
NodoDosTres<T>* ArbolDosTres<T>::buscarNodo(const T info, NodoDosTres<T> * nodo) {
    if(nodo == nullptr)
        return nullptr;
    if(esHoja(nodo))
        return nodo;
    else if(checaNodoDos(nodo)) {
        if(info <= nodo->getMenor())
            return buscarNodo(info, nodo->getIzquierdo());
        else
            return buscarNodo(info, nodo->getDerecho());
    }
    else if(checaNodoTres(nodo)) {
        if(info <= nodo->getMenor())
            return buscarNodo(info, nodo->getIzquierdo());
        else if(info > nodo->getMayor())
            return buscarNodo(info, nodo->getDerecho());
        else
            return buscarNodo(info, nodo->getCentro());
    }
    return nodo;
}

template <class T>
void ArbolDosTres<T>::printAsc() {
    printAsc(raiz, 0);
    std::cout << std::endl;
}

template <class T>
void ArbolDosTres<T>::printAsc(NodoDosTres<T> * nodo, int lv) {
    if(nodo == nullptr)
        return;
    if(esHoja(nodo)) {
        if(checaNodoDos(nodo)) {
            std::cout << nodo->getMenor() << " "<< std::flush;
        }
        else if(checaNodoTres(nodo)) {
            std::cout << nodo->getMenor() << " " << nodo->getMayor();
        }
    }
    else if(checaNodoDos(nodo)) {
        printAsc(nodo->getIzquierdo(), lv);
        std::cout << nodo->getMenor() << " "<< std::flush;
        printAsc(nodo->getDerecho(), lv);
    }
    else if(checaNodoTres(nodo)) {
        printAsc(nodo->getIzquierdo(), lv);
        std::cout << nodo->getMenor() << " "<< std::flush;
        printAsc(nodo->getCentro(), lv);
        std::cout << nodo->getMayor() << " "<< std::flush;
        printAsc(nodo->getDerecho(), lv);
    }
}

template <class T>
void ArbolDosTres<T>::printDesc() {
    printDesc(raiz, 0);
    std::cout << std::endl;
}

template <class T>
void ArbolDosTres<T>::printDesc(NodoDosTres<T> * nodo, int lv) {
    if(nodo == nullptr)
        return;
    if(esHoja(nodo)) {
        if(checaNodoDos(nodo)) {
            std::cout << nodo->getMenor() << " "<< std::flush;
        }
        else if(checaNodoTres(nodo)) {
            std::cout << nodo->getMayor() << " " << nodo->getMenor() << " ";
        }
    }
    else if(checaNodoDos(nodo)) {
        printDesc(nodo->getDerecho(), lv);
        std::cout << nodo->getMenor() << " "<< std::flush;
        printDesc(nodo->getIzquierdo(), lv);
    }
    else if(checaNodoTres(nodo)) {
        printDesc(nodo->getDerecho(), lv);
        std::cout << nodo->getMayor() << " "<< std::flush;
        printDesc(nodo->getCentro(), lv);
        std::cout << nodo->getMenor() << " "<< std::flush;
        printDesc(nodo->getIzquierdo(), lv);
    }
}


template <class T>
void ArbolDosTres<T>::arreglar(NodoDosTres<T>* nodo) {
    if(isRoot(nodo)) {
        asignarRaiz(nodo->getCentro());
        delete nodo;
    }
    else {
        bool threeKeys = false;
        NodoDosTres<T>* padre = nodo->getPadre();
        if(checaNodoDos(padre)) {
            NodoDosTres<T>* hermano = new NodoDosTres<T>();
            if(padre->getDerecho() == nodo)
                hermano = padre->getIzquierdo();
            else
                hermano = padre->getDerecho();
            if(padre->getDerecho() == nodo) {
                
                if(checaNodoTres(padre->getIzquierdo())){
                    threeKeys = true;
                    T hermanoLower = hermano->getMenor();
                    T hermanoHigher = hermano->getMayor();
                    T padreVal = padre->getMenor();
                    T keys[3] = {hermanoLower,hermanoHigher,padreVal};
                    ordenar(keys,3);
                    T low = keys[0];
                    T mid = keys[1];
                    T high = keys[2];
                    nodo->setInfo(high);
                    padre->borrarLlaves();
                    padre->setInfo(mid);
                    hermano->borrarLlaves();
                    hermano->setInfo(low);
                    
                    
                    if(!esHoja(nodo)) {
                        nodo->setDerecho(nodo->getCentro());
                        nodo->setCentro(nullptr);
                        nodo->setIzquierdo(hermano->getDerecho());
                        nodo->getIzquierdo()->setPadre(nodo);
                        hermano->setDerecho(hermano->getCentro());
                        hermano->setCentro(nullptr);
                    }
                }
            }
            else {
                if(checaNodoTres(padre->getDerecho()))
                {
                    threeKeys = true;
                    T hermanoLower = hermano->getMenor();
                    T hermanoHigher = hermano->getMayor();
                    T padreVal = padre->getMenor();
                    T keys[3] = {hermanoLower,hermanoHigher,padreVal};
                    ordenar(keys,3);
                    T low = keys[0];
                    T mid = keys[1];
                    T high = keys[2];
                    nodo->setInfo(low);
                    padre->borrarLlaves();
                    padre->setInfo(mid);
                    hermano->borrarLlaves();
                    hermano->setInfo(high);
                    
                    if(!esHoja(nodo)) {
                        nodo->setIzquierdo(nodo->getCentro());
                        nodo->setCentro(nullptr);
                        nodo->setDerecho(hermano->getIzquierdo());
                        nodo->getDerecho()->setPadre(nodo);
                        hermano->setIzquierdo(hermano->getCentro());
                        hermano->setCentro(nullptr);
                    }
                }
            }
        }
        else if(checaNodoTres(padre)) {
            NodoDosTres<T>* hermano = new NodoDosTres<T>();
            if(padre->getDerecho() == nodo) {
                if(checaNodoTres(padre->getCentro())) {
                    threeKeys = true;
                    hermano = padre->getCentro();
                    nodo->setInfo(padre->getMayor());
                    padre->setMayor(hermano->getMayor());
                    hermano->borrarMayor();
                    if(!esHoja(nodo)) {
                        nodo->setDerecho(nodo->getCentro());
                        nodo->setIzquierdo(hermano->getDerecho());
                        nodo->getIzquierdo()->setPadre(nodo);
                        hermano->setDerecho(hermano->getCentro());
                        hermano->setCentro(nullptr);
                    }
                }
            }
            else if(padre->getCentro() == nodo) {
                if(checaNodoTres(padre->getIzquierdo())) {
                    threeKeys = true;
                    hermano = padre->getIzquierdo();
                    nodo->setInfo(padre->getMenor());
                    padre->setMenor(hermano->getMayor());
                    hermano->borrarMayor();
                    if(!esHoja(nodo)) {
                        nodo->setDerecho(nodo->getCentro());
                        nodo->setIzquierdo(hermano->getDerecho());
                        nodo->getIzquierdo()->setPadre(nodo);
                        hermano->setDerecho(hermano->getCentro());
                        hermano->setCentro(nullptr);
                    }
                }
            }
            else {
                if(checaNodoTres(padre->getCentro())) {
                    threeKeys = true;
                    hermano = padre->getCentro();
                    nodo->setInfo(padre->getMenor());
                    padre->setMenor(hermano->getMenor());
                    hermano->cambioMayorAMenor();
                    if(!esHoja(nodo)) {
                        nodo->setIzquierdo(nodo->getCentro());
                        nodo->setDerecho(hermano->getIzquierdo());
                        nodo->getDerecho()->setPadre(nodo);
                        hermano->setIzquierdo(hermano->getCentro());
                        hermano->setCentro(nullptr);
                    }
                }
            }
        }
        if(!threeKeys) {
            NodoDosTres<T>* hermano = new NodoDosTres<T>();
            if(checaNodoDos(padre)) {
                if(padre->getDerecho() == nodo) {
                    hermano = padre->getIzquierdo();
                    hermano->setInfo(padre->getMenor());
                    
                    if(!esHoja(nodo)) {
                        hermano->setCentro(hermano->getDerecho());
                        hermano->setDerecho(nodo->getCentro());
                    }
                    padre->setCentro(hermano);
                    padre->getCentro()->setPadre(padre);
                    padre->setIzquierdo(nullptr);
                    padre->setDerecho(nullptr);
                    padre->borrarLlaves();
                    delete nodo;
                }
                else {
                    hermano = padre->getDerecho();
                    hermano->setInfo(padre->getMenor());
                    if(!esHoja(nodo))
                    {
                        hermano->setCentro(hermano->getIzquierdo());
                        hermano->setIzquierdo(nodo->getCentro());
                        hermano->getIzquierdo()->setPadre(hermano);
                    }
                    padre->setCentro(hermano);
                    padre->getCentro()->setPadre(padre);
                    padre->setIzquierdo(nullptr);
                    padre->setDerecho(nullptr);
                    padre->borrarLlaves();
                    delete nodo;
                }
            }
            else if(checaNodoTres(padre)) {
                if(padre->getDerecho() == nodo) {
                    hermano = padre->getCentro();
                    hermano->setInfo(padre->getMayor());
                    if(!esHoja(nodo)) {
                        hermano->setCentro(hermano->getDerecho());
                        hermano->setDerecho(nodo->getCentro());
                        hermano->getDerecho()->setPadre(hermano);
                    }
                    padre->setDerecho(hermano);
                    padre->getDerecho()->setPadre(padre);
                    padre->setCentro(nullptr);
                    padre->borrarMayor();
                    delete nodo;
                }
                else if(padre->getCentro() == nodo) {
                    hermano = padre->getIzquierdo();
                    hermano->setInfo(padre->getMenor());
                    if(!esHoja(nodo)) {
                        hermano->setCentro(hermano->getDerecho());
                        hermano->setDerecho(nodo->getCentro());
                        hermano->getDerecho()->setPadre(hermano);
                    }
                    padre->setIzquierdo(hermano);
                    padre->getIzquierdo()->setPadre(padre);
                    padre->setCentro(nullptr);
                    padre->borrarMenor();
                    padre->cambioMayorAMenor();
                    delete nodo;
                }
                else {
                    hermano = padre->getCentro();
                    hermano->setInfo(padre->getMenor());
                    if(!esHoja(nodo)) {
                        hermano->setCentro(hermano->getIzquierdo());
                        hermano->setIzquierdo(nodo->getCentro());
                        hermano->getIzquierdo()->setPadre(hermano);
                    }
                    padre->setIzquierdo(hermano);
                    padre->getIzquierdo()->setPadre(padre);
                    padre->setCentro(nullptr);
                    padre->borrarMenor();
                    padre->cambioMayorAMenor();
                    delete nodo;
                }
            }
            if(padre->sinLlaves()) {
                hermano->setPadre(padre);
                arreglar(padre);
            }
        }
    }
}

template <class T>
bool ArbolDosTres<T>::borrar(T info) {
    NodoDosTres<T>* nodo = new NodoDosTres<T>();
    nodo = encontrarNodoABorrar(raiz, info);
    if(nodo) {
        NodoDosTres<T>* leafNode = new NodoDosTres<T>();
        if(!esHoja(nodo)) {
            leafNode = getSucesorInorder(nodo);
            T swapVal = leafNode->getMenor();
            nodo->setMenor(swapVal);
        }
        else {
            if(nodo->getMayor() == info) {
                nodo->borrarMayor();
                return true;
            }
        }
        leafNode->borrarMenor();
        if(leafNode->sinLlaves()) {
            arreglar(leafNode);
        }
        return true;
    }
    else
        return false;
}

template <class T>
NodoDosTres<T>* ArbolDosTres<T>::getSucesorInorder(NodoDosTres<T>* nodo) {
    if (nodo) {
        NodoDosTres<T> * workingNode = nodo->getIzquierdo();
        if(workingNode){
            while (workingNode->getDerecho() != nullptr) {
                workingNode = workingNode->getDerecho();
            }
            return workingNode;
        }
        return nullptr;
        
    } else {
        return nullptr;
    }
}

template <class T>
NodoDosTres<T>* ArbolDosTres<T>::encontrarNodoABorrar(NodoDosTres<T>* nodo, T info) {
    if(nodo == nullptr)
        return nullptr;
    if(esHoja(nodo)) {
        if(checaNodoDos(nodo)) {
            if(nodo->getMenor() == info){
                return nodo;
            }
        }
        else if(checaNodoTres(nodo)) {
            if(nodo->getMenor() == info || nodo->getMayor() == info) {
                return nodo;
            }
        }
        return nullptr;
    }
    else if(checaNodoDos(nodo)) {
        if(info == nodo->getMenor()) {
            return nodo;
        }
        
        if(info < nodo->getMenor())
            return encontrarNodoABorrar(nodo->getIzquierdo(), info);
        else
            return encontrarNodoABorrar( nodo->getDerecho(), info);
    }
    else if(checaNodoTres(nodo))
    {
        if(nodo->getMenor() == info || nodo->getMayor() == info) {
            return nodo;
        }
        if(info < nodo->getMenor())
            return encontrarNodoABorrar(nodo->getIzquierdo(), info);
        else if(info > nodo->getMayor())
            return encontrarNodoABorrar(nodo->getDerecho(), info);
        else
            return encontrarNodoABorrar(nodo->getCentro(), info);
    }
    return nullptr;
}

template <class T>
bool ArbolDosTres<T>::encontrarNodo(NodoDosTres<T>* nodo, T info) {
    if(nodo == nullptr)
        return false;
    if(esHoja(nodo)) {
        if(checaNodoDos(nodo)) {
            if(nodo->getMenor() == info)
            {
                return true;
            }
        }
        else if(checaNodoTres(nodo)) {
            if(nodo->getMenor() == info || nodo->getMayor() == info) {
                return true;
            }
        }
        return false;
    }
    else if(checaNodoDos(nodo)) {
        if(info == nodo->getMenor()) {
            return true;
        }
        
        if(info < nodo->getMenor())
            return encontrarNodo(nodo->getIzquierdo(), info);
        else
            return encontrarNodo( nodo->getDerecho(), info);
    }
    else if(checaNodoTres(nodo)) {
        if(nodo->getMenor() == info || nodo->getMayor() == info) {
            return true;
        }
        if(info < nodo->getMenor())
            return encontrarNodo(nodo->getIzquierdo(), info);
        else if(info > nodo->getMayor())
            return encontrarNodo(nodo->getDerecho(), info);
        else
            return encontrarNodo(nodo->getCentro(), info);
    }
    return false;
}

template <class T>
bool ArbolDosTres<T>::esDosTres() {
    return esDosTres(raiz);
}

template <class T>
bool ArbolDosTres<T>::esDosTres(NodoDosTres<T>* nodo) {
    nivelesHoja.clear();
    getNivelesHoja(raiz);
    T cmp = nivelesHoja[0];
    bool leafs = true;
    for(int i=1; i<nivelesHoja.size(); i++) {
        if(nivelesHoja[i] != cmp)
            leafs = false;
    }
    return leafs;
}

template <class T>
void ArbolDosTres<T>::getNivelesHoja(NodoDosTres<T>* nodo) {
    if(nodo == nullptr)
        return;
    if(esHoja(nodo)) {
        nivelesHoja.push_back(getNivel(nodo));
    }
    else if(checaNodoDos(nodo)) {
        getNivelesHoja(nodo->getIzquierdo());
        getNivelesHoja(nodo->getDerecho());
    }
    else if(checaNodoTres(nodo)) {
        getNivelesHoja(nodo->getIzquierdo());
        getNivelesHoja(nodo->getCentro());
        getNivelesHoja(nodo->getDerecho());
    }
}

template <class T>
void ArbolDosTres<T>::esHoja() {
    esHoja(raiz);
}

template <class T>
bool ArbolDosTres<T>::esHoja(NodoDosTres<T> * nodo) {
    if(nodo->getIzquierdo() == nullptr && nodo->getCentro() == nullptr && nodo->getDerecho() == nullptr)
        return true;
    else
        return false;
}

template <class T>
void ArbolDosTres<T>::ancestros(NodoDosTres<T> * nodo) const {
    if (nodo) {
        std::cout << *nodo << " -> ";
        ancestros(nodo->getPadre());
    }
}

template <class T>
int ArbolDosTres<T>::getAltura() const {
    return getAltura(raiz);
}

template <class T>
int ArbolDosTres<T>::getAltura(NodoDosTres<T> * nodo) const {
    if (!nodo)
        return -1;
    return 1 + std::max(getAltura(nodo->getIzquierdo()), getAltura(nodo->getDerecho()));
}

template <class T>
int ArbolDosTres<T>::getProfundidad() const {
    return getProfundidad(raiz);
}

template <class T>
int ArbolDosTres<T>::getProfundidad(NodoDosTres<T> * nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    else {
        return getProfundidad(nodo->getPadre())+1;
    }
}

template <class T>
int ArbolDosTres<T>::getNivel() const {
    return getNivel(raiz);
}

template <class T>
int ArbolDosTres<T>::getNivel(NodoDosTres<T> * nodo) const {
    int nivel = 0;
    while (nodo != nullptr && nodo->getPadre() != nullptr) {
        nivel++;
        nodo = nodo->getPadre();
    }
    return nivel;
}

template <class T>
void ArbolDosTres<T>::ordenar(T a[], int N) {
    
    int i, j, flag = 1;
    int temp;
    int numLength = N;
    for(i = 1; (i <= numLength) && flag; i++) {
        flag = 0;
        for (j=0; j < (numLength -1); j++) {
            if (a[j+1] < a[j]) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                flag = 1;
            }
        }
    }
    return;
}
