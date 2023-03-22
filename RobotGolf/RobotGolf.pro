TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

#=====================OpenCV Includes=======================
INCLUDEPATH += C:\AINT308Lib\OpenCV41\release\install\include

LIBS += -LC:\AINT308Lib\OpenCV41\release\lib
LIBS +=    -lopencv_core411 \
    -lopencv_highgui411 \
    -lopencv_imgproc411 \
    -lopencv_features2d411 \
    -lopencv_calib3d411 \
    -lopencv_videoio411 \
    -lopencv_imgcodecs411 \
    -lopencv_face411 \
    -lopencv_objdetect411 \
    -lopencv_bgsegm411 \


SOURCES += \
        main.cpp
