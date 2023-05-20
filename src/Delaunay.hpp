#include <vector>
#include <array>

#ifndef _DELAUNAY_HPP_
#define _DELAUNAY_HPP_


class Coord2D {
public:
    double x;
    double y;
    Coord2D();
    Coord2D(double x, double y);
    Coord2D(const Coord2D &coords);
    bool operator==(const Coord2D& other) const;
};


class Node
{
    Coord2D coords;
    int i;
public:
    Node();
    Node(Coord2D coords, int i);
    Node(double x, double y, int i);
    Node(const Node &node);
    ~Node();
    bool operator==(const Node& other) const;
    bool operator<(const Node& other) const;
    Coord2D get_coords() const;
    int get_index() const;
};


class Triangle
{
    std::array<Node, 3> data;
public:
    Triangle(std::array<Node, 3>);
    Triangle(Node, Node, Node);
    Node& operator[](int index);
    bool operator==(const Triangle& other) const;
    std::array<Node, 3> get_vertices() const;
    Coord2D circumcenter();
    bool circumscribe(Node& n);
};


class Delaunay
{
    std::vector<Node> nodes;
    std::vector<Triangle> triangles{};
    Triangle super_triangle();
public:
    Delaunay(std::vector<Coord2D> points);
    ~Delaunay();
    std::vector<Triangle> compute();
};


double dist(const Coord2D& p1, const Coord2D& p2);
Coord2D midpoint(const Coord2D& p1, const Coord2D& p2);
double slope(const Coord2D& p1, const Coord2D& p2);


#endif // _DELAUNAY_HPP_