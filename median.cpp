#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
//using Eigen::MatrixXd;

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

int main(){
	Array<double,3,4> m(3,4);
	m << 5,2,3,4,
		 4,5,6,5,
		 1,8,9,7;
	cout << m << '\n';
    cout << median(m, 0, true) << '\n';
    cout << median(m, 1, true) << '\n';
    cout << median(m, 2, true) << '\n';
    cout << median(m, 0, false) << '\n';
    cout << median(m, 1, false) << '\n';
    cout << median(m, 2, false) << '\n';
    cout << median(m, 3, false) << '\n';
}

//void median(MatrixBase<Derived>& b){
//	cout << b.size();
//}