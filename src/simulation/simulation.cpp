#include<iterator>
#include<list>
#include<simulation.h>


class simulation{
public:
    std::list<model> models;
    std::list<bus> buses;

    bool simulate(simulationConfig config){
        long totalSteps = config.stopTime/config.stepSize;

        analyseSimulation();

        for (long i = 0; i < totalSteps; i++)
        {
            precalculate();
            //iterate over each remaining model

            //start resoving step by step
            std::list<modelRef> resolvedModels = resolve();
        }
        
    }
    
private:
    std::list<supermodel> supermodels;

    bool precalculate(){
        //  a. Check for two same buses
        //  b. Check for one same buses    
    }
    std::list<modelRef> resolve(){}

    std::list<modelRef> analyseSimulation(){
        auto currentBus = buses.begin(); 
        for (size_t i = 0; i < buses.size(); i++)
        {
            //iterate over each bus searching for two components with two same busses
            for (size_t n = 0; n < models.size(); n++)
            {
                //select all buses with one matching bus
                //--> Save for later
            }
            currentBus++;   
        }
        
    }
};