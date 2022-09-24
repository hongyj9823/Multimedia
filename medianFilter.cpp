#include <opencv2\opencv.hpp>


#include <opencv2\opencv.hpp>

int compare(CvScalar a, CvScalar b)		// a-b
{
	int bri1 = a.val[0] + a.val[1] + a.val[2]; 
	int bri2 = b.val[0] + b.val[1] + b.val[2]; 
	return bri1-bri2;
}

int main()
{
	IplImage * src = cvLoadImage("d:\\saltpepper.jpg");
	CvSize size =cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);
	
//	int type = CV_BLUR;				// mean filter;
//	int type = CV_GAUSSIAN;
//	int type = CV_MEDIAN;
//	cvSmooth(src, dst, type, 11);


	int k = 3;
	int num = (2*k+1)*(2*k+1);
	CvScalar * f = new CvScalar [num];
	for(int y=0; y<size.height; y++)
		for(int x=0; x<size.width; x++)
		{
			int count = 0;
			for(int v=-k; v<=k; v++)
				for(int u=-k; u<=k; u++)
				{
					if(y+v<0 || y+v>size.height-1) continue;
					if(x+u<0 || x+u>size.width-1) continue;
					f[count] = cvGet2D(src, y+v, x+u);
					count ++;
				}

			for(int j=0; j<count-1; j++)
				for(int i=j+1; i<count; i++)
					if(compare(f[j],f[i])>0)
					{
						CvScalar temp = f[j];
						f[j] = f[i];
						f[i] = temp;
					}

			CvScalar g = f[count/2];
			cvSet2D(dst, y, x, g);
		}
	delete [] f;

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}
