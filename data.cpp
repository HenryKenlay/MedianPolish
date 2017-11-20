#include <iostream>
#include <Eigen/Dense>
#include <fstream>

using namespace std;
using namespace Eigen;


ArrayXXd make_dummy_data(int, int);
void write_array(ArrayXXd, string);
ArrayXXd read_array(string);
int number_rows(string);
int number_cols(string);

int main(){
	srand(0);
	ArrayXXd data = make_dummy_data(3, 2);
	write_array(data, "test");
	ArrayXXd data = read_array("test");
	cout << data;
}

ArrayXXd make_dummy_data(int n, int m){
	ArrayXXd data = ArrayXXd::Random(n, m);
	for(int i = 0; i < n; i++){
		double row_val = rand()%10;
		for(int j = 0; j < m; j++){
			data(i,j) += row_val;
		}
	}
	for(int i = 0; i < m; i++){
		double col_val = rand()%10;
		for(int j = 0; j < n; j++){
			data(j,i) += col_val;
		}
	}
	return data;
}

void write_array(ArrayXXd data, string fname){
	ofstream file;
	file.open(fname);
	if (file.is_open()){
		file << data;
	}
	file.close();
}

ArrayXXd read_array(string fname){
	int n = number_rows(fname);
	int m = number_cols(fname);
	ArrayXXd data = ArrayXXd::Zero(n, m);
	ifstream fs(fname);
	string line;
	int row = 0;
	int column = 0;
	while (fs >> line){
        data(row, column) = atof(line.c_str());
        column++;
        if(column == m){
        	row++;
        	column = 0;
        }
    }
    fs.close();
    return data;
}

int number_rows(string fname){
	ifstream fs(fname);
	string line;
	int no_rows = 0;
	while(getline(fs, line)){
		no_rows++;
	}
    fs.close();
    return no_rows;
}

int number_cols(string fname){
	ifstream fs(fname);
	string line;
	getline(fs, line);
	int no_cols = 0;
	for(int i = 0; i<line.length(); i++){
		if(line[i] == '.'){
			no_cols ++;
		}
	}
    fs.close();
    return no_cols;
}