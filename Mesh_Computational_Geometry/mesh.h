#ifndef MESH_H
#define MESH_H

#include <QOpenGLWidget>

class Point
{
public:
    double _x;
    double _y;
    double _z;

    Point():_x(),_y(),_z() {}
    Point(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_) {}
};

class Vector // Classe qui représente un sommet en 2D
{
public:
    Vector() {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;
    int Face_Index = 0;
};

class Face
{
public:
    Face() {}
    Face(int point1, int point2, int point3) {
        index_points.push_back(point1);
        index_points.push_back(point2);
        index_points.push_back(point3);
        adj_f.resize(3, -1); // Initialiser à -1 pour indiquer qu'aucune face adjacente n'est définie.
    };

    Face(int point1, int point2, int point3, int face1, int face2, int face3) {
    index_points.push_back(point1);
    index_points.push_back(point2);
    index_points.push_back(point3);
    adj_f.push_back(face1);
    adj_f.push_back(face2);
    adj_f.push_back(face3);
    };

    std::vector<int> index_points;
    std::vector<int> adj_f;
};

class Mesh
{
public:
    Mesh() {}
    Mesh(const std::vector<Vector>& points, const std::vector<Face>& faces) : points(points), faces(faces) {}
    std::vector<Vector> points;
    std::vector<Face> faces;
};

class TopologicalMesh
{
public:
    TopologicalMesh() {}
    TopologicalMesh(const Mesh& mesh) {
        std::map<std::pair<int, int>, std::pair<int, int>> Map;
        points = mesh.points;
        faces_table = mesh.faces;
        std::pair<int, int> currentArrete;
        for (int i = 0; i < mesh.faces.size(); i++) {
            for (int j = 0; j < 3; j++) {
                int i1 = (j + 1) % 3;
                int i2 = (j + 2) % 3;
                currentArrete = std::make_pair(std::min(faces_table[i].index_points[i1], faces_table[i].index_points[i2]), std::max(faces_table[i].index_points[i1], faces_table[i].index_points[i2]));
                if (Map.find(currentArrete) != Map.end()) {
                    faces_table[i].adj_f[j] = Map[currentArrete].first;
                    faces_table[Map[currentArrete].first].adj_f[Map[currentArrete].second] = i;
                }
                else {
                    Map.insert(std::make_pair(currentArrete, std::make_pair(i, j)));
                }

                // Remplir l'index des points :
                if (points[faces_table[i].index_points[j]].Face_Index == 0) {
                    points[faces_table[i].index_points[j]].Face_Index = i;
                }
            }
        }
    }

    TopologicalMesh(const TopologicalMesh& mesh)
    {
        std::map<std::pair<int, int>, std::pair<int, int>> Map;
        points = mesh.points;
        faces_table = mesh.faces_table;
        std::pair<int, int> currentArrete;
        for (int i = 0; i < mesh.faces_table.size(); i++) {
            for (int j = 0; j < 3; j++) {
                int i1 = (j + 1) % 3;
                int i2 = (j + 2) % 3;
                currentArrete = std::make_pair(std::min(faces_table[i].index_points[i1], faces_table[i].index_points[i2]), std::max(faces_table[i].index_points[i1], faces_table[i].index_points[i2]));
                if (Map.find(currentArrete) != Map.end()) {
                    faces_table[i].adj_f[j] = Map[currentArrete].first;
                    faces_table[Map[currentArrete].first].adj_f[Map[currentArrete].second] = i;
                }
                else {
                    Map.insert(std::make_pair(currentArrete, std::make_pair(i, j)));
                }

                // Remplir l'index des points :
                if (points[faces_table[i].index_points[j]].Face_Index == 0) {
                    points[faces_table[i].index_points[j]].Face_Index = i;
                }
            }
        }
    }

    std::vector<Vector> points;
    std::vector<Face> faces_table;

    // void drawMesh();
    //void drawMeshWireFrame();
};

class GeometricWorld //Generally used to create a singleton instance
{
  
public :
  GeometricWorld();
  void draw();
  void drawWireFrame();
  void TriangleSplit(const Vector& vertex);
  void EdgeSplit(int indice_face, int edge);
  void FaceSplit(int indice_face);
  void EdgeFlip(int face1, int face2);
  QVector<Vector> _bBox;  // Bounding box // ou std::vector
  // ** TP Can be extended with further elements;
  TopologicalMesh _mesh;
  int index_sommet=-1;
  Vector color = Vector(1,1,0);
};


#endif // MESH_H
