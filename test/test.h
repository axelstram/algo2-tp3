
#ifndef AED2_TEST_H_INCLUDED
#define AED2_TEST_H_INCLUDED

#include "../aed2/TiposBasicos.h"
#include <algorithm>
#include <functional>
#include <list>
#include <map>
#include <ostream>
#include <sstream>

//no nos queda otra que hacer una macro para el numero de linea
#define STR__LINE__(var) std::ostringstream var; var << __LINE__;

///Imprime un mensaje de error si la impresion de x no es igual y
#define ASEGURAR(x,y)   { \
    STR__LINE__(linea) \
    Asegurar((x), (y), String(__FILE__) + " - Linea " + linea.str()); \
}

///Imprime un mensaje de error si la impresion de x es igual a la de y
#define DESASEGURAR(x,y) { \
    STR__LINE__(linea) \
    Asegurar((x), (y), String(__FILE__) + " - Linea " + linea.str(), TestComparador(std::operator!=), "!="); \
}

///Imprime un mensaje de error si x no evalua a true
#define AFIRMAR(x)  ASEGURAR(x, true)

///Imprime un mensaje de error si x no evalua a false
#define NEGAR(x)    ASEGURAR(x, false)

namespace aed2{
    typedef std::pointer_to_binary_function<const String&, const String&, bool> TestComparador;

    /**
     * Imprime un mensaje de error si cmp(sT, sS) es falsa,
     * donde sT es la impresion de T de acuerdo a trim,
     * sS es igual a s de acuerdo a trim,
     * cmp es una funcion que compara dos strings,
     * trim es un string que indica qué caracteres hay que borrar de s
     * y de la impresion de T (esto se usa para borrar espacios).
     * Por ultimo, nombreComparador y errMsg se utilizan para imprimir
     * el mensaje.
     */
    template<typename T>
    void Asegurar(const T& t, 
                  const String& s, 
                  String errMsg = String(), 
                  TestComparador cmp =  TestComparador(std::operator==),  
                  const String& nombreComparador = "==",
                  const String& trim=String(" \n\r\t")) {
        std::ostringstream out;
        out << t;

        String sT = out.str();
        String sS = s;        
        
        for(String::const_iterator itTrim = trim.begin(); itTrim != trim.end(); ++itTrim) {
            std::remove(sT.begin(), sT.end(), *itTrim);
            std::remove(sS.begin(), sS.end(), *itTrim);
        }
        if (not cmp(sT, sS)) {
            std::cerr << errMsg << ": !(" << sS << nombreComparador << sT << ")" << std::endl;
            assert(false);
        }
    }

    /**
     * Equivalente a Asegurar(t, impresion de r, errMsg, cmp, nombreComparador, trim)
     */
    template<typename T, typename R>
    void Asegurar(const T& t, 
                  const R& r, 
                  String errMsg = String(), 
                  TestComparador cmp =  TestComparador(std::operator==),  
                  const String& nombreComparador = "==",
                  const String& trim=String(" \n\r\t")) {
        std::ostringstream out;
        out << r;
        Asegurar(t, out.str(), errMsg, cmp, nombreComparador, trim);
    }
    
    class Tester {
        public:
            typedef void (*Test)(std::ostream&);
            void NuevoSet(const String& nombre, Nat verbReq=1);
            void Declarar(const String& nombre, Test t, Nat verbReq=2);
            void Declarar(const String& testSet, const String& nombre, Test t, Nat verbReq=2);
            void UsarSet(const String& testSet);
            
            void Ejecutar(const std::list<String>& testSets) const;
            void Ejecutar(const String& testSet) const;
            void Ejecutar() const;
            void EjecutarTodos() const;
            
            void setOutput(std::ostream& o);
            void setVerborragia(Nat level);
            
            static Tester* Instance();
        private:
            class TestSet;
            typedef std::map< String, TestSet > TestSets;

            Tester();
            //prohibido copiar
            Tester(const Tester&);
            Tester& operator=(const Tester&);
            
            void Ejecutar(TestSets::const_iterator) const;
            std::ostream& getOutput(Nat verbReq) const;
            std::ostream& getOutput(Nat verbReq, std::ostream& defOs) const;
       
            TestSets testSets;
            std::ostream* os;
            String testSetEnUso;
            Nat verborragia;
            static Tester instance;
            
            class TestSet {
                public:
                    TestSet(const String& nombre, Nat verbReq);
                    void Agregar(const String& nombre, Test t, Nat verbReq);
                    void Ejecutar(Nat verborragia) const;
              
                private:
                    typedef std::list< Test > Tests;
                    typedef std::list< String > Nombres;
                    typedef std::list< Nat > VerborragiaTests;

                    Tests tests;
                    Nombres nombres;
                    VerborragiaTests verbs;
                    String nombreSet;
                    Nat verbRequerido;
                    Tester* elTester;
            };
    };
    
}

#endif //AED2_TEST_H_INCLUDED
