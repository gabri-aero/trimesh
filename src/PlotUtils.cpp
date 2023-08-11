#include "PlotUtils.hpp"
#include "Delaunay.hpp"

void Plot::plot_nodes(std::vector<Node> nodes) {
    Gnuplot gp;

    std::vector<std::pair<double, double>> node_pts;

    for(Node& node: nodes) {
        node_pts.push_back(std::make_pair(
            node.get_x(),
            node.get_y()
        ));
    }

    gp << "set title 'Node Plot'\n";
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    
    gp << "stats '-' using 1:2 nooutput\n";
    gp.send1d(node_pts);

    gp << "x_min = STATS_min_x\n";
    gp << "x_max = STATS_max_x\n";
    gp << "y_min = STATS_min_y\n";
    gp << "y_max = STATS_max_y\n";

    gp << "x_padding = 0.1 * (x_max - x_min)\n";
    gp << "y_padding = 0.1 * (y_max - y_min)\n";

    gp << "set xrange [x_min - x_padding : x_max + x_padding]\n";
    gp << "set yrange [y_min - y_padding : y_max + y_padding]\n";

    gp << "plot '-' with points pointtype 7 lc rgb 'black' notitle\n";
    gp.send1d(node_pts);
}

void Plot::plot_mesh(std::vector<Edge> edges, std::vector<Node> nodes) {
    Gnuplot gp;

    gp << "set size ratio -1 \n";

    // Construct the filename string
    std::stringstream filenameStream;
    filenameStream << "output" << nodes.size() << ".png"; // You can choose the desired file extension
    std::string filename = filenameStream.str();

    // Set the output filename in Gnuplot
    gp << "set terminal pngcairo\n";
    gp << "set output '" << filename << "'\n";

    std::vector<boost::tuple<double, double, double, double>> mesh_pts;
    std::vector<std::pair<double, double>> node_pts;

    for(Edge& edge: edges) {
        mesh_pts.push_back(boost::make_tuple(
            edge.get_vertices().at(0).get_x(),
            edge.get_vertices().at(0).get_y(),
            edge.get_vertices().at(1).get_x() - edge.get_vertices().at(0).get_x(),
            edge.get_vertices().at(1).get_y() - edge.get_vertices().at(0).get_y()
        ));
    }


    for(Node& node: nodes) {
        node_pts.push_back(std::make_pair(
            node.get_x(),
            node.get_y()
        ));
    }

    gp << "set title 'Mesh Plot'\n";
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    
    gp << "stats '-' using 1:2 nooutput\n";
    gp.send1d(node_pts);

    gp << "x_min = STATS_min_x\n";
    gp << "x_max = STATS_max_x\n";
    gp << "y_min = STATS_min_y\n";
    gp << "y_max = STATS_max_y\n";

    gp << "x_padding = 0.1 + 0.1 * (x_max - x_min)\n";
    gp << "y_padding = 0.1 + 0.1 * (y_max - y_min)\n";

    gp << "set xrange [x_min - x_padding : x_max + x_padding]\n";
    gp << "set yrange [y_min - y_padding : y_max + y_padding]\n";
    
    gp << "plot '-' with vectors nohead notitle, '-' with points pointtype 7 lc rgb 'black' pointsize 0.2 notitle, \n";
    gp.send1d(mesh_pts);
    gp.send1d(node_pts);

    gp << "set output\n";
}

void Plot::close_gnuplot(){
    std::system("pkill gnuplot");
}