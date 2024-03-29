#include "cg3d.h"

point3d * VectorProduct3d(point3d * u, point3d * v) {
 point3d * w;
 w = (point3d *) malloc(sizeof(point3d));
 
/* 
 i  j  k
 u1 u2 u3       u2v3i + u3v1j + u1v2k - u2v1k - u3v2i - u1v3j = (u2v3 - u3v2)i + (u3v1 - u1v3)j + (u1v2 - u2v1)k 
 v1 v2 v3
 */ 

 w->x = (u->y)*(v->z) - (u->z)*(v->y);
 w->y = (u->z)*(v->x) - (u->x)*(v->z);
 w->z = (u->x)*(v->y) - (u->y)*(v->x);

 w->w = 1;
 
 w->color = 1;
 
 return w;
 }
 
float Modulo3d(point3d * u) {
 return (sqrt(((u->x)*(u->x))+((u->y)*(u->y))+((u->z)*(u->z))));
 }

point3d * Versor3d(point3d * u) {
 point3d * w;
 float modulo = Modulo3d(u);
 w = (point3d *) malloc(sizeof(point3d));

 w->x = (u->x) / modulo;
 w->y = (u->y) / modulo; 
 w->z = (u->z) / modulo;

 w->w = 1;
 
 w->color = 1;
 
 return w;
 }
 
face * CreateFace(int numbers_of_points) {
  face * fob;
 
  fob = (face *) malloc(sizeof(face));
  fob->numbers_of_points = 0;
  fob->points = (point3d *) malloc(numbers_of_points*sizeof(point3d));
 
  return fob;
  }

point3d * SetPointFace(float x, float y, float z, int color, face * fc) {
  point3d * pnt;

  pnt = (point3d *) malloc(sizeof(point3d));
  pnt->x = x;
  pnt->y = y;
  pnt->z = z;
  pnt->w = 1.0;
  pnt->color = color;
  fc->points[fc->numbers_of_points] = *pnt;
  fc->numbers_of_points = fc->numbers_of_points + 1;

  return pnt;
  }

point3d * SetNormal(float x, float y, float z) {
  point3d * w;

  w = (point3d *) malloc(sizeof(point3d));
  w->x = x;
  w->y = y;
  w->z = z;
  w->w = 1;

  w = Versor3d(w);

  return w;
  }

point3d * SetViewUp(float x, float y, float z) {
  point3d * vu;

  vu = (point3d *) malloc(sizeof(point3d));
  vu->x = x;
  vu->y = y;
  vu->z = z;
  vu->w = 1;

  vu = Versor3d(vu);

  return vu;
  }

point3d * SetObserver(float x, float y, float z) {
  point3d * ov;

  ov = (point3d *) malloc(sizeof(point3d));
  ov->x = x;
  ov->y = y;
  ov->z = z;
  ov->w = 1;

  return ov;
  }

object3d * CreateObject3D(int numbers_of_faces) {
  object3d * ob;
 
  ob = (object3d *) malloc(sizeof(object3d));
  ob->numbers_of_faces = 0;
  ob->faces = (face *) malloc(numbers_of_faces*sizeof(face));
 
  return ob;
  }

int SetObject3D(face * fc, object3d * ob) {
  ob->faces[ob->numbers_of_faces] = *fc;
  ob->numbers_of_faces = ob->numbers_of_faces + 1;

  return 0;
  }

point3d * LinearTransf3d(matrix3d * W, point3d * u) {
 point3d * p;
  
 p = (point3d *) malloc(sizeof(point3d));
// Descomente para printar os valores das operações
 p->x = W->a11*u->x + W->a12*u->y + W->a13*u->z + W->a14*u->w;
//  printf("X = %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f = %0.3f \n", W->a11, u->x, W->a12, u->y, W->a13, u->z, W->a14, u->w, p->x);
 p->y = W->a21*u->x + W->a22*u->y + W->a23*u->z + W->a24*u->w;
//  printf("Y = %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f = %0.3f \n", W->a21, u->x, W->a22, u->y, W->a23, u->z, W->a24, u->w, p->y);
 p->z = W->a31*u->x + W->a32*u->y + W->a33*u->z + W->a34*u->w;
//  printf("Z = %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f = %0.3f \n", W->a31, u->x, W->a32, u->y, W->a33, u->z, W->a34, u->w, p->z);
 p->w = W->a41*u->x + W->a42*u->y + W->a43*u->z + W->a44*u->w;
//  printf("W = %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f + %0.3f * %0.3f = %0.3f \n", W->a41, u->x, W->a42, u->y, W->a43, u->z, W->a44, u->w, p->w);
 p->color = u->color;
  
 return p;  
 }

object3d * ConvertObjectBase(point3d * w, point3d * vu, point3d * ov, object3d * ob) {
 matrix3d * H;
 object3d * mob;
 point3d * p0, * p1, * u, * v;
 int numbers_of_points, numbers_of_faces;

 u = VectorProduct3d(vu,w);
 u = Versor3d(u);
 v = VectorProduct3d(u,w);

 H = (matrix3d *) malloc(sizeof(matrix3d));
 H->a11 = u->x; H->a12 = u->y; H->a13 = u->z; H->a14 = ov->x;
 H->a21 = v->x; H->a22 = v->y; H->a23 = v->z; H->a24 = ov->y;
 H->a31 = w->x; H->a32 = w->y; H->a33 = w->z; H->a34 = ov->z;
 H->a41 = 0;    H->a42 = 0;    H->a43 = 0;    H->a44 = 1;
  
 p0 = (point3d *) malloc(sizeof(point3d));
 p1 = (point3d *) malloc(sizeof(point3d));
 
 mob = (object3d *) malloc(sizeof(object3d));
 mob->numbers_of_faces = ob->numbers_of_faces;
 mob->faces = (face *) malloc(ob->numbers_of_faces*sizeof(face));
 
 for(numbers_of_faces=0;numbers_of_faces<ob->numbers_of_faces;numbers_of_faces++) {
   mob->faces[numbers_of_faces].numbers_of_points = ob->faces[numbers_of_faces].numbers_of_points;
   mob->faces[numbers_of_faces].points = (point3d *) malloc(ob->faces[numbers_of_faces].numbers_of_points*sizeof(point3d));
   for(numbers_of_points=0;numbers_of_points<ob->faces[numbers_of_faces].numbers_of_points;numbers_of_points++) {
     p0->x = ob->faces[numbers_of_faces].points[numbers_of_points].x;
     p0->y = ob->faces[numbers_of_faces].points[numbers_of_points].y;
     p0->z = ob->faces[numbers_of_faces].points[numbers_of_points].z;
     p0->w = ob->faces[numbers_of_faces].points[numbers_of_points].w;
     p0->color = ob->faces[numbers_of_faces].points[numbers_of_points].color;
     p1 = LinearTransf3d(H,p0);
     mob->faces[numbers_of_faces].points[numbers_of_points].x = p1->x;    
     mob->faces[numbers_of_faces].points[numbers_of_points].y = p1->y; 
     mob->faces[numbers_of_faces].points[numbers_of_points].z = p1->z;
     mob->faces[numbers_of_faces].points[numbers_of_points].w = p1->w;
     mob->faces[numbers_of_faces].points[numbers_of_points].color = p1->color;
     }
   } 

 return mob; 
 }
 
object * ParalProjFaces(object3d * ob3d) {
 object * facelist;
 int numbers_of_points, numbers_of_faces;
 
 facelist = (object *) malloc(ob3d->numbers_of_faces*sizeof(object));
 for(numbers_of_faces=0;numbers_of_faces<ob3d->numbers_of_faces;numbers_of_faces++) {
   facelist[numbers_of_faces].numbers_of_points = ob3d->faces[numbers_of_faces].numbers_of_points;
   facelist[numbers_of_faces].points = (point *) malloc(facelist[numbers_of_faces].numbers_of_points*sizeof(point));
   for(numbers_of_points=0;numbers_of_points<ob3d->faces[numbers_of_faces].numbers_of_points;numbers_of_points++) {
     facelist[numbers_of_faces].points[numbers_of_points].x = ob3d->faces[numbers_of_faces].points[numbers_of_points].x;
     facelist[numbers_of_faces].points[numbers_of_points].y = ob3d->faces[numbers_of_faces].points[numbers_of_points].y;
     facelist[numbers_of_faces].points[numbers_of_points].w = 1;
     facelist[numbers_of_faces].points[numbers_of_points].color = ob3d->faces[numbers_of_faces].points[numbers_of_points].color;      
     }
   }
 
 return facelist;
 }

object * PerspProjFaces(object3d * ob3d, float zpp, float zcp) {
 object * facelist;
 int numbers_of_points, numbers_of_faces;
 
 facelist = (object *) malloc(ob3d->numbers_of_faces*sizeof(object));
 for(numbers_of_faces=0;numbers_of_faces<ob3d->numbers_of_faces;numbers_of_faces++) {
   facelist[numbers_of_faces].numbers_of_points = ob3d->faces[numbers_of_faces].numbers_of_points;
   facelist[numbers_of_faces].points = (point *) malloc(facelist[numbers_of_faces].numbers_of_points*sizeof(point));
   for(numbers_of_points=0;numbers_of_points<ob3d->faces[numbers_of_faces].numbers_of_points;numbers_of_points++) {
     facelist[numbers_of_faces].points[numbers_of_points].x = ((ob3d->faces[numbers_of_faces].points[numbers_of_points].x)*(zpp-zcp))/(ob3d->faces[numbers_of_faces].points[numbers_of_points].z-zcp);
     facelist[numbers_of_faces].points[numbers_of_points].y = ((ob3d->faces[numbers_of_faces].points[numbers_of_points].y)*(zpp-zcp))/(ob3d->faces[numbers_of_faces].points[numbers_of_points].z-zcp);
     facelist[numbers_of_faces].points[numbers_of_points].w = 1;
     facelist[numbers_of_faces].points[numbers_of_points].color = ob3d->faces[numbers_of_faces].points[numbers_of_points].color;      
     }
   }
 
 return facelist;  
 }

 matrix3d * Set3DRotZMatrix(float theta) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  
  m->a11 = cos((theta*M_PI)/180.0); 
  m->a12 = (-1.0)*sin((theta*M_PI)/180.0);
  m->a13 = 0.0;
  m->a14 = 0.0;

  m->a21 = sin((theta*M_PI)/180.0);
  m->a22 = cos((theta*M_PI)/180.0);
  m->a23 = 0.0;
  m->a24 = 0.0;


  m->a31 = 0.0;
  m->a32 = 0.0;
  m->a33 = 1.0;
  m->a34 = 0.0;

  m->a41 = 0.0;
  m->a42 = 0.0;
  m->a43 = 0.0;
  m->a44 = 1.0;

  
  return m;
  }

  matrix3d * Set3DRotXMatrix(float theta) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  
  m->a11 = 1.0; 
  m->a12 = 0.0;
  m->a13 = 0.0;
  m->a14 = 0.0;

  m->a21 = 0.0;
  m->a22 = cos((theta*M_PI)/180.0);
  m->a23 = (-1.0)*sin((theta*M_PI)/180.0);
  m->a24 = 0.0;


  m->a31 = 0.0;
  m->a32 = sin((theta*M_PI)/180.0);
  m->a33 = cos((theta*M_PI)/180.0);
  m->a34 = 0.0;

  m->a41 = 0.0;
  m->a42 = 0.0;
  m->a43 = 0.0;
  m->a44 = 1.0;

  
  return m;
  }

  matrix3d * Set3DRotYMatrix(float theta) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  
  m->a11 = cos((theta*M_PI)/180.0); 
  m->a12 = 0.0;
  m->a13 = sin((theta*M_PI)/180.0);
  m->a14 = 0.0;

  m->a21 = 0.0;
  m->a22 = 1.0;
  m->a23 = 0.0;
  m->a24 = 0.0;


  m->a31 = (-1.0)*sin((theta*M_PI)/180.0);
  m->a32 = 0.0;
  m->a33 = cos((theta*M_PI)/180.0);
  m->a34 = 0.0;

  m->a41 = 0.0;
  m->a42 = 0.0;
  m->a43 = 0.0;
  m->a44 = 1.0;

  
  return m;
  }

  matrix3d * SetProjPersMatrix(float Zup, float Zcp) {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  
  m->a11 = 1.0;
  m->a12 = 0.0;
  m->a13 = 0.0;
  m->a14 = 0.0;

  m->a21 = 0.0;
  m->a22 = 1.0;
  m->a23 = 0.0;
  m->a24 = 0.0;


  m->a31 = 0.0;
  m->a32 = 0.0;
  m->a33 = Zup/(Zup-Zcp);
  m->a34 = (-1)*(Zup*Zcp)/(Zup-Zcp);

  m->a41 = 0.0;
  m->a42 = 0.0;
  m->a43 = 1.0/(Zup-Zcp);
  m->a44 = (-1)*Zcp/(Zup-Zcp);

  
  return m;
  }

  matrix3d * SetProjParaMatrix() {
  matrix3d * m;

  m = (matrix3d *) malloc(sizeof(matrix3d));
  
  m->a11 = 1.0;
  m->a12 = 0.0;
  m->a13 = 0.0;
  m->a14 = 0.0;

  m->a21 = 0.0;
  m->a22 = 1.0;
  m->a23 = 0.0;
  m->a24 = 0.0;


  m->a31 = 0.0;
  m->a32 = 0.0;
  m->a33 = 0.0;
  m->a34 = 0.0;

  m->a41 = 0.0;
  m->a42 = 0.0;
  m->a43 = 0.0;
  m->a44 = 1.0;

  
  return m;
  }
 
object3d * TransObj3d(object3d * ob, matrix3d * m) {
  int i, j;
  object3d * obj;
  point3d * pt;
  face * teste;

  //Descomente abaixo para ver o funcionamento
  obj = CreateObject3D(ob->numbers_of_faces);
  // printf("Numero de faces: %d\n", ob->numbers_of_faces);
  for(i=0;i<ob->numbers_of_faces;i++) {
    obj->faces[i] = *(CreateFace(ob->faces[i].numbers_of_points));
    // printf("\tNumero de pontos na face %d: %d\n", i, ob->faces[i].numbers_of_points);
    for(j=0; j < ob->faces[i].numbers_of_points; j++){
      // printf("\t\tPonto %d \n", j);
      // printf("\t\t\tCoordenada X: %f \n \t\t\tCoordenada Y: %f \n \t\t\tCoordenada Z: %f \n \t\t\tCoordenada W: %f \n", ob->faces[i].points[j].x, ob->faces[i].points[j].y, ob->faces[i].points[j].z, ob->faces[i].points[j].w);
      pt = LinearTransf3d(m,&(ob->faces[i].points[j]));
      SetPointFace(pt->x, pt->y, pt->z, pt->color, &(obj->faces[i]));
      // printf("\t\t\tNovo X: %f \n \t\t\tNovo Y: %f \n \t\t\tNovo Z: %f \n \t\t\tNovo W: %f \n", obj->faces[i].points[j].x, obj->faces[i].points[j].y, obj->faces[i].points[j].z, obj->faces[i].points[j].w);
      }
    SetObject3D(&(obj->faces[i]),obj);
    }

  return obj;
  }