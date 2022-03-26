#include <opencv2\opencv.hpp>

int main()
{
	CvSize size = cvSize(500,100);
	IplImage * img = cvCreateImage(size, 8, 3);
	cvSet(img, cvScalar(255,255,255));

	for(int y=0; y<size.height; y++)
		for(int x=0; x<size.width; x++)
		{
												// 0< x < W
			float ix =2*float(x)/size.width-1;		// -1< ix <1
			float iy =2*float(y)/size.height-1;		// -1< iy <1
			float f = sqrt(ix*ix+iy*iy)/sqrt(2.0f);
			cvSet2D(img, y, x, cvScalar(255*f, 0, 255-255*f));
		}

	cvShowImage("image", img);
	cvWaitKey();

	return 0;
}