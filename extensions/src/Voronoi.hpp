#include "boost/polygon/point_data.hpp"
#include "godot_cpp/classes/polygon2d.hpp"
#include <boost/polygon/voronoi.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <vector>
class Voronoi : public godot::Object
{
    GDCLASS( Voronoi, godot::Object )
public:
    void addVertex( const godot::Vector2 &vec );
    void compute();
    godot::TypedArray<godot::Polygon2D> getPolygons();

private:
    godot::TypedArray<godot::Polygon2D> polygons_;
    std::vector<boost::polygon::point_data<double>> vertices_;

protected:
    static void _bind_methods();
};
