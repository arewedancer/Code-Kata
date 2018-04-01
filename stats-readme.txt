Algorithm
generateCombination: generate combination pairs (for vector index)
artist-to-idx hash-map: artist to seq/no hashmap
freq: artist pair idx to frequenc hashmap
for each line of input, update artist-to-idx hashmap, 
put unique artist list into set/vector, 
sort artist index, (so pair is ascending integers)
based on generated pair combination, 
increment frequency hashmap. 
calculate max freq on one scan, output all pairs and their frequency that are 
at least max/2.

Compile(g++ 5+):
g++ -std=c++11 -o stats stats.cc

To-Do:
exception handling
argument parsing
input ETL
really should code this in python
put data in Redis
