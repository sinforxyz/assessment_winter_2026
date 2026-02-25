#include "detector.hpp"
#include <iostream>
#include <cmath>

const cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) << 
    1284.547433507284, 0.0, 651.7508235222139,
    0.0, 1284.2364120767988, 526.5637803861928,
    0.0, 0.0, 1.0);

const cv::Mat distCoeffs = (cv::Mat_<double>(1,5) << 
    -0.37358321087789575, 0.17992488578084675, 
    -0.0003940895801771612, -0.0007097534681170694, 0.0);

const float REAL_DIAMETER_MM = 17.0f;

float calculateDistance(float radius_pixels) {
    double focal_length = (cameraMatrix.at<double>(0,0) + 
                          cameraMatrix.at<double>(1,1)) / 2.0;
    float distance = (REAL_DIAMETER_MM * focal_length) / (2.0f * radius_pixels);
    return distance;
}

std::vector<BulletInfo> detectBullets(const std::string& input_path, 
                                       const std::string& output_path) {
    std::vector<BulletInfo> bullets;
    cv::Mat img = cv::imread(input_path);
    cv::Mat undistorted;
    cv::undistort(img, undistorted, cameraMatrix, distCoeffs);

    cv::Mat hsv;
    cv::cvtColor(undistorted, hsv, cv::COLOR_BGR2HSV);
    cv::Scalar lower_green(45, 70, 70);
    cv::Scalar upper_green(75, 200, 200);

    cv::Mat mask;
    cv::inRange(hsv, lower_green, upper_green, mask);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
        if (contour.size() < 20) continue;
        cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(contour, center, radius);
        if (radius < 5 || radius > 100) continue;
        BulletInfo bullet;
        bullet.center = center;
        bullet.radius = radius;
        bullet.distance = calculateDistance(radius);
        bullets.push_back(bullet);
        
        cv::circle(undistorted, center, static_cast<int>(radius), 
                  cv::Scalar(0, 255, 0), 2);
        char text[50];
        sprintf(text, "%f m", bullet.distance / 1000.0);

        cv::putText(undistorted, text, 
                   cv::Point(center.x - 30, center.y - radius - 10),
                   cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 255), 2);
    }
    cv::imwrite(output_path, undistorted);
    return bullets;
}

int main() {
    std::vector<BulletInfo> bullets1 = detectBullets("imgs/test1.jpg", 
                                                     "imgs/result_test1.jpg");
    std::vector<BulletInfo> bullets2 = detectBullets("imgs/test2.jpg", 
                                                     "imgs/result_test2.jpg");
    return 0;
}