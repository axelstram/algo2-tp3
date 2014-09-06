#include "aed2.h"
#include "diccTrie.h"
#include <iostream>

using namespace std;



void DiccTrieNuevoEsVacio() {

	diccTrie<int>* d = new diccTrie<int>();
	ASEGURAR((d->claves()).Cardinal(), 0);


	delete d;
}

/*
void DiccTrieConMuchosElementos() {
	diccTrie<int>* d = new diccTrie<int>();
	Conj<String>* conjComp = new Conj<String>();

	ASEGURAR((d->claves()).Cardinal(), 0);

	String s = "clave";
	int i = 4;

	conjComp->Agregar(s);
	d->definir(s, i);
	AFIRMAR(d->definido(s));
	s = "claves";
	i = 7;

	conjComp->Agregar(s);
	d->definir(s, i);

    AFIRMAR(d->definido(s));

	s = "menem";
	
	d->definir(s, i);
	conjComp->Agregar(s);

	AFIRMAR(d->definido(s));
	
	s = "menem2015";
	d->definir(s, i);
	conjComp->Agregar(s);

	AFIRMAR(d->definido(s));

	ASEGURAR(d->claves(),*conjComp);
	ASEGURAR(d->obtener(s),7);

	delete conjComp;
	delete d;


}
*/


int main(void) {
	DiccTrieNuevoEsVacio();
    DiccTrieConMuchosElementos();


	return 0;
}


