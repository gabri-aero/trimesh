#include <vector>

#ifndef _DELAUNAY_HPP_
#define _DELAUNAY_HPP_


class Coord2D {
public:
    double x;
    double y;
    Coord2D();
    Coord2D(double x, double y);
    Coord2D(const Coord2D &coords);
};


class Node
{
    Coord2D coords;
    int i;
    std::vector<int> neighbors;
public:
    Node();
    Node(Coord2D coords, int i);
    Node(double x, double y, int i);
    Node(const Node &node);
    ~Node();
    Coord2D get_coords();
};



class Delaunay
{
    std::vector<Node> nodes{};
public:
    Delaunay(std::vector<Coord2D> points);
    ~Delaunay();
    std::vector<Node> get_nodes();
    void compute();
    std::vector<Node> super_triangle();
};



#endif // _DELAUNAY_HPP_