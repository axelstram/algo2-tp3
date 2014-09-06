
#include "test.h"

namespace aed2{
    
    Tester Tester::instance; //declaracion de la variable estatica;
    //declaracion de un buffer nulo
    struct nullstream : std::ostream {
            struct nullbuf : std::streambuf {
                int overflow(int c) {return traits_type::not_eof(c);}
            };
            nullstream(): std::ios(&m_sbuf), std::ostream(&m_sbuf) {} 
        private:
            nullbuf m_sbuf;
    } cnull;

    Tester::Tester() : os(&std::clog), verborragia(0) {}
    
    void Tester::NuevoSet(const String& nombre, Nat verbReq) {
        TestSets::iterator it = testSets.find(nombre);
        assert(it == testSets.end());
        testSets.insert( std::pair<String, TestSet >(nombre, TestSet(nombre, verbReq)) );
    }
    
    void Tester::Declarar(const String& nombre, Tester::Test t, Nat verbReq) {
        assert(testSetEnUso != String());
        Declarar(testSetEnUso, nombre, t, verbReq);
    }
    
    void Tester::Declarar(const String& testSet, const String& nombre, Tester::Test t, Nat verbReq) {
        TestSets::iterator it = testSets.find(testSet);
        assert(it != testSets.end());
        it->second.Agregar(nombre, t, verbReq);
    }
    
    void Tester::UsarSet(const String& testSet) {
        testSetEnUso = testSet;
    }
            
    void Tester::Ejecutar(const std::list<String>& testSets) const {
        std::list<String>::const_iterator it = testSets.begin();
        while(it != testSets.end()) {
            Ejecutar(*it);
            ++it;
        }
    }
    
    void Tester::Ejecutar(const String& testSet) const {
        TestSets::const_iterator it = testSets.find(testSet);
        if(it != testSets.end()) Ejecutar(it);
        else std::cerr << "No se encontro el TestSet: " << testSet << std::endl;
    }
        
    void Tester::Ejecutar(Tester::TestSets::const_iterator it) const {
        it->second.Ejecutar(verborragia);
    }
    
    void Tester::Ejecutar() const {
        Ejecutar(testSetEnUso);
    }
    
    void Tester::EjecutarTodos() const {
        Tester::TestSets::const_iterator it;
        for(it = testSets.begin(); it != testSets.end(); ++it)
            Ejecutar(it);
    }
            
    void Tester::setOutput(std::ostream& o) {
        os = &o;
    }
            
    void Tester::setVerborragia(Nat level) {
        verborragia = level;
    }
            
            
    Tester* Tester::Instance() {
        return &instance;
    }

    std::ostream& Tester::getOutput(Nat verbReq) const {
        return getOutput(verbReq, *os);
    }
    
    std::ostream& Tester::getOutput(Nat verbReq, std::ostream& defOs) const {
        return verbReq <= verborragia ? defOs : cnull;
    }

    Tester::TestSet::TestSet(const String& nombre, Nat verbReq) : 
        nombreSet(nombre), 
        verbRequerido(verbReq), 
        elTester(Tester::Instance()) 
        {}
    
    void Tester::TestSet::Agregar(const String& nombre, Tester::Test t, Nat verbReq) {
        tests.push_back(t);
        nombres.push_back(nombre);
        verbs.push_back(verbReq);
    }

    void Tester::TestSet::Ejecutar(Nat verborragia) const {
        std::ostream& osTestSet = elTester->getOutput(verbRequerido);
        osTestSet << "Ejecutando TestSet: " << nombreSet << std::endl;


        Tests::const_iterator itTest = tests.begin();
        Nombres::const_iterator itNombre = nombres.begin();
        VerborragiaTests::const_iterator itVerbs = verbs.begin();
        while(itTest != tests.end()) {
            std::ostream& osTest = elTester->getOutput(*itVerbs, osTestSet);
            osTest << "Ejecutando test: " << *itNombre << std::endl;
            (*itTest)(osTest);
            osTest << "Finalizando la ejecución de test: " << *itNombre << std::endl;
            ++itTest; ++itNombre; ++itVerbs;
        }
        
        osTestSet << "Finalizando Ejecucion de TestSet: " << nombreSet << std::endl;
    }
    
}
