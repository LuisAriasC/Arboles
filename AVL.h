#include<iostream>

using namespace std;

template <class T>
struct NodoA{
    T data;
    NodoA *izq;
    NodoA *der;
    NodoA *pad;
    int alt;
    int prof;
    int niv;
};


template <class T>
class AVL{
private:
    NodoA<T>* raiz;
    
    NodoA<T>* insercion(T x, NodoA<T> *r){
                
        if(r == NULL){
            r = new NodoA<T>;
            r->data = x;
            r->alt = 0;
            r->izq = r->der = NULL;
        }
        
        else if(x < r->data){
            r->izq = insercion(x, r->izq);
            if(alturaNodo(r->izq) - alturaNodo(r->der) == 2){
                if(x < r->izq->data) r = rotacion_Der_Simple(r);
                else r = rotacion_Der_Doble(r);
            }
        }
        
        else if(x > r->data){
            r->der = insercion(x, r->der);
            if(alturaNodo(r->der) - alturaNodo(r->izq) == 2){
                if(x > r->der->data) r = rotacion_Izq_Simple(r);
                else r = rotacion_Izq_Doble(r);
            }
        }
        r->alt = max(alturaNodo(r->izq), alturaNodo(r->der))+1;
        return r;
    }
    
    bool busqueda(T x, NodoA<T> *r){
        bool v = false;
        if (r == NULL) {
            v = false;
        }
        else{
            if (x > r->data) {
                v = busqueda(x, r->der);
            }
            else if (x < r->data){
                v = busqueda(x, r->izq);
            }
            else v = true;
        }
        return v;
    }
    
    NodoA<T>* rotacion_Der_Simple(NodoA<T> *&r){
        NodoA<T> *ref = r->izq;
        r->izq = ref->der;
        ref->der = r;
        r->alt = max(alturaNodo(r->izq), alturaNodo(r->der))+1;
        ref->alt = max(alturaNodo(ref->izq), r->alt)+1;
        return ref;
    }
    
    NodoA<T>* rotacion_Izq_Simple(NodoA<T> *&r){
        NodoA<T> *ref = r->der;
        r->der = ref->izq;
        ref->izq = r;
        r->alt = max(alturaNodo(r->izq), alturaNodo(r->der))+1;
        ref->alt = max(alturaNodo(r->der), r->alt)+1 ;
        return ref;
    }
    
    NodoA<T>* rotacion_Izq_Doble(NodoA<T> *&r){
        r->der = rotacion_Der_Simple(r->der);
        return rotacion_Izq_Simple(r);
    }
    
    NodoA<T>* rotacion_Der_Doble(NodoA<T> *&r){
        r->izq = rotacion_Izq_Simple(r->izq);
        return rotacion_Der_Simple(r);
    }
    
    NodoA<T>* minimo_Eliminacion(NodoA<T> *r){
        if(r == NULL) return NULL;
        else if(r->izq == NULL) return r;
        else return minimo_Eliminacion(r->izq);
    }
    
    NodoA<T>* maximo_Eliminacion(NodoA<T> *r){
        if(r == NULL) return NULL;
        else if(r->der == NULL) return r;
        else return maximo_Eliminacion(r->der);
    }
    
    NodoA<T>* remover(T x, NodoA<T> *r){
        
        NodoA<T>* temp;
        
        if(r == NULL) return NULL;
        else if(x < r->data) r->izq = remover(x, r->izq);
        else if(x > r->data) r->der = remover(x, r->der);
        
        else if(r->izq && r->der){
            temp = minimo_Eliminacion(r->der);
            r->data = temp->data;
            r->der = remover(r->data, r->der);
        }
        
        else{
            temp = r;
            if(r->izq == NULL) r = r->der;
            else if(r->der == NULL) r = r->izq;
            delete temp;
        }
        
        if(r == NULL) return r;
        
        r->alt = max(alturaNodo(r->izq), alturaNodo(r->der))+1;
        
        if(alturaNodo(r->izq) - alturaNodo(r->der) == 2){
            if(alturaNodo(r->izq->izq) - alturaNodo(r->izq->der) == 1) return rotacion_Izq_Simple(r);
            else return rotacion_Izq_Doble(r);
        }
        
        else if(alturaNodo(r->der) - alturaNodo(r->izq) == 2){
            if(alturaNodo(r->der->der) - alturaNodo(r->der->izq) == 1) return rotacion_Der_Simple(r);
            else return rotacion_Der_Doble(r);
        }
        return r;
    }
    
    int alturaNodo(NodoA<T> *r){
        return (r == NULL ? -1 : r->alt);
    }
    
    void inorden(NodoA<T> *r){
        if(r == NULL) return;
        inorden(r->izq);
        cout << r->data << " ";
        inorden(r->der);
    }
    
    void inorden_r(NodoA<T> *r){
        if(r == NULL) return;
        inorden_r(r->der);
        cout << r->data << " ";
        inorden_r(r->izq);
    }
    
    NodoA<T>* recorrido(T x,NodoA<T> *r){
        NodoA<T>* re;
        if (r == NULL) {re = NULL;}
        else if (x < r->data){ re = recorrido(x, r->izq);}
        else if (x > r->data){ re = recorrido(x, r->der);}
        else re = r;
        
        return re;
    }
public:
    
    AVL(){raiz = NULL;}
    
    void insertar(T x){raiz = insercion(x, raiz);}
    
    void eliminar(T x){raiz = remover(x, raiz);}
    
    void buscar(T x){
       cout << busqueda(x, raiz);
    }
    
    void imprimir(){
        int op;
        cout << "\tImprimir -" << endl;
        cout << "1)De menor a mayor\n2)De mayor a menor" << endl;
        cout << "Opción: ";
        cin >> op;
        if (op == 1) {
            inorden(raiz);
            cout << endl;
        }
        if (op == 2){
            inorden_r(raiz);
            cout << endl;
        }
    }
    
    void obtenerAltura(T x){
        NodoA<T> disp;
        if (busqueda(x, raiz) == true){
            disp = *recorrido(x, raiz);
            cout << disp.alt << endl;
        }
    };
};


