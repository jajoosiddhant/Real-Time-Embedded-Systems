
/**
 * @file cap.cpp
 * @brief This file consists of all the function definitions related to Pi camera functionality.
 * @author Satya Mehta, Ayush Dhoot, Siddhant Jajoo
 * @date 05/01/2019
 * @see https://www.geeksforgeeks.org/opencv-c-program-face-detection/
 * @copyright Copyright (C) 2019
 * 
 */

#include "../inc/main.h"
#include "../inc/cap.h"
#include "../inc/ultrasonic_sensor.h"
#include "../inc/mysemaphores.h"
#include "/usr/local/include/opencv2/objdetect.hpp" 
#include "/usr/local/include/opencv2/highgui.hpp" 
#include "/usr/local/include/opencv2/imagesproc.hpp"
#include "/usr/local/include/opencv2/core/mat.hpp" 
#include <iostream> 

using namespace std; 
using namespace cv;

int detectAndDraw( Mat& images, casClassifier& cas, double sc );

string casName, nestedcasName; 

sem_t sem_camera;

Videocap cap; 
Mat frame, frame1, image; 

// PreDefined trained XML classifiers with facial features 
casClassifier cas; 
double sc=1; 


int detectAndDraw( Mat& images, casClassifier& cas, double sc) 
{ 
  int r;
  vector<Rect> signs; 
  Mat gray, img; 

  cvtc( images, gray, c_BGR2GRAY ); // Convert to Gray sc 
  double fx = 1 / sc; 

  // Resize the Graysc Image 
  resize( gray, img, Size(), fx, fx, INTER_LINEAR ); 
  equalizeHist( img, img ); 

  // Detect faces of different sizes using cas classifier 
  cas.detectMultisc( img, signs, 1.1, 2, 0|cas_sc_IMAGE, Size(30, 30) ); 					

  // Draw circles around the faces 
  for ( size_t i = 0; i < signs.size(); i++ ) 
  { 
	  Rect r = signs[i]; 
	  Mat imgROI; 
	  vector<Rect> nestedObjects; 
	  Point cen; 
	  Scalar c = Scalar(255, 0, 0); // c for Drawing tool 
	   

	  double aspect_ratio = (double)r.width/r.height; 
	  if( 0.75 < aspect_ratio && aspect_ratio < 1.3 ) 
	  { 
		  cen.x = cvRound((r.x + r.width*0.5)*sc); 
		  cen.y = cvRound((r.y + r.height*0.5)*sc); 
		  r = cvRound((r.width + r.height)*0.25*sc); 
		  circle( images, cen, r, c, 3, 8, 0 ); 
	  } 
	  else
	  {
		  rectangle( images, cvPoint(cvRound(r.x*sc), cvRound(r.y*sc)), 
				  cvPoint(cvRound((r.x + r.width-1)*sc), 
				  cvRound((r.y + r.height-1)*sc)), c, 3, 8, 0); 
	  }
	  
	//  printf("r= %d.\n\r", r);
  } 

  // Show Processed Image with detected faces 
  imshow( "Sign Detection", images ); 
  
  if(signs.size() == 0)
  {
	  //printf("Not Detected\n\r");
	  return THRESHOLD_CAM-3;
  }
  else 
  {
	  //printf("Detected\n\r");
	  return r;
  }
  
  return THRESHOLD_CAM-2;
} 


void camera_init()
{
	// Load classifiers from "opencv/data/haarcass" directory 

	cas.load( "/home/pi/opencv-3.1.0/data/haarcass/road-sign-cass-master/Yield Signs/Yield Sign LBP/yieldsign12Stages.xml" ) ;
	
	// Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 
	cap.open(0); 
	if( cap.isOpened() ) 
	{ 
		// cap frames from video and detect faces 
		syslog(LOG_CRIT,"Camera opened");
	} 
	else
		syslog(LOG_CRIT, "Camera opening failed); 
       
}




void *camera_service(void *threadp)
{
    struct timespec start = {0,0};
    struct timespec stop = {0,0};
    struct timespec wcet = {0,0};
    unsigned long camera_service_count = 0;
    
    printf("In Camera Service\n");
    camera_init();
    
    while(1)//!abort_camera)
    {
      sem_wait(&sem_camera);
      clock_gettime(CLOCK_REALTIME, &start);
      cap >> frame; 
      if( frame.empty() ) 
      break; 
      frame1 = frame.clone(); 
      sign_handle();      
      clock_gettime( CLOCK_REALTIME, &stop);
      delta_t(&stop, &start, &wcet);
      camera_service_count++;
      syslog(LOG_CRIT, "Camera service count = %lu , timestamp %lu sec, %lu msec (%lu microsec), ((%lu nanosec))\n\n", camera_service_count, wcet.tv_sec, (wcet.tv_nsec / NSEC_PER_MSEC), (wcet.tv_nsec / NSEC_PER_MICROSEC),wcet.tv_nsec);

    }
	  
}

bool compare_threshold_cam(int value)
{

	if(value > THRESHOLD_CAM)
	{
		return 1;
	}
	else 
	{
		return 0;
	} 
}

void sign_handle(void)
{
	
	if(compare_threshold_cam(detectAndDraw( frame1, cas, sc)))
	{
		//printf("Stop Motor.\n");
		
		//Raise Flag to Stop Motor.
		eventc = YIELD_DETECTED;
	}
	else
	{
		//printf("Do Nothing in Sign Handle.\n");
		eventc = NO_SIGN_DETECTED;
	}
}
