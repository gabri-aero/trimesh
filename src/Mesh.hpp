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
    static Boundary line(Coord2D p0, Coord2D p1, double h);
    static Boundary circle(Coord2D p0, double r, double h);
    static Boundary naca(std::string code, double chord);
    static Boundary combine(Boundary b1, Boundary b2);
    template<typename T, typename... Args>
    static Boundary combine(T value, Args... args);
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