#include "mesh.h"
#include <iostream>
#include <ostream>

Vector cross(const Vector & u, const Vector & v) {
    return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

float dot(const Vector & u, const Vector & v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector normalize(const Vector & u) {
    float norm = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    return Vector(u.x / norm, u.y / norm, u.z / norm);
}

Vector operator*(const Vector & u, float a) {
    return Vector(u.x * a, u.y * a, u.z * a);
}

Vector operator+(const Vector & u, const Vector & v) {
    return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector operator-(const Vector & u, const Vector & v) {
    return Vector(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vector operator/(const Vector & u, float a) {
    return Vector(u.x / a, u.y / a, u.z / a);
}

float norm(const Vector & u) {
    return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

GeometricWorld::GeometricWorld()
{
    // ensemble de teste dans le plan xy
    std::vector<Vector> vecteurDePoints;
    Vector p0(0, 0, 0);
    Vector p1(2, 0, 0);
    Vector p2(0., 2, 0);
    Vector p3(2, 2, 0.0);
    Vector p4(1, 3, 0);
    Vector p5(-1, 1, 0);
    Vector p6(3, 1, 0);
    Vector p7(1, -1, 0);
    vecteurDePoints.push_back(p0);
    vecteurDePoints.push_back(p1);
    vecteurDePoints.push_back(p2);
    vecteurDePoints.push_back(p3);
    vecteurDePoints.push_back(p4);
    vecteurDePoints.push_back(p5);
    vecteurDePoints.push_back(p6);
    vecteurDePoints.push_back(p7);

    std::vector<Face> vecteurDeFaces;
    Face f0(0, 1, 2);
    Face f1(1, 2, 3);
    Face f2(1, 6, 3);
    Face f3(0, 7, 1);
    Face f4(2, 3, 4);
    Face f5(0, 2, 5);

    vecteurDeFaces.push_back(f0);
    vecteurDeFaces.push_back(f1);
    vecteurDeFaces.push_back(f2);
    vecteurDeFaces.push_back(f3);
    vecteurDeFaces.push_back(f4);
    vecteurDeFaces.push_back(f5);
    for (int i = 0; i < vecteurDePoints.size(); i++) {
        _bBox.push_back(vecteurDePoints[i]);
    }
    // _bBox.push_back(p0);
    // _bBox.push_back(p1);
    // _bBox.push_back(p2);
    // _bBox.push_back(p3);
    // _bBox.push_back(p4);

    Mesh pyramide(vecteurDePoints, vecteurDeFaces);
    _mesh = TopologicalMesh(pyramide);
    //     for (int i = 0; i < _mesh.points.size(); i++) {
    //     std::cout << "Sommet " << i << " : " << _mesh.points[i].x << " " << _mesh.points[i].y << " " << _mesh.points[i].z << " | Index : " << _mesh.points[i].Face_Index << std::endl;
    // }

    // for (int i = 0; i < _mesh.faces_table.size(); i++) {
    //     std::cout << "Face " << i << " : " << _mesh.faces_table[i].index_points[0] << " " << _mesh.faces_table[i].index_points[1] << " " << _mesh.faces_table[i].index_points[2] << std::endl;
    //     std::cout << "Face adjacente : " << _mesh.faces_table[i].adj_f[0] << " " << _mesh.faces_table[i].adj_f[1] << " " << _mesh.faces_table[i].adj_f[2] << std::endl;
    // }
}

// The following functions could be displaced into a module OpenGLDisplayGeometricWorld that would include mesh.h

// Draw a Point
void glPointDraw(const Vector & p) {
    glVertex3f(p.x, p.y, p.z);
}

//Example with a bBox
void GeometricWorld::draw() {
     if (index_sommet != -1) {
        glColor3d(1,0,0);
        for (int i = 0; i < _mesh.faces_table.size(); i++) {
            for (int j = 0; j < 3; j++) {
                if (_mesh.faces_table[i].index_points[j] == index_sommet) {
                glBegin(GL_TRIANGLES);
                glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[0]]);
                glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[1]]);
                glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[2]]);
                glEnd();
                break;
                }
            }
        }   
    }
    glColor3d(color.x,color.y,color.z);
    for (int i = 0; i < _mesh.faces_table.size(); i++) {
        glBegin(GL_TRIANGLES);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[0]]);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[1]]);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[2]]);
        glEnd();
    }
}

//Example with a wireframe bBox
void GeometricWorld::drawWireFrame() {
    glColor3d(0,0,0);
        for (int i = 0; i < _mesh.faces_table.size(); i++) {
        glBegin(GL_LINE_STRIP);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[0]]);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[1]]);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[0]]);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[2]]);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[2]]);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[1]]);
        glEnd();
    }
}

void GeometricWorld::TriangleSplit(const Vector& inserted_vertex)
{
    _mesh.points.push_back(inserted_vertex);
    // finding if on edge or not :
    int indice_face = 0;
    Vector v01 = _mesh.points[_mesh.faces_table[indice_face].index_points[1]] - _mesh.points[_mesh.faces_table[indice_face].index_points[0]];
    Vector v12 = _mesh.points[_mesh.faces_table[indice_face].index_points[2]] - _mesh.points[_mesh.faces_table[indice_face].index_points[1]];
    Vector v20 = _mesh.points[_mesh.faces_table[indice_face].index_points[0]] - _mesh.points[_mesh.faces_table[indice_face].index_points[2]];
    Vector v0 = inserted_vertex - _mesh.points[_mesh.faces_table[indice_face].index_points[0]];
    Vector v1 = inserted_vertex - _mesh.points[_mesh.faces_table[indice_face].index_points[1]];
    if (cross(v01, v0).z == 0){
        EdgeSplit(indice_face, 2);
    }
    else if (cross(v20, v0).z == 0){
        EdgeSplit(indice_face, 1);
    }
    else if (cross(v12, v1).z == 0){
        EdgeSplit(indice_face, 0);
    }
    else {
        FaceSplit(indice_face);
    }
    
} 

void GeometricWorld::EdgeSplit(int indice_face, int edge)
{
    int p1 = _mesh.faces_table[indice_face].index_points[(edge+1)%3];
    int face_p1,face_p2; 
    int p2 = _mesh.faces_table[indice_face].index_points[(edge+2)%3];
    int last_point;
    for (int j=0; j<3; j++)
    {
        if (_mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]].index_points[j] != p1 && _mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]].index_points[j] != p2)
        {
            last_point = _mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]].index_points[j];
        }
        else if ( _mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]].index_points[j] == p1)
        {
            face_p1 = _mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]].adj_f[j];
        }
        else if (_mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]].index_points[j] == p2)
        {
            face_p2 = _mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]].adj_f[j];
        }
    }
    _mesh.faces_table.push_back(Face(p2,(int)_mesh.points.size() - 1,last_point,face_p2,_mesh.faces_table[indice_face].adj_f[edge],indice_face));
    _mesh.faces_table[_mesh.faces_table[indice_face].adj_f[edge]] = Face(p1,(int)_mesh.points.size() - 1,last_point,face_p1,(int)_mesh.faces_table.size() -1,indice_face);
    _mesh.faces_table.push_back(Face(_mesh.faces_table[indice_face].index_points[edge],(int)_mesh.points.size() - 1, _mesh.faces_table[indice_face].index_points[(edge+2)%3],_mesh.faces_table[indice_face].adj_f[edge],_mesh.faces_table[indice_face].adj_f[(edge+1)%3], indice_face));
    _mesh.faces_table[indice_face] = Face(_mesh.faces_table[indice_face].index_points[edge], _mesh.faces_table[indice_face].index_points[(edge+1)%3], (int)_mesh.points.size() - 1,_mesh.faces_table[indice_face].adj_f[edge],(int)_mesh.faces_table.size() -1, _mesh.faces_table[indice_face].adj_f[(edge+2)%3]);

            // for (int i = 0; i < _mesh.faces_table.size(); i++) {
    //         if (i == indice_face) {
                // Opposite triangle
                //  _mesh.faces_table.push_back(Face(p2,_mesh.points.size() - 1,last_point,face_p2,_mesh.faces_table[indice_face].adj_f[edge],indice_face));
                // _mesh.faces_table[_mesh.faces_table[i].adj_f[edge]] = Face(p1,_mesh.points.size() - 1,last_point,face_p1,_mesh.faces_table.size() -1,indice_face);
                // _mesh.faces_table.push_back(Face(_mesh.faces_table[i].index_points[edge],_mesh.points.size() - 1, _mesh.faces_table[i].index_points[(edge+2)%3],_mesh.faces_table[i].adj_f[edge],_mesh.faces_table[i].adj_f[(edge+1)%3], indice_face));
                // _mesh.faces_table[i] = Face(_mesh.faces_table[i].index_points[edge], _mesh.faces_table[i].index_points[(edge+1)%3], _mesh.points.size() - 1,_mesh.faces_table[i].adj_f[edge],_mesh.faces_table.size() -1, _mesh.faces_table[i].adj_f[(edge+2)%3]);
                // break;
        //     }
        // }
}

void GeometricWorld::FaceSplit(int indice_face)
{
for (int i = 0; i < _mesh.faces_table.size(); i++) {
            if (i == indice_face) {
                _mesh.faces_table.push_back(Face(_mesh.faces_table[i].index_points[1], _mesh.faces_table[i].index_points[2], (int)_mesh.points.size() - 1));
                _mesh.faces_table.push_back(Face(_mesh.faces_table[i].index_points[2], _mesh.faces_table[i].index_points[0], (int)_mesh.points.size() - 1));
                _mesh.faces_table[i] = Face(_mesh.faces_table[i].index_points[0], _mesh.faces_table[i].index_points[1], (int)_mesh.points.size() - 1);
                break;
            }
        }
        _mesh = TopologicalMesh(_mesh);

}

void GeometricWorld::EdgeFlip(int face1, int face2)
{
Face f1 = _mesh.faces_table[face1];
Face f2 = _mesh.faces_table[face2];
int p1=-1, p2=-1;
int idx_p1, idx_p2;
for (int i = 0; i < 3; i++) {
    bool found = false;
    for (int j = 0; j < 3; j++) {
        if (f1.index_points[i] == f2.index_points[j]) {
            found = true;
            break;
        }
    }
    if (!found) {
        if (p1 == -1) {
            idx_p1 = i;
            p1 = f1.index_points[i];
        }
    }
}
for (int i = 0; i < 3; i++) {
    bool found = false;
    for (int j = 0; j < 3; j++) {
        if (f2.index_points[i] == f1.index_points[j]) {
            found = true;
            break;
        }
    }
    if (!found) {
        if (p1 != -1) {
            idx_p2 = i;
            p2 = f2.index_points[i];
        }
        else {
            std::cout << "Erreur : les deux faces n'ont pas d'arrete commune" << std::endl;
        }
    }
}  

_mesh.faces_table[face1] = Face(p1, f1.index_points[(idx_p1+1)%3],p2,f2.adj_f[(idx_p2+2)%3],f1.adj_f[idx_p1],f1.adj_f[(idx_p1+2)%3]);
int new_face = f1.adj_f[(idx_p1+1)%3];
_mesh.faces_table[face2] = Face(p2, f1.index_points[(idx_p1+2)%3],p1,new_face,f2.adj_f[idx_p2],f2.adj_f[(idx_p2+1)%3]);

}