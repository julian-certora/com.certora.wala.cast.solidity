#include "solidityBridge.h"

int main(int argc, char **argv) {
    solidity::StringMap sources = gatherSources(argc-1, (const char **)++argv);

    solidity::frontend::CompilerStack compiler;
    compileSources(compiler, sources);
    
    if (compiler.state() == solidity::frontend::CompilerStack::State::AnalysisSuccessful) {
        std::vector<std::string> sourceASTs = compiler.sourceNames();
        for (std::vector<std::string>::iterator t=sourceASTs.begin(); t!=sourceASTs.end(); ++t)
        {
            std::cout<<*t<<std::endl;
        }
    } else {
        solidity::langutil::ErrorList errs = compiler.errors();
        for (std::vector<std::shared_ptr<solidity::langutil::Error const>>::iterator e = errs.begin();
             e != errs.end();
             e++)
        {
            std::cout << *e << std::endl;
        }
    }
}

