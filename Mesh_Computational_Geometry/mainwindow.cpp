#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mesh.h"
#include "gldisplaywidget.h"

#include <iostream>

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
    if (valeurSpinBox > glDisplayWidget->_geomWorld._mesh.points.size() + 1)
    {
        std::cout << "Erreur : le nombre de sommets demandé est supérieur au nombre de sommets du maillage" << std::endl;
    }
    else
    {
        glDisplayWidget->_geomWorld.index_sommet = valeurSpinBox - 1;
    }
}

void MainWindow::read_OFF()
{
    GLDisplayWidget *glDisplayWidget = ui->maillage;
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