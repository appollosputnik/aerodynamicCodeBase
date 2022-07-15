# aerodynamicCodeBase
This is an Aerocode base platform to exploit Aero activities with open source tools.

1.  We have an Aerofoil shape optimization tool, by name 'aerodynamics.xlsx'
2.  This Excel sheet calculate and can generate an Aerofoil or a 2D wing by specifying camber and thickness.
3.  And a code, Qt code, you can load this code in Qt Creator to draw any 3D surfaces.
4.  We have full set of Aerodynamic-CFD code in this  STRUCTURED AND UNSTRUCTURED PDE MAPPED GRID, and some a number of Solver. More details will be provided 
    as we progress over the period of time. 
5.  I am also writing a good quality manual so that you can play around with it.




# Build Instructions.
1. Load the .pro file into Qt Creator studio.
2. And just Build. and run.
3. It is so far a pure Qt code you can build without any much problem.


Dated: 13/07/2022
1.  Now it draws an airfoil inside the bounding box and witin control points of a bezier curve.
2.  Just goto to airfoil section tab and you will see the bounding box drew by default. The tutorial parameters as follows
    a. chord = 1 m    //In normalized form
    b. camber = 0.07 // in percent of chord.
    c. max thickness = 0.3 // in percent of chord.
    d. Equation order = 2; // if number of control points = 3 and then order = 2. The control points as follows (0,0), (30,22), (100,0) for upper surfaces.
				   // lly for lower surfaces 3 control points taken into consideration if not read from file.
				   // (0,0), (30,-8), (100,0)
                           // This middles points (30,22) or (30,-8) are coming from camber consideration which is given as 0.07 or 7%c.
    e. number of knots = 10 //
3. Finally click on apply button to draw the bezier airfoil...


Date: 14/07/2022
1.  Now do the process of yesterday and you will see more refined and smoothened curve airfoil and convex hull of the anchors.

Date: 15/07/2022
1.  A new tab added for Aerodynamic real time curve and ploting.
2.  This curve will require you to press a 'start' button and play the evolution. Finally it runs on exploration basis. so that the population of CL data points   
    against alpha value be generated. Only real time is shown here, but not exactly full featured CL~Alpha is drawn so far. It's under progress of calculation.
