#include <iostream>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>
#include "utf8.h"

using namespace std;

int main() {
    setlocale( LC_ALL, "pl_PL" );
    int testCases;

    cin >> testCases;
    for (int i = 0; i < testCases; i++) {
        string text;
        string pattern;
        cin >> text;
        cin >> pattern;
        ifstream file(text);
        stringstream buffer;
        buffer << file.rdbuf();
        istreambuf_iterator<char> iterator(buffer.rdbuf());
        istreambuf_iterator<char> endOfString;

        if (!utf8::is_valid(iterator, endOfString)) {
            cout << "invalid text encoding" << endl;
            throw invalid_argument("invalid text encoding");
        }

        text = buffer.str();
        const char *sourceText = text.c_str();
        size_t hash1 = hash<string>{}(pattern);
        int counter = 0;
        int position = 0;
        int lastPosition = text.length() - pattern.length();

        while (position < lastPosition) {
            string patternToEvaluate = text.substr(position, pattern.length());
            size_t hash2 = hash<string>{}(patternToEvaluate);
            if ((hash1 == hash2) && (patternToEvaluate.compare(pattern) == 0)) {
                cout << counter << " ";
            }

            const char *prevVal = sourceText;
            utf8::next(sourceText, sourceText + 4);
            position += (sourceText - prevVal);
            counter++;
        }
        cout << endl;
    }
    return 0;
}