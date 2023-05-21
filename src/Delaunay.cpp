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

// Edge constructors
Edge::Edge() {
}

Edge::Edge(Node n1, Node n2)
{
    data = std::array<Node, 2> {n1, n2};
    std::sort(data.begin(), data.end());
}

Edge::Edge(const Edge &edge) {
    data = edge.data;
}

bool Edge::operator==(const Edge& other) const {
    return data[0] == other.data[0] && data[1] == other.data[1];
}

bool Edge::operator<(const Edge& other) const {
    if(data[0] == other.data[0]) {
        return data[1] < other.data[1];
    } else {
        return data[0] < other.data[0];
    }
}

std::ostream& operator<<(std::ostream& os, const Edge& t) {
    os << "[" 
    << t.data[0].get_index() << " "
    << t.data[1].get_index() << "]";
    return os;
}

std::array<Node, 2> Edge::get_vertices() const {
    return data;
}

std::array<int, 2> Edge::get_vertices_index() const {
    return std::array<int, 2>{data[0].get_index(), data[1].get_index()};
}

// Triangle constructors
Triangle::Triangle(Node n1, Node n2, Node n3)
{
    data = std::array<Node, 3> {n1, n2, n3};
    std::sort(data.begin(), data.end());
    edges = std::array<Edge, 3>{Edge{n1, n2}, Edge{n2, n3}, Edge{n1, n3}};
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

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    os << "[" 
    << t.data[0].get_index() << " "
    << t.data[1].get_index() << " " 
    << t.data[2].get_index() << "]";
    return os;
}

// Getter for triangle vertices
std::array<Node, 3> Triangle::get_vertices() const {
    return data;
}

std::array<Edge, 3> Triangle::get_edges() const {
    return edges;
}

std::array<int, 3> Triangle::get_vertices_index() const {
    std::array<int, 3> index;
    for(int i{0}; i < 3; i++) {
        index[i] = data[i].get_index();
    }
    return index;
}

std::array<std::array<int, 2>, 3> Triangle::get_edges_index() const {
    std::array<Edge, 3> edges{get_edges()};
    return std::array<std::array<int, 2>, 3>{
        edges[0].get_vertices_index(),
        edges[1].get_vertices_index(),
        edges[2].get_vertices_index()
    };
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
    double m3 = -1 / slope(v1, v2);

    // Checking for vertical lines
    if(std::isinf(m1)) {
        m1 = m3;
        p1 = p3;
    } else if(std::isinf(m2)) {
        m2 = m3;
        p2 = p3;
    }

    // Solve for lines intersection
    double x = ( (p2.y - m2*p2.x) - (p1.y - m1*p1.x) ) / (m1 - m2);
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

    // Compute values of rect-supertriangle
    max_x += 3*dx;
    min_x -= 3*dx;
    max_y += 3*dy;
    min_y -= 3*dy;

    // Create supertriangle nodes
    Node n1{min_x, min_y, -3};
    Node n2{max_x, min_y, -2};
    Node n3{(max_x+min_x)*0.5, max_y, -1};

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
    std::vector<Edge> edges{};

    // Loop over all nodes
    for(Node& node: nodes) {
        // Ensure vertices to be removed is clear
        edges.clear();
        // Loop over all triangles
        for(size_t i{0}; i<triangles.size(); i++) {
            auto triangle = triangles.at(i);
            if(triangle.circumscribe(node)) {
                // Retrieve vertices and add to removed ones
                auto v = triangle.get_edges();
                edges.insert(edges.end(), v.begin(), v.end());
                // Remove triangle because it is no longer Delaunay
                triangles.erase(std::remove(triangles.begin(), triangles.end(), triangle), triangles.end());
                i--;
            }
        }
        // Remove duplicated edges (they do not form Delaunay triangules)
        std::sort(edges.begin(), edges.end());
        int N{static_cast<int>(edges.size())};
        Edge edge_to_remove{};
        for(size_t i{0}; i < (N-1); i++) {
            if(edges.at(i) == edges.at(i+1)) {
                edge_to_remove = edges.at(i);
                edges.erase(std::remove(edges.begin(), edges.end(), edge_to_remove), edges.end());
                i--;
                N-=2;
            }
        }
        // Create new triangles
        for (const Edge& edge: edges) {
            auto nodes = edge.get_vertices();
            Node n1 = nodes.at(0);
            Node n2 = nodes.at(1);
            triangles.push_back(Triangle{node, n1, n2});
        }
    }

    // Remove super triangle nodes
    std::array<int, 3> index; // Instantiate variable
    size_t i{0};
    while(i < triangles.size()) {
        index = triangles[i].get_vertices_index();
        for(int& j: index) {
            if(j < 0) {
                triangles.erase(std::remove(triangles.begin(), triangles.end(), triangles[i--]), triangles.end());
                break;
            }
        }
        i++;
    }


    return triangles;
}

std::vector<Edge> Delaunay::get_edges() {
    std::set<Edge> edges;
    for(Triangle& triangle: triangles) {
        auto triangle_edges = triangle.get_edges();
        edges.insert(triangle_edges.begin(), triangle_edges.end());
    }
    std::vector<Edge> sorted_edges(edges.begin(), edges.end());
    std::sort(sorted_edges.begin(), sorted_edges.end());
    return sorted_edges;
}

std::vector<std::array<int, 2>> Delaunay::get_edges_index() {
    std::vector<std::array<int, 2>> edges_index;
    for(const Edge& edge: get_edges()) {
        edges_index.push_back(edge.get_vertices_index());
    }
    return edges_index;
}