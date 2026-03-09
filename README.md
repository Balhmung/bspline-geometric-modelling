# B-Spline Geometric Modelling Framework 🧮

[![University Project](https://img.shields.io/badge/Project-Cranfield_University-blue.svg)](https://www.cranfield.ac.uk/)
[![C++](https://img.shields.io/badge/Language-C++-00599C.svg)](https://isocpp.org/)


This repository contains a comprehensive **C++ computational framework** for reconstructing smooth geometric curves and free-form surfaces from discrete sets of 3D data points. It implements core CAD (Computer-Aided Design) algorithms for B-spline approximation and interpolation, addressing key geometric fairness, parameterization, and numerical stability challenges.

---

## 🎯 Project Overview & Objectives

In computational engineering and Computer-Aided Geometric Design (CAGD), representing and reconstructing geometry from digitized data is a fundamental challenge. This project solves two core problems evaluated in standard engineering workflows:

1. **Cubic B-spline Curve Interpolation:** Creating smooth, continuous $C^2$ bounded curves over planar 2D/3D datasets. The framework compares three parameterisation methodologies (Uniform, Chord Length, and Centripetal) and explores their effect on curvature distribution and mitigation of oscillations in irregularly sampled geometries.
2. **Tensor-Product Bi-cubic B-spline Surface Construction:** Generating robust 3D parameter-driven approximation surfaces from structured $N \times M$ grids of data points using a separable two-stage approximation algorithm.

### Visualization: Surface Reconstruction
*Example generation over Dataset 1 (10×10 target segments):*

| Control Point Grid | Surface Segmentation & Curvature | Generated Smooth B-Spline Surface |
| :---: | :---: | :---: |
| <img src="../GeometricModellingB_Image/1_10BSplineSurfControlPoint.png" width="250" alt="Control Point Grid"> | <img src="../GeometricModellingB_Image/1_10BSplineSurfSegmentation.png" width="250" alt="Surface Segmentation Analysis"> | <img src="../GeometricModellingB_Image/1_10BSplineSurf.png" width="250" alt="Generated B-Spline Surface"> |

---

## 🚀 Key Technical Features

### Mathematical Abstractions & Interpolation Methods
*   **Parameterisation Strategies:** Supports uniform, chord-length, and centripetal parameterization techniques to handle highly non-uniform data sampling accurately.
*   **Knot Vector Construction:** Employs optimal interior knot distribution using the averaging method and open (clamped) knot constraints for guaranteed endpoint interpolation.
*   **Cox-de Boor Recursion:** Exact numeric calculation of basis functions.

### Separable Two-Stage Surface Approximation
Instead of adopting an expensive full 2D interpolation system matrix, the project employs an efficient tensor-product separable strategy:
1.  **Row-wise Phase ($v$-direction):** Computes intermediate cubic B-spline approximations for each data row.
2.  **Column-wise Phase ($u$-direction):** Generates the final multi-dimensional control net by performing spline calculations downwards on the intermediate rows.

### Error Analysis & Validation
Quantitative evaluation components ensure that generated geometries accurately mirror underlying structural grids:
*   `computeLSQError`: Calculates the objective Least Squares error metric between the original dataset and point projections.
*   `computeAVError` / `computeMAXError`: Computes the absolute average and local maximum deviations, essential for defining bounds on engineering tolerances.

---

## 📂 Architecture and Code Structure

The implementation employs modular object-oriented C++ classes supporting vector math and algorithmic abstractions. Below is the UML class diagram for the tensor-product B-spline surface construction framework:

<div align="center">
  <img src="../../UMLPartB.png" alt="UML Class Diagram for Part B" width="600">
</div>

*   **`BsplineCurve` / `BsplineSurf`**: Defines the foundational cubic and bi-cubic geometry evaluations. Inherits from abstract topologies (`AbsCurve`, `AbsSurface`).
*   **`BsplineCdata` (Curve Data)**: Aggregates curve datasets, processes parameterizations, and invokes linear solvers for interpolation control point calculations.
*   **`BsplineSdata` (Surface Data)**: Manages surface structured data grids and drives the separable two-stage generation process mapped across $u$ and $v$ parametric configurations.
*   **Mathematics Underpinnings**: Foundational operators via `point.h`, `vector.h`, `matrix.h`, and `linearSolve.h` using self-contained direct Gaussian algorithms.

---

## 💻 Building and Execution

The repository bundles a native Microsoft Visual Studio execution context to quickly evaluate sample databanks.

1.  Open `GeometricModelling_Assignement_B.sln` using Visual Studio. 
2.  Set the build target architecture (e.g., `x64`).
3.  Ensure data samples (like `datapoints4.dat`) reside natively within the working directory for parsing.
4.  Run the application!

### Example Interactive Flow

The target execution program reads spatial data and accepts configuration parameters for surface fidelity:
```text
Enter the number of segments in u: 10
Enter the number of segments in v: 10
Enter the order in u: 4
Enter the order in v: 4
The least squares error is: 0.1423
```
After executing, the framework outputs serialised generated surfaces via IGES format interfaces or flattened parameterized points to `.dat` models ready for CAD visualisation (e.g., Onshape, SolidWorks).
