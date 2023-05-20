#include <limits>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <array>

#include "Delaunay.hpp"


// Coord2D functions declaration
Coord2D::Coord2D() {
}

Coord2D::Coord2D(double x, double y) 
    : x{x}, y{y} {   
}

Coord2D::Coord2D(const Coord2D &coords) {
    x = coords.x;
    y = coords.y;
}

// Node constructors declaration
Node::Node() {
}

Node::Node(Coord2D coords, int i)
    : coords{coords}, i{i} {
}

Node::Node(double x, double y, int i) 
    : coords{Coord2D{x, y}}, i{i} {
}

Node::Node(const Node &node) {
    coords = node.coords;
    i = node.i;
}

Node::~Node() {

}

Coord2D Node::get_coords() const {
    return coords;
}

int Node::get_index() const {
    return i;
}

bool Triangle::circumscribe(Node& n) {
    Coord2D circum_center{circumcenter()};
    double circum_radius{dist(circum_center, data[0].get_coords())};
    double distance{dist(circum_center, n.get_coords())};

    return distance < circum_radius;    
}

// Auxiliary functions

double dist(const Coord2D& p1, const Coord2D& p2) {
    double dx{p1.x - p2.x};
    double dy{p1.y - p2.y};
    return sqrt(dx*dx + dy*dy);
}

Coord2D midpoint(const Coord2D& p1, const Coord2D& p2) {
    return Coord2D{(p1.x + p2.x)*0.5, (p1.y + p2.y)*0.5};
}

double slope(const Coord2D& p1, const Coord2D& p2) {
    return (p2.y - p1.y) / (p2.x - p1.x);
}

// Triangle class
Triangle::Triangle(std::array<Node, 3> data)
    : data{data} {
}

Triangle::Triangle(Node n1, Node n2, Node n3)
{
    data = std::array<Node, 3> {n1, n2, n3};
}


Node& Triangle::operator[](int index) {
    if (index >= 3) 
        throw std::out_of_range("Index out of range");
    return data[index];
}

Coord2D Triangle::circumcenter() {

    // Compute triangle midpoints
    Coord2D p1 = midpoint(data[0].get_coords(), data[1].get_coords());
    Coord2D p2 = midpoint(data[1].get_coords(), data[2].get_coords());
    Coord2D p3 = midpoint(data[2].get_coords(), data[0].get_coords());

    // Compute the slope of two of the heights
    double m1 = slope(p1, p3);
    double m2 = slope(p2, p3);

    // Solve for lines intersection
    double x = ( (p2.y - m2*p2.x) + (p1.y - m1*p1.x) ) / (m1 - m2);
    double y = m1 * (x - p1.x) + p1.y;

    return Coord2D{x, y};
}

// Delaunay declarations
// Constructor only add nodes
Delaunay::Delaunay(std::vector<Coord2D> points) {
    int i{};
    for(Coord2D &point: points) {
        nodes.emplace_back(point, i++);
    }
}

Delaunay::~Delaunay() {
}

Triangle Delaunay::super_triangle() {

    double min_x{std::numeric_limits<double>::infinity()};
    double min_y{std::numeric_limits<double>::infinity()};
    double max_x{-std::numeric_limits<double>::infinity()};
    double max_y{-std::numeric_limits<double>::infinity()};

    double x, y;

    for(Node &node: nodes) {
        x = node.get_coords().x;
        y = node.get_coords().y;

        max_x = (x > max_x) ? x : max_x;
        max_y = (y > max_y) ? y : max_y;
        min_x = (x < min_x) ? x : min_x;
        min_y = (y < min_y) ? y : min_y;
    }

    double dx = max_x - min_x;
    double dy = max_y - min_y;
    double delta = dx + dy;

    max_x += delta;
    min_x -= delta;
    max_y += delta;
    min_y -= delta;

    Node n1{min_x, min_y, -3};
    Node n2{max_x, min_y, -2};
    Node n3{max_x, max_y, -1};

    Triangle outer_nodes{n1, n2, n3};

    return outer_nodes;
}


std::vector<Triangle> Delaunay::compute() {
    // Empty triangles for clean re-computation
    triangles.clear();

    // Compute super triangle
    triangles.push_back(super_triangle());

    return triangles;
}