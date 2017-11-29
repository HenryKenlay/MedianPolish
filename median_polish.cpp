#include <Eigen/Dense>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Eigen;

void median_polish(Array<double,Dynamic,Dynamic>, double, int);
ArrayXd median_of_each_row(Array<double,Dynamic,Dynamic> m);
ArrayXd median_of_each_col(Array<double,Dynamic,Dynamic> m);
double median(Array<double,Dynamic,Dynamic>, int, bool);
ArrayXXd read_array(string);


int main(){
	ArrayXXd data = read_array("5_6");
    median_polish(data, 0.01, 10);
    return(0);
}


void median_polish(Array<double,Dynamic,Dynamic> z, double eps = 0.01, int maxiter = 10){
    int nr = z.rows();
    int nc = z.cols();
    double t = 0.0;
    ArrayXd r = ArrayXd::Zero(nr);
    ArrayXd c = ArrayXd::Zero(nc);
    double oldsum = 0.0;
    for(int i = 0; i < maxiter; i++){
        median_of_each_row(z);
    }
    return;
}


ArrayXd median_of_each_row(Array<double,Dynamic,Dynamic> m){
    int nr = m.rows();
    ArrayXd r = ArrayXd::Zero(nr);
    for(int i = 0; i < nr; i++){
        r(i) = median(m, i, true);
    }
    return r;
}

ArrayXd median_of_each_col(Array<double,Dynamic,Dynamic> m){
    int nc = m.cols();
    ArrayXd c = ArrayXd::Zero(nc);
    for(int i = 0; i < nc; i++){
        c(i) = median(m, i, false);
    }
    return c;
}

double median(Array<double,Dynamic,Dynamic> m, int index, bool isRow){
	int size;
	double mCopy[size];
	isRow ? size = m.cols() : size = m.rows();
	for(int i = 0; i < size; i++){
		isRow ? mCopy[i] = m(index, i) : mCopy[i] = m(i, index); 
	}

	partial_sort(mCopy, &mCopy[1+size/2], &mCopy[size]);
	if (size%2 == 0){
		return 0.5*(mCopy[size/2] + mCopy[size/2 - 1]);
	} else{
		return mCopy[(size-1)/2];
	}
}

ArrayXXd read_array(string fname){
	int n = stoi(fname.substr(0, fname.find("_")));
	int m = stoi(fname.substr(fname.find("_")+1));
	ArrayXXd data = ArrayXXd::Zero(n, m);
	ifstream fs("data/" + fname);
	string line;
	int row = 0;
	int column = 0;
	while (fs >> line){
		stringstream lineStream(line);
		string cell;
        while (getline(lineStream, cell, ',')){
        	data(row, column) = stod(cell);
        	column++;
        }
        column = 0;
        row++;
    }
    fs.close();
    return data;
}

