#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Scanner
{
    public:
        Scanner();
        virtual ~Scanner();
        void scanInput(string &inputFile);
        void scanWord(string word);

    protected:

    private:
};

#endif // SCANNER_H
