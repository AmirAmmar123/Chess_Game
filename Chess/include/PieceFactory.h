//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_PIECEFACTORY_H
#define CHESS_PIECEFACTORY_H
#include <map>
#include <memory>
#include <vector>
#include "Coordinate.h"
#include "Color.h"

using defaultIDKeyType = std::string;
/**
    The abstract factory.
    Implemented using the Singleton pattern
*/
template <class manufacturedObj, typename classIDKey=defaultIDKeyType>
class genericFactory
{
    /* The following is C++11's typedef for a pointer to a function!
	 a BASE_CREATE_FN is a static factory method: a function that
     returns an smart pointer to a manufactuedObj.  Note that you can customize
     the type of parameters to allow overloaded ctors*/
    using BASE_CREATE_FN = std::shared_ptr<manufacturedObj> (*) (Coordinate cord, Color type);

    /* FN_REGISTRY is the registry of all the BASE_CREATE_FN
     pointers registered.  Functions are registered using the
     regCreateFn member function (see below).*/
    using FN_REGISTRY = std::map<classIDKey, BASE_CREATE_FN>;
    FN_REGISTRY registry;

    /* Singleton implementation */
    genericFactory();
    genericFactory(const genericFactory&) = delete; // Ruled out
    genericFactory &operator=(const genericFactory&) = delete; // Ruled out
public:

    /// Singleton access.
    static genericFactory &instance();

    /// Classes derived from manufacturedObj call this function once
    /// per program to register the class ID key, and a pointer to
    /// the function that creates the class.
    void regCreateFn(const classIDKey &, BASE_CREATE_FN);

    /// Create a new class of the type specified by className.
    std::shared_ptr<manufacturedObj> create(const classIDKey &className,
                                            Coordinate cord, Color type) const;
};

template <class manufacturedObj, typename classIDKey>
genericFactory<manufacturedObj, classIDKey>::genericFactory()
{
}

template <class manufacturedObj, typename classIDKey>
genericFactory<manufacturedObj, classIDKey> &genericFactory<manufacturedObj, classIDKey>::instance()
{
    // Note that this is not thread-safe!
    static genericFactory theInstance;
    return theInstance;
}

/// Register the creation function.  This simply associates the classIDKey
/// with the function used to create the class.  The return value is a dummy
/// value, which is used to allow static initialization of the registry.
template <class manufacturedObj, typename classIDKey>
void genericFactory<manufacturedObj, classIDKey>::regCreateFn(const classIDKey &clName, BASE_CREATE_FN func)
{
    registry[clName]=func;
}

/// The create function simple looks up the class ID, and if it's in the list,
/// the statement "(*i).second();" calls the function.
template <class manufacturedObj, typename classIDKey>
std::shared_ptr<manufacturedObj> genericFactory<manufacturedObj, classIDKey>::create(const classIDKey &className,Coordinate cord, Color type) const
{
    std::shared_ptr<manufacturedObj> ret(nullptr);

    typename FN_REGISTRY::const_iterator regEntry = registry.find(className);
    if (regEntry != registry.end()) {
        return (*regEntry).second(cord,type);
    }
    return ret;
}

/// Helper template to make registration simple.
template <class ancestorType,
        class manufacturedObj,
        typename classIDKey=defaultIDKeyType>
class registerInFactory {
public:
    static std::shared_ptr<ancestorType> createInstance(Coordinate cord, Color type)
    {
        return std::shared_ptr<ancestorType>(manufacturedObj::createInstance(cord,type));
    }
    registerInFactory(const classIDKey &id)
    {
        genericFactory<ancestorType>::instance().regCreateFn(id, createInstance);
    }
};

#endif //CHESS_PIECEFACTORY_H
