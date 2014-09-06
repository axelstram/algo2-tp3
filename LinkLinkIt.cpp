#include "LinkLinkIt.h"


lli::lli(acat& ac) {
	
	links = new diccTrie<nodoLink>();
	arbolCat = &ac;
	
	
	//Obtengo la cantidad de categorias del Arbol de Categorias.
	int cantidadCategorias = 1;
	
	acat::ItCategorias it = arbolCat->categorias();
    
    while (it.HaySiguiente())  {
		
        cantidadCategorias++;
        it.Avanzar();
    
    }

	ids = new nodoIds*[cantidadCategorias + 1];
	ids[0] = NULL; //La primera posicion no me interesa, ya que los ids empiezan desde 1.
	
	
	linksOrdenados.c = " ";
	linksOrdenados.esLlamadaConsecutiva = false;
	linksOrdenados.ls;
	
	int i = 1;
	
	while (i < cantidadCategorias + 1) {
		
		nodoIds* r = new nodoIds(); //El constructor crea la lista vacia linksCatEHijos
		r->cantLinks = 0;
		r->diaUltimoAcceso = 0;
		ids[i] = r;
		
		i++;
		
	}
	
}



lli::~lli() {
	
	delete links;
	
	
	//Obtengo la cantidad de categorias del Arbol de Categorias.
	int cantidadCategorias = 1;
	
	acat::ItCategorias it = arbolCat->categorias();

    while (it.HaySiguiente())  {
		
        cantidadCategorias++;
        it.Avanzar();
    
    }	
    	
	
	for (int i = 1; i < cantidadCategorias + 1; i++) {
		
		delete ids[i];
		
	}
	
	delete[] ids;
		

}




void lli::nuevoLink(const Link& link, const Categoria& cat) {	
	
	nodoLink f1(cat, link); //O(|cat| + |link|)
	
	links->definir(link, f1); //O(|link| + copiar(f1)) = O(|link| + |cat|)
	
	//Obtengo una referencia del link dentro del arbol.
	nodoLink& nd = links->obtener(link); //O(|link|)
	
	infoLink info(nd.link, nd.cat, 0);   //O(1)
	linksDelSistema.AgregarAtras(info); //O(1)
		
	if (cat != arbolCat->raiz()) {
		
		const Categoria catPadre = arbolCat->padre(cat); //O(|cat|)
		
		acat::ItCategorias it = arbolCat->hijos(catPadre); //O(|cat|)
		//Obtengo el nodoCat padre de la categoria cat que me pasaron por parametro.
	    const nodoCat* padre = &((it.Siguiente()).nodoPadre()); //O(1)
	    
	    //actualizo los links y la cantidad de links de la categoria cat.
	    ids[arbolCat->id(cat)]->linksCatEHijos->AgregarAdelante(&nd); //O(1)
	    ids[arbolCat->id(cat)]->cantLinks = ids[arbolCat->id(cat)]->linksCatEHijos->Longitud(); //O(1)
	
	
		//Recorro los sucesivos padres hasta llegar a la raiz.
		while (padre->tienePadre()) {    //O(h)
		
			const int id = padre->idNodo(); //O(1)
			
			ids[id]->linksCatEHijos->AgregarAdelante(&nd); //O(1)
		
			ids[id]->cantLinks = ids[id]->linksCatEHijos->Longitud(); //O(1)

		
			padre = &padre->nodoPadre();	//O(1)
		
		
		}
		
	}
		
	
	//Actualizo la raiz.
		
	ids[1]->linksCatEHijos->AgregarAdelante(&nd); //O(1)
		
	ids[1]->cantLinks = ids[1]->linksCatEHijos->Longitud();	//O(1)
		
	
	linksOrdenados.esLlamadaConsecutiva = false;	//O(1)
		
}

//Complejidad Total: O(|link| + |cat| + h)
	

void lli::acceso(const Link& l, const Fecha& fecha) {
	
	nodoLink& in = links->obtener(l);
	
	//Si se volvio a acceder en la ultima fecha
	if ( !(in.accesosLink->EsVacia()) && (in.accesosLink->Primero()).f == fecha ) {
		
		(in.accesosLink->Primero()).cantAccesos++;
		
	} else {
		
		fechaYAccesos fa;
		fa.cantAccesos = 1;
		fa.f = fecha;
		
		(in.accesosLink)->AgregarAdelante(fa);
		
	}
	
	//Creo un nuevo acceso para el link l.
	accesos acc(l);
	acc.f = fecha;
	accesosSis.AgregarAdelante(acc);
	
	
	const int id = arbolCat->id(in.cat);
	
	
	if (id != 1) {
		
		const Categoria catPadre = arbolCat->padre(in.cat); //O(|cat|)
		
		acat::ItCategorias it = arbolCat->hijos(catPadre); //O(|cat|)
		//Obtengo el nodoCat padre de la categoria cat que me pasaron por parametro.
	    const nodoCat* padre = &((it.Siguiente()).nodoPadre()); //O(1)
	    
	    
		//Actualizo el dia del ultimo acceso para esa categoria.
		ids[id]->diaUltimoAcceso = fecha;
		
		//Recorro los sucesivos padres hasta llegar a la raiz.
		while (padre->tienePadre()) {    //O(h)
		
			const int id = padre->idNodo(); //O(1)
			
			ids[id]->diaUltimoAcceso = fecha;
		
			padre = &padre->nodoPadre();	//O(1)
		
		
		}
		
	}
	
	ids[1]->diaUltimoAcceso = fecha;
	
	
	
	
	
	
	linksOrdenados.esLlamadaConsecutiva = false;
	
}




int lli::cantLinks(const Categoria& cat) const {
	
	int id = arbolCat->id(cat);
	
	return ids[id]->cantLinks;
	
}



acat::ItCategorias lli::categorias() {
	
	return arbolCat->categorias();
	
}




lli::ItLinks lli::Links() {
	
	//Actualizo los accesos recientes del link.
	for (int i = 0; i < linksDelSistema.Longitud(); i++) {
		
		const Link link = *(linksDelSistema[i].link);
		const Categoria cat = *(linksDelSistema[i].cat);
		
		linksDelSistema[i].accesosRec = accesosRecientes(cat, link);
		
	}
	
	return ItLinks(linksDelSistema);
	
}

	


const Categoria& lli::categoriaLink(const Link& l) const {
	
	nodoLink& f = links->obtener(l);
	return f.cat;
	
}



const Fecha lli::fechaActual() const {
	
	accesos a = accesosSis.Primero();
	return a.f;
	
}



const Fecha lli::fechaUltimoAcceso(const Link& l) const {
	
	nodoLink i = links->obtener(l);
	return i.accesosLink->Primero().f;
	
}



int lli::accesosRecientesDia(const Link& l, const Fecha& fecha) const {
	
	nodoLink in = links->obtener(l);
	Lista<fechaYAccesos>::Iterador it = in.accesosLink->CrearIt();
	
	while (it.HaySiguiente()) {
		
		if ( it.Siguiente().f == fecha ) {
			
			return it.Siguiente().cantAccesos;
			
		}
		
		it.Avanzar();
		
	}
	
	return 0;
	
}




const bool lli::esReciente(const Link& l, const Fecha& fecha) const {
	
	return ( (MenorReciente(l) <= fecha) && (fecha <= fechaUltimoAcceso(l)) );
	
}



int lli::MenorReciente(const Link& l) const {
	
	const int diasRecientes = 3;
	
	if (fechaUltimoAcceso(l) + 1 >= diasRecientes) {
		
		return (fechaUltimoAcceso(l) + 1 - diasRecientes);
		
	} else {
		
		return 0; //diasRecientes - diasRecientes
		
	}
	
}




int lli::accesosRecientes(const Categoria& cat, const Link& l) const {
	
	int recientes = DiasRecientesParaCategoria(cat);
	int accesos = 0;
	nodoLink info = links->obtener(l);
	Lista<fechaYAccesos>::Iterador it = info.accesosLink->CrearIt();
	
	for (int i = 0; i <= 2; i++) {
		
		if (it.HaySiguiente()) {
			
			Fecha fecha = it.Siguiente().f;
			
			if (recientes <= fecha + 2) {
				
				int accesosDeEseLink = it.Siguiente().cantAccesos;
				accesos = accesos + accesosDeEseLink;
				
			}
			
			it.Avanzar();
			
		}
		
	}
	
	return accesos;
	
}




int lli::DiasRecientesParaCategoria(const Categoria& cat) const {
	
	int i = arbolCat->id(cat);
	return ids[i]->diaUltimoAcceso;
	
}





int lli::accesosRecientesRapido(int recientes, nodoLink& nl) const {
	
	int accesos = 0;
	Lista<fechaYAccesos>::Iterador it = nl.accesosLink->CrearIt();
	
	for (int i = 0; i <= 2; i++) {
		
		if (it.HaySiguiente()) {
			
			Fecha fecha = it.Siguiente().f;
			
			if (recientes - fecha <= 2) {
				
				int accesosDeEseLink = it.Siguiente().cantAccesos;
				accesos = accesos + accesosDeEseLink;
				
			}
			
			it.Avanzar();
			
		}
		
	}
	
	return accesos;
	
}



lli::ItLinks lli::linksOrdenadosPorAccesos(const Categoria& cat) {
	
	if ( (linksOrdenados.c == cat) && (linksOrdenados.esLlamadaConsecutiva) ) { //O(|c|)
		
		return CrearItLinksOrdenados(linksOrdenados.ls); //O(n)
		
	} else {
		
		int i = arbolCat->id(cat);
		Lista<nodoLink*>& listaLinks = *(ids[i]->linksCatEHijos);
		int d = ids[i]->diaUltimoAcceso;
		
		OrdenarEnElLugar(listaLinks,d);
		
		linksOrdenados.c = cat;
		linksOrdenados.esLlamadaConsecutiva = true;
		PasarAListaInfoLink(listaLinks, d, linksOrdenados.ls);
		
		return CrearItLinksOrdenados(linksOrdenados.ls);
		
	}
	
}
		
//Complejidad Total: O(|c| + n) en llamadas consecutivas
//                   O(|c| + n²) en otro caso



void lli::OrdenarEnElLugar(Lista<nodoLink*>& ls, int diaUltimoAcceso) {
	
	
	Lista<nodoLink*>::Iterador it1 = ls.CrearIt();
	
	for (int i = 0; i < ls.Longitud() - 1; i++) {
		
		Lista<nodoLink*>::Iterador max = it1;


		Lista<nodoLink*>::Iterador it2 = it1;
		it2.Avanzar();
			
			
		for (int j = i + 1; j < ls.Longitud(); j++) {
			
			
			if ( accesosRecientesRapido(diaUltimoAcceso, *(it2.Siguiente())) >
				 accesosRecientesRapido(diaUltimoAcceso, *(max.Siguiente())) ) {
				
					max = it2;
					
				}
		
			it2.Avanzar();
				
		}
		
		
		nodoLink* aux = it1.Siguiente();
		it1.Siguiente() = max.Siguiente();
		max.Siguiente() = aux;
		
		
		it1.Avanzar();
		
	}
	
}





void lli::PasarAListaInfoLink(const Lista<nodoLink*>& listaLinks, int recientes, Lista<infoLink>& ls) {
	
	Lista<infoLink> lin;
	Lista<nodoLink*>::const_Iterador it = listaLinks.CrearIt();
	
	while (it.HaySiguiente()) {
		
		int accesosRec = accesosRecientesRapido(recientes, *it.Siguiente());
		
		infoLink in(it.Siguiente()->link, it.Siguiente()->cat, accesosRec);
		
		lin.AgregarAtras(in);
		
		it.Avanzar();
		
	}
	
	ls = lin;
	
}
	
	

lli::ItLinks lli::CrearItLinksOrdenados(const Lista<infoLink>& ls) {
	
	return ItLinks(ls);

}



bool lli::ItLinks::HaySiguiente() const {
	
	return it.HaySiguiente();
	
}


const infoLink& lli::ItLinks::Siguiente() const {
	
	return it.Siguiente();
	
}


void lli::ItLinks::Avanzar() {
	
	it.Avanzar();
	
}




