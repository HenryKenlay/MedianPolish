#include <Eigen/Dense>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Eigen;

void median_polish(ArrayXXd&, double, int, bool);
ArrayXd median_of_each_row(ArrayXXd& m);
ArrayXd median_of_each_col(ArrayXXd& m);
double median(ArrayXXd&, int, bool);
double median_vec(ArrayXd& m);
ArrayXXd read_array(string);


int main(int argc, char** argv){
    string n = argv[1];
    string m = argv[2];
    ArrayXXd data = read_array(n + "_" + m);
    if (argc < 4){
        median_polish(data, 0.01, 10, true);
    }
    return(0);
}

void median_polish(ArrayXXd& z, double eps, int maxiter, bool verbose){
    int nr = z.rows();
    int nc = z.cols();
    double t = 0.0;
    ArrayXd r = ArrayXd::Zero(nr);
    ArrayXd c = ArrayXd::Zero(nc);
    double oldsum = 0.0;
    // other declarations
    ArrayXd rdelta;
    ArrayXd cdelta;
    double delta;
    double newsum;
    bool converged = false;
    for(int i = 0; i < maxiter; i++){
        rdelta = median_of_each_row(z);
        for(int j = 0; j < nc; j++){
            z.col(j) = z.col(j) - rdelta;
        }
        r = r + rdelta;
        delta = median_vec(c);
        c = c - delta;
        t = t + delta;
        cdelta = median_of_each_col(z);
        for(int j = 0; j < nr; j++){
            z.row(j) = z.row(j) - cdelta.transpose();
        }
        c = c + cdelta;
        delta = median_vec(r);
        r = r - delta;
        t = t + delta;
        newsum = z.abs().sum();
        if ((newsum == 0) || (abs(newsum - oldsum) < eps*newsum)){
            converged = true;
            break;
        } else{
            oldsum = newsum;
        }
        if (verbose){
            cout << i+1 << ": " << newsum << endl;
        }
    }
    if (converged){
        if (verbose){
            cout << "Final: " << newsum << endl;
        }
    } else{
        cerr << "Median polish did not converge in " << maxiter << " iterations" << endl;
    }
    return;
} 


ArrayXd median_of_each_row(ArrayXXd& m){
    int nr = m.rows();
    ArrayXd r = ArrayXd::Zero(nr);
    for(int i = 0; i < nr; i++){
        r(i) = median(m, i, true);
    }
    return r;
}

ArrayXd median_of_each_col(ArrayXXd& m){
    int nc = m.cols();
    ArrayXd c = ArrayXd::Zero(nc);
    for(int i = 0; i < nc; i++){
        c(i) = median(m, i, false);
    }
    return c;
} 

double median(ArrayXXd& m, int index, bool isRow){
	int size;
	isRow ? size = m.cols() : size = m.rows();
	double mCopy[size];
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

double median_vec(ArrayXd& m){
	int size = m.size();
	double mCopy[size];
	for(int i = 0; i < size; i++){
		mCopy[i] = m(i);
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

