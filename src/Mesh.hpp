#include <vector>

#include <Delaunay.hpp>

#ifndef _MESH_HPP_
#define _MESH_HPP_

class Boundary {
    std::vector<Edge> edges;
    std::vector<Node> nodes;
public:
    Boundary(std::vector<Node>, std::vector<Edge>);
    Boundary(std::vector<Node>, bool closed=true);
    std::vector<Edge> get_edges();
    std::vector<Node> get_nodes();
};

class Mesh {
    std::vector<Edge> segments;
    Delaunay triangulation;
public:
    Mesh(Boundary boundary, double h);
    bool inside_domain(Coord2D p);
    Delaunay get_triangulation();
};


#endif //_MESH_HPP_