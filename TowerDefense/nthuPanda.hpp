#ifndef NTHUPANDA_HPP_INCLUDED
#define NTHUPANDA_HPP_INCLUDED

#include "Panda.hpp"
#include "Ice.hpp"
class nthuPanda : public Panda {
public:
    nthuPanda(int x, int y, int w, int h);
    void CreateIce();
};

#endif // NTHUPANDA_HPP_INCLUDED
