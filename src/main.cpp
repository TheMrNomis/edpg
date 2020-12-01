#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

#include "log.h"

void drawCenteredText(cv::Mat& img, std::string const& text, cv::Point const& anchor, cv::Scalar const& color)
{
    int const    fontFace  = cv::FONT_HERSHEY_SIMPLEX;
    double const fontScale = 1.0;
    int const    thickness = 1;

    int baseLine;

    cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseLine);

    cv::Point pos = anchor + cv::Point(-textSize.width/2, textSize.height/2);
    cv::putText(img, text, pos, fontFace, fontScale, color);
}

int main(int argc, char** argv) {
    Log::ensure(argc == 3) << "Usage: " << argv[0] << " <input> <output>";

    cv::String inputFilename = argv[1];
    cv::String outputFilename = argv[2];

    cv::String face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_frontalface_alt.xml");

    cv::CascadeClassifier face_cascade;
    Log::ensure(face_cascade.load(face_cascade_name)) << "Cannot load face classifier";

    cv::Mat img = cv::imread(inputFilename, cv::IMREAD_COLOR);
    Log::ensure(!img.empty()) << "Cannot read image \"" << inputFilename << "\"";

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img, faces);

    for(size_t i = 0; i < faces.size(); ++i)
    {
        cv::Rect const& faceRect = faces[i];

        cv::Scalar const white(255, 255, 255);
        cv::Scalar const magenta(255, 0, 255);

        cv::Point center(faceRect.x + faceRect.width/2, faceRect.y + faceRect.height/2 );
        cv::Size size(faceRect.width/2, faceRect.height/2);

        std::vector<cv::Point> circlePts;
        cv::ellipse2Poly(center, size, 0, 0, 360, 10, circlePts);

        cv::fillConvexPoly(img, circlePts, white);
        cv::polylines(img, circlePts, true, magenta, 4);

        drawCenteredText(img, std::to_string(i), center, magenta);
    }

    cv::imwrite(outputFilename, img);

    return EXIT_SUCCESS;
}
