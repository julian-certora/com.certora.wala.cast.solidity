//
//  solidityBridge.cpp
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/18/25.
//
#include "solidityBridge.h"

solidity::StringMap gatherSources(int argc, char const**argv) {
    solidity::StringMap sources;
    
    for(int i = 0; i < argc; i+=2) {
        std::string a1 = std::string(argv[i]);
        std::string a2 = std::string(argv[i+1]);
        
        std::ifstream t(a1);
        std::stringstream buffer;
        buffer << t.rdbuf();
        std::string file = buffer.str();
        
        sources[a2] = file;
    }
    return sources;
}

void compileSources(
    solidity::frontend::CompilerStack& compiler,
    const solidity::StringMap &sources)
{
    compiler.setSources(sources);
    
    compiler.parseAndAnalyze(solidity::frontend::CompilerStack::State::AnalysisSuccessful);
    
    std::cout << compiler.state() << " " << solidity::frontend::CompilerStack::State::AnalysisSuccessful << std::endl;
}
