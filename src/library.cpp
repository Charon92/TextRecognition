#include "../include/library.h"

#include <iostream>



std::string TextRecognition::recognise(const std::string& image) {
    cv::Mat img, greyscale, threshold;

    int threshold_value = 0;
    int threshold_type = 3;
    int const max_value = 255;
    int const max_type = 4;
    int const max_binary_value = 255;
    int erosion_elem = 0;
    int erosion_size = 0;
    int dilation_elem = 0;
    int dilation_size = 0;
    int const max_elem = 2;
    int const max_kernel_size = 21;

    auto *api = new tesseract::TessBaseAPI();
    api->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY);
    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetVariable("debug_file", "tesseract.log");

    img = cv::imread(image, 1);

    std::cout << "READ IMAGE: " << img.rows << "x" << img.cols << std::endl;

    cv::cvtColor(img, greyscale, cv::COLOR_BGR2GRAY);

    cv::imwrite("./static/images/processed/greyscale.jpg", greyscale);

    cv::Mat element = getStructuringElement( cv::MORPH_RECT,
                                             cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                             cv::Point( dilation_size, dilation_size ) );

    cv::dilate(greyscale, greyscale, element);
    cv::erode(greyscale, greyscale, element);

    cv::imwrite("./static/images/processed/greyscale_processed.jpg", greyscale);

    cv::threshold(greyscale, threshold, 150, 255, cv::THRESH_BINARY);

    api->SetImage(threshold.data, threshold.cols, threshold.rows, 1, threshold.step);
    std::string outText = api->GetUTF8Text();
    tesseract::ResultIterator* ri = api->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;

    std::cout << "RI: " << ri << std::endl;

    if (ri != 0) {
        do {
            const char* word = ri->GetUTF8Text(level);
            float conf = ri->Confidence(level);
            int x1, y1, x2, y2;
            ri->BoundingBox(level, &x1, &y1, &x2, &y2);
            printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
                   word, conf, x1, y1, x2, y2);
            cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 3, 8, 0);
            delete[] word;
        } while (ri->Next(level));
    } else {
        std::cout << "Couldn't find anything in ri" << std::endl;
    }

    std::cout << "TEXT: " << outText << std::endl;

    cv::imwrite("./static/images/processed/threshold.jpg", threshold);
    cv::imwrite("./static/images/processed/highlighted.jpg", img);

    api->End();

    return outText;
}

TextRecognition::TextRecognition() {
    std::cout << "Creating TextRecognition Instance..." << std::endl;
}

TextRecognition::~TextRecognition() {
    std::cout << "Destroying TextRecognition Instance..." << std::endl;
}
