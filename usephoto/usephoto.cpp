#include <opencv2\opencv.hpp>

int main()
{
	IplImage *src = cvLoadImage("c:\\sejong_small.jpg");
	if (src == nullptr) { printf("file not found"); }
	CvSize size = cvGetSize(src);
	IplImage *dst1 = cvCreateImage(size, 8, 3);
	if (dst1 == nullptr) { printf("file not found"); }

	IplImage *dst2 = cvCreateImage(size, 8, 3);
	if (dst2 == nullptr) { printf("file not found"); }

	IplImage *dst3 = cvCreateImage(size, 8, 3);
	if (dst3 == nullptr) { printf("file not found"); }

	IplImage *dst4 = cvCreateImage(size, 8, 3);
	if (dst4 == nullptr) { printf("file not found"); }

	IplImage *dst5 = cvCreateImage(size, 8, 3);
	if (dst5 == nullptr) { printf("file not found"); }

	IplImage *dst6 = cvCreateImage(size, 8, 3);
	if (dst6 == nullptr) { printf("file not found"); }

	//문제 1번
	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, size.height - y - 1, x);
			cvSet2D(dst1, y, x, f);
		}
	}
	//문제 2번
	for (int y1 = 0; y1 < size.height; y1++)
	{
		for (int x1 = 0; x1 < size.width / 2; x1++)
		{
			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst2, y1, x1 + (size.width / 2), f);
		}
	}//하나만 출력하니깐 오른쪽 반만 나옴 그리고 x1+(size.width/2)+1하니깐 안나옴
	for (int y1 = 0; y1 < size.height; y1++)
	{
		for (int x1 = size.width / 2; x1 < size.width; x1++)
		{
			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst2, y1, x1 - (size.width / 2), f);
		}
	}
	//문제 3번
	//마름모 만들기//절대좌표하다가 상대좌표로 바꿔보기
	for (int y3 = 0; y3 < size.height; y3++)
	{
		for (int x3 = 0; x3 < size.width; x3++)
		{			CvScalar f = cvGet2D(src, y3, x3);			int yk = (y3 - size.height / 2);			int xk =(x3 - size.width / 2);			if (xk < 0 )			{				xk = -xk;			}			if (yk < 0)			{				yk = -yk;			}		if ((size.width/2)*(double)yk+(size.height/2*(double)xk)<(size.width/2*size.height/2))
			{

			cvSet2D(dst3, y3, x3, f);

			}
			else
			{
				int bri = f.val[0] + f.val[1] + f.val[2];
				CvScalar g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(dst3, y3, x3, g);			
			}
		}//흑백만들기
	}
	//문제 4번
	for (int y4 = 0; y4 < size.height; y4++)
	{
		for (int x4 = 0; x4 < size.width; x4++)
		{			CvScalar f = cvGet2D(src, y4, x4);			///정수 실수 바꿔줘야 답이나옴 왜그런지는 전혀 모르겠음
			if (((double)x4 - (size.width / 2))*((double)x4 - (size.width / 2)) / ((size.width / 2)*(size.width / 2)) + (((double)y4 - (size.height / 2))*((double)y4 - (size.height / 2))) / ((size.height / 2)*(size.height / 2)) < 1)
			{
				cvSet2D(dst4, y4, x4, f);
			}
			else
			{
				int bri = f.val[0] + f.val[1] + f.val[2];
				CvScalar g = cvScalar(bri / 3, bri / 3, bri / 3);
				cvSet2D(dst4, y4, x4, g);
			}
		}
	}
	//문제 5번
	for (int y5 = 0; y5 < size.height; y5++)
	{
		for (int x5 = 0; x5 < size.width; x5++)
		{			CvScalar f = cvGet2D(src, y5, x5);			///정수 실수 바꿔줘야 답이나옴 왜그런지는 전혀 모르겠음
			double k = ((double)x5 - (size.width / 2))*((double)x5 - (size.width / 2)) / ((size.width / 2)*(size.width / 2)) + (((double)y5 - (size.height / 2))*((double)y5 - (size.height / 2))) / ((size.height / 2)*(size.height / 2));
			if (k <= 0.01||(0.04<=k&&k<=0.09)||(0.16<=k&&k<=0.25)||(0.36<=k&&k<=0.49)|| (0.64<=k&&k<=0.81)||(1<=k&&k<=1.21)||(1.44<=k&&k<=1.69)) 
			{
				cvSet2D(dst5, y5, x5, f);
			}
		}
	}
	int flag = 0;
	int y6 = 0;
	int x6 = 0;
	int yt = 0;
	int xt = 0;
	
	//문제 6번
	while ( x6 <=size.width)
	{
		if (flag == 0)
		{
			for (y6 = yt; y6 < yt + (size.height / 10); y6++)
			{
				if (y6 == size.height)
				{
					xt += (size.width / 10);
					yt = 0;
					flag = 1;
					break;
				}
				for (x6 = xt; x6 < xt + (size.width / 10); x6++)
				{					CvScalar f = cvGet2D(src, y6, x6);					cvSet2D(dst6, y6, x6, f);
				}
			}
			yt += (size.height / 10);
			flag = 1;
		}
		if (flag == 1)
		{
			
			for (y6 = yt; y6 < yt + (size.height / 10); y6++)
			{

				if (y6 == size.height)
				{
					xt += (size.width / 10);
					yt = 0;
					flag = 0;
					break;

				}
				for (x6 = xt; x6 < xt + (size.width / 10); x6++)
				{
				}
			}
			yt += (size.height / 10);
			flag = 0;
		}
	}
	cvShowImage("image1", dst1);
	cvShowImage("image2", dst2);
	cvShowImage("image3", dst3);
	cvShowImage("image4", dst4);
	cvShowImage("image5", dst5);
	cvShowImage("image6", dst6);
	cvWaitKey();

	return 0;
}
