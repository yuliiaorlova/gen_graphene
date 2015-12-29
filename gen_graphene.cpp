

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef struct
{
    double x, y;
} atom_position;


int max_number_of_atoms;
int number_of_atoms;

int nx,  ny;
double d_CC;
string file_name;

atom_position *positions = NULL;
atom_position origin;
atom_position atomic_basis[4];



double ax, by;

int main(int argc, char *argv[])
{
    
    
 
    if (argc!=5){
        std::cout<<"error: wrong invocation!"<<endl;
        std::cout<<"try with:"<<endl;
        std::cout<<"gen_graphene <int nx>, <int ny>, <float d_CC>, <string file_name>"<<endl;
        return 0;
    }
    
    
    
    nx=atoi(argv[1]);
    ny=atoi(argv[2]);
    d_CC=atof(argv[3]);
    file_name=argv[4];
    
    cout<<"nx="<<nx<<endl;
    cout<<"ny="<<ny<<endl;
    cout<<"d_CC="<<d_CC<<endl;
    cout<<"file_name="<<file_name<<endl;
    
    max_number_of_atoms=nx*ny*4;
    ax=3.0*d_CC;
    by=sqrt(3.0)*d_CC;
    
    atomic_basis[0].x=0.5*d_CC;
    atomic_basis[0].y=0.5*sqrt(3.0)*d_CC;
    
    atomic_basis[1].x=d_CC;
    atomic_basis[1].y=0.0;

    atomic_basis[2].x=2.0*d_CC;
    atomic_basis[2].y=0.0;

    atomic_basis[3].x=2.5*d_CC;
    atomic_basis[3].y=0.5*sqrt(3.0)*d_CC;

    
    
    positions = new atom_position[max_number_of_atoms];

    number_of_atoms=0;
    
    int i, j, k;
    
    for (i=0; i<nx; i++)
    {
        for(j=0; j<ny; j++)
        {
            origin.x=i*ax;
            origin.y=j*by;
            
            for(k=0; k<4; k++)
            {
                positions[number_of_atoms].x=origin.x+atomic_basis[k].x;
                positions[number_of_atoms].y=origin.y+atomic_basis[k].y;
                number_of_atoms++;

            }
        }
    }
    
    //put data in file
    
    ofstream output_file;
    
    output_file.open(file_name.c_str());
    if(output_file.is_open()==0)
    {
        cout<<"error: could not create output file!"<<endl;
        exit(1);
    }
    
    output_file<<number_of_atoms<<endl;
    output_file<<"graphene, d_CC="<< d_CC << ", nx="<<nx << ", ny="<<ny<<endl;
    
    for (i=0; i<number_of_atoms; i++){
        output_file<<"C"<< " " <<positions[i].x<< " "<<positions[i].y<< " "<< "0.0"<<endl;
    }
    /*
    for (i=0; i<number_of_atoms; i++){
        output_file<<i+1<< " " <<1<<" "<<positions[i].x<< " "<<positions[i].y<< " "<< "0.0"<<endl;
    }
    */
    output_file.close();
    
    delete [] positions; //clean memory in the end of the program

    return 0;
}
