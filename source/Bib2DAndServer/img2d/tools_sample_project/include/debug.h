#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <sstream>


#ifndef NDEBUG
    /**
    \class AssertException
    \brief Exceptions throws by eassert

    Assert exceptions are thrown by the eassert function declared in debug.h\n
    For now assert exception do not show the line number of the exception, but it should be fixed...
    \author Nicolas Moreaud
    */
    class AssertException {
        public:
          AssertException(std::string assertionString, int line, std::string filename) {
                std::ostringstream tmp;
                tmp << "Assertion failed : " << assertionString << ", file " << filename << " line " << line;
                message = tmp.str();
                std::cerr << message << std::endl; // not mandatory : can be put at the top of the main.
          }

          std::string what() {
              return message;
          }

        private:
          std::string message;
    };

    // for unix. Should make one for windows too
    #define eassert(assertion) eassert_aux(assertion, (#assertion), __LINE__, __FILE__)


    inline void eassert_aux(bool assertion, std::string assertionString, int line, std::string filename)
    {
        if (assertion == false)
        {
            throw AssertException(assertionString, line, filename);
        }
    }
#else
    #define eassert(assertion) ;
#endif // NDEBUG


#ifdef UNIT_TESTS
    #ifndef NDEBUG
        #include <cppunit/extensions/HelperMacros.h>
        #define CPPUNIT_SHOULD_THROW_ASSERT(command) \
            CPPUNIT_ASSERT_THROW(command, AssertException);
    #else
        #define CPPUNIT_SHOULD_THROW_ASSERT(command) ;
    #endif // NDEBUG
#endif // UNIT_TESTS

#endif // DEBUG_H
