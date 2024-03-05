#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mesh.h"
#include "gldisplaywidget.h"
#include <chrono>
#include <thread>
#include <iostream>

float dot(const Vector & a, const Vector & b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector cross(const Vector & a, const Vector & b) {
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float norm(const Vector & a) {
    return sqrt(dot(a, a));
}

float norm_float(const float & a) {
    return sqrt(a * a);
}

int index_of(const Face & f, int i) {
    for (int j = 0; j < 3; j++) {
        if (f.index_points[j] == i) {
            return j;
        }
    }
    return -1;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Maillage, SIGNAL(released()), this, SLOT(Maillage()));
    connect(ui->Import_Mesh, SIGNAL(clicked()), this, SLOT(read_OFF()));
    connect(ui->Save_Mesh, SIGNAL(clicked()), this, SLOT(save_OFF()));
    connect(ui->Color, SIGNAL(released()), this, SLOT(color()));
    connect(ui->WireFrame, SIGNAL(clicked()), this, SLOT(wireFrame()));
    ui->WireFrame->setChecked(true);
    ui->Position->setChecked(true);
    connect(ui->Laplacian, SIGNAL(released()), this, SLOT(Compute_Laplacian()));
    connect(ui->Quit, SIGNAL(released()), this, SLOT(quit()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Maillage()
{
    int valeurSpinBox = ui->Sommet->value();
    GLDisplayWidget *glDisplayWidget = ui->maillage;
    glDisplayWidget->_geomWorld.laplacian = false;
    glDisplayWidget->_geomWorld.color = Vector(1,1,0);
    if (valeurSpinBox > glDisplayWidget->_geomWorld._mesh.points.size() + 1)
    {
        std::cout << "Erreur : le nombre de sommets demandé est supérieur au nombre de sommets du maillage" << std::endl;
    }
    else
    {
        glDisplayWidget->_geomWorld.index_sommet = valeurSpinBox - 1;
    }
}

void MainWindow::Compute_Laplacian()
// void laplacian(std::vector<float>& u, GLDisplayWidget *glDisplayWidget)
{
    GLDisplayWidget *glDisplayWidget = ui->maillage;
    glDisplayWidget->_geomWorld.laplacian = true;
    glDisplayWidget->_geomWorld.laplacian_vector = std::vector<float>();
    std::vector<float> u;
    std::vector<float> normal;
    std::vector<float> u2;
    std::vector<float> u3;
    std::vector<float> new_u;
    float value;
    int triangle;
    int time = 9;
    if (ui->Position->isChecked())
    {
        for (int i=0; i<glDisplayWidget->_geomWorld._mesh.points.size(); i++)
        {
            triangle = glDisplayWidget->_geomWorld._mesh.points[i].Face_Index;
            value = norm(cross(glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle],i)+1)%3]] - glDisplayWidget->_geomWorld._mesh.points[i],glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle],i)+2)%3]] - glDisplayWidget->_geomWorld._mesh.points[i] ));
            normal.push_back(value);
            u.push_back(glDisplayWidget->_geomWorld._mesh.points[i].x);
            new_u.push_back(glDisplayWidget->_geomWorld._mesh.points[i].x);
            u2.push_back(glDisplayWidget->_geomWorld._mesh.points[i].y);
            u3.push_back(glDisplayWidget->_geomWorld._mesh.points[i].z);
        }
    }
    else
    {
        u.push_back(200);
        new_u.push_back(200);
        time = 7;
        for (int i=1; i<glDisplayWidget->_geomWorld._mesh.points.size(); i++)
        {
            u.push_back(0);
            new_u.push_back(0);
        }
    }
    while (time <10)
    {
    for (int i=0; i<glDisplayWidget->_geomWorld._mesh.points.size(); i++)
    {
        // std::cout << "sommet : " << i << std::endl;
        // calcul du laplacien
        float alpha_ij,beta_ij,num,den;
        Vector a,b,c;
        float ab,ac,bc,s_p;
        float area = 0;
        float sum = 0;
        float dx = 0;
        float dy = 0;
        float dz = 0;
        int premier_triangle = glDisplayWidget->_geomWorld._mesh.points[i].Face_Index;
        int last_triangle = premier_triangle;
        int triangle_suivant = -1;
        int s;
        while (triangle_suivant != premier_triangle)
        {
            // ajout à la somme
            // computation of the area 
            a = glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[0]];
            b = glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[1]];
            c = glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[2]];
            ab = norm(b-a);
            ac = norm(c-a);
            bc = norm(c-b);
            s_p = (ab + ac + bc) / 2;
            area += sqrt(s_p*(s_p-ab)*(s_p-ac)*(s_p-bc));
            // alpha_ij
            num = dot(glDisplayWidget->_geomWorld._mesh.points[i] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle],i)+1)%3]], glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle],i)+2)%3]] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle],i)+1)%3]]);
            den = norm(cross(glDisplayWidget->_geomWorld._mesh.points[i] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle],i)+1)%3]], glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle],i)+2)%3]] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle],i)+1)%3]]));
            alpha_ij = num/den;
            for (int j = 0; j < 3; j++)
            {
                if (glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[j] == i)
                {
                    s = j+1;
                    break;
                }
            }
            s = s % 3;
            triangle_suivant = glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].adj_f[s];
            num = dot(glDisplayWidget->_geomWorld._mesh.points[i] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant],i)+2)%3]], glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant],i)+1)%3]] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant],i)+2)%3]]);
            den = norm(cross(glDisplayWidget->_geomWorld._mesh.points[i] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant],i)+2)%3]], glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant],i)+1)%3]] - glDisplayWidget->_geomWorld._mesh.points[glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant].index_points[(index_of(glDisplayWidget->_geomWorld._mesh.faces_table[triangle_suivant],i)+2)%3]]));
            beta_ij = num/den;
            int k = glDisplayWidget->_geomWorld._mesh.faces_table[last_triangle].index_points[(s+1)%3];
            if (ui->Position->isChecked())
            {
                dx += (alpha_ij + beta_ij)*(u[k] - u[i]);
                dy += (alpha_ij + beta_ij)*(u2[k] - u2[i]);
                dz += (alpha_ij + beta_ij)*(u3[k] - u3[i]);
            }
            else {
                sum += (alpha_ij + beta_ij)*(u[k] - u[i]);
            }
            
            last_triangle = triangle_suivant;
        }
        if (ui->Position->isChecked())
        {
            dx /= (2 * area);
            dy /= (2 * area);
            dz /= (2 * area);
            sum = norm(Vector(dx,dy,dz));
            sum /= (2*normal[i]);
        }
        if (i!=0 && time <9) {
            new_u[i] = 0.5 * sum / area;
        }
        if (time <9) {
            // u[i] += 0.5 * sum / area;
            if (time ==7) {
                glDisplayWidget->_geomWorld.laplacian_vector.push_back(0.5 * sum / area);
            }
            else {
                glDisplayWidget->_geomWorld.laplacian_vector[i] = 0.5 * sum / area;
            }
        }
        else {
        glDisplayWidget->_geomWorld.laplacian_vector.push_back(0.5 * sum / area);
        }
    }

    // We normalize the laplacian vector
    float max = 0;
    float min = 0;
    // Essayer de maintenir min à 0 et faire norm_float(laplacian_vector)
    for (int i=0; i<glDisplayWidget->_geomWorld._mesh.points.size(); i++)
    {
        u[i] = new_u[i];
        if (norm_float(glDisplayWidget->_geomWorld.laplacian_vector[i]) > max)
        {
            // max = norm_float(glDisplayWidget->_geomWorld.laplacian_vector[i]);
            max = norm_float(glDisplayWidget->_geomWorld.laplacian_vector[i]);
        }
        else if (glDisplayWidget->_geomWorld.laplacian_vector[i] < min)
        {
            min = glDisplayWidget->_geomWorld.laplacian_vector[i];
        }
    }
    for (int i=0; i<glDisplayWidget->_geomWorld._mesh.points.size(); i++)
    {
        glDisplayWidget->_geomWorld.laplacian_vector[i] = (glDisplayWidget->_geomWorld.laplacian_vector[i]) - min / (max - min);
        // glDisplayWidget->_geomWorld.laplacian_vector[i] = (norm_float(glDisplayWidget->_geomWorld.laplacian_vector[i]) - min) / (max - min);
        // std::cout << glDisplayWidget->_geomWorld.laplacian_vector[i] << std::endl;
    }
    time+=1;
    // //call paintGL
    // glDisplayWidget->update();
    // std::this_thread::sleep_for(std::chrono::seconds(1)); // wait 1 second for visualization
    }
}

void MainWindow::read_OFF()
{
    GLDisplayWidget *glDisplayWidget = ui->maillage;
    glDisplayWidget->_geomWorld.laplacian = false;
    glDisplayWidget->_geomWorld.color = Vector(1,1,0);
    std::vector<Vector> points;
    std::vector<Face> faces;
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open OFF file"), "", tr("OFF Files (*.off)"));

    QFile file(fileName);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

QTextStream in(&file);
in.readLine();

int len_p, len_f;
in >> len_p >> len_f;

// Ignorer la fin de la ligne
in.readLine();

points.reserve(len_p);
faces.reserve(len_f);

float x, y, z;
for (int i = 0; i < len_p; i++) {
    in >> x >> y >> z;
    Vector p(x, y, z);
    points.push_back(p);
}

int nbr_face;
for (int i = 0; i < len_f; i++) {
    int i1, i2, i3;
    in >> nbr_face >> i1 >> i2 >> i3;
    Face f(i1, i2, i3);
    faces.push_back(f);
}

Mesh loaded(points, faces);
glDisplayWidget->_geomWorld._mesh = TopologicalMesh(loaded);
}


void MainWindow::save_OFF()
{
    GLDisplayWidget *glDisplayWidget = ui->maillage;
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save OFF file"), "", tr("OFF Files (*.off)"));


    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << "OFF\n";
    out << glDisplayWidget->_geomWorld._mesh.points.size() << " " << glDisplayWidget->_geomWorld._mesh.faces_table.size() << " 0\n";

    // Écriture des coordonnées des sommets
    for (const Vector& vertex : glDisplayWidget->_geomWorld._mesh.points) {
        out << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    // Écriture des faces
    for (const Face& face : glDisplayWidget->_geomWorld._mesh.faces_table) {
        out << "3 " << face.index_points[0] << " " << face.index_points[1] << " " << face.index_points[2] << "\n";
    }
}
file.close();

}

void MainWindow::wireFrame()
{
    if (ui->WireFrame->isChecked())
    {
        GLDisplayWidget *glDisplayWidget = ui->maillage;
        glDisplayWidget->isWireFrame = true;
    }
    else
    {
        GLDisplayWidget *glDisplayWidget = ui->maillage;
        glDisplayWidget->isWireFrame = false;
    }
}


void MainWindow::color()
{
    QColorDialog dialog;
    QColor hexColor = dialog.getColor();

    QString hexString = hexColor.name().mid(1);
    int r = hexColor.red();
    int g = hexColor.green();
    int b = hexColor.blue();

    // Convertir les valeurs RVB en valeurs entre 0 et 1
    float rf = static_cast<float>(r) / 255.0f;
    float gf = static_cast<float>(g) / 255.0f;
    float bf = static_cast<float>(b) / 255.0f;

    GLDisplayWidget *glDisplayWidget = ui->maillage;
    glDisplayWidget->_geomWorld.color = Vector(rf, gf, bf);

}

void MainWindow::quit()
{
    QApplication::quit();
}