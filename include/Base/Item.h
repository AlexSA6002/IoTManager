#pragma once

#include "Named.h"
#include "Assigned.h"
#include "Value.h"

class Item : public Named,
             public Assigned {
   public:
    Item(const String& name, const String& assign) : Named{name}, Assigned{assign} {};

    virtual ~Item(){};
};