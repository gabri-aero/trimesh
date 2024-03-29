#include <vector>
#include <array>
#include <iostream>
#include <set>

#ifndef _DELAUNAY_HPP_
#define _DELAUNAY_HPP_

const double eps = 1e-9;

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
    void set_index(int index);
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
    double length();
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
    bool operator!=(const Triangle& other) const;
    bool operator<(const Triangle& other) const; 
    std::array<Node, 3> get_vertices() const;
    std::array<Edge, 3> get_edges() const;
    std::array<int, 3> get_vertices_index() const;
    std::array<std::array<int, 2>, 3> get_edges_index() const;
    Coord2D circumcenter();
    Coord2D centroid();
    bool circumscribe(Node& n);    
    double get_alpha();  
    double get_area();
    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};

class Delaunay
{
    std::vector<Node> nodes;
    std::vector<Triangle> triangles{};
    Triangle super_triangle();
public:
    Delaunay();
    Delaunay(std::vector<Coord2D> points);
    Delaunay(std::vector<Triangle> triangles, std::vector<Node> nodes);
    ~Delaunay();
    std::vector<Triangle> compute();
    Triangle add_point(double x, double y);
    Triangle add_point(Coord2D p);
    Triangle add_point(Node p);
    std::vector<Node> get_nodes() const;
    std::vector<Edge> get_edges() const;
    std::vector<std::array<int, 2>> get_edges_index() const;
    std::vector<Triangle> get_triangles() const;
    std::vector<std::array<int, 3>> get_triangles_index() const;
    std::vector<std::pair<Triangle, Edge>> get_neighbors(Triangle t);
    std::vector<Triangle> refine(double alpha, double h);
    std::vector<Triangle> get_bad_triangles(double alpha);
    std::vector<Triangle> get_big_triangles(double h);
};


double dist(const Coord2D& p1, const Coord2D& p2);
Coord2D midpoint(const Coord2D& p1, const Coord2D& p2);
double slope(const Coord2D& p1, const Coord2D& p2);


#endif // _DELAUNAY_HPP_