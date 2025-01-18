#include<simulation.h>

bool bus::operator==(bus& other){
    return this->id==other.id;
}