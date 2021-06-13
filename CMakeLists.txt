cmake_minimum_required(VERSION 3.19)
project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(LexicalAnalyzer main.cpp
        src/DFA.cpp include/DFA.h
        src/Parser.cpp include/Parser.h
        src/NFA.cpp include/NFA.h
        src/Node.cpp include/Node.h
        src/Scanner.cpp include/Scanner.h
        src/Edge.cpp include/Edge.h src/GLOBAL.cpp include/GLOBAL.h src/Minimizer.cpp include/Minimizer.h include/Convertor.h src/Convertor.cpp include/LL1_parser.h src/LL1_parser.cpp include/table.h src/table.cpp include/ParseTable.h src/ParseTable.cpp include/readGrammar.h src/readGrammar.cpp)