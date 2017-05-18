#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

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

	image = imread(imageName.c_str(), IMREAD_COLOR);

	image.copyTo(image_gray);

	cvtColor(image, image_gray, CV_BGR2GRAY);
	
	//Mat image = imread("../landscapes-267a.jpg");
	Mat new_image = Mat::zeros(image_gray.size(), image_gray.type());


	for (int j = 2; j < image.rows - 4; j++) {
		for (int i = 2; i < image.cols - 4; i++) {

			ch = 0.0;

			for (int m = 0; m < 5; m++) {
				for (int k = 0; k < 5; k++) {
					fVal = (float)(image_gray.at<uchar>(j + (m - 2), i + (k - 2)));

					ch += (1.0 / 25.0) * fVal;
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
