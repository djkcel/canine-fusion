#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Load the input images
    Mat img1 = imread(argv[1], IMREAD_COLOR);
    Mat img2 = imread(argv[2], IMREAD_COLOR);

    // Find the bounding boxes of the non-white pixels in each image
    Rect roi1 = boundingRect(img1);
    Rect roi2 = boundingRect(img2);

    // Compute the dimensions of the fused image
    int fused_width = max(roi1.width, roi2.width);
    int fused_height = max(roi1.height, roi2.height);

    // Create a new image of the fused dimensions
    Mat fused_image(fused_height, fused_width, CV_8UC3, Scalar(255, 255, 255));

    // Copy the non-white pixels from each image into the new image
    Mat roi_fused1 = fused_image(Rect(0, 0, roi1.width, roi1.height));
    img1(roi1).copyTo(roi_fused1);

    Mat roi_fused2 = fused_image(Rect(0, 0, roi2.width, roi2.height));
    img2(roi2).copyTo(roi_fused2);

    // Save the fused image to disk
    imwrite("fused.png", fused_image);

    return 0;
}
