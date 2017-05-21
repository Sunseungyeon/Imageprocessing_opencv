#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	string imageName("C:/Program Files/opencv/sources/samples/data/lena_noise.png");
	if (argc > 1) {
		imageName = argv[1];
	}
	Mat image, image_tmp;

	float arrG[25], arrB[25], arrR[25], temp;

	image = imread(imageName.c_str(), IMREAD_COLOR);

			  //Mat image = imread("../landscapes-267a.jpg");
	Mat new_image = Mat::zeros(image.size(), image.type());
	image.copyTo(image_tmp);

	for (int j = 2; j < image.rows - 4; j++) {
		for (int i = 2; i < image.cols - 4; i++) {

			for (int m = 0; m < 5; m++) {
				for (int k = 0; k < 5; k++) {
					arrB[m*5 +k] = (float)(image_tmp.at<cv::Vec3b>(j + (m - 2), i + (k - 2))[0]);
					arrG[m * 5 + k] = (float)(image_tmp.at<cv::Vec3b>(j + (m - 2), i + (k - 2))[1]);
					arrR[m * 5 + k] = (float)(image_tmp.at<cv::Vec3b>(j + (m - 2), i + (k - 2))[2]);
				}
			}
			
			for (int p = 0; p < 25; p++) {
				for (int q = p+1; q < 25; q++) {
					if (arrB[p] >= arrB[q]) {
						temp = arrB[p];
						arrB[p] = arrB[q];
						arrB[q] = temp;
					}

					if (arrG[p] >= arrG[q]) {
						temp = arrG[p];
						arrG[p] = arrG[q];
						arrG[q] = temp;
					}

					if (arrR[p] >= arrR[q]) {
						temp = arrR[p];
						arrR[p] = arrR[q];
						arrR[q] = temp;
					}
				}
			}

			// new image
			new_image.at<cv::Vec3b>(j, i)[0] = (int)arrB[12];
			new_image.at<cv::Vec3b>(j, i)[1] = (int)arrG[12];
			new_image.at<cv::Vec3b>(j, i)[2] = (int)arrR[12];
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
