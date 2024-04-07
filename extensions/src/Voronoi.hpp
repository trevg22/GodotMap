#include "godot_cpp/classes/polygon2d.hpp"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <vector>
class Voronoi : public godot::Object {
  GDCLASS(Voronoi, godot::Object)
public:
  void addVertex(const godot::Point2 &point);
  void compute();
  godot::TypedArray<godot::Polygon2D> getPolygons();

private:
  godot::TypedArray<godot::Polygon2D> polygons_;
  std::vector<godot::Point2> vertices_;

protected:
  static void _bind_methods();
};
