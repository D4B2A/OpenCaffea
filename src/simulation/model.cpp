#include<simulation.h>
#include<list>
/*
class model
{
public:
private:
};
*/
std::list<bus*> model::getConnectedBusses() {
    return this->connectedBusses;
}

void model::calculate() {
    for(auto currentSubModel = this->subModels.begin();currentSubModel!=this->subModels.end();++currentSubModel) {
        (*currentSubModel)->calculate();
    }
}