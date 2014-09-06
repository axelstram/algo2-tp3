#ifndef LINKLINKIT_H_
#define LINKLINKIT_H_


#include "diccTrie.h"
#include "arbolCat.h"
#include "Tipos.h"
#include "aed2.h"
#include <vector>





class infoLink {
	
	private:
	
		const Link* link;
		const Categoria* cat;
		int accesosRec;
		
	public:
	
		infoLink(const Link& l, const Categoria& c, const int& acc) :accesosRec(acc), link(&l), cat(&c) {}
		~infoLink() {}
		
		const Link& obtenerLink() const {return *link;}
		const Categoria& obtenerCategoriaLink() const {return *cat;}
		const int obtenerAccesosRecientes() const {return accesosRec;}
	
	
	friend class lli;
	
};





class lli {
	

	private:
	
	
		//Estructuras:
	
		struct fechaYAccesos {
			
			Fecha f;
			int cantAccesos;
			
			fechaYAccesos() {}
			~fechaYAccesos() {};
			
		};
	
	
		struct nodoLink {
			
			Lista<fechaYAccesos>* accesosLink;
			const Categoria cat;
			const Link link;
			
			nodoLink(const Categoria& c, const Link& l) :cat(c), link(l) {accesosLink = new Lista<fechaYAccesos>();}
				 
			~nodoLink() {delete accesosLink;};
			
			nodoLink(const nodoLink& nd) : cat(nd.cat), link(nd.link) {
				
				if (nd.accesosLink != NULL) {
					
					accesosLink = new Lista<fechaYAccesos>(*(nd.accesosLink));
				
				} else {
				
					accesosLink = new Lista<fechaYAccesos>();
					
				}
				
			}
			
		};
		
		
		
		
		struct accesos {
			
			Fecha f;
			const Link link;
			
			accesos(const Link& l) :link(l) {}
			~accesos() {};
			
		};
		
		
		struct nodoIds {
			
			int cantLinks;
			Lista<nodoLink*>* linksCatEHijos;
			Fecha diaUltimoAcceso;
			
			nodoIds() {linksCatEHijos = new Lista<nodoLink*>();}
			~nodoIds() {delete linksCatEHijos;}
			
			/*
			nodoIds& operator= (const nodoIds& otro) {
				
				cantLinks = otro.cantLinks;
				diaUltimoAcceso = otro.diaUltimoAcceso;
				
				if (linksCatEHijos != NULL)
					delete linksCatEHijos;
					
				linksCatEHijos = new Lista<nodoLink>(*(otro.linksCatEHijos));
				
			}*/
			
		};
		
		
		struct listaDeIterador {
						
			Categoria c;
			bool esLlamadaConsecutiva; 
			Lista<infoLink> ls;
			
		};
		
	
	
	
	
		//Atributos:
		diccTrie<nodoLink>* links;
		acat* arbolCat;
		nodoIds** ids;
		Lista<accesos> accesosSis;
		listaDeIterador linksOrdenados;
		Lista<infoLink> linksDelSistema;
	
		
		lli() {}; //Constructor sin parametros. No se puede llamar.
		int DiasRecientesParaCategoria(const Categoria& cat) const;
		int MenorReciente(const Link& l) const;
		int accesosRecientesRapido(int recientes, nodoLink& nl) const;
		void OrdenarEnElLugar(Lista<nodoLink*>& ls, int diaUltimoAcceso);
		void PasarAListaInfoLink(const Lista<nodoLink*>& listaLinks, int recientes, Lista<infoLink>& ls);
		
		
	public:
	
		class ItLinks;
		
		ItLinks CrearItLinksOrdenados(const Lista<infoLink>& ls);
	
		lli(acat& ac);
		~lli();
		
		//Interfaz:
		void nuevoLink(const Link& l, const Categoria& cat);
		void acceso(const Link& l, const Fecha& f);
		acat::ItCategorias categorias();
		ItLinks Links();
		const Categoria& categoriaLink(const Link& l) const;
		const Fecha fechaActual() const;
		const Fecha fechaUltimoAcceso(const Link& l) const;
		int accesosRecientesDia(const Link& l, const Fecha& f) const;
		const bool esReciente(const Link& l, const Fecha& f) const;
		int accesosRecientes(const Categoria& cat, const Link& l) const;
		ItLinks linksOrdenadosPorAccesos(const Categoria& cat);
		int cantLinks(const Categoria& cat) const;
		
		
		
		
		class ItLinks {
			
			private:
			
				Lista<infoLink> listaIter;
				Lista<infoLink>::Iterador it;
				ItLinks(const Lista<infoLink>& ls) {listaIter = ls; it = listaIter.CrearIt();}
				
			public:
			
				ItLinks& operator= (const ItLinks& otra) 
					{it = otra.it; listaIter = otra.listaIter; return *this;}

				bool operator== (const ItLinks& otro) const {return it == otro.it;}
				
				bool HaySiguiente() const;
			    const infoLink& Siguiente() const;
				void Avanzar();	
			
			
			
			friend class lli;
			
		};
		

};






#endif
