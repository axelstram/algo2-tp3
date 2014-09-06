#ifndef ARBOLCAT_H
#define ARBOLCAT_H

#include "diccTrie.h"
#include "Tipos.h"
#include "aed2.h"




class nodoCat {

    private:
        int id;
        int altura;
        String cat;
        const nodoCat* padre;
        Conj<const nodoCat*>* hijos; //Conjunto de las categorias hijas.

        //Constructor del nodo.
        nodoCat(const int& id, const int& altura, const Categoria& cat, const nodoCat* p = NULL);
        void agregarCatHija(const nodoCat& cat);
        const Conj<const nodoCat*>& hijosNodo() const;


    public:

        ~nodoCat();
        const int& idNodo() const;
        const int& alturaNodo() const;
        const Categoria& categoriaNodo() const;
        const nodoCat& nodoPadre() const;
        bool tienePadre() const;

        const nodoCat& operator= (const nodoCat& nd) {
			
			id = nd.id;
			altura = nd.altura;
			cat = nd.cat;
			padre = nd.padre;
			
			delete hijos;
			
			hijos = new Conj<const nodoCat*>(*(nd.hijos));
			
		}
		
		
        nodoCat(const nodoCat& nd); //Constructor por copia.


        friend class acat;
        friend class ItCategorias;

};




class acat {

    private:

        const Categoria Raiz;
        diccTrie<nodoCat>* tr;
        int ultimoId;
        int alturaArbol;
        Conj<const nodoCat*> cats;
        


    public:
    
		class ItCategorias;
		    		
		ItCategorias CrearItCategorias(const Conj<const nodoCat*>& c);
		

        acat(const String& cat); //Constructor.
        ~acat(); //Destructor.

        //Interfaz:
        //Funciones del Arbol de Categorias
        void agregar(const Categoria& cat, const Categoria& catHija);
        ItCategorias categorias() ;
        const Categoria& raiz() const;
        const Categoria& padre(const String& hija) const;
        int id(const Categoria& cat) const;
        int altura() const;
        bool esta(const Categoria& cat) const;
        bool esSubCategoria(const Categoria& padre, const Categoria& hija) const;
        int alturaCategoria(const Categoria& cat) const;
        ItCategorias hijos(const Categoria& cat);
        
        
        
		class ItCategorias {
			
			private:
				
				Conj<const nodoCat*>::const_Iterador it;
				ItCategorias(const Conj<const nodoCat*>& c) {it = c.CrearIt();}

				
			public:
				
				ItCategorias() {}
				ItCategorias(const ItCategorias& otra) : it(otra.it) {}
				
				ItCategorias& operator= (const ItCategorias& otra) 
					{it = otra.it; return *this;}

				bool operator== (const ItCategorias& otro) const {return it == otro.it;}
				
				bool HaySiguiente() const;
			    const nodoCat& Siguiente() const;
				void Avanzar();

			
				friend class acat;
			
		};
		
		

};



#endif
