template <class T>
class NodoDosTres{
    bool hasSmall = false;
    bool hasHigh = false;
    bool full = false;
    T* menor = nullptr;
    T* mayor = nullptr;
    T* tempCentro = nullptr;
    NodoDosTres<T>* padre = nullptr;
    NodoDosTres<T>* izquierdo = nullptr;
    NodoDosTres<T>* centro = nullptr;
    NodoDosTres<T>* derecho = nullptr;
    NodoDosTres<T>* temp = nullptr;
public:
    NodoDosTres<T>():izquierdo(nullptr),centro(nullptr),derecho(nullptr),padre(nullptr),menor(nullptr),mayor(nullptr),tempCentro(nullptr),temp(nullptr){}
    NodoDosTres(T _menor){
        menor = new T(_menor);
        hasSmall = true;
    }
    virtual ~NodoDosTres(){
        izquierdo = centro = derecho = padre = temp = nullptr;
        menor = mayor = nullptr;
    }
    
    NodoDosTres<T>* getTemp()
    {
        return temp;
    }
    
    void setTemp(NodoDosTres<T>* nodo)
    {
        temp = nodo;
    }
    
    T getTempCentro()
    {
        return *tempCentro;
    }
    
    void borrarTempCentro()
    {
        if(tempCentro)
        {
            tempCentro = nullptr;
        }
    }
    
    void setTempCentro(T _info)
    {
        if(tempCentro == nullptr)
        {
            tempCentro = new T(_info);
        }
        else
        {
            *tempCentro = _info;
        }
    }
    
    bool tieneTempCentro()
    {
        if(tempCentro)
            return true;
        else
            return false;
    }
    
    void setMenor(T _info)
    {
        if(menor!=nullptr)
        {
            *menor = _info;
        }
        else
        {
            menor = new T(_info);
        }
    }
    
    void setMayor(T _info)
    {
        if(mayor!=nullptr)
        {
            *mayor = _info;
        }
        else
        {
            mayor = new T(_info);
        }
    }
    
    T getMenor()
    {
        return *menor;
    }
    
    T getMayor()
    {
        return *mayor;
    }
    
    bool isFull()
    {
        if(mayor && menor)
            return true;
        return false;
    }
    
    bool tieneTresLlaves()
    {
        return mayor && menor && tempCentro;
    }
    
    void setInfo(T _info)
    {
        if(!menor)
        {
            menor = new T(_info);
        }
        else
        {
            if(_info >= *menor)
            {
                if(!mayor)
                {
                    mayor = new T(_info);
                }
            }
            else if(_info < *menor)
            {
                mayor = new T(*menor);
                *menor = _info;
            }
        }
    }
    
    void borrarLlaves()
    {
        if(menor)
            menor = nullptr;
        if(mayor)
            mayor = nullptr;
    }
    
    void setInfoCentro(T _info)
    {
        if(mayor && menor)
        {
            if(!tempCentro)
            {
                tempCentro = new T(_info);
                if(_info < *menor)
                {
                    *tempCentro = *menor;
                    *menor = _info;
                }
                else if(_info >= *menor && _info <= *mayor)
                {
                    *tempCentro = _info;
                }
                else
                {
                    *tempCentro = *mayor;
                    *mayor = _info;
                }
            }
            else
            {
                if(_info < *menor)
                {
                    *tempCentro = *menor;
                    *menor = _info;
                }
                else if(_info >= *menor && _info <= *mayor)
                {
                    *tempCentro = _info;
                }
                else
                {
                    *tempCentro = *mayor;
                    *mayor = _info;
                }
            }
        }
    }
    
    void borrarMayor()
    {
        if(mayor)
        {
            mayor = nullptr;
        }
    }
    
    void borrarMenor()
    {
        if(menor)
            menor = nullptr;
    }
    
    void cambioMayorAMenor()
    {
        if(!menor)
            menor = new T(*mayor);
        else
            *menor = *mayor;
        mayor = nullptr;
    }
    
    
    bool hasLower(){
        if(menor==nullptr)
            return false;
        else
            return true;
    }
    bool hasHigher(){
        if(mayor==nullptr)
            return false;
        else
            return true;
    }
    
    bool sinLlaves()
    {
        return !menor && !mayor;
    }
    
    NodoDosTres<T> * getIzquierdo() const { return izquierdo; }
    void setIzquierdo(NodoDosTres<T> * info) { izquierdo = info; }
    
    NodoDosTres<T> * getDerecho() const { return derecho; }
    void setDerecho(NodoDosTres<T> * info) { derecho = info; }
    
    NodoDosTres<T> * getCentro() const { return centro; }
    void setCentro(NodoDosTres<T> * info) { centro = info; }
    
    NodoDosTres<T> * getPadre() const { return padre; }
    void setPadre(NodoDosTres<T> * info) { padre = info; }
};
