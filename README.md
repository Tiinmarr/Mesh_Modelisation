# Mesh_Modelisation

## Initialization

In order to use these files, you have to install [Qt](https://www.qt.io/download) on your computer. 

Personnally, I got the *MSVC-2019* compiler but normally, you can get other one.

Tu run the project, juste open [Mesh_Computational_Geometry.pro](/Mesh_Computational_Geometry/Mesh_Computational_Geometry.pro), then compile (CTRL+b) and execute (CTRL+r) the project.

## Usage

This work come from a BE at Ecole Centrale de Lyon. We worked on the 3D modelisation thanks to triangulated mesh.

In this example, you have a graphical interface where you have both options :

![Graphical interface](/Picture/Graphical_interface.png)


- First you got a simple pyramid mesh. (you can check or not the wireframe)

- By chossing a number and click on "Maillage" you gonna to turn around a vertex of the mesh. All the faces associated to this vertex will be painted in red.

- By clicking on "Import un mesh", you can import a mesh. (Please be sure it's in .off format)

- By clicking on "Sauver un mesh", you can save your mesh under .off format.

- By clicking on "Couleur", you will change the displaying color of the mesh.

Finally, if you want to quit the application, please push the button "Quitter".

Thanks,

## Laplacian :

I added a Laplacian button. (For this, I suggest you to use the "sharp_sphere.off" file, which works very well !)

You can choose to compute the curvature (courbure) of a mesh or the diffsuion of temperature with a source of heat on the vertex 0. (For computing this vertex, put the counter to 1 and click on the button "maillage"n this will display in red the faces around the vertex).

For the Temperature, you could get a result like this : 

![gif](/Picture/temperature_diffusion.gif)

The curvature looks like these pictures which perfectly show the most curved places of the mesh : 

![sphere](/Picture/courbure.png)

![star](/Picture/courbure_star.png)

## Credits

[Raphaëlle Chaine](mailto:raphaelle.chaine@univ-lyon1.fr) lessons in Ecole Centrale de Lyon

