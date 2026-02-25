#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

struct BulletInfo {
    cv::Point2f center;  // 圆心坐标
    float radius;        // 半径（像素）
    float distance;      // 距离（毫米）
};

// 检测小弹丸并计算距离
std::vector<BulletInfo> detectBullets(const std::string& input_path, 
                                       const std::string& output_path);

#endif