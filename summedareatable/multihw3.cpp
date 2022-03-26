#pragma warining(disable:4996)
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
void myFastestMeanFilter(IplImage *src, IplImage *dst, int k);
int main()
{
	cout << "=============================================" << endl;
	cout << "Software Department, Sejong University" << endl;
	cout << "Multimedia Programming Class" << endl;
	cout << "Homework: Fastest Mean Filter" << endl;
	cout << "=============================================" << endl << endl;
	IplImage *src;
	char a[100];
	int num = 0;
	while (true)
	{
		cout << "Input File Path:";
		cin >> (a);
		src = cvLoadImage(a);
		if (src == nullptr)
		{
			cout << "File not Found!" << endl;
		}
		else
		{
			break;
		}
	}
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);
	cout << "Input Kernel Size:";
	cin >> num;
	myFastestMeanFilter(src, dst, num);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}
void myFastestMeanFilter(IplImage *src, IplImage *dst, int k)
{
	CvSize size = cvGetSize(src);
	int num = (2 * k + 1)*(2 * k + 1);
	int x, y;
	CvScalar **f = new CvScalar*[size.height];
	CvScalar **re = new CvScalar*[size.height];

	for (int i = 0; i < size.height; i++)
	{
		f[i] = new CvScalar[size.width];
	}

	for (int i = 0; i < size.height; i++)
	{
		re[i] = new CvScalar[size.width];
	}

	for (y = 0; y < size.height; y++)
	{
		for (x = 0; x < size.width; x++)
		{
			f[y][x] = cvGet2D(src, y, x);
			if (x >= 1)
			{
				f[y][x].val[0] += f[y][x - 1].val[0];
				f[y][x].val[1] += f[y][x - 1].val[1];
				f[y][x].val[2] += f[y][x - 1].val[2];
			}

		}

	}
	for (x = 0; x < size.width; x++)
	{
		for (y = 0; y < size.height; y++)
		{
			if (y >= 1)
			{
				f[y][x].val[0] += f[y - 1][x].val[0];
				f[y][x].val[1] += f[y - 1][x].val[1];
				f[y][x].val[2] += f[y - 1][x].val[2];
			}
		}
	}
	for (y = k; y < size.height-k; y++)
	{
		for (x = k; x < size.width-k ; x++)
		{

			{if (y - (2 * k + 1) >= 0 && x - (2 * k + 1) >= 0)
			{
				re[y][x].val[0] = (f[y][x].val[0] - f[y - (2 * k + 1)][x].val[0] - f[y][x - (2 * k + 1)].val[0] + f[y - (2 * k + 1)][x - (2 * k + 1)].val[0]) / num;
				re[y][x].val[1] = (f[y][x].val[1] - f[y - (2 * k + 1)][x].val[1] - f[y][x - (2 * k + 1)].val[1] + f[y - (2 * k + 1)][x - (2 * k + 1)].val[1]) / num;
				re[y][x].val[2] = (f[y][x].val[2] - f[y - (2 * k + 1)][x].val[2] - f[y][x - (2 * k + 1)].val[2] + f[y - (2 * k + 1)][x - (2 * k + 1)].val[2]) / num;
			}
			cvSet2D(dst, y, x, re[y][x]);
			}
		}
	}
	for (int i = 0; i < size.height; i++)
	{
		delete[]f[i];
	}
	delete[]f;
	for (int i = 0; i < size.height; i++)
	{
		delete[]re[i];
	}
	delete[]re;
}