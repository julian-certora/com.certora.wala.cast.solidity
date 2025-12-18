#include <fstream>
#include <sstream>

#include <liblangutil/CharStream.h>
#include <liblangutil/ErrorReporter.h>
#include <libsolidity/parsing/Parser.h>
#include <libsolidity/analysis/TypeChecker.h>
#include <libsolidity/analysis/StaticAnalyzer.h>
#include <libsolidity/analysis/Scoper.h>
#include <libsolidity/analysis/NameAndTypeResolver.h>
#include <libsolidity/analysis/GlobalContext.h>
#include <libsolidity/analysis/SyntaxChecker.h>
#include <libsolidity/analysis/ReferencesResolver.h>
#include <libsolidity/analysis/DocStringTagParser.h>
#include <libsolidity/interface/CompilerStack.h>

#include <assert.h>

int main(int argc, char **argv) {
    solidity::StringMap sources;

    for(int i = 1; i < argc; i+=2) {
        std::string a1 = std::string(argv[i]);
        std::string a2 = std::string(argv[i+1]);
        
        std::ifstream t(a1);
        std::stringstream buffer;
        buffer << t.rdbuf();
        std::string file = buffer.str();
        
        sources[a2] = file;
    }
    
    solidity::frontend::CompilerStack compiler;
    compiler.setSources(sources);
    
    compiler.parseAndAnalyze(solidity::frontend::CompilerStack::State::AnalysisSuccessful);
    
    std::cout << compiler.state() << " " << solidity::frontend::CompilerStack::State::AnalysisSuccessful << std::endl;
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
             e++) {
            std::cout << *e << std::endl;
        }
    }
}

