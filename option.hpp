#ifndef __OPTION_H__
#define __OPTION_H__

#include <unistd.h> 
#include <iostream> 
#include <string> 

using namespace std; 

static void showUsage(string programName){
    cout << "Usage: " << programName << " [sourcCodeFile].fw\n"
        << "More Options : \n" 
        << "\t-h \t\tShow this help message\n"
        << "\t-o \t\tSet output .t(target file) name, default outputfile is a.t\n"
        << "\t-t \t\tShow symbol table as debugging message\n"
        << "\t-f \t\tShow defined functions' list and it's arugment as debugging message\n";
    return;  
}



void parseInput(int argc, char* argv[], string& outFile, string& inFile,  bool& showSymbol, bool& showFunction){
    char option; 
    const char* optstring = "fto:h:"; 
    optind = 1; 
    while(-1 != (option = getopt(argc, argv, optstring))) {
        switch(option){
            case 'h':
                showUsage(argv[0]); 
                exit(0); 
            case 'o':
                outFile = string(optarg); 
                break; 
            case 't' : 
                showSymbol = true; 
                break; 
            case 'f' : 
                showFunction = true; 
                break; 
            default: 
                throw invalid_argument("unknown option" + string(argv[optind-1])); 
        }
    }
    return; 
}

#endif 