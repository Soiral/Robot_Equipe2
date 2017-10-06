#include <iostream>
#include <stdio.h>
#include "Robot.h"
#include "serialib.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
 * Fonction de démonstration
 */
void demoRobot(char c)
{
    Robot robot;
  switch(c) {
	case '0':   cout << "Arret" << endl; break; 
	case '1':   cout << "Avancer doucement" << endl; break;
	case '2':   cout << "Avancer rapidement" << endl; break;
	case '3':   cout << "Reculer doucement" << endl; break;
	case '4':   cout << "Reculer rapidement" << endl; break;
	case '5':   cout << "Tourner a gauche doucement" << endl; break;
	case '6':   cout << "Tourner a gauche rapidement" << endl; break;
	case '7':   cout << "Tourner a droite doucement" <<endl; break;
	case '8':   cout << "Tourner a droite doucement" <<endl; break;
	case '9':   cout << "Tourner a gauche en arriere doucement" <<endl; break;
	case 'a':   cout << "Tourner a gauche en arriere rapidement" <<endl; break;
	case 'b':   cout << "Tourner a droite en arriere doucement" <<endl; break;
	case 'c':   cout << "Tourner a droite en arriere rapidement" <<endl; break;

	}
       robot.sendOrder(c);
    
}


char traitement(Mat frame)
{
    int64 t0 = cv::getTickCount();
    Mat imgThreshold, hsv_frame, canny_frame;
    double X_center = 320 *3, X1_center=0, X2_center=0, Y1_tier = 213 *3, Y2_tier = 427 *3, rate =0;

	cout << "traitement"<< endl;

//	    cvtColor(frame, hsv_frame, CV_BGR2HSV);

	// ROUGE
       //cv::Scalar min(120, 150, 80); 
	    //cv::Scalar max(130, 255, 255); 

	 // NOIR
    //cv::Scalar min(30, 30, 30); 
    //cv::Scalar max(100, 100, 100); 

	// BLEU
   // cv::Scalar min(100, 150, 0); 
   // cv::Scalar max(140, 255, 255); 

//    cv::inRange(hsv_frame, min, max, imgThreshold);

    int64 t1 = cv::getTickCount();
    cv::Canny(frame, canny_frame, 100, 200, 3);
    int64 tcanny = cv::getTickCount();
    
   // cv::Mat Test = imread("/var/www/html/test02.jpg");
    
    int64 t_canny = (tcanny - t1)/cv::getTickFrequency();
    cout << "Temps de traitement Canny() : " << t_canny << "s" << endl;   

    imwrite("test1.jpg", frame);
    imwrite("test_canny.jpg", canny_frame);

    
   //int64 tfin = cv::getTickCount();
  // cout << "Temps d'execution : " << (tfin - t0)/cv::getTickFrequency() << "s" << endl;

  //255 -> blanc
  //cout << "Matrice : " << canny_frame  << endl;

	double X1_blanc=0, X2_blanc=0, i=0 , j=0;

	for (i = 0; i < X_center*2; ++i) {
		if (canny_frame.at<double>(i, Y1_tier) >= 30){
			X1_blanc = i;
			cout << "X1_blanc : " << X1_blanc << endl;
			for (j = 0; j < 10; ++j)
				++i;
			for (i; i < X_center*2; ++i) {
				if (canny_frame.at<double>(i, Y1_tier) >= 30){
					X2_blanc = i;
					cout << "X2_blanc : " << X2_blanc << endl;
				break;
				}

			}
		break;
		}
	
	}
	X1_center = X1_blanc +( X2_blanc - X1_blanc)/2;
	X1_blanc = 0, X2_blanc = 0;
	
	for (i = 0; i < X_center *2; ++i) {
		if (canny_frame.at<double>(i, Y2_tier) >= 30){
			X1_blanc = i;
			cout << "X1_blanc2 : " << X1_blanc << endl;
			for (j = 0; j < 10; ++j)
				++i;	
			for (i; i < X_center *2; ++i) {
				if (canny_frame.at<double>(i, Y2_tier) >= 30){
					X2_blanc = i;	
					cout << "X2_blanc2 : " << X2_blanc << endl;
				break;
				}
			}
		break;
		}
	}
	X2_center = X1_blanc +(X2_blanc - X1_blanc)/2;
 
	cout << "X1_center : " << X1_center << endl;
	cout << "X2_center ; " << X2_center << endl;
 
	 int64 tfin2 = cv::getTickCount();
         int64 t_final = (tfin2 - t0)/cv::getTickFrequency();
  	 cout << "Temps d'execution de tout le traitement image: " << (tfin2 - t0)/cv::getTickFrequency() << "s" << endl;
	 rate = X1_center - X2_center; 
cout << "rate :" << rate << endl;
    

if (rate > 300)
	return '7';
		else 
		if (rate < -300)
			return '5';
			 else  return '1';

}

char demoCV()
{
    Mat frame;
    VideoCapture *cap;

    bool ok = false;
    while (!ok) {
	cap = new VideoCapture(0);

   	if (!cap->isOpened()) {
       	 cout << "Unable to open the device webcam, retrying" << endl;
       	 delete cap;
	 usleep(1000000);
    	} else {
	 ok = true;
	}
    }
cout << "test" << endl;
    *cap >> frame; 
char ret = traitement(frame);
 cout << "order ---> " << ret << endl;
 return ret;

}




int main(int argc, char *argv[])
{
    char c;
while(1) {
    c = demoCV();
    demoRobot(c);
    sleep(2);
    demoRobot(0);
}
//sleep((2));
//demoRobot(0);
}
