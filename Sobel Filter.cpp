#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	string imageName("C:/Program Files/opencv/sources/samples/data/lena512_gray.bmp");
	if (argc > 1) {
		imageName = argv[1];
	}
	Mat image, image_gray;

	float ch;
	float fVal;

	float x[3][3] = { 1, 0, -1, 2, 0, -2, 1, 0, -1 };
	float y[3][3] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };
	float gx=0, gy=0;

	image = imread(imageName.c_str(), IMREAD_COLOR);

	cvtColor(image, image_gray, CV_BGR2GRAY);
	//Mat image = imread("../landscapes-267a.jpg");
	Mat new_image = Mat::zeros(image_gray.size(), image_gray.type());

	for (int j = 1; j < image.rows - 2; j++) {
		for (int i = 1; i < image.cols - 2; i++) {
			ch = 0.0;
			gx = 0;
			gy = 0;
			for (int m = 0; m < 3; m++) {
				for (int k = 0; k < 3; k++) {
					fVal = (float)(image_gray.at<uchar>(j + (m - 1), i + (k - 1)));

					gx += x[m][k] * fVal;
					gy += y[m][k] * fVal;
				}
			}
			ch = sqrt(pow(gx,2)+pow(gy,2));

			if (ch > 255.0) ch = 255;
			if (ch < 0.0) ch = 0;

			// new image
			new_image.at<uchar>(j, i)= ch;
		}
	}

	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);

	/// Wait until user press some key
	waitKey();
	return 0;
}
