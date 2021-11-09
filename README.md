# Text Recognition in images

A simple library that utilises the Tesseract OCR to locate text in images.

Outputs both a shared and static library when run as-is. This allows the use of a
`TextRecognition` class that has a `recognise` method which takes a filepath as a
`std::string` and returns a `std::string` of any text found as well as saving several
images with bounding boxes around found text.

## Building/Installing

In order to build you'll need to have both Tesseract OCR and Leptonica install. Instructions
to install them from source can be found here, 
[Tesseract](https://tesseract-ocr.github.io/tessdoc/Compiling.html) and
[Leptonica](http://leptonica.org/).

Or alternatively on Ubuntu use:

`sudo apt install tesseract-ocr libleptonica-dev`

And for Mac with Brew:

`brew install tesseract`
and
`brew install leptonica`

Or even better, use the provided Dockerfile! You can even just copy the install commands
from the Dockerfile to install both libraries locally.

---

## Further uses

If you'd like to use this in a Python application you can utilise another of my repos
to create a Python binding to this C++ class using [this](https://github.com/Charon92/cpp_python_template).

Feel free to copy, alter, update or even entirely replace this code as you see fit. It's
mostly for my benefit as I like using text recognition in applications and got fed up with
writing this sort of thing from scratch constantly.
