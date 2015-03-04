#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <cmath>
#include <iostream>
#include <vector>


const double scale = 1.2;
const int neighbors = 4;
const int minSize = 32;

const char *faceCascade = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml";
const char *profCascade = "/usr/share/opencv/haarcascades/haarcascade_profileface.xml";
const char *bodyCascade = "/usr/share/opencv/haarcascades/haarcascade_fullbody.xml";


void display(std::vector<cv::Rect> &rects, const char *type) {
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
		display(rects, "face");
		return 0;
	}

	cv::CascadeClassifier profClassifier = cv::CascadeClassifier(profCascade);
	profClassifier.detectMultiScale(img, rects, scale, neighbors, 0, min, max);
	if (rects.size() > 0) {
		display(rects, "profile");
		return 0;
	}

	cv::CascadeClassifier bodyClassifier = cv::CascadeClassifier(bodyCascade);
	bodyClassifier.detectMultiScale(img, rects, scale, neighbors, 0, min, max);
	if (rects.size() > 0) {
		display(rects, "body");
		return 0;
	}

	return 0;
}
