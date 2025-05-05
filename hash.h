#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <algorithm> 

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
       std::vector<unsigned long long> w(5, 0);
        int len = static_cast<int>(k.length());
        int numChunks = (len + 5) / 6;

        for (int i = 0; i < numChunks; ++i) {
            int start = len - (i + 1) * 6;
            if (start < 0) start = 0;
            int end = len - i * 6;
            int chunkLen = end - start;
            std::string chunk = k.substr(start, chunkLen);

            unsigned long long value = 0;
            for (char c : chunk) {
                HASH_INDEX_T num = letterDigitToNumber(c);
                value = value * 36 + num;
            }
            w[4 - i] = value;
        }

        unsigned long long hash = 0;
        for (int i = 0; i < 5; ++i) {
            hash += static_cast<unsigned long long>(rValues[i]) * w[i];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (std::isdigit(static_cast<unsigned char>(letter))) {
            return static_cast<HASH_INDEX_T>(letter - '0' + 26);
        } else {
            char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
            return static_cast<HASH_INDEX_T>(lower - 'a');
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
