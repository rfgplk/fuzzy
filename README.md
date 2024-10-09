<div align="right">


# Fuzzy
### a C++ Hamming/Levenshtein distance approximate string matching library
... so fast you'd think he was a hash. 
</div>

Fuzzy is an extremely fast approximate string matching (fuzzy finding) library. 
It offers two primary modes of operation, one via the Hamming metric and the other via the Levenshtein distance (by means of the W-F algorithm). The Hamming metric is extremely efficient, being able to parse and match strings at speeds of ~3-4 GB/s per thread based on current testing (Haswell/Broadwell/Skylake). The second, more precise mode of operation, is via the Levenshtein metric, which is slower but offers more accurate hits. 


## Usage
```cpp
similar(string, string); // gauge approximate similarity of two strings
metric_hamming(token, string); // retrieve a raw Hamming metric
metric_lsh(token, string); // retrieve a raw Levenshtein metric
rough_find(token, strings); // find an approximate string match by using the Hamming distance
precise_find(token, strings); // find a string match more precisely by using the Levenshetin distance
fuzzy_find(token, strings); // search for occurance of token in strings
fuzzy_exists(token, strings); // check if an exact match of a string exists
```


### Example
```cpp
    #include "src/fuzzy.hpp"
    std::string to_find = "Hello";
    std::vector<std::string> words = { "apples", "ello", "chameleon", "asphalt", "behemoth" };
    auto f = fuzzy::fuzzy_find(to_find, words, 3); // get top three results 
    std::string best_match = f(); // best match string by name
    long double likelihood = f.likelihood(); // get likelihood of string match
    std::string likelihood = f[n]; // get name of string at index, ordered from highest likelihood hit

```

## Installation

Fuzzy is a header only library. Just copy all files from `src/` and include `src/fuzzy.hpp` into your project.


## TODO
- [ ] add fuzzy_blob/fuzzy_bin
- [ ] add full SSE support
- [ ] expand AVX support via AVX-128 \& AVX-512
- [ ] more comprehensive unit test suite
- [ ] add functionality for string streaming
- [ ] C bindings

## Misc
no dependencies, requires C++20, tested with g++.

## License
Licensed under the Boost Software License.
