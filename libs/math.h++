// just make it a fucking math library ong bro
#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

double Sqrt(int Number, int Root)
{
    int j;
    double i,k=1;
    double incre = 0.001; 
	// 0.01 starting value it is the accuurate value upto 2 decimal places choose 0.01 or 0.001 or so on
	// the more the incre is lower the high the accuracy of root !
 
    for(i=1; i<=Number; i+=incre){ 
        for(j=0;j<Root;j++){ 
            k*=i;
        }
        if(k>Number){ 
            return (i-incre);
            break;
        }
        else
            k=1; 
    }
}

int poweroftwo(int num)
{

}

int GetMagnitude2D(int x1, int y1, int x2, int y2) 
{
    return Sqrt(x2-x1)
}

#endif