#ifndef DICCTRIE_H
#define DICCTRIE_H

#include "aed2.h"
#include "Tipos.h"


template < class T >
class diccTrie {

	private:


		struct diccT {

			diccT* hijos[256];
			T* significado;
			//Constructor de la estructura.
			diccT();
	
		};
	

		Conj<const String>* cc;
		diccT* arbol;

		//Funciones auxiliares.
		void borrarRecursivamente(diccT* arbol);
		bool esHoja(diccT* hijos[256]);



	public:
	
		class ItClavesDiccTrie;

		diccTrie(); //Constructor sin argumentos.
		//Interfaz
		bool definido(const String& clave) const;
		void definir(const String& clave, T& info);
		T& obtener(const String& clave) const;
		ItClavesDiccTrie CrearItClaves() const;

		~diccTrie(); //Destructor.
		
		
		
		
		
		class ItClavesDiccTrie {
			
			private:
			
				Conj<const String>::const_Iterador it;
				ItClavesDiccTrie(const Conj<const String>& c) {it = c.CrearIt();}

			public:
			
				ItClavesDiccTrie() {}
				ItClavesDiccTrie(const ItClavesDiccTrie& otra) : it(otra.it) {}
				
				ItClavesDiccTrie& operator= (const ItClavesDiccTrie& otra) 
					{it = otra.it; return *this;}

				bool operator== (const ItClavesDiccTrie& otro) const {return it == otro.it;}
				
				bool HaySiguiente() const;
			    const Categoria& Siguiente() const;
				void Avanzar();
				
				friend class diccTrie;				
								
			};		
		
		
		friend class ItClavesDiccTrie;
				
};


template <class T>
diccTrie<T>::diccT::diccT() {

		for (int i = 0; i < 256; i++) {

		    hijos[i] = NULL;

	    }

	    significado = NULL;

}




//Constructor
template <class T>
diccTrie<T>::diccTrie() {

	cc = new Conj<const String>();

	arbol = new diccT();

}




template <class T>
bool diccTrie<T>::definido(const String& clave) const {

	diccT* recorre = arbol;
	unsigned int i = 0;

	while (!(recorre == NULL) && i < clave.size()) {

		int pos = clave[i];

		recorre = recorre->hijos[pos];

		i++;

	}

	return !(recorre == NULL);

}





template <class T>
void diccTrie<T>::definir(const String& clave, T& in) {
	
		/* Creo una copia en el heap de la info que me pasan
		 * para evitar el problema de liberar memoria que esta
		 * en el stack.
		 *
		 * Para los fines del tp, lo que se va a copiar es un 
		 * nodoCat recien creado o un nodoLink. Copiar el id, la altura, el
		 * puntero a nodoPadre y el conjunto vacio es O(1) 
		 * (ya que solo se agregan categorias nuevas en la funcion 
		 * "agregar" del modulo Arbol Categorias, y en ese momento 
		 * la categoria que voy a definir no tiene categorias hijas), 
		 * y copiar la categoria es O(|clave|), ya que son el mismo
		 * string. Por lo tanto, no se altera la complejidad final
		 * de esta operacion. 
		 * 
		 * En el caso del nodoLink, tengo que copiar un puntero (O(1)),
		 * una categoria y un link (O(|link| + |cat|)) lo
		 * cual sigue cumpliendo la complejidad requerida.*/
		 
		//Asumo que el tipo T tiene un constructor por copia. 
		T* info = new T(in);
		

	    diccT* recorre = arbol;

		for (unsigned int i = 0; i < clave.size(); i++) {

			int pos = clave[i];

			if (recorre->hijos[pos] == NULL) {

				recorre->hijos[pos] = new diccT();

			}

			recorre = recorre->hijos[pos];

		}

		recorre->significado = info;

		cc->Agregar(clave);

}




template <class T>
T& diccTrie<T>::obtener(const String& clave) const {

	diccT* recorre = arbol;
	unsigned int i = 0;

	while (i < clave.size()) {

		int pos = clave[i];

		recorre = recorre->hijos[pos];

		i++;

	}

	return *(recorre->significado);

}


template <class T>
typename diccTrie<T>::ItClavesDiccTrie diccTrie<T>::CrearItClaves() const {
	
	return ItClavesDiccTrie(*cc);

}



template <class T>
diccTrie<T>::~diccTrie() {

	borrarRecursivamente(arbol);

	delete cc;

}



template <class T>
void diccTrie<T>::borrarRecursivamente(diccT* arbol) {

	diccT* recorre = arbol;

	if (esHoja(recorre->hijos)) {

		delete recorre->significado;
		delete recorre;

	} else {

		for (int i = 0; i < 256; i++) {

			if (recorre->hijos[i] != NULL)
			   borrarRecursivamente(recorre->hijos[i]);

		}
		
		delete recorre->significado;
		delete recorre;

	}

}


template <class T>
bool diccTrie<T>::esHoja(diccT* hijos[256]) {

	bool tieneHoja = false;
	int i = 0;

	while (i < 256 && !tieneHoja) {

		if (hijos[i] != NULL) {

			tieneHoja = true;

		}

		i++;

	}


	return !tieneHoja;

}



template <class T>
bool diccTrie<T>::ItClavesDiccTrie::HaySiguiente() const {
	
	return it.HaySiguiente();
	
}


template <class T>
const Categoria& diccTrie<T>::ItClavesDiccTrie::Siguiente() const {
	
	return it.Siguiente();
	
}



template <class T>
void diccTrie<T>::ItClavesDiccTrie::Avanzar() {
	
	it.Avanzar();
	
}








#endif
