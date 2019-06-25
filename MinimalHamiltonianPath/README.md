The program searches for minimal Hamiltonian path
in direct weighted graphs.

### Input file

The file in.txt contains graph. It is in the form of a table of integers with n rows and n columns. A field (i,j) give the weight of the direct edge from i-th node to j-th node. Negative value means that the edge does not exists. All diagonal fields must be negative. Separator must be a single space.

### Execution and output

You should run multiple instances of the program. Each takes the same input file but different parameters. Each instance writes answer to the output file out.txt, so watch out to not override it. The output file contains the minimal Hamiltonian path the the instance found. In the first row is total weight of the path, in the second row are nodes in the order that forms the path. Negative total weight means that the instance did not find the path.

### Parameters

The program takes two parameters. The first is a reminder r, the second is denominator d. The program searches all paths starting from any i-th node such that i mod d = r. So if you want to search Hamiltonian paths with parallel degree of 3, you should run 3 instances with parameters 0 3, 1 3, 2 3.

### Algoritm

The algorithm is brute force. It searches all possible paths in DFS manner.
