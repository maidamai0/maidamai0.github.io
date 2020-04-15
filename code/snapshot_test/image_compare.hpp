#pragma once

#include <QColor>
#include <QFile>
#include <QImage>

#include <iostream>
#include <string>

/**
 * @brief compare two image
 *
 * @param expected    the expected image path
 * @param actrual     the actual image path
 * @param theshold    theshold to decide if these iamges are the same
 * @return true       the two image are considered the same
 * @return false      the two imag are considered different
 */
auto image_diff(const std::string& expected, const std::string& actual,
                const double theshold = 0.1) -> bool {
  auto check_file_exist = [](const std::string& path) {
    if (!QFile(path.c_str()).exists()) {
      std::cout << "File " << path << " not exist\n";
      return false;
    }

    return true;
  };

  if (!check_file_exist(expected) || !check_file_exist(actual)) {
    return false;
  }

  QImage expected_image(expected.c_str());
  QImage actual_image(actual.c_str());

  double totaldiff = 0.0; // holds the number of different pixels
  int h = expected_image.height();
  int w = expected_image.width();
  int hsecond = actual_image.height();
  int wsecond = actual_image.width();
  if (w != wsecond || h != hsecond) {
    std::cerr << "Error, pictures must have identical dimensions!\n";
    return false;
  }

  for (int y = 0; y < h; y++) {
    uint* firstLine = (uint*) expected_image.scanLine(y);
    uint* secondLine = (uint*) actual_image.scanLine(y);
    for (int x = 0; x < w; x++) {
      uint pixelFirst = firstLine[x];
      int rFirst = qRed(pixelFirst);
      int gFirst = qGreen(pixelFirst);
      int bFirst = qBlue(pixelFirst);
      uint pixelSecond = secondLine[x];
      int rSecond = qRed(pixelSecond);
      int gSecond = qGreen(pixelSecond);
      int bSecond = qBlue(pixelSecond);

      const static auto max_color = 255.0;
      totaldiff += std::abs(rFirst - rSecond) / max_color;
      totaldiff += std::abs(gFirst - gSecond) / max_color;
      totaldiff += std::abs(bFirst - bSecond) / max_color;
    }
  }

  const auto diff = (totaldiff * 100) / (w * h * 3);

  return (diff < theshold);
}