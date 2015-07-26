#ifndef VANAGANDR_CONTAINERS_CAPACITY_HEADER
#define VANAGANDR_CONTAINERS_CAPACITY_HEADER

#define KIO 1024        // 2 ^10
#define MIO 1048576     // 2 ^20
#define GIO 1073741824  // 2 ^30


#define KO 1000       // 10^3
#define MO 1000000    // 10^6
#define GO 1000000000 // 10^9

#include <string>

enum CapacityType
{
    Power2 = 0,
    Power10 = 1
};

template<typename T>
std::string pretty_print_capacity(T cap, CapacityType t = Power2)
{
    std::string s("");
    if (t == Power2)
    {
        T gio =  cap / GIO;
        T mio = (cap % GIO) / MIO;
        T kio = ((cap % GIO) % MIO )/ KIO;
        T o   = (((cap % GIO) % MIO ) % KIO);

        if (gio != 0)
            s += std::to_string(gio) + " Gio ";

        if (mio != 0)
            s += std::to_string(mio) + " Mio ";

        if (kio != 0)
            s += std::to_string(kio) + " Kio ";

        if (o != 0)
            s += std::to_string(o) + " o ";

        if (cap == 0)
            s = "0 o ";

        return s;
    }
    else
    {
        T go =  cap / GO;
        T mo = (cap % GO) / MO;
        T ko = ((cap % GO) % MO )/ KO;
        T o   = (((cap % GO) % MO ) % KO);

        if (go != 0)
            s += std::to_string(go) + " Go ";

        if (mo != 0)
            s += std::to_string(mo) + " Mo ";

        if (ko != 0)
            s += std::to_string(ko) + " Ko ";

        if (o != 0)
            s += std::to_string(o) + " o ";

        if (cap == 0)
            s = "0 o";

        return s;
    }
}

#endif
