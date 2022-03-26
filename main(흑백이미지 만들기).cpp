#include <opencv2\opencv.hpp>

int main()
{
	IplImage * src = cvLoadImage("d:\\penguins.jpg");
	CvSize size = cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);

	for(int y=0; y<size.height; y++)
		for(int x=0; x<size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			int bri = f.val[0] + f.val[1] + f.val[2];
			CvScalar g = cvScalar(bri/7.0f*3, bri/7.0f*3, bri/7.0f);
			cvSet2D(dst, y, x, g);
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}