# Minimizer library

The next step is to implement a library that for any DNA/RNA sequence returns its set of minimizers, which are specific substrings of defined length k (often called k-mers), creates a lookup table, and supports querying. As alignment algorithms have quadratic time complexity, k-mer indexing is often used for fast detection of similar regions between two sequences (or one vs many) prior the alignment. However, collecting all k-mers can have a big impact on computational resources (both memory and execution time), especially choosing those that are quite frequent in the target sequence set. Considering only a subset of k-mers can alleviate the whole process while keeping reasonable levels of sensitivity. One such method is to use lexicographically smallest k-mers from a sliding window, called minimizers, which are described [here](https://academic.oup.com/bioinformatics/article/20/18/3363/202143) (you can ignore begin/end minimizers).

The library should be named in a form of `<color>_minimizer_engine` and should share its namespace with the alignment library. Other constraints apply as well, it has to be created with the same CMake file, linked to the mapper, and have its own unit tests which are run via GitHub Actions. The implementation has no requirements (it can be just one function or through a class) but the function for obtaining minimizers can follow the below prototype:

```cpp
std::vector<std::tuple<unsigned int, unsigned int, bool>> Minimize(
    const char* sequence, unsigned int sequence_len,
    unsigned int kmer_len,
    unsigned int window_len);
```

where the return value is the list of found minimizers (first `unsigned int` of tuple), their positions in the sequence (second `unsigned int` of tuple) and their origin (whether they are located on the original strand (`true` in tuple) or the [reverse complement](https://en.wikipedia.org/wiki/Complementarity_(molecular_biology)) (`false` in tuple)), while parameters `kmer_len` and `window_len` are self explanatory (check the provided paper).

Furthermore, the function `Minimize` should be polymorphic, meaning if the input is a range of sequences it will store a lookup/hash table for all sampled minimizers, their origins (sequence id and strand) and positions, and be declared void. This table will be useful to find minimizer matches for any given query sequence. In order to decrease the execution time of querying, a function `Filter` will help ignore the most frequent minimizers:

```cpp
void Filter(double frequency);
```

Finally, function `Map` will return a list of overlaps to similar sequences that are currently inside the hash table created with a beforehand call to the second version of `Minimize`:

```cpp
std::vector<Overlap> Map(const char* sequence, unsigned int sequence_len);
```

Function `Map` first transforms the query sequence to a vector of minimizers, searches the hash table for all minimizer matches, and from the list of all matches for a pair of `(fragment, reference)`, the longest linear chain should represent the best candidate on the reference from which the fragment was sequenced. That region can be obtained in quasilinear time by solving the longest increasing subsequence problem on the list of minimizer matches.
