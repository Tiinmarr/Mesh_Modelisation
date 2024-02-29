#include "mesh.h"
#include <iostream>
#include <ostream>

// Vector color_from_laplacian(float l1, float l2, float l3) {
//     float t = (l1 + l2 + l3) / 3;
//     if (t < 0.5) return Vector(-2 * t + 2,-2 * t + 2,1);
//     else return Vector(1 ,2 * t ,2 * t);
// }

Vector color_from_laplacian(float l1, float l2, float l3) {
    float t = (l1 + l2 + l3) / 3;
    if (t < 0.5) return Vector(-2 * t + 2,-2 * t + 2,1);
    else return Vector(1 ,2 * t ,2 * t);
}


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
    Face f0(0, 2, 1);
    Face f1(1, 2, 3);
    Face f2(0, 1, 4);
    Face f3(0, 4, 2);
    Face f4(1, 3, 4);
    Face f5(2, 4, 3);
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
    if (!laplacian){
     if (index_sommet != -1 && index_sommet < _mesh.points.size()) {
        glColor3d(1,0,0);
        int premier_triangle = _mesh.points[index_sommet].Face_Index;
        glBegin(GL_TRIANGLES);
        glPointDraw(_mesh.points[_mesh.faces_table[premier_triangle].index_points[0]]);
        glPointDraw(_mesh.points[_mesh.faces_table[premier_triangle].index_points[1]]);
        glPointDraw(_mesh.points[_mesh.faces_table[premier_triangle].index_points[2]]);
        glEnd();
        int last_triangle = premier_triangle;
        // calcul pour le premier triangle
        int triangle_suivant = -1;
        int s;
        while (triangle_suivant != premier_triangle)
        {
            for (int j = 0; j < 3; j++)
            {
                if (_mesh.faces_table[last_triangle].index_points[j] == index_sommet)
                {
                    s = j+1;
                    break;
                }
            }
            s = s % 3;
            triangle_suivant = _mesh.faces_table[last_triangle].adj_f[s];
            last_triangle = triangle_suivant;
            glBegin(GL_TRIANGLES);
            glPointDraw(_mesh.points[_mesh.faces_table[triangle_suivant].index_points[0]]);
            glPointDraw(_mesh.points[_mesh.faces_table[triangle_suivant].index_points[1]]);
            glPointDraw(_mesh.points[_mesh.faces_table[triangle_suivant].index_points[2]]);
            glEnd();
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
    else {
        for (int i = 0; i < _mesh.faces_table.size(); i++) {
        color = color_from_laplacian(laplacian_vector[_mesh.faces_table[i].index_points[0]],laplacian_vector[_mesh.faces_table[i].index_points[1]],laplacian_vector[_mesh.faces_table[i].index_points[2]]);
        // std::cout << color.x << " " << color.y << " " << color.z << std::endl;
        glBegin(GL_TRIANGLES);
        glColor3d(color.x,color.y,color.z);   
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[0]]);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[1]]);
        glPointDraw(_mesh.points[_mesh.faces_table[i].index_points[2]]);
        glEnd();
        }
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

