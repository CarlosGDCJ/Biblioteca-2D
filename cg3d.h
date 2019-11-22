#include "cg2d.h"

typedef struct HPoint3D {
  float x,
        y,
	z,
	w;
  int   color;
  } point3d;
      
typedef struct Face {
  int numbers_of_points;
  point3d * points;
  } face;
  
typedef struct Object3D {
  int numbers_of_faces;
  face * faces;
  } object3d;

typedef struct HMatrix3D {
  float a11, a12, a13, a14,
        a21, a22, a23, a24,
        a31, a32, a33, a34,
	      a41, a42, a43, a44;
        } matrix3d;

point3d * VectorProduct3d(point3d *, point3d *);
float Modulo3d(point3d *);
point3d * Versor3d(point3d *);
face * CreateFace(int);
point3d * SetPointFace(float, float, float, int, face *);
point3d * SetNormal(float,float,float);
point3d * SetViewUp(float,float,float);
point3d * SetObserver(float,float,float);
object3d * CreateObject3D(int);
int SetObject3D(face *, object3d *);
point3d * LinearTransf3d(matrix3d *, point3d *);
object3d * ConvertObjectBase(point3d *, point3d *, point3d *, object3d *);
object * ParalProjFaces(object3d *);
object * PerspProjFaces(object3d *, float, float);
object3d * TransObj3d(object3d * ob, matrix3d * m);

matrix3d * Set3DRotXMatrix(float theta);
matrix3d * Set3DRotYMatrix(float theta);
matrix3d * Set3DRotZMatrix(float theta);

