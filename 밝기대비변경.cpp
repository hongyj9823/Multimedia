#include <opencv2\opencv.hpp>

void adjustBriContrast(IplImage * src, IplImage * dst, 
	                   float a, float b)
{
	CvSize size = cvGetSize(src);
	for(int y=0; y<size.height; y++)
		for(int x=0; x<size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g = f;
			if(x>size.width/2)
				for(int k=0; k<3; k++)
					g.val[k]= a*f.val[k]+b;
			cvSet2D(dst, y, x, g);
		}
}

int main()
{
	IplImage * src = cvLoadImage("d:\\penguins.jpg");
	if(src == NULL) printf("File Not Found!");
	CvSize size = cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);

	float a = 1.0f;
	float b = 0.0f;
	while(true)
	{
		printf("a= %f, b= %f \n", a, b);
		adjustBriContrast(src, dst, a, b);
		cvShowImage("dst", dst);
		int key = cvWaitKey();
		switch(key)
		{
		case '1':	b += 10;	break;
		case '2':	b -= 10;	break;
		case '3':	a += 0.1f;	break;
		case '4':	a -= 0.1f;	break;
		case 'q':
		case 'Q':	exit(0);	break;
		default:				break;
		}
	}
	return 0;
}