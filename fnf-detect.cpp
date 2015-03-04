#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <iostream>
#include <vector>


const char *faceCascade = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml";


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

	cv::CascadeClassifier faceClassifier = cv::CascadeClassifier(faceCascade);
	std::vector<cv::Rect> faces;
	faceClassifier.detectMultiScale(img, faces, 1.1, 4);

	for (cv::Rect face : faces) {
		std::cout
			<< face.width << " "
			<< face.height << " "
			<< face.x << " "
			<< face.y << " "
			<< "face" << std::endl;
	}

	return 0;
}
