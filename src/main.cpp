#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input> <output>" << std::endl;
        return EXIT_FAILURE;
    }

    cv::String inputFilename = argv[1];
    cv::String outputFilename = argv[2];

    cv::String face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_frontalface_alt.xml");

    cv::CascadeClassifier face_cascade;
    if(!face_cascade.load(face_cascade_name))
    {
        std::cerr << "Cannot load face classifier" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat img = cv::imread(inputFilename, cv::IMREAD_COLOR);
    if(img.empty())
    {
        std::cerr << "Cannot read image \"" << inputFilename << "\"" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img, faces);

    for(cv::Rect faceRect: faces)
    {
        auto color = cv::Scalar(255, 0, 255);

        cv::Point center(faceRect.x + faceRect.width/2, faceRect.y + faceRect.height/2 );
        cv::ellipse(img, center, cv::Size(faceRect.width/2, faceRect.height/2), 0, 0, 360, color, 4);
    }

    cv::imwrite(outputFilename, img);

    return EXIT_SUCCESS;
}
