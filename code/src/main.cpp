#include <iostream>
#include <fstream>
#include <sstream>

#include "../inc/multimouse.h"
#include "../inc/configparser.h"

multimouse * mm = nullptr;

std::string cfgfilename = "../cfg/config.json";

int main(int argc, char** argv) {
    // read arg
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-c")==0) {
            cfgfilename = argv[i+1];
        } else{
            printf("-cFilenameandpathtoconfig.json\r\n");
        }
    }
    // create parser
    std::ifstream input_stream(cfgfilename);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    std::string jsonstr = buffer.str();
    configparser * myparser = new configparser(jsonstr);
    // parse config
    myparser->parse();
    // create mouses and cursor from config
    RealMouse * localmice;
    mmCursor * localcursors;
    mmCursor * remotecursors;
    int amount_ml = myparser->createLocalMice(localmice);
    int amount_cl = myparser->createLocalCursor(localcursors);
    int amount_cr = myparser->createRemoteCursor(remotecursors);
    // create multimouse
    mm = new multimouse(localmice,localcursors,remotecursors);

    std::cout << "Start!" << std::endl;

    sleep(1);

    mm->start();

    while(1);

    std::cout << "Bye!" << std::endl;
    free(mm);

    return 0;
}