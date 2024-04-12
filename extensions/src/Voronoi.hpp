#pragma once
#include "boost/polygon/point_data.hpp"
#include "boost/polygon/segment_data.hpp"
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
    // todo

private:
    typedef double coordinate_type;
    typedef boost::polygon::point_data<coordinate_type> point_type;
    typedef boost::polygon::segment_data<coordinate_type> segment_type;
    typedef boost::polygon::rectangle_data<coordinate_type> rect_type;
    typedef boost::polygon::voronoi_builder<int> VB;
    typedef boost::polygon::voronoi_diagram<coordinate_type> VD;
    typedef VD::cell_type cell_type;
    typedef VD::cell_type::source_index_type source_index_type;
    typedef VD::cell_type::source_category_type source_category_type;
    typedef VD::edge_type edge_type;
    typedef VD::cell_container_type cell_container_type;
    typedef VD::cell_container_type vertex_container_type;
    typedef VD::edge_container_type edge_container_type;
    typedef VD::const_cell_iterator const_cell_iterator;
    typedef VD::const_vertex_iterator const_vertex_iterator;
    typedef VD::const_edge_iterator const_edge_iterator;

    point_type shift_;
    std::vector<point_type> point_data_;
    std::vector<segment_type> segment_data_;
    rect_type brect_;
    VB vb_;
    VD vd_;
};
class Voronoi : public godot::Object
{
    GDCLASS( Voronoi, godot::Object )
public:
    void addVertex( const godot::Vector2 &vertex );
    void compute();
    static godot::PackedVector2Array toGodotVertices(
        const boost::polygon::voronoi_cell<double> &cell );
    godot::Array getPolygons();
    godot::Array getCellCenters();

private:
    godot::Array polygons_;
    Vor vor;
    // std::vector<boost::polygon::point_data<double>> vertices_;

protected:
    static void _bind_methods();
};
