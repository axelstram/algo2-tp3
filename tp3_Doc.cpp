#include "Driver.h"
#include "aed2_tests.h"

// funcion auxiliar para mostrar accesos ordenados de la categoria
void mostrarLinksOrdenados(Driver &d, const Categoria& cat)
{
    cout << "Links Ordenados: " << cat << endl;
    int n = d.cantLinks(cat);
    for(int i = 0; i < n; i++) {
        cout << i << "\t"
             << d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos(cat, i) << "\t" 
             << d.obtenerIesimoLinkOrdenadoPorAccesos(cat, i) << "\t" 
             << d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos(cat, i) << endl;
    }
}

void armarArbol(Driver& d) {
    /**
     * cat1
     *  |- cat2
     *  |   |- cat4
     *  |   \- cat5
     *  |
     *  \- cat3
     *      \- cat6
     */
    d.nuevoArbol("cat1");
    d.agregarCategoria("cat1","cat2");
    d.agregarCategoria("cat1","cat3");
    d.agregarCategoria("cat2","cat4");
    d.agregarCategoria("cat2","cat5");
    d.agregarCategoria("cat3","cat6");
}

void testDriverCtor() {
	Driver d;
}

void testArbolRaiz() {
	Driver d;
    d.nuevoArbol("cat1");
    ASSERT_EQ(d.cantCategoriasHijas("cat1"), 0);
    ASSERT_EQ(d.raiz(), "cat1");
}

void testArbolConHijos() {
	Driver d;
    d.nuevoArbol("cat1");
    d.agregarCategoria("cat1","cat2");
    ASSERT_EQ(d.raiz(), "cat1");
    ASSERT_EQ(d.cantCategoriasHijas("cat1"), 1);
    ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat1", 0), "cat2");
}

void testArbolConHijosQueRequiereCopia__OPCIONAL() {
	Driver d;
    String *c1 = new String("cat1");
    String *c1p = new String("cat1");
    String *c2 = new String("cat2");
    d.nuevoArbol(*c1);
    d.agregarCategoria(*c1p, *c2);
    delete c1;
    delete c1p;
    delete c2;
    ASSERT_EQ(d.raiz(), "cat1");
    ASSERT_EQ(d.cantCategoriasHijas("cat1"), 1);
    ASSERT_EQ(d.obtenerIesimaCategoriaHija("cat1", 0), "cat2");
}

void testArbolIDsConsecutivos()
{
    Driver d;
    armarArbol(d);

    ASSERT_EQ(d.id("cat1"),1);
    ASSERT_EQ(d.id("cat2"),2);
    ASSERT_EQ(d.id("cat3"),3);
    ASSERT_EQ(d.id("cat4"),4);
    ASSERT_EQ(d.id("cat5"),5);
    ASSERT_EQ(d.id("cat6"),6);
}

void testArbolConVariasCategorias() {
	Driver d;
    /**
     * cat1
     *  |- cat2
     *  \- cat3
     *      \- cat4
     */
    d.nuevoArbol("cat1");
    d.agregarCategoria("cat1","cat2");
    d.agregarCategoria("cat1","cat3");
    d.agregarCategoria("cat3","cat4");

    ASSERT_EQ(d.cantCategoriasHijas("cat1"), 2);
    ASSERT_EQ(d.cantCategoriasHijas("cat2"), 0);
    ASSERT_EQ(d.cantCategoriasHijas("cat3"), 1);
}

void testArbolIteradorHijasConVariosElementos()
{
    Driver d;
    armarArbol(d);

    ASSERT(d.obtenerIesimaCategoriaHija("cat1",0) == "cat2" ||
           d.obtenerIesimaCategoriaHija("cat1",0) == "cat3");
    ASSERT(d.obtenerIesimaCategoriaHija("cat1",1) == "cat2" ||
           d.obtenerIesimaCategoriaHija("cat1",1) == "cat3");
    ASSERT(d.obtenerIesimaCategoriaHija("cat1",0) != d.obtenerIesimaCategoriaHija("cat1",1));

}

void agregarLinks(Driver& d) {
    /** categoria {links propios sin hijos}
     *
     * cat1 {link_A, link_B}
     *  |- cat2 {link_C}
     *  |   |- cat4 {link_D}
     *  |   \- cat5
     *  |
     *  \- cat3
     *      \- cat6 {link_E}
     */
    d.nuevoLink("link_A", "cat1");
    d.nuevoLink("link_B", "cat1");
    d.nuevoLink("link_C", "cat2");
    d.nuevoLink("link_D", "cat4");
    d.nuevoLink("link_E", "cat6");
}

void accederLinks(Driver& d) {
    /** categoria {links propios} : [links ordenados por acceso]
     *
     * cat1 {link_A, link_B} :      [link_A,link_C,link_B] ++ permutacion( [link_D, link_E] )
     *  |- cat2 {link_C} :          [link_C, link_D]
     *  |   |- cat4 {link_D} :      [link_D]
     *  |   \- cat5 {} :            []
     *  |
     *  \- cat3 {} :                [link_E]
     *      \- cat6 {link_E} :      [link_E]
     */
    d.acceso("link_A",1);
    d.acceso("link_A",1);
    d.acceso("link_A",1);
    d.acceso("link_A",2);
    d.acceso("link_B",2);
    d.acceso("link_B",2);
    d.acceso("link_C",3);
    d.acceso("link_C",3);
    d.acceso("link_C",3);
}

void testSistemaCuentaLinksEnCategoriasDescendientes() {
	Driver d;
    armarArbol(d);
    agregarLinks(d);

    ASSERT_EQ(d.cantLinks("cat1"), 5);
    ASSERT_EQ(d.cantLinks("cat2"), 2);
    ASSERT_EQ(d.cantLinks("cat3"), 1);
}

void testSistemaLosLinksEstanOrdenadosSegunEspecificacion() {
	Driver d;
    armarArbol(d);
    agregarLinks(d);
    accederLinks(d);

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",0), "link_A");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",0), "cat1");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",0), 4);

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",1), "link_C");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",1), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",1), 3);

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",2), "link_B");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",2), "cat1");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",2), 2);

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat2",0), "link_C");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat2",0), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat2",0), 3);
}

int indiceLinkOrdenado(Driver &d, const Categoria& cat, const Link& l)
{
    int n = d.cantLinks(cat);
    for(int i = 0; i < n; i++) {
        if (d.obtenerIesimoLinkOrdenadoPorAccesos(cat, i) == l)
            return i;
    }
    ASSERT(false);
    return -1;
}

void testSistemaLosLinksPierdenAccesosSegunVentana() {
	Driver d;
    armarArbol(d);
    agregarLinks(d);
    accederLinks(d);

    // Corrimiento de ventana
    d.acceso("link_C",4);
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1", 0), "link_C");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",0), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",0), 4);
    
    
    int pos_link_A = indiceLinkOrdenado(d, "cat1", "link_A");
    // por la ventana link A queda con 1 acceso y eso lo lleva al final
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1", pos_link_A), 1);
    ASSERT(pos_link_A == 2);

    // Corrimiento de ventana
    d.acceso("link_A",4);
    d.acceso("link_A",4);
    d.acceso("link_A",4);
    d.acceso("link_A",4);
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",0), "link_A");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",0), "cat1");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",0), 5);
    // La cat2 no cambia
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat2",0), "link_C");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat2",0), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat2",0), 4);
}

void testSistemaLinksPuedenTenerDistintosAccesosYCambiarOrden()
{
    Driver d;
    armarArbol(d);

    /** categoria {links propios sin hijos}
     *
     * cat1 {link_C}
     *  |- cat2 {link_A, link_B}
     */
    d.nuevoLink("link_A", "cat2");
    d.nuevoLink("link_B", "cat2");
    d.nuevoLink("link_C", "cat1");

	//TODO  A 100  0  0  0
	//      B      2
	//      C         0  1
    for(int i=0;i<100;i++) {
        d.acceso("link_A", 1);
    }
    d.acceso("link_B", 2);
    d.acceso("link_B", 2);
	d.acceso("link_C", 4);
	
    ASSERT_EQ(d.cantLinks("cat1"), 3);
    ASSERT_EQ(d.cantLinks("cat2"), 2);
    
	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat2",0), "link_A");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat2",0), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat2",0), 100);

	ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat2",1), "link_B");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat2",1), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat2",1), 2);
 
    
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",0), "link_B");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",0), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",0), 2);

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",1), "link_C");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",1), "cat1");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",1), 1);

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",2), "link_A");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",2), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",2), 0);
}

void testSistemaAndaPorCopia__OPCIONAL() {
    Driver d;
    String *c1 = new String("cat1");
    String *c1p = new String("cat1");
    String *c2 = new String("cat2");
    d.nuevoArbol(*c1);
    d.agregarCategoria(*c1p, *c2);
    
    delete c1;
    delete c1p;
    delete c2;
    
    String *lA = new String("link_A");
    String *lAp = new String("link_A");
    String *c2p = new String("cat2");
    d.nuevoLink(*lA, *c2p);
    delete lA;
    delete c2p;
    
    d.acceso(*lAp, 1);
    delete lAp;
    
    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat1",0), "link_A");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1",0), "cat2");
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat1",0), 1);
}

void testSistemaCategoriasSinLinkTieneIterador()
{
    Driver d;
    armarArbol(d);

    d.nuevoLink("link_A", "cat4");
    
    ASSERT_EQ(d.cantLinks("cat1"), 1);
    ASSERT_EQ(d.cantLinks("cat2"), 1);
    ASSERT_EQ(d.cantLinks("cat3"), 0);
    ASSERT_EQ(d.cantLinks("cat4"), 1);
    ASSERT_EQ(d.cantLinks("cat5"), 0);
    ASSERT_EQ(d.cantLinks("cat6"), 0);
}

//
int main(void) {
    RUN_TEST(testDriverCtor);
    RUN_TEST(testArbolRaiz);
    RUN_TEST(testArbolConHijos);
    RUN_TEST(testArbolIDsConsecutivos);
    RUN_TEST(testArbolConVariasCategorias);
    RUN_TEST(testArbolIteradorHijasConVariosElementos);
    RUN_TEST(testSistemaCuentaLinksEnCategoriasDescendientes);
    RUN_TEST(testSistemaLosLinksEstanOrdenadosSegunEspecificacion);
    RUN_TEST(testSistemaLosLinksPierdenAccesosSegunVentana);
    RUN_TEST(testSistemaLinksPuedenTenerDistintosAccesosYCambiarOrden);
    RUN_TEST(testSistemaCategoriasSinLinkTieneIterador);
    
    RUN_TEST(testArbolConHijosQueRequiereCopia__OPCIONAL);
    RUN_TEST(testSistemaAndaPorCopia__OPCIONAL);
    
	return 0;
}
