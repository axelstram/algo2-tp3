#ifndef DRIVER_H_
#define DRIVER_H_

#include <stdlib.h>

// adaptar a los archivos que correspondan
#include "aed2.h"
#include "Tipos.h"
#include "arbolCat.h"
#include "LinkLinkIt.h"
//

using namespace std;

// Deberan adaptar la implementacion del Driver para que corresponda
// a los archivos, nombres de clases y metodos de su implementacion.
// El codigo otorgado del driver deberia ser de mucha ayuda para poder usarlo.
//
// IMPORTANTE: No debe alterarse en ningun aspecto la interfaz del driver.
//             Es por esto que se usan unicamente tipos basicos en la misma.
class Driver {
public:
	Driver();
	~Driver();

    ///////////////////////////////////////////////////////////////
    /// Arbol de Categorias

    // Generadores
    void nuevoArbol(const Categoria& raiz); // nuevo(raiz)
    void agregarCategoria(const Categoria& c, const Categoria& h); // agregar(ac, c, h)

    // Algunos observadores
    const Categoria& raiz();
    int id(const Categoria& c);
    
    // Iteracion de categorias hijas
    int cantCategoriasHijas(const Categoria& c);
    const Categoria& obtenerIesimaCategoriaHija(const Categoria& c, int i);
    


    ///////////////////////////////////////////////////////////////
    /// LinkLinkIt

    // Generador
    /** El LinkLinkIt se crea implicitamente en la primera llamada a nuevoLink
     * usando el arbol de categorias armado con la misma instancia del Driver.
     * SE INDEFINE si nunca se llamo a nuevoArbol
    */
    void nuevoLink(const Link& l, const Categoria& c);
    void acceso(const Link& l, Fecha f);
    
    // Iteracion de links ordenados por accesos
    class ItLinks;
    
    //lli::ItLinks linksOrdenados(const Categoria& cat);
    
    lli::ItLinks linksOrdenados(const Categoria& cat);


    int cantLinks(const Categoria& c);
    const Link& obtenerIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i);
    const Categoria& obtenerCategoriaIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i);
    int obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i);

private:
    acat* arbol;
    lli* sistema;
};

#endif /* DRIVER_H_ */
