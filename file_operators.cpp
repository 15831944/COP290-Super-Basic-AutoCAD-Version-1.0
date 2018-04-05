#include "file_operators.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#define PI 3.1415926

void copy_file(std::string input_file, std::string copied_file){
	using namespace std;
	ifstream infile;
	infile.open(input_file);
    ofstream outfile;
    outfile.open(copied_file);
    string content = "";
    int i;

    for(i=0 ; infile.eof()!=true ; i++) // get content of infile
        content += infile.get();

    i--;
    content.erase(content.end()-1);     // erase last character

    //cout << i << " characters read...\n";
    infile.close();

    outfile << content;                 // output
    outfile.close();
}


void rotate(std::string file_name,float alpha,float beta, float gamma){
	using namespace std;
	ifstream input_file;
	input_file.open(file_name);
	//input_file.open("3d_file1.txt");
	int vertices,edges,j;
	input_file >> vertices;
	float x_coord[vertices];
	float y_coord[vertices];
	float z_coord[vertices];

	int i=vertices;
	while(i>0){
		input_file >> x_coord[vertices-i];
		input_file >> y_coord[vertices-i];
		input_file >> z_coord[vertices-i];
		i--;
	}

	input_file>> edges;
	i= edges;
	int firstpoint[edges];
	int secondpoint[edges];
	while(i>0){
		input_file>> firstpoint[edges-i];
		input_file>> secondpoint[edges-i];
		i--;
	}

	int p;
	//now ill do what rotate is supposed to do and change my arrays and then store it back in my file!!
	float rotate_z[4][4];
	//initialise kar bchd
	for(i=0;i<4;i++){
		for (int j = 0; j < 4; ++j)
		{
			rotate_z[i][j]=0;
		}
	}
	float sin_c= sin(gamma*PI/180);
	float cos_c= cos(gamma*PI/180);
	rotate_z[0][0]=cos_c;
	rotate_z[0][1]=-1*sin_c;
	rotate_z[1][0]=sin_c;
	rotate_z[1][1]=cos_c;
	rotate_z[2][2]=1;
	rotate_z[3][3]=1;
	// //print this matrix
	// for(i=0;i<4;i++){
	// 	for(j=0;j<4;j++){
	// 		cout<<rotate_z[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	
	//cout<<endl;
	float rotate_y[4][4];
	//initialise
	for(i=0;i<4;i++){
		for (int j = 0; j < 4; ++j)
		{
			rotate_y[i][j]=0;
		}
	}
	float sin_b= sin(beta*PI/180);
	float cos_b= cos(beta*PI/180);
	rotate_y[0][0]=cos_b;
	rotate_y[2][0]=-1*sin_b;
	rotate_y[0][2]=sin_b;
	rotate_y[2][2]=cos_b;
	rotate_y[3][3]=1;
	rotate_y[1][1]=1;
	//print this matrix
	// for(i=0;i<4;i++){
	// 	for(j=0;j<4;j++){
	// 		cout<<rotate_y[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }


	cout<<endl;
	float rotate_x[4][4];
	//initialise
	for(i=0;i<4;i++){
		for (int j = 0; j < 4; ++j)
		{
			rotate_x[i][j]=0;
		}
	}
	float sin_a= sin(alpha*PI/180);
	float cos_a= cos(alpha*PI/180);
	rotate_x[1][1]=cos_a;
	rotate_x[1][2]=-1*sin_a;
	rotate_x[2][1]=sin_a;
	rotate_x[2][2]=cos_a;
	rotate_x[0][0]=1;
	rotate_x[3][3]=1;
	//print this matrix
	// for(i=0;i<4;i++){
	// 	for(j=0;j<4;j++){
	// 		cout<<rotate_x[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	//multiply these matrices with each other
	// i get a transition matrix 
	float transition_matrix[4][4];
	float temp[4][4];
	int k,l,m;
	float a;
	//solve for the mult of 2 matrices
	for(k=0;k<4;k++){
		for(l=0;l<4;l++){
			a=0;
			for(m=0;m<4;m++){
				a=a+rotate_x[k][m]*rotate_y[m][l];
			}
			temp[k][l]=a;
		}

	}
	// cout<<endl;
	// //print the intermediate matrix
	// for(i=0;i<4;i++){
	// 	for(j=0;j<4;j++){
	// 		cout<<temp[i][j]<<" ";
	// 	}
	// 	//cout<<endl;
	// }

	//mult with third
	for(k=0;k<4;k++){
		for(l=0;l<4;l++){
			a=0;
			//cout<<endl;
			for(m=0;m<4;m++){
				a=a+temp[k][m]*rotate_z[m][l];
				// cout<<temp[k][m]<<" "<<rotate_z[m][l];
				// cout<<endl;
			}
			//cout<<endl;
			transition_matrix[k][l]=a;
		}

	}
	// cout<<endl;
	// //print the transition matrix
	// for(i=0;i<4;i++){
	// 	for(j=0;j<4;j++){
	// 		cout<<transition_matrix[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	//generate appropriate file
	float temp_x;
	float temp_y;
	float temp_z;
	float array1[4];
	for(i=0;i<vertices;i++){
		temp_x=0;
		temp_y=0;
		temp_z=0;
		array1[0]=x_coord[i];
		array1[1]=y_coord[i];
		array1[2]=z_coord[i];
		array1[3]=1;
		for(j=0;j<4;j++){
			temp_x=temp_x+transition_matrix[0][j]*array1[j];
			temp_y=temp_y+transition_matrix[1][j]*array1[j];
			temp_z=temp_z+transition_matrix[2][j]*array1[j];

		}
		x_coord[i]=temp_x;
		y_coord[i]=temp_y;
		z_coord[i]=temp_z;
	}

	ofstream write_to;
	write_to.open (file_name);
	//overwrite contents with rotated points

	write_to<<vertices;
	write_to<<endl;

	for(i=0;i<vertices;i++){

		write_to<<x_coord[i]<<"  ";
		write_to<<y_coord[i]<<"  ";
		write_to<<z_coord[i]<<endl;
	}

	write_to<<edges<<endl;

	for(i=0;i<edges;i++){
		write_to<<firstpoint[i]<<"  ";
		write_to<<secondpoint[i]<<endl;
	}


	write_to.close();
}


void twod_to_threed(std::string file_name, std::string threed_file){

	using namespace std;
	ifstream input_file;
	input_file.open(file_name);

	int vertices;
	int edges;

	input_file>>vertices;
	input_file>>edges;


	float frontx[vertices];//y
	float fronty[vertices];//z

	float rightx[vertices]; //minusx
	float righty[vertices]; //z

	float topx[vertices];//y
	float topy[vertices];//-x

	int firstpoint[edges];
	int secondpoint[edges];


	int i,j,k;

	for(i=0;i<vertices;i++){
		input_file>>frontx[i];
		input_file>>fronty[i];
	}
	for (int i = 0; i < vertices; ++i)
	{
		input_file>>rightx[i];
		input_file>>righty[i];
	}
	for (int i = 0; i < vertices; ++i)
	{		
		input_file>>topx[i];
		input_file>>topy[i];
	}
	for(i=0;i<edges;i++){
		input_file>>firstpoint[i];
		input_file>>secondpoint[i];
	}

	ofstream write_to;
	write_to.open(threed_file);
	write_to<<vertices;
	write_to<<endl;



	for(j=0;j<vertices;j++){
		// i=firstpoint[j];
		write_to<<(-1*rightx[j]);
		write_to<<"   ";
		write_to<<frontx[j];
		write_to<<"   ";
		write_to<<fronty[j];
		write_to<<endl;	

	}


	write_to<<edges;
	write_to<<endl;

	for(j=0;j<edges;j++){
		write_to<<firstpoint[j];
		write_to<<"   ";
		write_to<<secondpoint[j];
		write_to<<endl;
	}
}	

