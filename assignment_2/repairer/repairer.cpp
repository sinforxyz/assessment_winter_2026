#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat src = cv::imread("imgs/noisy.jpg");
    cv::Mat dst;
    cv::fastNlMeansDenoisingColored(src, dst, 10, 10, 7, 21);
    cv::imwrite("imgs/noisy_.jpg", dst);
    return 0;
}