#include "TimeWindow.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

#define N 9 // Number of sensor state
#define M 8 // number of Sonar sensors

Point *robotPos[1000];
landmark *landmarks[1000];

static int indexPosition = 0;
static int indexLandmark = 0;

TimeWindow::TimeWindow()
{
	indexTW = 0;
}

TimeWindow::~TimeWindow()
{
}

void TimeWindow::addNewData2TW(SonarData * datas[])
{
	if (indexTW == N) {
		TBF();
		shiftTW();
	}

	for (int i = 0; i < M; i++) {
		TW[i][indexTW] = datas[i];
	}
	
	indexTW++;
}

void TimeWindow::shiftTW()
{

	for (int i = 0; i < M; i++)
	{
		delete TW[i][0];
		for (int j = 0; j <= N; j++)
		{
			TW[i][j] = TW[i][j + 1];
		}
	}

	indexTW--;
}

void TimeWindow::TBF()
{
	int row_i = N - 1;
	double r_max = 4900;

	for (int i = 0; i < M; i++)
	{
		double r_in = TW[i][row_i]->range;
		double nt = 0;
		double d1 = 0.0;

		double x_T = TW[i][row_i]->x + r_in*sin(TW[i][row_i]->theta);
		double y_T = TW[i][row_i]->y + r_in*cos(TW[i][row_i]->theta);

		double x_min = 9999999, y_min = 9999999; double x_max = -9999999, y_max = -999999;

		if (r_in < r_max) {
			//SonarData *G[N];
			//G[i] = TW[i][row_i];
			for (int j = N - 2; j > 0; j--) { // Reading
				for (int k = 0; k < M; k++) { // Sensors
					if (TW[k][j]->range < r_max) {
						     d1 = sqrt(pow((TW[i][row_i]->x - TW[k][j]->x), 2) + pow((TW[i][row_i]->y - TW[k][j]->y), 2));
						//if (isInRange(x_T, y_T, TW[k][j])) {
							double r_e = sqrt(pow((x_T - TW[k][j]->x), 2) + pow((y_T - TW[k][j]->y), 2));
							if ((r_e - TW[k][j]->range) < (d1 / nt + 1)) {
								//cout << "X_T :" << X_T << " Y_T:" << Y_T << " nt:" << nt << endl;
								if (TrianglePossible(TW[i][row_i], TW[k][j], x_T, y_T)) {
									//G[i+1] = TW[k][j];
									nt++;
									if (x_T < x_min) { x_min = x_T; }
									if (x_T < x_max) { x_max = x_T; }
									if (y_T < y_min) { y_min = y_T; }
									if (y_T < y_max) { y_max = y_T; }
								}
							}
					//	}
					}
				}
			}
		}
		if (nt >= 3) {
			if (((x_max - x_min) + (y_max - y_min)) >  100) {
				nt = -nt;
			}
			addLandmark(x_T, y_T, nt, TW[i][row_i]);
			addRobotPos(x_T, y_T);
			//cout << "Landmark : " << x_T << ":" << y_T << endl;
			//cout << nt << " landmark/s have been found..." << endl;
		}

	}
}

bool TimeWindow::TrianglePossible(SonarData *R2, SonarData *R1, double &x_t, double &y_t)
{
	double sensor_angle = 25;
	double r1 = R1->range;
	double r2 = R2->range;

	double dx = R1->x - R2->x;
	double dy = R1->y - R2->y;

	double dss = dx*dx + dy*dy;
	double drr = (r1*r1 - r2*r2 - dss) / 2;

	double x1_T, x2_T, y1_T, y2_T = 0;

	x1_T = R1->x + (dx*drr + abs(dy)*sqrt(r2*r2*dss - drr*drr)) / dss;
	y1_T = R1->y + (dy*drr + abs(dx)*sqrt(r2*r2*dss - drr*drr)) / dss;

	x2_T = R2->x + (dx*drr - abs(dy)*sqrt(r2*r2*dss - drr*drr)) / dss;
	y2_T = R2->y + (dy*drr - abs(dx)*sqrt(r2*r2*dss - drr*drr)) / dss;


	//cout << "P1 :" << (double)x1_T << "," << (double)y1_T << " P2 :" << (double)x2_T << "," << (double)y2_T << endl;
	double a = sqrt(pow((x1_T - R1->x), 2) + pow((y1_T - R1->y), 2));
	double b = sqrt(pow((x2_T - R2->x), 2) + pow((y2_T - R2->y), 2));
	//cout << "R1 =" << (int)R1->range << " calculated :" << (int)a << endl;
	//cout << "R2 =" << (int)R2->range << " calculated :" << (int)b << endl;


	if ((int)R1->range == (int)a) {
		x_t = x1_T;
		y_t = y1_T;
		return true;
	}
	if ((int)R2->range == (int)b) {
		x_t = x2_T;
		y_t = y2_T;
		return true;
	}

	return false;
}

bool TimeWindow::isInRange(double x_T, double y_T, SonarData *in)
{

	double result = atan((y_T - in->y) / (x_T - in->x));

	if ((result > (in->theta - 25 / 2)) && (result < (in->theta + 25 / 2))) {
		return true;
	}

	return false;
}

void TimeWindow::showAll()
{
	for (int i = 0; i < 8; i++)
	{
		cout << i ;
		for (int j = 0; j < 10; j++)
		{
			cout << ":" << TW[i][j]->x << "," << TW[i][j]->y;
		}
		cout << endl;
	}

}


void TimeWindow::addRobotPos(double x, double y)
{
	Point *p = new Point();
	p->x = x;
	p->y = y;

	robotPos[indexPosition] = p;
	indexPosition++;
}

void TimeWindow::savePos()
{
	ofstream myfile;
	myfile.open("example.csv");
	myfile << "X" << ", " << "Y" << "\n";

	for (int i = 0; i < indexPosition; i++) {
		myfile << robotPos[i]->x << ", " << robotPos[i]->y << "\n";
	}

	myfile.close();

	myfile.open("examplelandmark.csv");
	myfile << "X" << ", " << "Y" << "\n";

	for (int i = 0; i < indexLandmark; i++) {
		myfile << landmarks[i]->x_T << ", " << landmarks[i]->y_T << "\n";
	}

	myfile.close();
}
void TimeWindow::addLandmark(double x_T, double y_T, int nt, SonarData *data)
{
	landmark * p = new landmark(x_T, y_T, nt, data);
	landmarks[indexLandmark] = p;
	indexLandmark++;
}