#include <iostream>
#include <fstream>
#include "gnuplot_i.hpp"
#include "my_display.hpp"



void wait_for_key ()
{
	
    std::cout << std::endl << "		"<<"Press ENTER to continue..." << std::endl;
    std::cout<<"		";
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    return;
}

void frontview(std::string file_name){

	using namespace std;

	//read the file once again
	float max_x=-100000;
	float max_y=-100000;
	float max_z=-100000;
	float min_x=100000;
	float min_y=100000;
	float min_z=100000;

	ifstream input_file;
	input_file.open(file_name);
	//input_file.open("3d_file1.txt");
	int vertices,edges;
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
	//now i have read the 3d file and stored in arrays;
	//now find max_x etc

	for(i=0;i<vertices;i++){
		if(max_x<x_coord[i]) max_x=x_coord[i];
		if(min_x>x_coord[i]) min_x=x_coord[i];
		if(max_y<y_coord[i]) max_y=y_coord[i];
		if(min_y>y_coord[i]) min_y=y_coord[i];
		if(max_z<z_coord[i]) max_z=z_coord[i];
		if(min_z>z_coord[i]) min_z=z_coord[i];
	}

	float frontview_x[vertices];
	float frontview_y[vertices];

	for(i=0;i<vertices;i++){
		frontview_x[i]=y_coord[i];
		frontview_y[i]=z_coord[i];
	}

	//print these values to a file that gnuplot wants

	ofstream write_to;
	write_to.open("abc.txt");
	for ( i = 0; i < edges; ++i)
	{
		write_to<< frontview_x[firstpoint[i]]<<"  ";
		write_to<<frontview_y[firstpoint[i]]<<endl;
		write_to<<frontview_x[secondpoint[i]]<<"  ";
		write_to<<frontview_y[secondpoint[i]]<<endl;
		write_to<<"\n";

	}
	

	float actual_fix_p,actual_fix_n;
	if(max_y>max_z) actual_fix_p=max_y;
	else actual_fix_p=max_z;
	if(min_y<min_z) actual_fix_n=min_y;
	else actual_fix_n=min_z;

	actual_fix_p=1.15*actual_fix_p;
	actual_fix_n=1.15*actual_fix_n;



	write_to<< actual_fix_p<<"  "<< actual_fix_p<<endl;
	write_to<< actual_fix_p<<"  "<<actual_fix_p<<endl;
	write_to<<"\n";
	write_to<< actual_fix_n<<"  "<< actual_fix_n<<endl;
	write_to<< actual_fix_n<<"  "<<actual_fix_n<<endl;	

    Gnuplot g1;
    //cout<< "will try to make a square"<<endl;
    g1<<"unset border\n";
    g1<<"unset tics\n";
    g1<<"unset key\n";
    g1 << "set terminal x11 size 800,800\n";

    //g1<<"unset autoscale\n";
    g1 << "plot 'abc.txt' with linespoint lt 1 lw 4 \n";
    std::cin.get();

}

void orthographic_display(std::string file_name){

	using namespace std;

	//read the file once again
	float max_x=-100000;
	float max_y=-100000;
	float max_z=-100000;
	float min_x=100000;
	float min_y=100000;
	float min_z=100000;

	ifstream input_file;
	input_file.open(file_name);
	//input_file.open("3d_file1.txt");
	int vertices,edges;
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
	//now i have read the 3d file and stored in arrays;
	//now find max_x etc

	for(i=0;i<vertices;i++){
		if(max_x<x_coord[i]) max_x=x_coord[i];
		if(min_x>x_coord[i]) min_x=x_coord[i];
		if(max_y<y_coord[i]) max_y=y_coord[i];
		if(min_y>y_coord[i]) min_y=y_coord[i];
		if(max_z<z_coord[i]) max_z=z_coord[i];
		if(min_z>z_coord[i]) min_z=z_coord[i];
	}

	float frontview_x[vertices];
	float frontview_y[vertices];
	float rightview_x[vertices];
	float rightview_y[vertices];
	float topview_x[vertices];
	float topview_y[vertices];

	float shift_right= max_y +max_x + (max_y -min_y)/10;
	float shift_up= max_z +max_x + (max_z-min_z)/10;

	for(i=0;i<vertices;i++){
		frontview_x[i]=y_coord[i];
		frontview_y[i]=z_coord[i];
		rightview_x[i]=-1*x_coord[i] + shift_right;
		rightview_y[i]= z_coord[i];
		topview_x[i]= y_coord[i];
		topview_y[i]= -1*x_coord[i]+ shift_up;
	}

	//print these values to a file that gnuplot wants

	ofstream write_to;
	write_to.open("2d.txt");
	for ( i = 0; i < edges; ++i)
	{
		write_to<< frontview_x[firstpoint[i]]<<"  ";
		write_to<<frontview_y[firstpoint[i]]<<endl;
		write_to<<frontview_x[secondpoint[i]]<<"  ";
		write_to<<frontview_y[secondpoint[i]]<<endl;
		write_to<<"\n";

	}
	for (int i = 0; i < edges; ++i)
	{
		write_to<< rightview_x[firstpoint[i]]<<"  ";
		write_to<<rightview_y[firstpoint[i]]<<endl;
		write_to<<rightview_x[secondpoint[i]]<<"  ";
		write_to<<rightview_y[secondpoint[i]]<<endl;
		write_to<<"\n";		
	}
	for (int i = 0; i < edges; ++i)
	{
		write_to<< topview_x[firstpoint[i]]<<"  ";
		write_to<<topview_y[firstpoint[i]]<<endl;
		write_to<<topview_x[secondpoint[i]]<<"  ";
		write_to<<topview_y[secondpoint[i]]<<endl;
		write_to<<"\n";				
	}


	//to fix the autoscaling
	//do this
	float fix1=max_z-min_z;
	float fix2= max_y-min_y;
	float actual_fix;
	if(fix1>fix2) actual_fix=fix1;
	else actual_fix=fix2;
	actual_fix=2*actual_fix;


	write_to<< actual_fix<<"  "<< actual_fix<<endl;
	write_to<< actual_fix<<"  "<<actual_fix<<endl;

    Gnuplot g1;
    //cout<< "will try to make a square"<<endl;
    g1<<"unset border\n";
    g1<<"unset tics\n";
    g1<<"unset key\n";
    g1 << "set terminal x11 size 800,800\n";

    //g1<<"unset autoscale\n";
    g1 << "plot '2d.txt' with linespoint lt 1 lw 4 \n";
    std::cin.get();

}

int display_3d(std::string file_name){

	using namespace std;
	std::ifstream input_file;
	input_file.open(file_name);
	//input_file.open("3d_file1.txt");
	int vertices,edges;
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

	ofstream file;
	file.open ("out.txt");
	for(i=0;i<edges;i++){
		file<< x_coord[firstpoint[i]];
		file<<" ";
		file<< y_coord[firstpoint[i]];
		file<<" ";
		file<< z_coord[firstpoint[i]];
		file<<"\n";
		file<< x_coord[secondpoint[i]];
		file<<" ";
		file<< y_coord[secondpoint[i]];
		file<<" ";
		file<< z_coord[secondpoint[i]];
		file<<"\n";
		file<<"\n";
		file<<"\n";

	}
	file.close();
	string hey;
    Gnuplot g1;
    //cout<< "will try to make a square"<<endl;
    g1<<"unset border\n";
    g1<<"unset tics\n";
    g1<<"unset key\n";
    //g1<<"unset autoscale";	
    g1 << "set terminal x11 size 800,800\n";
    //g1<< "set size ratio -1";
    //g1<<"set view equal xyz";
    //g1<<"set size square";
    g1 << "splot 'out.txt' with linespoint lt 1 lw 4 \n";
    wait_for_key();
    //cout<<"im a cow..moooo";
    return 1;
}

