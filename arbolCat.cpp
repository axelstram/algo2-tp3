#include "arbolCat.h"


acat::acat(const Categoria& cat) : Raiz(cat) {

    ultimoId = 1;
    alturaArbol = 1;
    tr = new diccTrie<nodoCat>();

    nodoCat q(ultimoId, alturaArbol, cat);
    tr->definir(cat, q);
    
    nodoCat& r = tr->obtener(cat);
    cats.Agregar(&r);

}


acat::~acat() {

    delete tr;

}






void acat::agregar(const Categoria& cat, const Categoria& catHija) {

    ultimoId++;
    nodoCat& padre = tr->obtener(cat);
    int altNodo = 0;
    

    if (cat == Raiz) {

        altNodo = 2;

    } else {

        altNodo = padre.alturaNodo() + 1;

    }

	
    if (altNodo > alturaArbol) {
	//Aumento la altura del arbol.
        alturaArbol = altNodo;

    }


    nodoCat hija(ultimoId, altNodo, catHija, &padre);
    
	//Se hace una copia del nodo hija en el arbol.
    tr->definir(catHija, hija);
    
    //Obtengo la referencia dentro del arbol.
    nodoCat& q = tr->obtener(catHija);
    //Le agrego al padre un puntero al nodoCat hija que esta dentro del arbol.
    padre.agregarCatHija(q);
    
    cats.Agregar(&q); //Agrego la categoria nueva al conjunto de categorias.


}


acat::ItCategorias acat::categorias() {
		
	return CrearItCategorias(cats); 
	
}



const Categoria& acat::raiz() const {

    return Raiz;

}


const Categoria& acat::padre(const Categoria& hija) const {

    nodoCat q = tr->obtener(hija);
    
    return (q.padre)->categoriaNodo();

}


int acat::id(const Categoria& cat) const {

    nodoCat q = tr->obtener(cat);
    return q.idNodo();

}


int acat::altura() const {

    return alturaArbol;

}


bool acat::esta(const Categoria& cat) const {

    return tr->definido(cat);

}



bool acat::esSubCategoria(const Categoria& padre, const Categoria& hija) const {

    nodoCat q = tr->obtener(hija);
    bool esSubCat = false;

    while (q.categoriaNodo() != Raiz) {

        if (q.categoriaNodo() == padre) {

            esSubCat = true;

        }

         q = q.nodoPadre();

    }

    return esSubCat;

}



int acat::alturaCategoria(const Categoria& cat) const {

    nodoCat q = tr->obtener(cat);

    return q.alturaNodo();

}


acat::ItCategorias acat::hijos(const Categoria& cat) {

    nodoCat& q = tr->obtener(cat);

    ItCategorias itHijos = CrearItCategorias(q.hijosNodo());
    
    return itHijos;

}








//Funciones nodo

nodoCat::nodoCat(const int& id, const int& altura, const Categoria& cat, const nodoCat* p) :id(id), altura(altura), cat(cat), padre(p) {
	
	hijos = new Conj<const nodoCat*>();	
	
}



void nodoCat::agregarCatHija(const nodoCat& cat) {
	
	hijos->AgregarRapido(&cat);
	
}


nodoCat::~nodoCat() {
	
	delete hijos;
	
}



const int& nodoCat::idNodo() const {
	
	return id;
	
}


const int& nodoCat::alturaNodo() const {
	
	return altura;
	
}



const Categoria& nodoCat::categoriaNodo() const {
	
	return cat;
	
}



const nodoCat& nodoCat::nodoPadre() const {
	
	return *padre;
	
}


bool nodoCat::tienePadre() const {
	
	return padre != NULL;
	
}




const Conj<const nodoCat*>& nodoCat::hijosNodo() const {
	
	return *hijos;
	
}
	

nodoCat::nodoCat(const nodoCat& nd) :id(nd.id), altura(nd.altura), cat(nd.cat), padre(nd.padre) {

	if (nd.hijos != NULL) {
		
		hijos = new Conj<const nodoCat*>(*(nd.hijos));
		
	} else {
		
		hijos = new Conj<const nodoCat*>();
		
	}
	
}
 



//Iterador Categorias


acat::ItCategorias acat::CrearItCategorias(const Conj<const nodoCat*>& c) {
		
	return ItCategorias(c);
		
}


bool acat::ItCategorias::HaySiguiente() const {
	
	return it.HaySiguiente();
	
}


const nodoCat& acat::ItCategorias::Siguiente() const {
	
	return *(it.Siguiente());
	
}


void acat::ItCategorias::Avanzar() {
	
	it.Avanzar();
		
}


