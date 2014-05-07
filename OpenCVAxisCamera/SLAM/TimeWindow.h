#pragma once

struct SonarData {
	SonarData() {
		x = 0;
		y = 0;
		theta = 0;
		range = 0;
	}

	double x;
	double y;
	double theta;
	double range;
};

struct Point
{
	double x;
	double y;
	Point() {
		x = 0;
		y = 0;
	};
};

struct landmark {
	landmark(double x_T, double y_T, int nt, SonarData *data ) {
		this->x_T = x_T;
		this->y_T = y_T;
		this->nt = nt;
		this->d = data;
	}
	double x_T;
	double y_T;
	int nt;
	SonarData *d;
};


class TimeWindow
{
public:
	TimeWindow();
	~TimeWindow();

	void addNewData2TW(SonarData * datas[]);
	void shiftTW();

	void TBF();
	bool isInRange(double x_T, double y_T, SonarData *in);
	bool TrianglePossible(SonarData *R2, SonarData *R1, double &x_t, double &y_t);

	void showAll();

	void addRobotPos(double x, double y);
	void savePos();

	void addLandmark(double x_T, double y_T, int nt, SonarData *data);

private :
	SonarData * TW[8][10];
	int indexTW;
};

