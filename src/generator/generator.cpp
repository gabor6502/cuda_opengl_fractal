#include "generator.h"

#include "generator.cuh"

// -- Static Methods --

Generator *Generator::instance = nullptr;
Generator *Generator::getInstance()
{
    if (!instance)
    {
        instance = new Generator();
    }
    return instance;
}

void Generator::destroyInstance()
{
    if (!instance)
    {
        return;
    }
    delete instance;
    instance = nullptr;
}

// -- Constructor/Destructor --
Generator::Generator(){ 
    
    // do nothing for now
    sayhi();
}

Generator::~Generator()
{
    // do nothing for now
}

// -- Instance Methods --
