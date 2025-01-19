class bus {
    private:
        int id;
    public:
        bool operator==(bus& other);

};
class model {
    private:
        std::list<bus*> connectedBusses;
        float calculate_self(bool);
    public:
        float calculate(bool);
        std::list<model*> subModels;
        std::list<bus*> getConnectedBusses();

};

struct simulationConfig{
    float stopTime;
    float stepSize;
    float multipassAccuracy;
};

struct busNet {
    bus* bus;
    std::list<model*> models;
};