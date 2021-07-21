# Alignment library

Sequence alignment is a series of transformations which describes how to obtain one sequence from the other. The main use case in bioinformatics is to find similar regions between DNA chains, RNA chains or proteins in order to infer evolutionary and functional relationships. Alignments can be found using dynamic programming, an approach that solves a complicated problem by breaking it into smaller sub-problems and combining their optimal solutions. Dynamic programming algorithms for sequence alignment use a `(n + 1) * (m + 1)` matrix, where `n` and `m` are lengths of sequences that are being aligned. Each cell `(i, j)` of the matrix stores the best alignment score between substrings `[0, i]` and `[0, j]`, which can be calculated as the maximal score between the value of the upper cell plus the deletion cost, the value of the upper left cell plus the match or mismatch cost, and the value of the left cell plus the insertion cost. Once the matrix is completely filled, the optimal alignment can be found by backtracking from the best scoring cell of the matrix. A visual example is shown below.

![](figures/sample_alignment.png)

There are different versions of pairwise alignment algorithms, the Needleman-Wunsch algorithm for global alignment, the Smith-Waterman algorithm for local alignment and semi-global algorithms used for suffix-prefix and prefix-suffix alignments. The main differences between them are in the initialization step and the place from which the backtrack procedure can start.

Participants have to create a library which implements all three alignment algorithms. The library should be named in form of `<color>_alignment_engine` and should have its own namespace called after the color. The library has to be created with the same CMake file as the mapper, and eventually be linked to it. The implementation has no requirements (it can be just one function or through a class) but the alignment function should follow the below prototype:

```cpp
int Align(  // or <class name>::Align
    const char* query, unsigned int query_len,
    const char* target, unsigned int target_len,
    AlignmentType type,
    int match,
    int mismatch,
    int gap,
    std::string* cigar = nullptr,
    unsigned int* target_begin = nullptr);
```

where the return value is the alignment score, `AlignmentType` is an `enum class` determining the alignment type (i.e. global, local or semi-global), while `match`, `mismatch` and `gap` represent match, mismatch and insertion/deletion cost, respectively. There are also two optional arguments in which the function stores the [CIGAR](https://samtools.github.io/hts-specs/SAMv1.pdf) string of the alignment and the alignment beginning position on the target sequence, if they are not nullptr.

(**Optional**) Enhance the `Align` function with parameters `gap_open` and `gap_extend` and implement affine gaps.
