#include "Driver.h"
#include "aed2_tests.h"

void driverCtor() {
	Driver d;
}

void driverPuedeAgregarCategorias() {
	Driver d;
	
	
	//TESTS ARBOL DE CATEGORIAS.
	
    /**
     *        cat1
     *      / 	  \
     *  cat2       cat3
     *   /           \
     * cat5           cat4
     * 
     */
    d.nuevoArbol("cat1");
    d.agregarCategoria("cat1","cat2");
    d.agregarCategoria("cat1","cat3");
    d.agregarCategoria("cat3","cat4");
	d.agregarCategoria("cat2","cat5");

    ASSERT_EQ(d.raiz(), "cat1");
    ASSERT_EQ(d.id("cat1"), 1);
    ASSERT_EQ(d.id("cat2"), 2);
    ASSERT_EQ(d.id("cat3"), 3);
    ASSERT_EQ(d.id("cat4"), 4);
    ASSERT_EQ(d.id("cat5"), 5);
    
    ASSERT_EQ(d.cantCategoriasHijas("cat1"), 2);
    ASSERT_EQ(d.cantCategoriasHijas("cat2"), 1);
    ASSERT_EQ(d.cantCategoriasHijas("cat3"), 1);
    ASSERT_EQ(d.cantCategoriasHijas("cat4"), 0);
    

    ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat1", 0), "cat2");
    ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat3", 0), "cat4");
    ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat2", 0), "cat5");
    ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat1", 1), "cat3");
    
    
    
    //TESTS SISTEMA
    
    
    d.nuevoLink("www.menem.com", "cat1");
    d.nuevoLink("sida.com", "cat2");
    d.nuevoLink("asddsa", "cat5");
    

        
    d.acceso("www.menem.com", 1);
    d.acceso("www.menem.com", 1);
    d.acceso("www.menem.com", 1);
    d.acceso("www.menem.com", 2);
    d.acceso("sida.com", 2);
    d.acceso("www.menem.com", 7);
    d.acceso("www.menem.com", 7);
    
    
    
    
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 0), "www.menem.com");
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 1), "sida.com");
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 2), "asddsa");
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat5", 0), "asddsa");
	ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1", 0), 2);
	ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat5", 0), 0);
    
    
    
    ASSERT_EQ(d.cantLinks("cat2"), 2);
    ASSERT_EQ(d.cantLinks("cat1"), 3);
    ASSERT_EQ(d.cantLinks("cat5"), 1);
    ASSERT_EQ(d.cantLinks("cat4"), 0);
    ASSERT_EQ(d.cantLinks("cat3"), 0);
    
    d.nuevoLink("chipabarato", "cat4");
    
    ASSERT_EQ(d.cantLinks("cat2"), 2);
    ASSERT_EQ(d.cantLinks("cat1"), 4);
    ASSERT_EQ(d.cantLinks("cat5"), 1);
    ASSERT_EQ(d.cantLinks("cat4"), 1);
    ASSERT_EQ(d.cantLinks("cat3"), 1);
    
    d.nuevoLink("ElCarlos2015", "cat3");
    
    ASSERT_EQ(d.cantLinks("cat2"), 2);
    ASSERT_EQ(d.cantLinks("cat1"), 5);
    ASSERT_EQ(d.cantLinks("cat5"), 1);
    ASSERT_EQ(d.cantLinks("cat4"), 1);
    ASSERT_EQ(d.cantLinks("cat3"), 2);
    



    
}



void SoloRaiz() {
	
	Driver d;
	
	d.nuevoArbol("cat1");
	
	d.nuevoLink("www.google.com", "cat1");
	d.nuevoLink("www.random.com", "cat1");
	d.nuevoLink("www.uba.com", "cat1");
	d.nuevoLink("www.todoelsida.com", "cat1");
	
	d.acceso("www.google.com", 1);
	d.acceso("www.google.com", 1);
	d.acceso("www.random.com", 2);
	d.acceso("www.random.com", 2);
	d.acceso("www.random.com", 2);
	d.acceso("www.todoelsida.com", 3);
	
	
	
	
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 0), "www.random.com"); 
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 1), "www.google.com"); 
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 2), "www.todoelsida.com");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 3), "www.uba.com");
	
	
	d.acceso("www.uba.com", 4);
	d.acceso("www.uba.com", 4);
	d.acceso("www.uba.com", 4);
	d.acceso("www.uba.com", 4);
	d.acceso("www.uba.com", 4);
	
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 0), "www.uba.com");
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 1), "www.random.com"); 
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 2), "www.todoelsida.com"); 
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 3), "www.google.com");

	
}



void TestGrande() {
	
	Driver d;
	
	
	/*					   cat1
	 * 					 /  |   \
	 * 				   /	|	  \
	 * 				cat2  cat3      cat4
	 * 			   /  |	    |		|    \ 	
	 * 			cat5  cat6	cat7   cat8   cat9
	 * 			/                   |  \ 
	 *        cat10               cat11 cat12
	 * 
	 * 
	 * 
	*/
	
	//TESTS ARBOL DE CATEGORIAS:
	
    d.nuevoArbol("cat1");
    d.agregarCategoria("cat1","cat2");
    d.agregarCategoria("cat1","cat3");
    d.agregarCategoria("cat1","cat4");
    d.agregarCategoria("cat2","cat5");
    d.agregarCategoria("cat2","cat6");
    d.agregarCategoria("cat3","cat7");
    d.agregarCategoria("cat4","cat8");
    d.agregarCategoria("cat4","cat9");
    d.agregarCategoria("cat5","cat10");
    d.agregarCategoria("cat8","cat11");
    d.agregarCategoria("cat8","cat12");
    
    
    
    ASSERT_EQ(d.raiz(), "cat1");
    ASSERT_EQ(d.id("cat1"), 1);
    ASSERT_EQ(d.id("cat2"), 2);
    ASSERT_EQ(d.id("cat3"), 3);
    ASSERT_EQ(d.id("cat4"), 4);
    ASSERT_EQ(d.id("cat5"), 5);
    ASSERT_EQ(d.id("cat6"), 6);
    ASSERT_EQ(d.id("cat7"), 7);
    ASSERT_EQ(d.id("cat8"), 8);
    ASSERT_EQ(d.id("cat9"), 9);
    ASSERT_EQ(d.id("cat10"), 10);
    ASSERT_EQ(d.id("cat11"), 11);
    ASSERT_EQ(d.id("cat12"), 12);
    
    
    ASSERT_EQ(d.cantCategoriasHijas("cat1"), 3);
	ASSERT_EQ(d.cantCategoriasHijas("cat2"), 2);
    ASSERT_EQ(d.cantCategoriasHijas("cat3"), 1);
    ASSERT_EQ(d.cantCategoriasHijas("cat4"), 2);
    ASSERT_EQ(d.cantCategoriasHijas("cat5"), 1);
    ASSERT_EQ(d.cantCategoriasHijas("cat6"), 0);
    ASSERT_EQ(d.cantCategoriasHijas("cat7"), 0);
    ASSERT_EQ(d.cantCategoriasHijas("cat8"), 2);
    ASSERT_EQ(d.cantCategoriasHijas("cat9"), 0);
    ASSERT_EQ(d.cantCategoriasHijas("cat10"), 0);
    ASSERT_EQ(d.cantCategoriasHijas("cat11"), 0);
    ASSERT_EQ(d.cantCategoriasHijas("cat12"), 0);
    


	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat1", 0), "cat2");
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat1", 1), "cat3");
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat1", 2), "cat4");
	
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat2", 0), "cat5");
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat2", 1), "cat6");
	
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat3", 0), "cat7");
	
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat4", 0), "cat8");
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat4", 1), "cat9");
	
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat5", 0), "cat10");
	
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat8", 0), "cat11");
	ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat8", 1), "cat12");

	//TESTS ARBOL CATEGORIAS
	
	
	//TESTS SISTEMA:
	
	//Agrego links
	d.nuevoLink("l1", "cat1");
	d.nuevoLink("l2", "cat1");
	d.nuevoLink("l3", "cat1");
	d.nuevoLink("l4", "cat3");
	d.nuevoLink("l5", "cat4");
	d.nuevoLink("l6", "cat4");	
	d.nuevoLink("l7", "cat5");
	d.nuevoLink("l8", "cat6");
	d.nuevoLink("l9", "cat6");	
	d.nuevoLink("l10", "cat11");	
	d.nuevoLink("l11", "cat9");
	//links
	
	
	//TEST1:
	d.acceso("l5", 1);
	d.acceso("l5", 1);	
	d.acceso("l5", 1);
	d.acceso("l6", 1);
	d.acceso("l6", 1);
	d.acceso("l10", 2);
	d.acceso("l10", 2);
	d.acceso("l10", 2);
	d.acceso("l10", 2);
	d.acceso("l10", 2);
	d.acceso("l10", 2);
	d.acceso("l10", 2);
	d.acceso("l11", 3);
	
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat4", 0), "l10");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat4", 1), "l5");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat4", 2), "l6");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat4", 3), "l11");
	
	//Devuelve: [l10, l5, l6, l11]
	
	//TEST 2:
	d.acceso("l8", 4);
	d.acceso("l8", 4);
	d.acceso("l8", 4);
	d.acceso("l8", 4);
	d.acceso("l8", 4);
	d.acceso("l8", 4);
	d.acceso("l8", 4);	
	d.acceso("l8", 4);	
	d.acceso("l8", 4);
	
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat2", 0), "l8");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat2", 1), "l9");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat2", 2), "l7");
	
	//Devuelve: [l8, l9, l7]
	
	//TEST 3:
	d.acceso("l7", 4);
	d.acceso("l7", 4);
	d.acceso("l7", 4);
	d.acceso("l7", 4);
	d.acceso("l7", 4);
	
	d.acceso("l1", 4);
	d.acceso("l1", 4);
	d.acceso("l1", 4);
	
	
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 0), "l8");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 1), "l10");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 2), "l7");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 3), "l1");
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 4), "l11");
	
	ASSERT_EQ(d.cantLinks("cat10"), 0);
	
	
	/*lli::ItLinks it = d.linksOrdenados("cat1");
	
	std::cout << "[";
	
	while (it.HaySiguiente()) {
		
		cout << it.Siguiente().obtenerAccesosRecientes() << " ";
		
		it.Avanzar();
		
	}
	
	std::cout << "]" << endl;	
	*/
}





int main(void) {
    RUN_TEST(driverCtor);
    RUN_TEST(driverPuedeAgregarCategorias);
    RUN_TEST(SoloRaiz);
    RUN_TEST(TestGrande);
    

	return 0;
}
