rm ./Sudoku.exe
g++ -Xlinker -zmuldefs Main.cpp SudokuMap.cpp SudokuSolver.cpp GroupExclusion.cpp -o Sudoku.exe
./Sudoku.exe
