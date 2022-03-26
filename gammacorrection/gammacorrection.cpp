#include<opencv2/opencv.hpp>
#include<math.h>
void adjustGamma(IplImage *src, IplImage * dst, double gamma)
{
CvSize size = cvGetSize(src);
if (gamma <= 0)
{
	cvSet(dst, cvScalar(255, 255, 255));
}
else
{
	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;
			for (int k = 0; k < 3; k++)
				g.val[k] = pow(f.val[k] / 255, gamma) * 255; 
			cvSet2D(dst, y, x, g);
		}
	}
}
cvShowImage("Image", dst);

}
void Gammagraph(IplImage *graph, double gamma)
{
	cvSet(graph, cvScalar(255, 255, 255));
	if (gamma <= 0)
	{
		for (int x = 0; x < 250; x++)
		{
			int y = 0;
			cvSet2D(graph, y, x, cvScalar(0, 0, 0));
		}
	}
	else
	{
		for (int x = 0; x < 250; x++)
		{
			double  y = (250 - 1) - (pow((double)x / (250 - 1), gamma))*(250 - 1);
			cvSet2D(graph, y, x, cvScalar(0, 0, 0));
		}
	}
	cvShowImage("Graph", graph);
}
void adjustsin(IplImage *src, IplImage * dst, double sine)
{
	CvSize size = cvGetSize(src);
	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;
			for (int k = 0; k < 3; k++)
				g.val[k] = (255)* sin((2 * 3.14 / 249) * sine  * f.val[k]);

			cvSet2D(dst, y, x, g);
		}
	}
	cvShowImage("Image", dst);
}
void sinegraph(IplImage *graph, double sine)
{
	cvSet(graph, cvScalar(255, 255, 255));
	for (int x = 0; x < 250; x++)
	{
		double  y = (124) - (124)*sin((2 * 3.14 / 249)*sine*(double)x);
		cvSet2D(graph, y, x, cvScalar(0, 0, 0));
	}
	cvShowImage("Graph", graph);
}
int main()
{
	IplImage *src;
	char a[100];
	int num;
	printf("=============================================\n");
	printf("Dept. of Digital Contents, Sejong University\n");
	printf("Multimedia Programming Homework #2\n");
	printf("Point Processing - Gamma Correction and more\n");
	printf("=============================================\n");
	while (true)
	{
		printf("\nInput File Path: ");
		scanf("%s", a);
		src = cvLoadImage(a);
		if (src == nullptr)
		{
			printf("File not Found!");
		}
		else
		{
			break;
		}
	}
	printf("Select function (1=gamma, 2=sinusoidal):");
	scanf("%d", &num);
	printf("\n=============================================\n");
	if (num == 1)
	{
		CvSize size = cvGetSize(src);
		IplImage *dst = cvCreateImage(size, 8, 3);
		float gamma = 1.0f;

		adjustGamma(src, dst, gamma);

		IplImage *graph = cvCreateImage(cvSize(250, 250), 8, 3);
		Gammagraph(graph, gamma);

		printf("Gamma Function\n");
		printf("Press following keys!\n");
		printf("   1 : increasing Gamma by 0.1\n");
		printf("   2 : decreasing Gamma by 0.1\n");
		printf("   Q : quit the program\n");
		printf("=============================================\n");

	
		while (true)
		{
			int key = cvWaitKey();
			if (key == '1')
			{
				gamma += 0.1f;
				adjustGamma(src, dst, gamma);
				Gammagraph(graph, gamma);
				printf("Current Gamma = %f\n", gamma);
			}
			if (key == '2')
			{
				gamma -= 0.1f;
				adjustGamma(src, dst, gamma);
				Gammagraph(graph, gamma);
				if (gamma <= 0)
				{
					printf("Current Gamma = 0.000000\n");
					gamma = 0;
				}
				else
				{
					printf("Current Gamma = %f\n", gamma);
				}
			}
			if (key == 'Q') exit(0);
		}
	}
	else {
		CvSize size = cvGetSize(src);
		IplImage *dst = cvCreateImage(size, 8, 3);
		float sine = 1.0f;
	
		adjustsin(src, dst, sine);
	
		IplImage *graph = cvCreateImage(cvSize(250, 250), 8, 3);
		sinegraph(graph, sine);
		printf("Sinusoidal Function\n");
		printf("Press following keys!\n");
		printf("   1 : increasing frequency\n");
		printf("   2 : decreasing frequency\n");
		printf("   Q : quit the program\n");
		printf("=============================================\n");
	
		while (true)
		{
			int key = cvWaitKey();
			if (key == '1')
			{
				sine += 0.5f;
				adjustsin(src, dst, sine);
				sinegraph(graph, sine);
				printf("Current Freq. = %f\n", sine);
			}
			if (key == '2')
			{
				sine -= 0.5f;
				if (sine <= 0.5)
				{
					printf("Current Freq. = 0.500000\n");
					sine = 0.500000;
				}
				else
				{
					printf("Current Freq. = %f\n", sine);
				}
				adjustsin(src, dst, sine);
				sinegraph(graph, sine);
			}
			if (key == 'Q') exit(0);
		}
	}
	return 0;
}