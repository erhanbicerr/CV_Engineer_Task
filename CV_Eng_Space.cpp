#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat image;
Mat temp;
Mat tempRotated;
Mat result;

const char* image_window = "Source Image";
const char* result_window = "Result window";

void matchMethod() {



	matchTemplate(image, temp, result, TM_CCOEFF_NORMED);


	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	matchLoc = maxLoc;

	cout << maxVal << endl;

	if (maxVal < 0.8) {

		rotate(temp, tempRotated, ROTATE_90_CLOCKWISE);
		temp = tempRotated;
		matchMethod();

	}

	else {

	cout << "Location of Template (4 points):" << endl;
	cout << "[" << matchLoc.x << "," << matchLoc.y << "]," << "[" << matchLoc.x + temp.cols << "," << matchLoc.y << "]" << endl;
	cout << "[" << matchLoc.x << "," << matchLoc.y + temp.rows << "]," << "[" << matchLoc.x + temp.cols << "," << matchLoc.y + temp.rows << "]" << endl;

	rectangle(image, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows), CV_RGB(0, 255, 0));

	imshow("Found it!", image);
	waitKey(0);

	}

}

int main()
{
	
	image = imread("StarMap.png");
	temp = imread("Small_area.png");

	imshow("Image", image);
	waitKey(0);



	matchMethod();


	system("pause");
	return 0;

}

