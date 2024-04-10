#pragma once
#include "boost/polygon/point_data.hpp"
#include "boost/polygon/voronoi_diagram.hpp"
#include <boost/polygon/voronoi.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/polygon2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <vector>
class Vor
{
public:
    void addVertex( const boost::polygon::point_data<double> &vertex );
    void compute();
    std::vector<boost::polygon::voronoi_cell<double>> getCells();
    //todo
    boost::polygon::voronoi_diagram<double> vd_;
private:
    std::vector<boost::polygon::point_data<double>> vertices_;
};
class Voronoi : public godot::Object
{
    GDCLASS( Voronoi, godot::Object )
public:
    void addVertex( const godot::Vector2 &vertex );
    void compute();
    static godot::PackedVector2Array toGodotVertices(const boost::polygon::voronoi_cell<double> &cell);
    godot::Array getPolygons();

private:
    godot::Array polygons_;
    Vor vor;
    // std::vector<boost::polygon::point_data<double>> vertices_;

protected:
    static void _bind_methods();
};
