#include <vector>
#include <array>
#include <iostream>
#include <set>

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
    Node(Coord2D coords, int i=0);
    Node(double x, double y, int i=0);
    Node(const Node &node);
    ~Node();
    bool operator==(const Node& other) const;
    bool operator<(const Node& other) const;
    double get_x() const;
    double get_y() const;
    Coord2D get_coords() const;
    int get_index() const;
};


class Edge
{
    std::array<Node, 2> data;
public:
    Edge();
    Edge(Node, Node);
    Edge(const Edge &edge);
    bool operator==(const Edge& other) const;
    bool operator<(const Edge& other) const;
    std::array<Node, 2> get_vertices() const;
    std::array<int, 2> get_vertices_index() const;
    friend std::ostream& operator<<(std::ostream& os, const Edge& e);
};


class Triangle
{
    std::array<Node, 3> data;
    std::array<Edge, 3> edges;
public:
    Triangle(Node, Node, Node);
    Node& operator[](int index);
    bool operator==(const Triangle& other) const;
    bool operator<(const Triangle& other) const; 
    std::array<Node, 3> get_vertices() const;
    std::array<Edge, 3> get_edges() const;
    std::array<int, 3> get_vertices_index() const;
    std::array<std::array<int, 2>, 3> get_edges_index() const;
    Coord2D circumcenter();
    bool circumscribe(Node& n);    
    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
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
    std::vector<Node> get_nodes() const;
    std::vector<Edge> get_edges() const;
    std::vector<std::array<int, 2>> get_edges_index() const;
    std::vector<Triangle> get_triangles() const;
    std::vector<std::array<int, 3>> get_triangles_index() const;
};


double dist(const Coord2D& p1, const Coord2D& p2);
Coord2D midpoint(const Coord2D& p1, const Coord2D& p2);
double slope(const Coord2D& p1, const Coord2D& p2);


#endif // _DELAUNAY_HPP_