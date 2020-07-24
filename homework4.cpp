#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <fstream>
#include <map>


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

    std::string toFile()
    {
        std::string out = "p ";
        out.append(std::to_string(x));
        out.append(" ");
        out.append(std::to_string(y));
        // out.append("\n");
        return out;
    }

    bool operator==(Point& point)
    {
        return point.x == x && point.y == y;
    }

    bool operator!=(Point& point)
    {
        return point.x != x || point.y != y;
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

Vector sub(Point p1, Point p2)
{
    return Vector(p2, p1);
}

class Triangle
{
    public:
        Point p1, p2, p3;
    
        Triangle(Point P1, Point P2, Point P3)
        {
            p1 = P1;
            p2 = P2;
            p3 = P3;
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

double crossR2(Vector v1, Vector v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

double orientedArea(Triangle triangle)
{
    double crossP1P2 = crossR2( Vector(triangle.p1), Vector(triangle.p2) );
    double crossP2P3 = crossR2( Vector(triangle.p2), Vector(triangle.p3) );
    double crossP3P1 = crossR2( Vector(triangle.p3), Vector(triangle.p1) );
    
    double double_area = crossP1P2 + crossP2P3 + crossP3P1;

    return double_area / 2;
}

double isCCW(Triangle triangle)
{
    double area = orientedArea(triangle);
    return area > 0;
}

void toCW(Triangle triangle)
{
    if(isCCW(triangle))
    {
        Point p1 = triangle.p1;
        triangle.p1 = triangle.p2;
        triangle.p2 = p1;
    }
}

class Edge
{

public:
    Point start, end;

    Edge()
    {
    }

    Edge(Point Start, Point End)
    {
        start = Start;
        end = End;
    }

    Vector toVector()
    {
        return Vector(start, end);
    }

    std::string toString()
    {
        std::string out = "e[ ";
        out.append(start.toString());
        out.append(" ");
        out.append(end.toString());
        out.append(" ]\n");
        return out;
    }

    bool operator!=(Edge& edge)
    {
        return start != edge.start || end != edge.end;
    }

    bool operator==(Edge& edge)
    {
        return start == edge.start && end == edge.end;
    }
};

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

std::vector<Point> merge(std::vector<Point> left, std::vector<Point> right)
{
	int i = 0;
    int j = 0;

    int left_len = left.size();
    int right_len = right.size();

	std::vector<Point> merged;

	while(i < left_len && j < right_len)
	{
		if(left[i].x < right[j].x || (left[i].x == right[j].x && left[i].y < right[j].y)) {
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

std::vector<Point> mergeSort(std::vector<Point> array)
{
    int len = array.size();

	if(len <= 1)
	{
		return array;
	}

	int pivot = len/2;

    std::vector<Point> leftSlice(array.begin(), array.begin() + pivot);
	std::vector<Point> rightSlice(array.begin() + pivot, array.end());
    
	std::vector<Point> leftArray = mergeSort(leftSlice);
	std::vector<Point> rightArray = mergeSort(rightSlice);

    return merge(leftArray, rightArray);
}

std::vector<Point> mergeAngular(std::vector<Point> left, std::vector<Point> right, Point base)
{
	int i = 0;
    int j = 0;

    int left_len = left.size();
    int right_len = right.size();

	std::vector<Point> merged;

	while(i < left_len && j < right_len)
	{
        Angle leftAngle = Angle( Vector( base, left[i] ) );
        Angle rightAngle = Angle( Vector( base, right[j] ) );

        double squareLeft = leftAngle.unitarySquare();
        double squareRight = rightAngle.unitarySquare();

		if(squareLeft < squareRight || (squareLeft == squareRight && left[i].x < right[j].x)) {
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

std::vector<Point> mergeSortAngular(std::vector<Point> array, Point base)
{
    int len = array.size();

	if(len <= 1)
	{
		return array;
	}

	int pivot = len/2;

    std::vector<Point> leftSlice(array.begin(), array.begin() + pivot);
	std::vector<Point> rightSlice(array.begin() + pivot, array.end());
    
	std::vector<Point> leftArray = mergeSortAngular(leftSlice, base);
	std::vector<Point> rightArray = mergeSortAngular(rightSlice, base);

    return mergeAngular(leftArray, rightArray, base);
}

void printPoints(std::string title, std::vector<Point> points)
{
    std::cout << "\n" << title << std::endl;

    for(auto& point : points)
    {
        std::cout << point.toString() << std::endl;
    }
    std::cout << std::endl;
}

bool intersect(Edge e1, Edge e2)
{
    Vector s1_base = e1.toVector();
    Vector s1_lower = Vector(e1.start, e2.start);
    Vector s1_upper = Vector(e1.start, e2.end);

    double s1_base_lower = crossR2(s1_base, s1_lower);
    double s1_base_upper = crossR2(s1_base, s1_upper);

    Vector s2_base = e2.toVector();
    Vector s2_lower = Vector(e2.start, e1.start);
    Vector s2_upper = Vector(e2.start, e1.end);

    double s2_base_lower = crossR2(s2_base, s2_lower);
    double s2_base_upper = crossR2(s2_base, s2_upper);

    bool s1_ok = s1_base_lower * s1_base_upper < 0;
    bool s2_ok = s2_base_lower * s2_base_upper < 0;

    return s1_ok && s2_ok;
}

bool containsEdge(std::vector<Edge> edges, Edge edge)
{
    for(auto& someEdge : edges)
    {
        if(edge == someEdge) return true;
    }

    return false;
}

std::vector<Triangle> scanTriangulation(std::vector<Point> points)
{
    if(points.size() < 3) throw "Invalid number of points";

    std::vector<Point> sortedPoints = mergeSort(points);
    
    std::vector<Triangle> triangulation = {};

    std::vector<Edge> edges = {};
    edges.reserve(3 * points.size());

    edges.push_back(Edge(sortedPoints[0], sortedPoints[1]));
    
    sortedPoints.erase(sortedPoints.begin());
    sortedPoints.erase(sortedPoints.begin());

    //TODO: Conferir por que isto aqui é O(n^3)
    for(auto& point : sortedPoints)
    {
        std::vector<Edge> candidatesEdges = {};

        for(auto& edge : edges)
        {
            Edge e1 = Edge(point, edge.start);
            Edge e2 = Edge(point, edge.end);

            if(!containsEdge(candidatesEdges, e1)) candidatesEdges.push_back(e1);
            if(!containsEdge(candidatesEdges, e2)) candidatesEdges.push_back(e2);
        }

        for(auto& candidateEdge : candidatesEdges)
        {
            bool isValid = true;

            for(auto& edge : edges)
            {
                if(candidateEdge != edge && intersect(candidateEdge, edge)) 
                {
                    isValid = false;
                    break;
                }
            }

            if(isValid)
            {
                edges.push_back(candidateEdge);
            }
        }

        Edge lastEdge = edges[edges.size() - 1];
        Edge prelastEdge = edges[edges.size() - 2];
        
        Triangle newTriangle = Triangle(prelastEdge.end, lastEdge.end, point);
        toCW(newTriangle);

        triangulation.push_back(newTriangle);
    }

    return triangulation;
}

std::vector<double> baricentricCoordnates(Point point, Triangle triangle)
{
    double triangle_area = orientedArea(triangle);

    Triangle t1 = Triangle(point, triangle.p2, triangle.p3);
    double delta1 = orientedArea(t1) / triangle_area;
    
    Triangle t2 = Triangle(triangle.p1, point, triangle.p3);
    double delta2 = orientedArea(t2) / triangle_area;

    Triangle t3 = Triangle(triangle.p1, triangle.p2, point);
    double delta3 = orientedArea(t3) / triangle_area;

    return { delta1, delta2, delta3 };
}

bool isInside(std::vector<Point> points, Point point)
{
    std::vector<Triangle> triangulation = scanTriangulation(points);

    for(auto& triangle : triangulation)
    {
        std::vector<double> deltas = baricentricCoordnates(point, triangle);

        if(deltas[0] > 0 && deltas[1] > 0 && deltas[2] > 0)
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char const *argv[])
{
    std::vector<Point> points = { Point(1,3), Point(2,5), Point(3,2), Point(4,5), Point(5,3) };
    Point p = Point(2,3);

    std::cout << "Question 1" << std::endl;
    printPoints("Points:", points);
    std::cout << "Is point " << p.toString() << " inside?" << std::endl;
    std::cout << (isInside(points, p) ? "Yes!" : "No...") << std::endl;
    // std::ofstream q1Out;
    // q1Out.open ("homework4Outputs/question1.tri");

    // std::vector<Triangle> triangulation = scanTriangulation(points);

    // for(auto& point : points)
    // {
    //     q1Out << point.toFile() << "\n";
    // }

    // for(auto& triangle : triangulation)
    // {
    //     int p1Index = -1;
    //     int p2Index = -1;
    //     int p3Index = -1;

    //     for(int i=0; i < points.size(); i++)
    //     {
    //         if(triangle.p1 == points[i]) p1Index = i;
    //         if(triangle.p2 == points[i]) p2Index = i;
    //         if(triangle.p3 == points[i]) p3Index = i;
    //     }

    //     q1Out << "t " << p1Index << " " << p2Index << " " << p3Index << "\n";
    // }

    // q1Out.close();
}