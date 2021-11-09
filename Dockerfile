FROM ubuntu:18.04

WORKDIR /home/usr

RUN apt-get update && apt-get install -y build-essential && \
    apt-get install -y cmake vim git libgtk2.0-dev pkg-config \
    libavcodec-dev libavformat-dev libswscale-dev && \
    apt-get install -y python-dev python-numpy libtbb2 \
    libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev \
    && apt-get clean && rm -rf /var/lib/apt-lists/*

RUN git clone https://github.com/opencv/opencv.git && \
    git clone https://github.com/opencv/opencv_contrib.git

RUN cd opencv && mkdir -p build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D \
             CMAKE_INSTALL_PREFIX=/usr/local -D \
             OPENCV_GENERATE_PKGCONFIG=ON -D \
             OPENCV_EXTRA_MODULES_PATH=/home/usr/opencv_contrib/modules .. \
    && make -j4 && make install

RUN apt-get install -y automake ca-certificates g++-8 \
    git libtool libleptonica-dev make pkg-config && \
    apt-get install -y --no-install-recommends asciidoc \
    docbook-xsl xsltproc && apt-get install -y libpango1.0-dev \
    && apt-get install -y libicu-dev libpango1.0-dev libcairo2-dev

RUN git clone https://github.com/tesseract-ocr/tesseract.git

RUN cd tesseract && ./autogen.sh && ./configure \
    && make && make install && make training && \
    make training-install && ldconfig

RUN mkdir /usr/local/share/tessdata

RUN curl -o /usr/local/share/tessdata/eng.traineddata https://raw.githubusercontent.com/tesseract-ocr/tessdata_best/master/eng.traineddata

WORKDIR /home

COPY ./ /

RUN cmake / && make && make install && \
    chown -R www-data:www-data / && \
    rm -rf /usr/local/include/opencv4 && \
    rm -rf /usr/lib/opencv4