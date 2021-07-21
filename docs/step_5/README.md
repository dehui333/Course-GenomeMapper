# Evaluation

Once the participants feel comfortable with their code, they should write a short script that parses two PAF files and calculates the Jaccard similarity of found overlaps. This will be useful to evaluate the accuracy of their implementation with Minimap. The script should just verify the begin and end positions of each overlap, taking into account a small epsilon for possible shifts.

A lot of third generation data sets can be freely downloaded from [ENA](https://www.ebi.ac.uk/ena/browser/home), which will help compile a table consisting of Jaccard similarity, memory consumption and CPU/Real time (use `/usr/bin/time -v` for both) of different implementations (Minimap being the reference). It is advised to evaluate implementations of other participants.
