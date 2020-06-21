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
		if(left[i].y < right[j].y || (left[i].y == right[j].y && left[i].x < right[j].x)) {
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

std::vector<Point> grahamHull(std::vector<Point> points)
{
    std::vector<Point> sortedPointsByAxis = mergeSort(points);

    Point basePoint = sortedPointsByAxis[0];

    std::vector<Point> hull = {basePoint};

    sortedPointsByAxis.erase(sortedPointsByAxis.begin());
    std::vector<Point> sortedPoints = mergeSortAngular(sortedPointsByAxis, basePoint);
    sortedPoints.insert(sortedPoints.begin(), basePoint);
    
    hull.reserve(sortedPoints.size());

    int index = 0;
    int ignoring = 0;

    do
    {
        Point current = sortedPoints[index];
        Point next = sortedPoints[index + ignoring + 1];
        Point nNext = sortedPoints[index + ignoring + 2];

        Triangle triangle = Triangle(current, next, nNext);

        if(isCCW(triangle))
        {
            hull.push_back(next);
            index += ignoring + 1;
            ignoring = 0;
        }
        else
        {
            ignoring++;
        }
    }
    while(index + ignoring + 2 <= sortedPoints.size());

    return hull;
}

bool contains(std::vector<Point> points, Point point)
{
    for(auto& somePoint : points)
    {
        if(somePoint == point)
        {
            return true;
        }
    }

    return false;
}

std::vector<Point> jarvisHull(std::vector<Point> points)
{
    std::vector<Point> sortedPoints = mergeSort(points);

    Point basePoint = sortedPoints[0];

    std::vector<Point> hull = { basePoint };

    Vector rotationAxis = Vector( basePoint, Point(basePoint.x + 1, basePoint.y) );

    Point currentPoint = basePoint;

    do
    {
        double minAngle = INFINITY;
        int selectedIndex = -1;

        for(int i = 0; i < sortedPoints.size(); i++)
        {
            if(currentPoint != sortedPoints[i] && ( !contains(hull, sortedPoints[i]) || sortedPoints[i] == basePoint))
            {
                Angle currentAngle = Angle( Vector( currentPoint, sortedPoints[i] ), rotationAxis );
                double pseudoValue = currentAngle.unitarySquare();
                
                if(pseudoValue >= 0 && pseudoValue < minAngle)
                {
                    minAngle = pseudoValue;
                    selectedIndex = i;
                }
                else if(pseudoValue == minAngle && currentPoint.x < sortedPoints[i].x)
                {
                    selectedIndex = i;
                }
            }
        }

        if(selectedIndex >= 0)
        {
            if(sortedPoints[selectedIndex] != basePoint)
            {
                hull.push_back(sortedPoints[selectedIndex]);

                rotationAxis = Vector( currentPoint, sortedPoints[selectedIndex] );
            }
            
            currentPoint = sortedPoints[selectedIndex];
        }
        else
        {
            throw "Unable to execute jarvis hull for this set of points. This is probably a bug in code.";
        }
    }
    while(currentPoint != basePoint);

    return hull;
}

bool isPointLeft(Point point, Edge edge)
{
    Vector pointVec = Vector(edge.start, point);
    Vector edgeVec = Vector(edge.start, edge.end);

    Angle angle = Angle(pointVec, edgeVec);
    
    return angle.unitarySquare() >= 0;
}

std::vector<Point> splitLeft(std::vector<Point> points, Edge edge)
{
    std::vector<Point> leftPoints = {};

    for(auto& point : points)
    {
        if(isPointLeft(point, edge))
        {
            leftPoints.push_back(point);
        }
    }

    return leftPoints;
}

std::vector<Point> splitRight(std::vector<Point> points, Edge edge)
{
    std::vector<Point> rightPoints = {};

    for(auto& point : points)
    {
        if(!isPointLeft(point, edge))
        {
            rightPoints.push_back(point);
        }
    }

    return rightPoints;
}

void quickHullStep(std::vector<Point>* hull, std::vector<Point> points, std::vector<Edge>* freeEdges)
{
    if(freeEdges->size() == 0)
    {
        return;
    }

    Edge edge = freeEdges->at(freeEdges->size() - 1);
    freeEdges->pop_back();

    double area = -INFINITY;
    int selectedIndex = -1;

    for(int i=0; i < points.size(); i++)
    {
        Triangle candidate = Triangle(edge.start, edge.end, points[i]);
        double candidateArea = orientedArea(candidate);

        if(candidateArea > area)
        {
            area = candidateArea;
            selectedIndex = i;
        }
    }
    std::cout << "selectedIndex " << selectedIndex << std::endl;
    if(selectedIndex >= 0)
    {
        if(!contains(*hull, points[selectedIndex]))
        {
            hull->push_back(points[selectedIndex]);
            freeEdges->push_back( Edge(edge.start, points[selectedIndex]) );
            freeEdges->push_back( Edge(points[selectedIndex], edge.end) );
        }
    }
    else
    {
        throw "Unable to execute quick hull for this set of points. This is probably a bug in code.";
    }

    std::vector<Point> left = splitLeft(points, edge);
	std::vector<Point> right = splitRight(points, edge);

    quickHullStep(hull, left, freeEdges);
    quickHullStep(hull, right, freeEdges);
}

std::vector<Point> quickHull(std::vector<Point> points)
{
    std::vector<Point> hull = {};
    hull.reserve(points.size());
    std::vector<Edge> freeEdges = {};
    freeEdges.reserve(points.size());

    std::vector<Point> sortedPoints = mergeSort(points);

    Point lessExtreme = sortedPoints[0];
    Point greaterExtreme = sortedPoints[sortedPoints.size() - 1];

    sortedPoints.erase(sortedPoints.begin());
    sortedPoints.pop_back();

    Edge middleEdge = Edge(lessExtreme, greaterExtreme);
    freeEdges.push_back(middleEdge);
    
    std::vector<Point> left = splitLeft(points, middleEdge);
	std::vector<Point> right = splitRight(points, middleEdge);

    quickHullStep(&hull, left, &freeEdges);
    quickHullStep(&hull, right, &freeEdges);

    return hull;
}

int main(int argc, char const *argv[])
{
    std::cout << "Homework 3: Convex hulls" << std::endl;
    bool showDetails = argc >= 2 && std::string(argv[1]) == "detailed";

    std::vector<Point> points = { Point(1,0), Point(3,0), Point(5,0), Point(6,1), Point(1,3), Point(0,1), Point(4,1.5), Point(1.5, 2.2), Point(3.5,3) };

    std::vector<Point> graham_hull = grahamHull(points);
    printPoints("Graham Hull of ", points);
    printPoints("is ", graham_hull);

    try
    {
        std::vector<Point> jarvis_hull = jarvisHull(points);
        printPoints("Jarvis Hull of ", points);
        printPoints("is ", jarvis_hull);
    }
    catch(char const* exception)
    {
        std::cout << "ERROR!" << std::endl;
        std::cout << exception << std::endl;
    }
}