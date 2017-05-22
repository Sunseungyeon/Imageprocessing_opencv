#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

//mask
double **mask;

int main(int argc, char** argv) {
	string imageName("C:/Program Files/opencv/sources/samples/data/lena512_gray.bmp");
	void createMask(int);

	int size=0;

	if (argc > 1) {
		imageName = argv[1];
	}
	Mat image, image_gray;

	float ch;
	float fVal;

	image = imread(imageName.c_str(), IMREAD_COLOR);

	cvtColor(image, image_gray, CV_BGR2GRAY);
	//Mat image = imread("../landscapes-267a.jpg");
	Mat new_image = Mat::zeros(image_gray.size(), image_gray.type());

	while (1) {
		printf("input filter size of odd number: ");
		scanf("%d", &size);
		if (size % 2 == 0)
			printf("input number is not odd number. retry!\n");
		else
			break;
	}

	createMask(size);

	for (int j = 0; j < image.rows - size; j++) {
		for (int i = 0; i < image.cols - size; i++) {
			ch = 0.0;
			for (int m = 0; m < size; m++) {
				for (int k = 0; k < size; k++) {
					fVal = (float)(image_gray.at<uchar>(j + (m), i + (k)));

					ch += mask[m][k] * fVal;
				}
			}

			// new image
			new_image.at<uchar>(j, i) = ch;
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

void createMask(int size) {
	int i = 0, j = 0;
	double sum = 0.0;
	double sigma = 0.0;
	double r, s;

	printf("input sigma value: ");
	scanf("%lf", &sigma);

	s = 2.0 * sigma * sigma;

	mask = (double**)malloc(size * sizeof(double*));
	for (i = 0; i < size; i++) {
		mask[i] = (double*)malloc(size * sizeof(double));
	}

	int k = size / 2;
	double tmp;
	// generate 5x5 kernel
	for (int x = -k; x <= k; x++)
	{
		for (int y = -k; y <= k; y++)
		{
			r = sqrt(x*x + y*y);
			tmp = (exp(-(r*r) / s)) / (3.1415926535 * s);
			mask[x + k][y + k] = tmp;
			sum += mask[x + k][y + k];
		}
	}
	// normalize the Kernel
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mask[i][j] /= sum;
}
