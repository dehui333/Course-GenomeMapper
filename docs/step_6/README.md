# (Optional) Optimization

In order to decrease memory and execution time requirements of the mapper, you might want to try the following (difficulty in increasing order):
- minimize only a portion of the reference at a time
- load only a portion of fragment at a time
- parallelize hash table creation
- use Radix sort where applicable
- use banded alignment
- vectorize alignment using SIMD paradigm
