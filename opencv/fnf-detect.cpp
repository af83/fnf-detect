#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <cmath>
#include <iostream>
#include <vector>


const double hairOffset = 0.12;
const double scale = 1.1;
const int neighbors = 4;
const int minSize = 64;
const int maxCorners = 20;
const double qualityLevel = 0.05;
const int minDistance = 30;
const int featureSize = 3;

const char *faceCascade = "/usr/share/opencv/lbpcascades/lbpcascade_frontalface.xml";
const char *profCascade = "/usr/share/opencv/haarcascades/haarcascade_profileface.xml";


void display(std::vector<cv::Rect> &rects, const char *type) {
	cv::groupRectangles(rects, 0);
	for (cv::Rect rect : rects) {
		std::cout
			<< rect.x << " "
			<< rect.y << " "
			<< rect.width << " "
			<< rect.height << " "
			<< type << std::endl;
	}

}


int main(int argc, const char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: fnf-detect <image>" << std::endl;
		return -1;
	}

	const char *filename = argv[1];
	cv::Mat img = imread(filename, cv::IMREAD_GRAYSCALE);
	if (img.empty())
	{
		std::cerr << "Cannot read" << filename << std::endl;
		return -1;
	}
	cv::equalizeHist(img, img);

	double length = sqrt(img.size().area());
	cv::Size min = cv::Size(minSize, minSize);
	cv::Size max = cv::Size(length / 3, length / 3);
	std::vector<cv::Rect> rects;

	cv::CascadeClassifier faceClassifier = cv::CascadeClassifier(faceCascade);
	faceClassifier.detectMultiScale(img, rects, scale, neighbors, 0, min, max);
	if (rects.size() > 0) {
		for (cv::Rect rect : rects) {
			rect.y -= rect.height * hairOffset;
			if (rect.y < 0) rect.y = 0;
		}
		display(rects, "face");
		return 0;
	}

	cv::CascadeClassifier profClassifier = cv::CascadeClassifier(profCascade);
	profClassifier.detectMultiScale(img, rects, scale, neighbors, 0, min, max);
	if (rects.size() > 0) {
		display(rects, "profile");
		return 0;
	}

	std::vector<cv::Point2f> corners;
	goodFeaturesToTrack(img, corners, maxCorners, qualityLevel, minDistance);
	for (cv::Point2f corner : corners) {
		rects.push_back(cv::Rect(corner.x - featureSize/2,
		                         corner.y - featureSize/2,
			                 featureSize,
			                 featureSize));
	}
	display(rects, "feature");

	return 0;
}
