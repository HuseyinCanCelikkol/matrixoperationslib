#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cstdio> 
#include <stdint.h>
int i, j;


using namespace std;

template<class T>

class Matrix {

public:
	Matrix();
	Matrix(int rows, int columns, int value);
	Matrix(int rows, int columns, double value);
	Matrix(int rows, int columns, char mytype);
	void print();
	void print(string file);
	Matrix<T> resize(int rows, int columns);
	Matrix<T> operator+(Matrix<T> obj);
	Matrix<T> operator=(Matrix<T> obj);
	Matrix<T> operator-(Matrix<T> obj);
	Matrix<T> operator*(Matrix<T> obj);
	Matrix<T> operator+(int value);
	Matrix<T> operator-(int value);
	Matrix<T> operator*(int value);
	Matrix<T> operator/(int value);
	Matrix<T> operator%(int value);
	Matrix<T> operator^(int value);
	Matrix<T> Transpose();
	Matrix<T> emul(Matrix<T>* obj);
	
protected:
	unsigned int row;
	unsigned int column;
	T** matrix;
	void createMatrix();//Matrisi oluþtur
	
};

template<class T> void Matrix<T>::createMatrix() {
	this->matrix = new T * [this->row];			//
	for (i = 0; i < this->row; i++) {			//matrisin tanýmý
		this->matrix[i] = new T[this->column];	//
	}
}

template<class T> Matrix<T>::Matrix() {			//10x10 0 dolu matris
	this->row = 10;
	this->column = 10;
	this->createMatrix();

	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			this->matrix[i][j] = 0;			
		}
	}
}

template<class T> Matrix<T>::Matrix(int rows, int columns, int value) {			// row x column integer "value" dolu matris

	this->row = rows;
	this->column = columns;
	this->createMatrix();

	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			this->matrix[i][j] = value; 
		}
	}
}

template<class T> Matrix<T>::Matrix(int rows,int columns, double value) {		// row x column double "value" dolu matris constructoru

	this->row = rows; this->column = columns;
	this->createMatrix();

	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			this->matrix[i][j] = value;
		}
	}
}

template<class T> Matrix<T>::Matrix(int rows, int columns,char mytype){			// birim veya random degerli matris constructoru
	this->row = rows; this->column = columns;
	if (mytype == 'e') {
		if(this->row == this->column){
			this->createMatrix();
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				this->matrix[i][j] = 0;
			}
		}

		for (i = 0; i < this->row; i++) {
			this->matrix[i][i] = 1;
		}
		}
		else {
			cout << "There's no Equal Row and Columns" << endl; //row == column degilse hata mesaji (birim matriste row = column olmalý)
			cout << "Process Cancelled";
		}
	}

	if (mytype == 'r') {

		this->createMatrix();
		srand(time(NULL));
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				this->matrix[i][j] = rand() % 256;
			}
		}
	}
}

template<class T> void Matrix<T>::print() {				//ekrana yazdir
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			cout << this->matrix[i][j] << "\t";
			if (j == this->column - 1) cout << endl << endl;
		}
	}
}

template<class T> void Matrix<T>::print(string file) {			//dosyaya yazdir
	ofstream myfile;
	myfile.open(file.c_str());
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			myfile << this->matrix[i][j] << "\t";
			if (j == this->column - 1) myfile << endl << endl;
		}
	}
	myfile.close();
}

template<class T> Matrix<T> Matrix<T>::resize(int rows, int columns) {			//matrisi resize et

	Matrix<T>* temp2 = new Matrix(rows, columns, 0);
	if (this->row <= rows && this->column <= columns) {							//matrisi her yonden buyutuyor isek:
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				temp2->matrix[i][j] = this->matrix[i][j];
			}
			for (int k = this->row; k < rows; k++)
			{
				for (int l = this->column; l < columns; l++) {
					temp2->matrix[k][l] = 0;
				}
			}
		}
	}

	if (this->row <= temp2->row && this->column >= temp2->column) {			// Matrisin rowunu buyutup veya sabit birakip column unu kucultuyor isek
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < temp2->column; j++) {
				temp2->matrix[i][j] = this->matrix[i][j];
			}
			for (int k = this->row; k < rows; k++)
			{
				int l = columns;
				temp2->matrix[k][l] = 0;//boþ kalan yerlere 0 yazar 

			}
		}
	}

	if (this->row >= temp2->row && this->column <= temp2->column) {			// Matrisin columnunu buyutup veya sabit birakip row unu kucultuyor isek
		for (i = 0; i < temp2->row; i++) {
			for (j = 0; j < this->column; j++) {
				temp2->matrix[i][j] = this->matrix[i][j];
			}
			for (int k = this->row; k < rows; k++)
			{
				for (int l = this->column; l < columns; l++) {
					temp2->matrix[k][l] = 0;
				}
				for (int k = this->column; k < columns; k++)
				{
					int l = rows;
					temp2->matrix[k][l] = 0;

				}
			}
		}
	}
	if (this->row >= temp2->row && this->column >= temp2->column) {			// Matrisi kucultuyor isek
		for (i = 0; i < temp2->row; i++) {
			for (j = 0; j < temp2->column; j++) {
				temp2->matrix[i][j] = this->matrix[i][j];
			}
		}
		for (int k = rows; k < this->row; k++)
		{
			for (int l = 0; l < this->column; l++) {
				this->matrix[k][l] = 0;
			}
		}
	}
	this->matrix = temp2->matrix;
	this->row = rows; this->column = columns;

	return *this;
}

template<class T> Matrix<T> Matrix<T>::operator+(Matrix<T> obj) {
	if (this->row == obj.row && this->column == obj.column) {
		Matrix<T> temp;
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				temp.matrix[i][j] = this->matrix[i][j] + obj.matrix[i][j];
			}
		}
		temp.resize(this->row, this->column);
		return temp;
	}
	else {
		cout << "There's no equal rows or columns!" << endl;
		cout << "Process cancelled." << endl;
	}
}


template<class T> Matrix<T> Matrix<T>::operator=(Matrix<T> obj) {
	if (this->row == obj.row && this->column == obj.column) {
		Matrix<T> temp;
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				this->matrix[i][j] = obj.matrix[i][j];
			}
		}
		temp.resize(this->row, this->column);
		return temp;
	}
	else {
		cout << "There's no equal rows or columns!" << endl;
		cout << "Process cancelled." << endl;
	}
}
template<class T> Matrix<T> Matrix<T>::operator-(Matrix<T> obj) {
	if (this->row == obj.row && this->column == obj.column) {
		Matrix<T> temp;
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				temp.matrix[i][j] = this->matrix[i][j] - obj.matrix[i][j];
			}
		}
		temp.resize(this->row, this->column);
		return temp;
	}
	else {
		cout << "There's no equal rows or columns!" << endl;
		cout << "Process cancelled." << endl;
	}
}

template<class T> Matrix<T> Matrix<T>::operator*(Matrix<T> obj) {
	if (this->column == obj.row) {
		Matrix<T> temp;
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				temp.matrix[i][j] = this->matrix[i][j] * obj.matrix[j][i];
			}
		}
		temp.resize(this->row, this->column);
		return temp;
	}
	else {
		cout << "There's no equal rows or columns!" << endl;
		cout << "Process cancelled." << endl;
	}
}

template<class T> Matrix<T> Matrix<T>::operator+(int value) {


	Matrix<T> temp;
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			temp.matrix[i][j] = this->matrix[i][j] + value;
		}
	}
	temp.resize(this->row, this->column);
	return temp;

}

template<class T> Matrix<T> Matrix<T>::operator-(int value) {


	Matrix<T> temp;
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			temp.matrix[i][j] = this->matrix[i][j] - value;
		}
	}
	temp.resize(this->row, this->column);
	return temp;

}

template<class T> Matrix<T> Matrix<T>::operator*(int value) {


	Matrix<T> temp;
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			temp.matrix[i][j] = this->matrix[i][j] * value;
		}
	}
	temp.resize(this->row, this->column);
	return temp;

}

template<class T> Matrix<T> Matrix<T>::operator/(int value) {


	Matrix<T> temp;
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			temp.matrix[i][j] = this->matrix[i][j] / value;
		}
	}
	temp.resize(this->row, this->column);
	return temp;

}

template<class T> Matrix<T> Matrix<T>::operator%(int value) {


	Matrix<T> temp;
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			temp.matrix[i][j] = this->matrix[i][j] % value;
		}
	}
	temp.resize(this->row, this->column);
	return temp;

}

template<class T> Matrix<T> Matrix<T>::operator^(int value) {


	Matrix<T> temp;
	for (i = 0; i < this->row; i++) {
		for (j = 0; j < this->column; j++) {
			temp.matrix[i][j] = pow(this->matrix[i][j], value);
		}
	}
	temp.resize(this->row, this->column);
	return temp;

}

template<class T> Matrix<T> Matrix<T>::Transpose() {
	Matrix<T> temp;
	for (i = 0; i < this->row; i++) {
		for (j = 0; j <this->column; j++) {
			temp.matrix[j][i] = this->matrix[i][j];
		}
	}
	temp.resize(this->row, this->column);
	return temp;
}

template<class T> Matrix<T> Matrix<T>::emul(Matrix<T>* obj) {
	if (this->row == obj->row && this->column == obj->column) {
		Matrix<T> temp;
		for (i = 0; i < this->row; i++) {
			for (j = 0; j < this->column; j++) {
				temp.matrix[i][j] = this->matrix[i][j] * obj->matrix[i][j];
			}
		}
		temp.resize(this->row, this->column);
		return temp;
	}
	else {
		cout << "There's no equal rows or columns!" << endl;
		cout << "Process cancelled." << endl;
	}
}


template<class T> class Table : public Matrix<T> {
public:
	Table();
	Table(int rows, int columns, int value);
	Table(int rows, int columns, double value);
	Table(int rows, int columns, char mytype);
	void print();
	int itemAt(int rows, int columns);
	int itemAt(string s);
	int itemAt(string rs, string cs);
	void setRowNames(string s[], int n);
	void setColNames(string s[], int n);

private:
	void SetRowColDefault();
	string* rownames;
	string* colnames;
};
template<class T> void Table<T>::SetRowColDefault() {
	this->rownames = new string[this->row];
	for (int i = 0; i < this->row; i++) {
		stringstream convertstring;
		convertstring << i;
		string str;
		convertstring >> str;
		this->rownames[i] = str;

	}
	this->colnames = new string[this->column];
	if (this->column < 26) {
		for (int i = 0; i < this->column; i++) {
			char c = 65 + i;
			stringstream convertstring;
			convertstring << c;
			string str;
			convertstring >> str;
			this->colnames[i] = str;
		}
	}
	else {
		for (int i = 0; i < 26; i++) {
			char c = 65 + i;
			stringstream convertstring;
			convertstring << c;
			string str;
			convertstring >> str;
			this->colnames[i] = str;
		}
	}
}

template<class T> void Table<T>::setColNames(string s[], int n) {
	for (i = 0; i < n; i++) {
		if (s[i].length() > 4) {
			s[i].resize(4);
			this->colnames[i] = s[i];
		}
		else {
			this->colnames[i] = s[i];
		}
	}
}

template<class T> void Table<T>::setRowNames(string s[], int n) {
	for (i = 0; i < n; i++) {
		if (s[i].length() > 8) {
			s[i].resize(8);
			this->rownames[i] = s[i];
		}
		else {
			this->rownames[i] = s[i];
		}
	}
}

template<class T> Table<T>::Table():Matrix<T>() {
	this->SetRowColDefault();
}

template<class T> Table<T>::Table(int rows, int columns, int value):Matrix<T>(rows,columns,value) {
	this->SetRowColDefault();
}

template<class T> Table<T>::Table(int rows, int columns, double value):Matrix<T>(rows,columns,value) {
	this->SetRowColDefault();
}

template<class T> Table<T>::Table(int rows, int columns, char mytype) :Matrix<T>(rows, columns, mytype) {
	this->SetRowColDefault();
}
template<class T> void Table<T>::print() {

	cout << "\t";
	for (i = 0; i < this->column; i++) {

		cout << "\t" << this->colnames[i];
	}
	cout << endl << endl;
	for (i = 0; i < this->row; i++) {
		if (this->rownames[i].length() == 8) {
			cout << this->rownames[i] << "\t";
		}
		else {
			cout << this->rownames[i] << "\t\t";
		}
		for (j = 0; j < this->column; j++) {
			cout << this->matrix[i][j] << "\t";
			if (j == this->column - 1) cout << endl << endl;
		}
	}


}

template<class T> int Table<T>::itemAt(int rows, int columns) {
	return this->matrix[rows][columns];
}

template<class T> int Table<T>::itemAt(string s) {
	if(s.at(0) <= this->column + 64){
		char c = s.at(0);
		s.erase(0, 1);
		stringstream convert(s);
		int a;
		convert >> a;
		if(a <= this->row-1){
			return this->matrix[a][c - 65];
		}
		
		else {
			cout << "Entered an invalid value" << endl;
			cout << "Process Cancelled. Returned 0." << endl << endl;
			return 0;
		}
	}
	else {
		cout << "Entered an invalid value" << endl;
		cout << "Process Cancelled. Returned 0."<<endl <<endl;
		return 0;
	}
}

template<class T> int Table<T>::itemAt(string rs, string cs) {
	int tempcol, temprow;
	for (i = 0; i < this->column; i++) {
		if (this->colnames[i] == cs) {
			tempcol = i;
			break;
		}
	}
	for (i = 0; i < this->row; i++) {
		if (this->rownames[i] == rs) {
			temprow = i;
			break;
		}
	}
	return this->matrix[temprow][tempcol];
}

int main() {
	
	Matrix<int> matrix = new Matrix<int>(10,10,'e');
	matrix.print();
}

