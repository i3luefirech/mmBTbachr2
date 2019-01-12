#include <iostream>
#include <fstream>
#include <sstream>

#include "../inc/multimouse.h"
#include "../inc/configparser.h"
#include "../inc/mrmCfgParser.h"
#include "../inc/mrmMouse.h"
#include "../inc/mrmCursor.h"
#include "../inc/mrmScreen.h"
#include "../inc/mrmOSCursor.h"
#include "../inc/mrmMultiRemoteMouse.h"
#include "../inc/mrmUDPServer.h"

using namespace std;

mrmMultiRemoteMouse * mrm = nullptr;
multimouse * mm = nullptr;

string cfgfilename = "../cfg/config.json";

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
    ifstream input_stream(cfgfilename);
    stringstream buffer;
    buffer << input_stream.rdbuf();
    string jsonstr = buffer.str();
    mrmCfgParser * myparser = new mrmCfgParser(jsonstr);
    // parse config
    myparser->parse();
    // create objects
    list<mrmMouse> localmice;
    list<mrmCursor> localcursors;
    list<mrmCursor> remotecursors;
    list<mrmScreen> remotescreens;
    mrmUDPClient * udpclient;
    mrmUDPServer * udpserver;

    int amountlm = 0;
    int amountlc = 0;
    int amountrc = 0;
    int amountrs = 0;
    localmice = myparser->createLocalMice(&amountlm);
    localcursors = myparser->createLocalCursors(&amountlc);
    remotecursors = myparser->createRemoteCursors(&amountrc);
    remotescreens = myparser->createScreens(&amountrs);
    cout << "amount: " << amountlm << ", " << amountlc << ", " << amountrc << ", " << amountrs << endl;
    int port = myparser->getUDPPort();
    udpclient = new mrmUDPClient(port);
    udpserver = new mrmUDPServer(port);

    mrm = new mrmMultiRemoteMouse(localmice, amountlm, localcursors, amountlc, remotecursors, amountrc, remotescreens, amountrs, udpclient, udpserver);

    mrm->start();

    udpclient->sendtest();

    while(1){sleep(1);};

    return 0;
}