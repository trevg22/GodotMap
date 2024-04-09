#include "Voronoi.hpp"
#include <vector>
int main()
{
    Vor vor;
    // godot::Voronoi vor2;
    std::vector<boost::polygon::point_data<double>> verts;
    verts.push_back( { 40, 40 } );
    verts.push_back( { 40, 50 } );
    verts.push_back( { 50, 00 } );
    verts.push_back( { 50, 40 } );

    for ( const auto &vert : verts )
    {
        vor.addVertex( vert );
    }
    vor.compute();
}
