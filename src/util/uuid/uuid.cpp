#include "uuid.h"

UUID_Manager::UUID_Manager() {
    UUID_Manager("uuid.data");
}

UUID_Manager::UUID_Manager(std::string uuid_FILE) {
    blockFileStream.open(uuid_FILE, std::fstream::in | std::fstream::out | std::fstream::binary);
}

void UUID_Manager::freeUUID(UUID uuid){
    //get block
    int blockID = getBlock(uuid);
    //search for UUIDBlock
    std::map<int,UUID_Block>::iterator mapElement = UUIDMap.find(blockID)
    //check if UUIDMap contains block
    if(mapElement!= UUIDMap.end()) {
        //Found UUIDBlock
        //Set Bitmap to free
        mapElement -> second ^= 1<<(uuid&0xf);
        freeUUIDs++;
    }
    //nothing to free here
}

int UUID_Manager::loadBlock(int blockID){
    //construct buffer for BlockEntry
    char * buffer = new char [16];
    //Set Position to BlockID
    blockFileStream.seekg(blockID*16,std::ios_base::beg);
    blockFileStream.read(buffer, 16);
    //check if reading file was successful
    if(blockFileStream) {
        delete buffer;
        return 1;
    }
    //copy buffer to UUID_Block
    UUID_Block uuid_Block;
    for(int i = 0; i<16;i++) {
        uuid_Block.blockData[i] = buffer[i];
    }
    std::pair<std::map<int,UUID_Block>::iterator,bool> ret;
    ret = UUIDMap.insert(std::pair<int, UUID_Block>(blockID, uuid_Block));
    currentUUIDBlockElement = &(*(ret.first));
    delete buffer;
    return 0;
}

int UUID_Manager::storeBlock(int blockID){
    //search for UUID_Block in UUIDMap
    std::map<int,UUID_Block>::iterator mapElement = UUIDMap.find(blockID);
    if(mapElement!= UUIDMap.end()) {
        char * buffer = new char [16];
        //copy mapElement to buffer
        for(int i = 0; i<16; i++) {
            buffer[i] = mapElement->second[i];
        }
        blockFileStream.seekp(blockID*16,std::ios_base::beg);
        blockFileStream.write(buffer, 16);
        delete buffer;
        if(blockFileStream) {
            return 1;
        }
        return 0;
    }
}

int UUID_Manager::storeBlock(int blockID, UUID_Block* uuidBlock) {
    char * buffer = new char [16];
        //copy mapElement to buffer
        for(int i = 0; i<16; i++) {
            buffer[i] = uuidBlock[i];
        }
        blockFileStream.seekp(blockID*16,std::ios_base::beg);
        blockFileStream.write(buffer, 16);
        delete buffer;
        if(blockFileStream) {
            return 1;
        }
        return 0;
}

int UUID_Manager::addBlock() {
    maxBlockID++;
    freeUUIDs += 16;
    UUIDMap.insert(std::pair<int, UUID_Block>(maxBlockID, new UUID_Block));
    return maxBlockID;
}


UUID UUID_Manager::getUUID() {
    //check if there are UUIDs available
    UUID uuid;
    if(freeUUIDs==0) {
        //Add new block
        int block = addBlock();
        uuid.uuid = block*16; //return first UUID
    }
    else {
        if(freeUUIDs_loaded==0) {
            //search for free UUIDs on disc
            loadFreeBlocks(8);
        }
        for(std::map<int,UUID_Block>::iterator mapItem = UUIDMap.begin(); mapItem!= UUIDMap.end(), mapItem++){
            char data = mapItem->second.blockData
            if(!~(data)) {
                //check if there is at least one free slot
                for(int i = 0; data; i++){
                    if(data&0x1) {
                        uuid.uuid = mapItem->first*16+i;
                        break;
                    }
                    data>>1;
                }
            }
        }
    }
    freeUUIDs_loaded -= 1;
    freeUUIDs -= 1;
    return uuid;

}

void UUID_Manager::loadFreeBlocks(int num){
    int counter = 0;
    freeUUIDs_loaded = 0;
    UUIDMap.clear(); //FIXME: Make sure, that there isn't a memory leak, since only the pointers are cleared, not the data pointed to.
    //iterate over each block
    for(int i = 0; i<maxBlockID; i++){
        loadBlock(i);
        if(!~(UUIDMap[i].blockData)) {
            UUIDMap.insert(std::pait<int,UUID_Block>(i, currentUUIDBlockElement));
            counter++;
            if(counter>=num) return;
        }
    }
}


UUID_Manager::~UUID_Manager() {
    //save all UUID Tables
    for (std::map<int,UUID_Block>::iterator it=UUIDMap.begin(); it!=UUIDMap.end(); ++it) {
        storeBlock((*it).first,&((*it).second));
    }
}

int UUID_Manager::getBlock(UUID uuid) {
    return uuid/128;
}