# MedianPolish
Implementation of median polish algorithm in C++

# Compiling C++
I did these experiments on a mac. The compiler that comes with Xcode doesn't have openmp installed. The following command installs homebrew version which includes openmp. 
`brew install gcc --without-multilib`

The C++ scripts are then compiled with the following (where x is replaced with 1, 2 or 3)
`/usr/local/Cellar/gcc/7.2.0/bin/g++-7 median_polish-vx.cpp -o median_polish-vx.out -fopenmp`

# Recreating results 
After compiling the C++ code. Generate the test data with the command
`python makedata.py`
Next run the experiments with the command
`python timeprograms.py`
The figures can be generated with
`python makefigs.py`
