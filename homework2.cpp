#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <math.h>


void printValues(std::string title, std::vector<double> array)
{
    std::cout << "\n" << title << std::endl;

    for(auto& value : array)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

class Point
{    

public:
    double x, y;

    Point()
    {
        x = 0; y = 0;
    }

    Point(double X, double Y)
    {
        x = X; y = Y;
    }

    std::string toString()
    {
        std::string out = "p( ";
        out.append(std::to_string(x));
        out.append(", ");
        out.append(std::to_string(y));
        out.append(" )");
        return out;
    }

    bool operator==(Point& point)
    {
        return point.x == x && point.y == y;
    }
        
};

class Vector
{

public:
    double x, y;

    Vector()
    {
        x = 0; y = 0;
    }

    Vector(Point p)
    {
        x = p.x; y = p.y;
    }

    Vector(Point start, Point end)
    {
        x = end.x - start.x;
        y = end.y - start.y;
    }

};

double dot(Vector v1, Vector v2)
{
    double x = v1.x * v2.x;
    double y = v1.y * v2.y;

    return x + y;
}

double sqrLen(Vector v)
{
    double x = pow(v.x, 2);
    double y = pow(v.y, 2);

    return x + y;
}

double len(Vector v)
{
    double sqred_len = sqrLen(v);
    return sqrt(sqred_len);
}

class Angle
{

public:
    Angle(Vector v)
    {
        _v1 = v;
        _v2 = _u;
    }
    
    Angle(Vector v1, Vector v2)
    {
        _v1 = v1;
        _v2 = v2;
    }

    double value()
    {
        return calcAngle(_v1, _v2);
    }

    double orientedValue()
    {
        double angleV1 = _v1.y >= 0 ? calcAngle(_u, _v1) : 2 * 3.1415 - calcAngle(_u, _v1);
        double angleV2 = _v2.y >= 0 ? calcAngle(_u, _v2) : 2 * 3.1415 - calcAngle(_u, _v2);

        return angleV1 - angleV2;
    }

    double unitarySquare()
    {
        double angle1 = pseudoAngleUnitarySquare(_v1);
        double angle2 = pseudoAngleUnitarySquare(_v2);

        return angle1 - angle2;
    }

private:
    Vector _u = Vector( Point(1.0, 0.0) );
    Vector _v1;
    Vector _v2;

    double pseudoAngleUnitarySquare(Vector v)
    {
        if(v.y >= 0)
        {
            if(v.x >= 0)
            {
                if(v.x >= v.y)
                {
                    return v.y / v.x;
                }
                else
                {
                    return 2 - v.x / v.y;
                }
            }
            else if(-v.x <= v.y)
            {
                return 2 + (-v.x) / v.y;
            }
            else
            {
                return 4 - v.y / (-v.x);
            }
        }
        else if(v.x < 0)
        {
            if(-v.x >= -v.y)
            {
                return 4 + (-v.y) / (-v.x);
            }
            else
            {
                return 6 - (-v.x) / (-v.y);
            }
        }
        else if(v.x <= -v.y)
        {
            return 6 + v.x / (-v.y);
        }
        else
        {
            return 8 - (-v.y) / v.x;
        }
    }

    double calcAngle(Vector v1, Vector v2)
    {
        double dotRes = dot(v1, v2);
        double lenV1 = len(v1);
        double lenV2 = len(v2);

        double cos = dotRes / ( lenV1 * lenV2 );
        double angle = acos( cos );

        return angle;
    }
};

std::vector<double> merge(std::vector<double> left, std::vector<double> right)
{
	int i = 0;
    int j = 0;

    int left_len = left.size();
    int right_len = right.size();

	std::vector<double> merged;

	while(i < left_len && j < right_len)
	{
		if(left[i] < right[j]) {
			merged.push_back(left[i]);
            i++;
		} else {
			merged.push_back(right[j]);
            j++;
		}
	}

	while(i < left_len) {
		merged.push_back(left[i]);
        i++;
	}

	while(j < right_len) {
		merged.push_back(right[j]);
        j++;
	}

	return merged;
}

std::vector<double> mergeSort(std::vector<double> array)
{
    int len = array.size();

	if(len <= 1)
	{
		return array;
	}

	int pivot = len/2;

    std::vector<double> leftSlice(array.begin(), array.begin() + pivot);
	std::vector<double> rightSlice(array.begin() + pivot, array.end());
    
	std::vector<double> leftArray = mergeSort(leftSlice);
	std::vector<double> rightArray = mergeSort(rightSlice);
	return merge(leftArray, rightArray);
}

int main(int argc, char const *argv[])
{
    std::cout << "Homework 2: Angles, Primitives and Point Polygon Problems" << std::endl;
    bool showDetails = argc >= 2 && std::string(argv[1]) == "detailed";

    Vector a = Vector( Point(0, 5) );
    Vector b = Vector( Point(5, 0) );

    Angle angleAB = Angle(a, b);
    std::cout << "\nUnitary square angle a, b:\t" << angleAB.unitarySquare() << std::endl;

    Vector c = Vector( Point(2, 5) );
    Vector d = Vector( Point(-5, 0) );

    Angle angleBC = Angle(b, c);
    Angle angleCD = Angle(c, d);
    Angle angleAD = Angle(a, d);

    std::vector<double> angles = { angleAB.value(), angleBC.value(), angleCD.value(), angleAD.value() };
    std::vector<double> orientedAngles = { angleAB.orientedValue(), angleBC.orientedValue(), angleCD.orientedValue(), angleAD.orientedValue() };
    std::vector<double> pseudoAngles = { angleAB.unitarySquare(), angleBC.unitarySquare(), angleCD.unitarySquare(), angleAD.unitarySquare() };

    printValues( "\nOrdering angles", mergeSort(angles) );
    printValues( "\nOrdering oriented angles", mergeSort(orientedAngles) );
    printValues( "\nOrdering pseudo angles", mergeSort(pseudoAngles) );
}