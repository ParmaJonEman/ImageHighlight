#include <iostream>
#include "main.h"

bool roiAcquired = false;
bool leftMouseDown = false;
Mat originalImage;
Point point1, point2;

int main(int argc, char **argv) {
    string imageFile;
    parseParameters(argc, argv, &imageFile);
    cout << "Selected Image: " << imageFile << endl;

    try {
        originalImage = imread(imageFile, 1);
        if (originalImage.empty())
            throw (string("Cannot open input originalImage ") + imageFile);
        imshow("window", originalImage);
        setMouseCallback("window", mouse_click, 0);
        waitKey();
    }
    catch (string &str) {
        cerr << "Error: " << argv[0] << ": " << str << endl;
        return (1);
    }
    catch (Exception &e) {
        cerr << "Error: " << argv[0] << ": " << e.msg << endl;
        return (1);
    }
    return 0;
}

void mouse_click(int event, int x, int y, int flags, void *param)
{

    switch(event)
    {
        case EVENT_MOUSEMOVE:{
            if(leftMouseDown && !roiAcquired){
                int xStart, yStart, xEnd, yEnd;
                xStart = min(point1.x, x);
                yStart = min(point1.y, y);
                xEnd = max(point1.x, x);
                yEnd = max(point1.y, y);

                Mat clonedImage = originalImage.clone();
                rectangle(clonedImage, Point(xStart, yStart), Point(xEnd, yEnd), Scalar(255,0,0), 2, LINE_8);
                imshow("window", clonedImage);
            }
            break;
        }
        case EVENT_LBUTTONDOWN:
        {
            cout<<"Mouse Button Pressed"<<endl;
            leftMouseDown = true;
            if(!roiAcquired)
            {
                point1.x = x;
                point1.y = y;
            }
            else
            {
                std::cout<<"ROI Already Acquired"<<std::endl;
            }
            break;
        }
        case EVENT_LBUTTONUP:
        {
            leftMouseDown = false;
            if(!roiAcquired)
            {
                Mat cl;
                cout<<"Mouse Button Released"<<std::endl;

                point2.x = x;
                point2.y = y;

                Mat roi(originalImage, Rect(point1, point2));

                cout << "Point 1: " << point1.x << ", " << point1.y << endl;
                cout << "Point 2: " << point2.x << "," << point2.y << endl;

                Mat darkFilter(originalImage.rows, originalImage.cols, CV_32FC3, Scalar(0.50, 0.50, 0.50));
                originalImage.convertTo(originalImage, CV_32FC3);
                originalImage = darkFilter.mul(originalImage);
                originalImage.convertTo(originalImage, CV_8UC3);

                cvtColor( roi, roi, COLOR_BGR2HSV );
                Mat Bands[3];
                split(roi, Bands);
                equalizeHist( Bands[2], Bands[2] );
                vector<Mat> channels = {Bands[0], Bands[1], Bands[2]};
                merge(channels, roi);
                cvtColor( roi, roi, COLOR_HSV2BGR );

                int xStart, yStart;
                xStart = min(point1.x, point2.x);
                yStart = min(point1.y, point2.y);

                roi.copyTo(originalImage(cv::Rect(xStart,yStart,roi.cols, roi.rows)));

                imshow("window", originalImage);
                roiAcquired = true;
            }
            else
            {
                cout<<"ROI Already Acquired"<<endl;
            }
            break;
        }

    }

}

static int parseParameters(int argc, char **argv, string *imageFile) {
    String keys =
            {
                    "{help h usage ? |                            | print this message   }"
                    "{@imagefile|| originalImage you want to use	}"
            };

    // Get required parameters.
    // If no image is passed in, or if the user passes in a help param, usage info is printed
    CommandLineParser parser(argc, argv, keys);
    parser.about("Lomo v1.0");

    if (!parser.has("@imagefile") || parser.has("help")) {
        parser.printMessage();
        return (0);
    }

    *imageFile = parser.get<string>("@imagefile");
    return (1);
}
