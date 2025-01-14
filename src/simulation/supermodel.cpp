#include<list>
#include<simulation.h>

class superModel{
    public:
    private:
        std::list<modelRef> submodels;
        std::list<bus*> buses;
};