# Mapper

Once both libraries are finalized, they need to be linked to the mapper and the following command line arguments need to be added:
- `-c` - calculate alignment (default: false)
- `-a <str>` - alignment type (default: global)
- `-m <int> ` - match cost (default: 3)
- `-n <int>` - mismatch cost (default: -5)
- `-g <int>` - gap cost (default: -4)
- `-k <int>` - k-mer size (default: 15)
- `-w <int>` - window size (default: 10)
- `-f <int>` - k-mer frequency threshold (default: 0.001)

The mapper should create a hash table out of the reference file, filter the most frequent minimizers, and find overlaps for each sequence in combined fragment files. The overlaps should be printed to stdout in [PAF](https://github.com/lh3/miniasm/blob/master/PAF.md) format. If options `-c` is chosen, overlap regions `[q_begin, q_end]` and `[t_begin, t_end]` need to be utilized to find the alignment between a fragment and the reference, while the CIGAR string should be stored in the 13th output column in format `cg:Z:<CIGAR>` (the default behavior is without alignment to significantly decrease the run time). As mapping/alignment of sequences is independent from each other, it can be trivially parallelized and either [OpenMP](https://www.openmp.org/) or [thread_pool](parallelized) should be used, preferably the latter.
