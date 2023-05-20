#include <limits>
#include <vector>

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
    neighbors = node.neighbors;
}

Node::~Node() {

}

Coord2D Node::get_coords() {
    return coords;
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

std::vector<Node> Delaunay::get_nodes() {
    return nodes;
}

std::vector<Node> Delaunay::compute_initial_nodes() {

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

    std::vector<Node> outer_nodes{n1, n2, n3};

    return outer_nodes;
}