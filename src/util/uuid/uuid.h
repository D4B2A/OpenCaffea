#include <stdio.h>
#include <map>
#include <iostream>
#include <string>
#include <bitset>


struct UUID_Block {
    int8_t blockData[16];
};

struct UUID{
    long uuid;
};

class UUID_Manager{
    private:
        UUID_Block* currentUUIDBlockElement = NULL; //For opimization
        int maxBlockID = 0;
        int freeUUIDs = 0;
        int freeUUIDs_loaded = 0;
        std::fstream blockFileStream;
        std::string uuid_FILE;
        std::map<int, UUID_Block> UUIDMap;
        int storeBlock(int blockID);
        int storeBlock(int blockID, UUID_Block* uuidBlock);
        void loadBlock(int blockID);
        int getBlock(UUID uuid);
        int addBlock();
        void loadFreeBlocks(int num);
    public:
        void freeUUID(UUID uuid);
        UUID getUUID();
        UUID_Manager();
        UUID_Manager(std::string uuid_File);
        ~UUID_Manager();
};