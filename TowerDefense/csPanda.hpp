#ifndef CSPANDA_HPP_INCLUDED
#define CSPANDA_HPP_INCLUDED

#include "Panda.hpp"
#include "Ice.hpp"
class csPanda : public Panda {
public:
    csPanda(int x, int y, int w, int h);
    void CreateIce();
};


#endif // CSPANDA_HPP_INCLUDED
