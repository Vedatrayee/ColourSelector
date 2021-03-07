#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture video(0);
	Mat frame;
	Mat hsvImage, frame_t; 
	int hueMinimum = 0, saturationMinimum = 0, valueMinimum = 0;
	int hueMaximum = 179, saturationMaximum = 255, valueMaximum = 255;

	namedWindow("Trackbar"); //Trackbar to find value of colour
	createTrackbar("Hue Min", "Trackbar", &hueMinimum, 179);
	createTrackbar("Hue Max", "Trackbar", &hueMaximum, 179);
	createTrackbar("Sat Min", "Trackbar", &saturationMinimum, 255);
	createTrackbar("Sat Max", "Trackbar", &saturationMaximum, 255);
	createTrackbar("Value Min", "Trackbar", &valueMinimum, 255);
	createTrackbar("Value Max", "Trackbar", &valueMaximum, 255);

	while (true) {

		video.read(frame); 
		cvtColor(frame, hsvImage, COLOR_BGR2HSV);

		Scalar lower(hueMinimum, saturationMinimum, valueMinimum);
		Scalar upper(hueMaximum, saturationMaximum, valueMaximum);

		inRange(hsvImage, lower, upper, frame_t);
		
		cout << hueMinimum << "," << saturationMinimum << "," << valueMinimum << "," << hueMaximum << "," << saturationMaximum << "," << valueMaximum << endl;
		imshow("Video", frame);
		imshow("Threshold", frame_t);
		if (waitKey(25) >= 0)
		{
			break;
		}
	}
	video.release();
	destroyAllWindows();
}