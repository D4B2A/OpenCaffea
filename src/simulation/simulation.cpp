#include<iterator>
#include<list>
#include<simulation.h>


class simulation{
public:
    std::list<model> models;
    std::list<bus> buses;

    int simulate(simulationConfig config){
        long totalSteps = config.stopTime/config.stepSize;

        std::list<model*> supermodels = analyseSimulation();

        for (long i = 0; i < totalSteps; i++)
        {
            for (auto currentModel = supermodels.begin(); currentModel!=supermodels.end();++currentModel)
            {
                (*currentModel)->calculate();
            }
            
        }
        
    }
    
private:

    /// @brief 
    /// @return
    std::list<model*> analyseSimulation(){
        std::list<busNet> matchingModels;
         
        for (auto currentBus = buses.begin(); currentBus != buses.end(); ++currentBus)
        {
            //iterate over each bus searching for two components with two same busses
            //initiate iterator for models
            std::list<model*> tempModels;    
            for (auto currentModel = models.begin(); currentModel!=models.end(); ++currentModel)
            {
                //select all buses with one matching bus
                //--> Save for later
                auto connectedBusses = currentModel->getConnectedBusses();
                for (auto currentTestBus = connectedBusses.begin(); currentTestBus != connectedBusses.end(); ++currentTestBus) {
                    if((**currentTestBus)==(*currentBus)) {
                        tempModels.push_back(&(*currentModel));
                        break;
                    }
                }           
            }
            //Save model list
            matchingModels.push_back(busNet(&(*currentBus), tempModels));   
        }
        //true if current loop achieved progress. Reset to false at the start of each loop
        bool progress = true;
        while(progress){
            progress = false;
            for (auto currentBusNet = matchingModels.begin(); currentBusNet != matchingModels.end(); ++currentBusNet) {
            }
        }
        free(&progress);
    }
};