

#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <corecrt_math.h>


double f(double p1, double p2, double p3, double p4, double t)
{
	double temp = 1 - t;
	return pow(temp, 3) * p1 + 3 * t * pow(temp, 2) * p2 + 3 * t * t * temp * p3 + pow(t, 3) * p4; //посчитанная формула
}


double kas(double p1, double p2, double p3, double p4, double t) {

	
	return -3 * p1 + 6 * p1 * t - 3 * p1 * t * t + 3 * p2 + 12 * p2 * t + 9 * p2 * t * t + 6 * p3 * t * t - 9 * p3 * t * t + 3 * p4 * t * t;
}


//double length3d(double a1, double b1, double c1, double a2, double b2, double c2)
//{
//	double res;
//	res = sqrt(((a2 - a1) * (a2 - a1)) + ((b2 - b1) * (b2 - b1)) + ((c2 - c1) * (c2 - c1)));
//	return res;
//}

//double normalize(double a1, double b1, double c1, int num)
//{
//	double locLength = length3d(0, 0, 0, a1, b1, c1);
//	double inv_length = (1 / locLength);
//	double x = x * inv_length;
//	double y = y * inv_length;
//	double z = z * inv_length;
//	if (num == 0) return a1;
//	else if (num == 1) return b1;
//	else if (num == 2) return c1;
//}

void figure()
{
	double A[] = { 0, 0, -2 };
	double B[] = { -1.52, 0.3, 0 };
	double C[] = { -0.18, 1.62, 0 };
	double D[] = { 1.5,0.74, 0 };
	double E[] = { 1.2,-1.1, 0 };
	double F[] = { -0.68,-1.38, 0 };

	double G[] = {-0.96,0.2,1};
	double H[] = {-0.09,1.04,1};
	double I[] = {0.97,0.48,1};
	double J[] = {0.77,-0.69,1};
	double K[] = {-0.42,-0.88,1};
	double L[] = { 0,0,1 };
	

	
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(0.45, 0.99, 0.84, 0.2);
	glVertex3dv(A);
	glVertex3dv(B);
	glVertex3dv(C);
	glVertex3dv(D);
	glVertex3dv(E);
	glVertex3dv(F);
	glVertex3dv(B);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3dv(L);
	glVertex3dv(G);
	glVertex3dv(H);
	glVertex3dv(I);
	glVertex3dv(J);
	glVertex3dv(K);
	glVertex3dv(G);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex3dv(B);
	glVertex3dv(G);
	glVertex3dv(C);
	glVertex3dv(H);
	glVertex3dv(D);
	glVertex3dv(I);
	glVertex3dv(E);
	glVertex3dv(J);
	glVertex3dv(F);
	glVertex3dv(K);
	glVertex3dv(B);
	glVertex3dv(G);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3d(0, 0, 0);
	glVertex3dv(A);
	glVertex3dv(B);

	glVertex3dv(A);
	glVertex3dv(C);

	glVertex3dv(A);
	glVertex3dv(D);

	glVertex3dv(A);
	glVertex3dv(E);

	glVertex3dv(A);
	glVertex3dv(F);

	glVertex3dv(B);
	glVertex3dv(C);

	glVertex3dv(C);
	glVertex3dv(D);

	glVertex3dv(D);
	glVertex3dv(E);

	glVertex3dv(E);
	glVertex3dv(F);

	glVertex3dv(F);
	glVertex3dv(B);

	glVertex3dv(G);
	glVertex3dv(B);

	glVertex3dv(C);
	glVertex3dv(H);

	glVertex3dv(I);
	glVertex3dv(D);

	glVertex3dv(E);
	glVertex3dv(J);

	glVertex3dv(K);
	glVertex3dv(F);

	glVertex3dv(K);
	glVertex3dv(G);
	glVertex3dv(H);
	glVertex3dv(I);
	glVertex3dv(J);
	glVertex3dv(K);
	glVertex3dv(G);
	glEnd();

}

double Ermit(double p1, double p4, double r1, double r4, double t)
{
	double t3 = pow(t, 3);
	double t2 = pow(t, 2);
	double res =p1*(2*t3-3*t2+1)+p4*((-2)*t3+3*t2)+r1*(t3-2*t2+t)+r4*(t3-t2) ;
	return res;
}

double angle(double a1, double b1, double c1, double a2, double b2, double c2 )
{
	double scal = a1 * a2 + b1 * b2 + c1 * c2;
	double mod = sqrt(pow(a1,2)+ pow(b1, 2) + pow(c1, 2) ) * sqrt(pow(a2, 2) + pow(b2, 2) + pow(c2, 2) );
	double cosA = scal / mod;
	return acos(cosA) * 180 / 3.14;
}

double fact(double n)
{
	int res = 1;
	for (int i = 1; i <= n; i+=1)
	{
		res = res * i;
	}
	return res;
}

double B(double i, double u)
{
	return (fact(3) / (fact(i) * fact(3 - i))) * pow(u, i) * pow(1 - u, 3 - i);
}

double surface(double P16[4][4][3], double u,double v,int num)
{
	double res = 0;
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			res += B(i, u) * B(j, v) * P16[i][j][num];
		}
	}
	return res;
}

double t_max = 0;
bool flag = 0;
void Render(double delta_time)
{
	if (flag == 0) t_max += delta_time / 5;
		if (t_max>1) flag = 1;
	
	if (flag == 1) t_max -= delta_time / 5;
		if (t_max<0)flag = 0;
	
	//t_max += delta_time / 10; //t_max становится = 1 за 5 секунд
	//if (t_max > 1) t_max = 0; //после обнуляется

	
	double P1[] = { 0,0,0 }; //Наши точки
	double P2[] = { 1,0,7 };
	double P3[] = { 4,0,3 };
	double P4[] = { 10,0,5 };

	double P5[] = { 0,0,0 }; //Наши точки
	double P6[] = { -1,0,7 };
	double P7[] = { -4,0,3 };
	double P8[] = { -10,0,1 };
	double R1[3];
	double R2[3];
	for (int score = 0; score < 3; score++)
	{
		R1[score] = P6[score] - P5[score];
		R2[score] = P8[score] - P7[score];
	}
	double Ppp[3];
	glPointSize(7);
	glBegin(GL_POINTS);
	glColor3d(0,0.76,0.1);
	glVertex3dv(P5);
	glVertex3dv(P7);
	glEnd();
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3d(0,0,0);
	glVertex3dv(P5);
	glVertex3dv(P6);
	glVertex3dv(P7);
	glVertex3dv(P8);
	glEnd();
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3d(0, 0.3, 0.76);
	for (double t = 0; t <= 1.0001; t += 0.01)							//t <= t_max;
	{
		Ppp[0] = Ermit(P5[0], P7[0], R1[0], R2[0], t);
		Ppp[1] = Ermit(P5[1], P7[1], R1[1], R2[1], t);
		Ppp[2] = Ermit(P5[2], P7[2], R1[2], R2[2], t);
		glVertex3dv(Ppp); //Рисуем точку P
	}
	glEnd();
	double P9[] = { 0,0,0 }; //Наши точки
	double P10[] = { -2,2,3 };
	double P11[] = { -3,2,5 };
	double P12[] = { -7,2,1 };
	double R3[3];
	double R4[3];
	for (int score = 0; score < 3; score++)
	{
		R3[score] = P10[score] - P9[score];
		R4[score] = P12[score] - P11[score];
	}
	glPointSize(7);
	glBegin(GL_POINTS);
	glColor3d(0, 0.76, 0.1);
	glVertex3dv(P9);
	glVertex3dv(P11);
	glEnd();
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3d(0, 0, 0);
	glVertex3dv(P9);
	glVertex3dv(P10);
	glVertex3dv(P11);
	glVertex3dv(P12);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3d(0, 0.3, 0.76);
	for (double t = 0; t <= 1.0001; t += 0.01)							//t <= t_max;
	{
		Ppp[0] = Ermit(P9[0], P11[0], R3[0], R4[0], t);
		Ppp[1] = Ermit(P9[1], P11[1], R3[1], R4[1], t);
		Ppp[2] = Ermit(P9[2], P11[2], R3[2], R4[2], t);
		glVertex3dv(Ppp); //Рисуем точку P
	}
	glEnd();
	glLineWidth(1);


	double P16[4][4][3] = {
		{{0,9,1}, {3,9,0}, {6,9,0}, {9,9,1}},
		{{0,6,0}, {3,6,4}, {6,6,4}, {9,6,0}},
		{{0,3,0}, {3,3,4}, {6,3,4}, {9,3,0}},
		{{0,0,1}, {3,0,0}, {6,0,0}, {9,0,1}},
	};
	glColor3d(0, 0, 1);


	double Pp[3];
	glPointSize(4);
	glBegin(GL_POINTS);
	double u = 0;
	double v = 0;
	for ( u = 0; u <=1; u+=0.1)
	{
		for ( v = 0; v <= 1; v += 0.1)
		{
			Pp[0] = surface(P16,u,v,0);
			Pp[1] = surface(P16, u, v, 1);
			Pp[2] = surface(P16, u, v, 2);
			glVertex3dv(Pp);
		}
	}
	glEnd();
	u = 0;
	v = 0;
	while (u <= 1) {
		glBegin(GL_LINE_STRIP);
		while (v <= 1) {
			Pp[0] = surface(P16, u, v, 0);
			Pp[1] = surface(P16, u, v, 1);
			Pp[2] = surface(P16, u, v, 2);
			glVertex3dv(Pp);
			v += 0.1;
		}
		v = 0;
		u += 0.1;
		glEnd();
	}
	u = 0;
	v = 0;
	while (u <= 1) {
		glBegin(GL_LINE_STRIP);
		while (v <= 1) {
			Pp[0] = surface(P16, v, u, 0);
			Pp[1] = surface(P16, v, u, 1);
			Pp[2] = surface(P16, v, u, 2);
			glVertex3dv(Pp);
			v += 0.1;
		}
		v = 0;
		u += 0.1;
		glEnd();
	}



	double P[3];
	double vec[3];
	glBegin(GL_LINE_STRIP); //построим отрезки P1P2 и P2P3
	glColor3d(0, 0, 0);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01)							//t <= t_max;
	{
		P[0] = f(P1[0], P2[0], P3[0], P4[0], t);
		P[1] = f(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = f(P1[2], P2[2], P3[2], P4[2], t);
		glVertex3dv(P); //Рисуем точку P
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= t_max; t += 0.01)							//t <= t_max;
	{
		P[0] = f(P1[0], P2[0], P3[0],P4[0], t);
		P[1] = f(P1[1], P2[1], P3[1],P4[1], t);
		P[2] = f(P1[2], P2[2], P3[2],P4[2], t);
		
		//glVertex3dv(P); //Рисуем точку P
	}
	glEnd();

	double vecXer[] = { 1,0,0 };

	vec[0] = kas(P1[0], P2[0], P3[0], P4[0], t_max);
	vec[1] = kas(P1[1], P2[1], P3[1], P4[1], t_max);
	vec[2] = kas(P1[2], P2[2], P3[2], P4[2], t_max);
 
	double Angle = angle(vecXer[0], vecXer[1], vecXer[2], vec[0], vec[1], vec[2]);
	double AngleCopy = 0;
	glColor3d(1, 0, 0.453);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	//glPointSize(10);
	//glBegin(GL_POINTS);
	//glVertex3dv(P);
	//glEnd();

	glPushMatrix();
	
	glTranslated(P[0], P[1], P[2]);
	glRotated(Angle, 0, 1, 0);
	glScaled(0.3, 0.3, 0.3);
	
	figure(); //перенес рисование фигуры в отдельную функцию
	glPopMatrix();


	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glEnd();
}
