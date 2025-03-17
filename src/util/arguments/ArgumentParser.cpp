#include "arguments.h"

#include<string>
#include<stdio.h>


runConfig ArgumentParser::parse(int argc, char* argv[]) {
    runConfig returnConfig; //Standard RunConfig
    returnConfig.verbose = false;
    for(int n = 1; n < argc; n++) {
        std::string param = argv[n];
        if(param=="-h"||param=="--help"); //print help
        else if(param=="-v"||param=="--verbose") returnConfig.verbose = true;
        else if(param=="-V"||param=="--version"); //print version
    }
    return returnConfig;
}