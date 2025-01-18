class bus {
    private:
        int id;
    public:
        bool operator==(bus& other);

};
class model {
    private:
        std::list<bus*> connectedBusses;
    public:
        void calculate();
        std::list<model*> subModels;
        std::list<bus*> getConnectedBusses();

};

struct simulationConfig{
    float stopTime;
    float stepSize;
};

struct busNet {
    bus* bus;
    std::list<model*> models;
};