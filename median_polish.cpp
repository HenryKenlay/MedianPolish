
int() main{
	
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