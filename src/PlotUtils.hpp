#include <vector>
#include <iostream>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.hpp"

#ifndef _PLOT_UTILS_HPP_
#define _PLOT_UTILS_HPP_

#include "Delaunay.hpp"

namespace Plot {

    void plot_nodes(std::vector<Node> nodes);
    void plot_mesh(std::vector<Edge> edges, std::vector<Node> nodes = std::vector<Node>{});
    void close_gnuplot();

}

#endif //_PLOT_UTILS_HPP_