#include "mesh.h"
#include <iostream>
#include <ostream>

GeometricWorld::GeometricWorld()
{
    std::vector<Vector> vecteurDePoints;
    Vector p0(0, 0, 0);
    Vector p1(2, 0, 0);
    Vector p2(0., 2, 0);
    Vector p3(2, 2, 0.0);
    Vector p4(1, 1, 2);
    vecteurDePoints.push_back(p0);
    vecteurDePoints.push_back(p1);
    vecteurDePoints.push_back(p2);
    vecteurDePoints.push_back(p3);
    vecteurDePoints.push_back(p4);

    std::vector<Face> vecteurDeFaces;
    Face f0(0, 1, 2);
    Face f1(1, 2, 3);
    Face f2(0, 1, 4);
    Face f3(0, 2, 4);
    Face f4(1, 3, 4);
    Face f5(2, 3, 4);
    vecteurDeFaces.push_back(f0);
    vecteurDeFaces.push_back(f1);
    vecteurDeFaces.push_back(f2);
    vecteurDeFaces.push_back(f3);
    vecteurDeFaces.push_back(f4);
    vecteurDeFaces.push_back(f5);
    for (int i = 0; i < vecteurDePoints.size(); i++) {
        _bBox.push_back(vecteurDePoints[i]);
    }
    _bBox.push_back(p0);
    _bBox.push_back(p1);
    _bBox.push_back(p2);
    _bBox.push_back(p3);
    _bBox.push_back(p4);

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

