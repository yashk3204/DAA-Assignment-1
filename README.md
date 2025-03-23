
# DAA Assignment - 1
## Group - 32

    1. Yash Kantamneni (2022A7PS0120H)
    2. Anshul Sharma (2022A7PS1290H)
    3. Raghav Singh Sengar (2022A7PS1797H)
    4. Sahil Yelvantge (2022A7PS1351H)
    5. Aryan Deshmukh (2022A7PS1283H)

## Execution Instructions:

`1.  Tomita`
- Keep the datasets in the same directory as the code tomita.cpp, and change the path of the infile in the main function (line 84) to this .txt file.
- Also change the path to the outfile to any .txt file in line 10 of the tomita.cpp file.

`2. ELS`
- Keep the datasets in the repository, in the same directory as the code, with the same names. 
- Compile the file els.cpp using "g++ els.cpp" and run it using "./a.out".
- When asked for testcase number, enter 1 for Enron, 2 for WikiVote and 3 for Skitter.
- Output will be printed in a new .txt file.

`3. Chiba`
- Keep the datasets in the same directory as the code chiba.cpp, and change the path of the infile in the main function (line 167) to this .txt file.
- Also change the path to the outfile to any .txt file in line 168 of the tomita.cpp file.

## Dataset Preparation

- The datasets were preprocessed by firstly making the vertices zero-indexed.
- Then we converted directed graphs to undirected by eliminating edges that were repeated i.e. if edge A had from node X and to node Y, and edge B had from node Y and to node X, either A or B was removed. This was done by a simple C++ code.

## Links

- [Report](https://drive.google.com/file/d/1tlA4FisdCrfhHJnxJ_BA4jFEstDXAeps/view?usp=sharing)
- [GitHub Repository](https://github.com/yashk3204/DAA-Assignment-1)
- [Drive link to datasets - raw and processed](https://drive.google.com/drive/folders/1-4az2Kc6ZPhNIgaqevhy0AFzrFek0PMV?usp=sharing)
- [Project Webpage](https://yashk3204.github.io/DAA-Assignment-1/)

## Results

### Paper 1 - Tomita
| Dataset | No. of Maximal Cliques | Size of Largest Clique | Runtime |
| :-------- | :------- | :------------------------- | :---------- |
| Enron | 226859 | 20 | 7.257s |
| WikiVote | 460185 | 17 | 4.844s |

### Paper 2 - ELS
| Dataset | No. of Maximal Cliques | Size of Largest Clique | Runtime |
| :-------- | :------- | :------------------------- | :---------- |
| Enron | 226859 | 20 | 0.974s |
| WikiVote | 460185 | 17 | 1.389s |
| Skitter | 37322355 | 67 | 212.470s |

### Paper 3 - Chiba
| Dataset | No. of Maximal Cliques | Size of Largest Clique | Runtime |
| :-------- | :------- | :------------------------- | :---------- |
| Enron | 226859 | 20 | 0.644s |
| WikiVote | 460185 | 17 | 0.881s |
| Skitter | 37322355 | 67 | 300.255s |

## Individual Contributions

| Name | Contribution |
| :-------- | :------- |
| Yash Kantamneni | Code for Tomita paper and its report/observations, GitHub repo and README |
| Anshul Sharma | Data preparation/preprocessing and project webpage |
| Raghav Singh Sengar | Code for ELS (Bron-Kerbosch) paper and its report, project webpage |
| Sahil Yelvantge | Code for Chiba and ELS papers and their report/observations |
| Aryan Deshmukh | Code for Chiba paper and its report/observations |