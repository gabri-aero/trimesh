#include <limits>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <array>
#include <set>

#include "Delaunay.hpp"


// Coord2D constructors
Coord2D::Coord2D() {
}

Coord2D::Coord2D(double x, double y) 
    : x{x}, y{y} {   
}

Coord2D::Coord2D(const Coord2D &coords) {
    x = coords.x;
    y = coords.y;
}

bool Coord2D::operator==(const Coord2D& other) const {
    return x == other.x && y == other.y;
}

// Node constructors
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

bool Node::operator==(const Node& other) const {
    return coords == other.coords && i == other.i;
}

bool Node::operator<(const Node& other) const {
    return i < other.i;
}

// Node getters
Coord2D Node::get_coords() const {
    return coords;
}

int Node::get_index() const {
    return i;
}

// Auxiliary functions for 2D

// Distance between two points
double dist(const Coord2D& p1, const Coord2D& p2) {
    double dx{p1.x - p2.x};
    double dy{p1.y - p2.y};
    return sqrt(dx*dx + dy*dy);
}

// Midpoint between two points
Coord2D midpoint(const Coord2D& p1, const Coord2D& p2) {
    return Coord2D{(p1.x + p2.x)*0.5, (p1.y + p2.y)*0.5};
}

// Slope of a line joining two points
double slope(const Coord2D& p1, const Coord2D& p2) {
    return (p2.y - p1.y) / (p2.x - p1.x);
}

// Triangle constructors
Triangle::Triangle(std::array<Node, 3> data)
    : data{data} {
}

Triangle::Triangle(Node n1, Node n2, Node n3)
{
    data = std::array<Node, 3> {n1, n2, n3};
}

// Define triangle subscript operator
Node& Triangle::operator[](int index) {
    if (index >= 3) 
        throw std::out_of_range("Index out of range");
    return data[index];
}

bool Triangle::operator==(const Triangle& other) const {
    return data[0] == other.data[0] && data[1] == other.data[1] && data[2] == other.data[2];
}

// Getter for triangle vertices
std::array<Node, 3> Triangle::get_vertices() const {
    return data;
}

// Compute triangle circumcenter based on intersection of two heights
Coord2D Triangle::circumcenter() {
    Coord2D v1 = data[0].get_coords();
    Coord2D v2 = data[1].get_coords();
    Coord2D v3 = data[2].get_coords();

    // Compute triangle midpoints
    Coord2D p1 = midpoint(v2, v3);
    Coord2D p2 = midpoint(v3, v1);
    Coord2D p3 = midpoint(v1, v2);

    // Compute the slope of two of the heights (perpendicular to edge slope)
    double m1 = -1 / slope(v2, v3);
    double m2 = -1 / slope(v3, v1);

    // Solve for lines intersection
    double x = ( (p2.y - m2*p2.x) + (p1.y - m1*p1.x) ) / (m1 - m2);
    double y = m1 * (x - p1.x) + p1.y;

    return Coord2D{x, y};
}

// Check if node is inside triangle circumcircle
bool Triangle::circumscribe(Node& n) {

    // Compute circumcenter
    Coord2D circum_center{circumcenter()};

    // Compute circum radiues
    double circum_radius{dist(circum_center, data[0].get_coords())};

    // Get distance from node to circumcenter
    double distance{dist(circum_center, n.get_coords())};

    // Node inside condition
    return distance < circum_radius;    
}

// Delaunay constructors
Delaunay::Delaunay(std::vector<Coord2D> points) {
    int i{};
    for(Coord2D &point: points) {
        nodes.emplace_back(point, i++);
    }
}

Delaunay::~Delaunay() {
}

// Super triangle computation
Triangle Delaunay::super_triangle() {
    // Set dummy limits
    double min_x{std::numeric_limits<double>::infinity()};
    double min_y{std::numeric_limits<double>::infinity()};
    double max_x{-std::numeric_limits<double>::infinity()};
    double max_y{-std::numeric_limits<double>::infinity()};

    double x, y;

    // Compute extreme values in x and y
    for(Node &node: nodes) {
        x = node.get_coords().x;
        y = node.get_coords().y;

        max_x = (x > max_x) ? x : max_x;
        max_y = (y > max_y) ? y : max_y;
        min_x = (x < min_x) ? x : min_x;
        min_y = (y < min_y) ? y : min_y;
    }

    // Set a delta with extreme values and outer rect-supertriangle
    double dx = max_x - min_x;
    double dy = max_y - min_y;
    double delta = dx + dy;

    // Compute values of rect-supertriangle
    max_x += delta;
    min_x -= delta;
    max_y += delta;
    min_y -= delta;

    // Create supertriangle nodes
    Node n1{min_x, min_y, -3};
    Node n2{max_x, min_y, -2};
    Node n3{max_x, max_y, -1};

    Triangle outer_nodes{n1, n2, n3};

    return outer_nodes;
}

// Run algorithm
std::vector<Triangle> Delaunay::compute() {

    // Empty triangles for clean re-computation
    triangles.clear();

    // Compute super triangle
    triangles.push_back(super_triangle());

    // Instantiate removed triangles vertices
    std::set<Node> vertices{};

    // Loop over all nodes
    for(Node& node: nodes) {
        // Loop over all triangles
        for(Triangle& triangle: triangles) {
            if(triangle.circumscribe(node)) {
                // Retrieve vertices and add to removed ones
                auto v = triangle.get_vertices();
                vertices.insert(v.begin(), v.end());
                // Remove triangle because it is no longer Delaunay
                triangles.erase(std::remove(triangles.begin(), triangles.end(), triangle), triangles.end());
            }
        }
        // Connect to retrieved vertices
        for (auto it1 = vertices.begin(); it1 != vertices.end(); it1++) {
            for (auto it2 = std::next(it1); it2 != vertices.end(); it2++) {
                Node n1 = *it1;
                Node n2 = *it2;
                triangles.push_back(Triangle{node, n1, n2});
            }
        }
    }

    return triangles;
}