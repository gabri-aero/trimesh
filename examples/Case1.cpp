#include <Delaunay.hpp>
#include <iostream>

int main() {
	std::vector<Coord2D> points;
	std::vector<double> x{0,1,2,0,1,2,0,1,2};
	std::vector<double> y{0,0,0,1,1,1,2,2,2};
	
	for(size_t i{0}; i<x.size(); i++) {
		points.push_back(Coord2D{x[i], y[i]});
	}

    Delaunay d{points};
	
	std::vector<Triangle> triangles = d.compute();

    return 0;
};
