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

float model::calculate(bool calculateChange) {
    float change = 0.0;
    change += this->calculate_self(calculateChange);
    for(auto currentSubModel = this->subModels.begin();currentSubModel!=this->subModels.end();++currentSubModel) {
        change += (*currentSubModel)->calculate(calculateChange);
    }
    return change;
}