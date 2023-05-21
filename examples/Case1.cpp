#include <Delaunay.hpp>
#include <iostream>

int main() {
	std::vector<Coord2D> points;
	std::vector<double> x{0,4,2,5,5};
	std::vector<double> y{0,0,2,1,7};
	
	for(size_t i{0}; i<x.size(); i++) {
		points.push_back(Coord2D{x[i], y[i]});
	}

    Delaunay d{points};
	
	std::vector<Triangle> triangles = d.compute();

    return 0;
};
