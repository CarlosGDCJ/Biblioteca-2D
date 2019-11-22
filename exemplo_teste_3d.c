#include "cg3d.h"

/*
	Para executar:
	gcc -c cg2d.c
        gcc -c cg3d.c
        gcc exemplo_teste_3d.c -o exemplo_teste_3d cg3d.o cg2d.o -lm
	./exemplo_teste_3d&
        ./view
*/

int main(void) {
 face * f1, * f2, * f3, * f4, * f5;
 object3d * objeto, * ob, * objetoRotX, * obRotX, * objetoRotY, * obRotY, * objetoRotZ, * obRotZ;
 point3d * Normal, * ViewUp, * Observador;
 object * faces, * facesRotX, * facesRotY, * facesRotZ;
 
 palette * palheta;
 bufferdevice * dispositivo;
 window * janela;
 viewport * porta, * porta2, * porta3, * porta4;
 
 float zcp, zpp;
 
 palheta = CreatePalette(6);
 SetColor(0,0,0,palheta);
 SetColor(1,1,1,palheta);
 SetColor(1,1,0,palheta);
 SetColor(1,0,0,palheta);
 SetColor(0,1,0,palheta);
 SetColor(0,0,1,palheta);
 
 f1 = CreateFace(3);
 SetPointFace(10.0,10.0,0.0,5,f1);
 SetPointFace(10.0,0.0,15.0,5,f1);
 SetPointFace(10.0,-10.0,0.0,5,f1);
 
 f2 = CreateFace(3);
 SetPointFace(-10.0,10.0,0.0,5,f2);
 SetPointFace(-10.0,0.0,15.0,5,f2);
 SetPointFace(-10.0,-10.0,0.0,5,f2);
 
 f3 = CreateFace(4);
 SetPointFace(10.0,10.0,0.0,3,f3);
 SetPointFace(10.0,0.0,15.0,3,f3);
 SetPointFace(-10.0,0.0,15.0,3,f3);
 SetPointFace(-10.0,10.0,0.0,3,f3); 

 f4 = CreateFace(4);
 SetPointFace(10.0,0.0,15.0,4,f4);
 SetPointFace(10.0,-10.0,0.0,4,f4);
 SetPointFace(-10.0,-10.0,0.0,4,f4);
 SetPointFace(-10.0,0.0,15.0,4,f4); 

 f5 = CreateFace(4);
 SetPointFace(10.0,10.0,0.0,5,f5);
 SetPointFace(10.0,-10.0,0.0,5,f5);
 SetPointFace(-10.0,-10.0,0.0,5,f5);
 SetPointFace(-10.0,10.0,0.0,5,f5);
 
 objeto = CreateObject3D(5);
 SetObject3D(f1,objeto);
 SetObject3D(f2,objeto);
 SetObject3D(f3,objeto);
 SetObject3D(f4,objeto);
 SetObject3D(f5,objeto);

 Normal = SetNormal(-1, 0, 0);
 ViewUp = SetViewUp(0, 1, 0);
 Observador = SetObserver(0, 0, 0);
 
 ob = ConvertObjectBase(Normal,ViewUp,Observador,objeto);
 
 //faces = ParalProjFaces(ob);
 zpp = 0.0;
 zcp = -60.0;
 faces = PerspProjFaces(ob,zpp,zcp);

 janela = CreateWindow(-30,-30,30,30);
 dispositivo = CreateBuffer(640,480);
 porta = CreateViewPort(0, 0, 319, 239);
 
 DrawObject(&faces[0],janela,porta,dispositivo,5);
 DrawObject(&faces[1],janela,porta,dispositivo,5);
 DrawObject(&faces[2],janela,porta,dispositivo,3);
 DrawObject(&faces[3],janela,porta,dispositivo,5);
 DrawObject(&faces[4],janela,porta,dispositivo,5);

// Rotação de 90 graus no eixo X (viewport inferior esquerda)
 objetoRotX = TransObj3d(ob, Set3DRotXMatrix(90));

 obRotX = ConvertObjectBase(Normal, ViewUp, Observador, objetoRotX);

 zpp = 0.0;
 zcp = -60.0;
 facesRotX = PerspProjFaces(obRotX,zpp,zcp);

 porta2 = CreateViewPort(320, 0, 639, 239);

 DrawObject(&facesRotX[0],janela,porta2,dispositivo,5);
 DrawObject(&facesRotX[1],janela,porta2,dispositivo,5);
 DrawObject(&facesRotX[2],janela,porta2,dispositivo,3);
 DrawObject(&facesRotX[3],janela,porta2,dispositivo,5);
 DrawObject(&facesRotX[4],janela,porta2,dispositivo,5);

// Rotação de 90 graus no eixo Y (viewport superior direita)
 objetoRotY = TransObj3d(ob, Set3DRotYMatrix(90));

 obRotY = ConvertObjectBase(Normal, ViewUp, Observador, objetoRotY);

 zpp = 0.0;
 zcp = -60.0;
 facesRotY = PerspProjFaces(obRotY,zpp,zcp);

 porta3 = CreateViewPort(0, 240, 319, 479);

 DrawObject(&facesRotY[0],janela,porta3,dispositivo,5);
 DrawObject(&facesRotY[1],janela,porta3,dispositivo,5);
 DrawObject(&facesRotY[2],janela,porta3,dispositivo,3);
 DrawObject(&facesRotY[3],janela,porta3,dispositivo,5);
 DrawObject(&facesRotY[4],janela,porta3,dispositivo,5);

// Rotação de 90 graus no eixo Z (viewport inferior direita)
 objetoRotZ = TransObj3d(ob, Set3DRotZMatrix(90));

 obRotZ = ConvertObjectBase(Normal, ViewUp, Observador, objetoRotZ);

 zpp = 0.0;
 zcp = -60.0;
 facesRotZ = PerspProjFaces(obRotZ,zpp,zcp);

 porta4 = CreateViewPort(320, 240, 639, 479);

 DrawObject(&facesRotZ[0],janela,porta4,dispositivo,5);
 DrawObject(&facesRotZ[1],janela,porta4,dispositivo,5);
 DrawObject(&facesRotZ[2],janela,porta4,dispositivo,3);
 DrawObject(&facesRotZ[3],janela,porta4,dispositivo,5);
 DrawObject(&facesRotZ[4],janela,porta4,dispositivo,5);

 Dump2PIPE(dispositivo,palheta);

 return 0; 
 }

