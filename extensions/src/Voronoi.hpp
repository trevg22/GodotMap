#pragma once
#include "boost/polygon/point_data.hpp"
#include <boost/polygon/voronoi.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/polygon2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <vector>
class Vor
{
public:
    void addVertex( const boost::polygon::point_data<double> &vertex );
    void compute();
    godot::Array getPolygons();

private:
    std::vector<boost::polygon::point_data<double>> vertices_;
};
class Voronoi : public godot::Object
{
    GDCLASS( Voronoi, godot::Object )
public:
private:
    godot::Array polygons_;
    // std::vector<boost::polygon::point_data<double>> vertices_;

protected:
    static void _bind_methods();
};
