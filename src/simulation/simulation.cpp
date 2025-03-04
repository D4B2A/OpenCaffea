#include <iterator>
#include <limits>
#include <list>
#include "simulation.h"


class Simulation
{
public:
    std::list<Model> models;
    std::list<Bus> buses;

    int simulate(simulationConfig config)
    {
        long totalSteps = config.stopTime / config.stepSize;

        std::list<Model *> supermodels = analyseSimulation();

        for (long i = 0; i < totalSteps; i++)
        {
            if (config.multipassAccuracy != 0.0)
            {
                float achievedChange = std::numeric_limits<float>::infinity();
                while (achievedChange > config.multipassAccuracy)
                {
                    achievedChange = 0.0;
                    for (auto currentModel = supermodels.begin(); currentModel != supermodels.end(); ++currentModel)
                    {
                        (*currentModel)->calculate(true);
                    }
                    //compare before/after ==> achievedChange
                }
            }
            else
            {
                for (auto currentModel = supermodels.begin(); currentModel != supermodels.end(); ++currentModel)
                {
                    (*currentModel)->calculate(false);
                }
            }
        }
    }

private:
    std::list<Model *> analyseSimulation()
    {
        std::list<busNet> matchingModels;

        for (auto currentBus = buses.begin(); currentBus != buses.end(); ++currentBus)
        {
            // iterate over each bus searching for two components with two same busses
            // initiate iterator for models
            std::list<Model *> tempModels;
            for (auto currentModel = models.begin(); currentModel != models.end(); ++currentModel)
            {
                // select all buses with one matching bus
                //--> Save for later
                auto connectedBusses = currentModel->getConnectedBusses();
                for (auto currentTestBus = connectedBusses.begin(); currentTestBus != connectedBusses.end(); ++currentTestBus)
                {
                    if ((**currentTestBus) == (*currentBus))
                    {
                        tempModels.push_back(&(*currentModel));
                        break;
                    }
                }
            }
            // Save model list
            busNet pushBusNet {&(*currentBus), tempModels};
            matchingModels.push_back(pushBusNet);
        }
        // true if current loop achieved progress. Reset to false at the start of each loop
        bool progress = true;
        while (progress)
        {
            progress = false;
            for (auto currentBusNet = matchingModels.begin(); currentBusNet != matchingModels.end(); ++currentBusNet)
            {
            }
        }
        free(&progress);
    }
};