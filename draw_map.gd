extends Node2D


var db:SQLite
# Called when the node enters the scene tree for the first time.
func _ready():
	var points2=[]
	db=SQLite.new()
	db.path="res://network.db"
	db.open_db()
	var query_cmd="SELECT * FROM Network"
	var db_data=db.select_rows("Network","",["*"])
	print(db_data)
	for row in db_data:
		points2.append(Vector2(row["Lat"],row["Lon"]))
	var points=[Vector2(40, 40),
								  Vector2(40, 50),
								  Vector2(50, 50),
								  Vector2(50, 40),
								  Vector2(100,100),
								  Vector2(25,25),
								Vector2(80,50),
								Vector2(200,145)
								]
	var vor=Voronoi.new()
	
	for coord in points2:
		vor.addVertex(coord)
		
	
	
	vor.compute();
	print("voronoi computed")
	var vertex_arr=vor.getPolygons()
	print("Get polygons")
	print(vertex_arr)
	for vertices in vertex_arr:
		var poly =Polygon2D.new()
		poly.polygon=vertices
		poly.set_color(Color(randf(),randf(),randf()))		
		add_child(poly)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
