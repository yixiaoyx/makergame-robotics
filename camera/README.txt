%%% Paste this whole thing in your terminal to install the dependencies %%%

  sudo apt-get -y install libopencv-dev build-essential cmake git libgtk2.0-dev pkg-config python-dev python-numpy libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils unzip

%%% Now paste all of this at the same time into your terminal to download and install opencv 3.2 %%%

  mkdir opencv
  cd opencv
  wget https://github.com/Itseez/opencv/archive/3.2.0.zip -O opencv-3.2.0.zip
  unzip opencv-3.2.0.zip
  cd opencv-3.2.0
  mkdir build
  cd build
  cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
  make -j $(nproc)
  sudo make install
  sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
  sudo ldconfig

%%% Now restart your comp and run this command to check that the install worked %%%

  pkg-config --modversion opencv

%%% the expected output from that command should be: 3.2.0 %%%

%%% if you have issues this is the site i used: https://www.linuxhint.com/how-to-install-opencv-on-ubuntu/ %%%
