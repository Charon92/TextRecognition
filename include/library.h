#ifndef TEXTRECOGNITION_LIBRARY_H
#define TEXTRECOGNITION_LIBRARY_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <chrono>
#include <bitset>
#include <cstdlib>
#include <stdexcept>

#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>
#include <opencv2/opencv.hpp>

class TextRecognition {
public:
    TextRecognition();
    ~TextRecognition();

    std::string recognise(const std::string& image);

};

#endif //TEXTRECOGNITION_LIBRARY_H
