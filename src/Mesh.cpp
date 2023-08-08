#include <vector>
#include <math.h>

#include <Mesh.hpp>
#include <Delaunay.hpp>

// Boundary constructors
Boundary::Boundary(std::vector<Node> nodes, std::vector<Edge> edges) 
: nodes{nodes}, edges{edges} {

}

Boundary::Boundary(std::vector<Node> nodes, bool closed) {
    // Assign nodes
    this->nodes = nodes;

    // Add extra node to nodes if closed
    if(closed) {
        nodes.push_back(nodes.at(0));
    }

    // Iterate over all nodes (except last one) and add it to the next node
    int j;
    for(int i{0}; i < (nodes.size()-1); i++) {
        j = i + 1;
        edges.emplace_back(nodes.at(i), nodes.at(j));
    }

    // Removed previously added node if closed
    if(closed) {
        nodes.pop_back();
    }
}

// Boundary getters
std::vector<Edge> Boundary::get_edges() {
    return edges;
}

std::vector<Node> Boundary::get_nodes() {
    return nodes;
}

// Mesh constructor
Mesh::Mesh(Boundary boundary, double h) {
    segments = boundary.get_edges();
    std::vector<Coord2D> points;
    for(Node& node: boundary.get_nodes()) {
        points.push_back(node.get_coords());
    }
    triangulation = Delaunay{points};
    triangulation.compute();
    triangulation.refine(30 * M_PI / 180, h);
}

// Check if point is inside the domain (based on given boundaries)
bool Mesh::inside_domain(Coord2D p) {
    // Instantiate variables
    std::vector<Node> intersecting_nodes;
    double m, n, x;
    int i{0};

    // Loop over all boundary edges (segments)
    for(Edge edge: segments) {
        // Get edge vertices
        Coord2D p1 = edge.get_vertices().at(0).get_coords();
        Coord2D p2 = edge.get_vertices().at(1).get_coords();

        // Check if one point y coordinate is greater and another lower (point in between w.r.t y coordinate)
        // This ensures that an horizontal line containing the point intersects the relevant boundary edge
        double sign = (p1.y - p.y) * (p2.y - p.y);
        if (sign <= 0) { 
            if (p1.x == p2.x) {
                // If node is vertical we already know the coordinates of the intersection point
                x = p1.x;
            } else {
                // Else we compute the intersection from y = mx + n
                m = (p2.y - p1.y) / (p2.x - p1.x);
                n = p2.y - m * p2.x;
                x = (p.y - n) / m;
            }
            // Check if intersection point lies to the left or to the right
            if (x < p.x) {
                if (p.y == p2.y || p.y == p1.y){
                    i += 1; // This will finally add 2 (given that we are looping over the edges we count this point twice)
                } else {
                    i += 2;
                }
            }
        }
    }
    return (i % 4) == 2; // in fact we want to check that (i/2) % 2 == 1 due to that "double counting" approach
}

// Mesh getters
Delaunay Mesh::get_triangulation() {
    // Instantiate triangles and nodes
    std::vector<Triangle> triangles;
    std::vector<Node> nodes;

    // Loop over triangulation triangules
    for(Triangle& triangle: triangulation.get_triangles()) {
        // Add triangle if centroid is inside the domain
        if(inside_domain(triangle.centroid())) {
            triangles.push_back(triangle);
        }
    }

    // Loop over triangulation nodes
    for(Node& node: triangulation.get_nodes()) {
        for(Edge edge: segments) {
            // Add node if it belongs to the boundary
            if(node == edge.get_vertices().at(0) || node == edge.get_vertices().at(1)) {
                nodes.push_back(node);
                break;
            } else if(inside_domain(node.get_coords())) { // or is inside the domain
                nodes.push_back(node);
                break;
            }
        }
    }

    // Re-built triangulation object
    return Delaunay{triangles, nodes};
}