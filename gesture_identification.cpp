//Program to give commands to your robot through certain gestures inputed using the webcam
#include "opencv2/highgui/highgui.hpp"
#include <typeinfo>
#include "opencv/cv.h"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	int nf = 0;
	Mat frame;
	VideoCapture cap(0);
	namedWindow("bw");

	while (1)
	{
		cap >> frame;
		if (frame.data)
		{
			int r = frame.rows;
			int c = frame.cols;
			Mat modify(r, c, CV_8UC3);
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{

					if (frame.at<Vec3b>(i, j)[2] > 230 && frame.at<Vec3b>(i, j)[1] >240 && frame.at<Vec3b>(i, j)[0] > 240)
					{
						modify.at<Vec3b>(i, j)[0] = 255;
						modify.at<Vec3b>(i, j)[1] = 255;
						modify.at<Vec3b>(i, j)[2] = 255;
					}
					else
					{
						modify.at<Vec3b>(i, j)[0] = 0;
						modify.at<Vec3b>(i, j)[1] = 0;
						modify.at<Vec3b>(i, j)[2] = 0;
					}
				}
			}
			Mat modify3;
			cvtColor(modify, modify3, CV_BGR2GRAY);

			Mat modify2(r, c, CV_8UC1);
			dilate(modify3, modify2, 3);
			int n1x1 = 1;
			int n1x2 = 1;
			int n1x3 = 1;
			int n2x1 = 1;
			int n2x2 = 1;
			int n2x3 = 1;
			int n3x1 = 1;
			int n3x2 = 1;
			int n3x3 = 1;
			int xy = 0;
			int xp = 0;
			int p[100000];
			for (int i = 0; i < r/3; i++)
			{
				for (int j = 0; j < c/3; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n1x1++;
					}
				}
			
				for (int j = c/3; j < 2*c/3; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n1x3++;
					}
				}
			
				for (int j = 2*c/3; j < c; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n1x2++;
					}
				}
			}
			for (int i = r/3; i < 2*r/3; i++)
			{
				for (int j = 0; j < c / 3; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n2x1++;
					}
				}

				for (int j = c / 3; j < 2 * c / 3; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n2x3++;
					}
				}

				for (int j = 2 * c / 3; j < c; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n2x2++;
					}
				}
			}
			for (int i = 2*r/3; i < r; i++)
			{
				for (int j = 0; j < c / 3; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n3x1++;
					}
				}

				for (int j = c / 3; j < 2 * c / 3; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n3x3++;
					}
				}

				for (int j = 2 * c / 3; j < c; j++)
				{
					if (modify2.at<uchar>(i, j) == 255)
					{
						xp = xp + i;
						xy = xy + j;
						n3x2++;
					}
				}
			}

			int nx = n1x1 + n1x2 + n1x3 + n2x1 + n2x2 + n2x3 + n3x1 + n3x2 + n3x3;
			p[nf] = xp / nx;
			/*for (int i = -2; i<3; i++)
			{
			for (int j = -2; j<3; j++)
			{
			modify2.at<uchar>(xp/nx+i,xy/nx+j) = 0;
			}
			}
			*/
			if (nf != 0 && p[nf]>p[nf - 1] + 20)
			{
				cout << "\n Move Left";
			}
			else

			{
				if (nf != 0 && p[nf] + 20 < p[nf - 1])
				{
					cout << "\n Move Right";
				}

				//else
				//{
				//	cout << "\n wait";
				//}
			}
			if (n1x1 > 4000 && n1x2 > 4000)
			{
				cout << "\n Move forward";
			}
			else
			{
				if (n2x1 > 4000 && n2x2 > 4000)
				{
					cout << "\n Move forward";
				}
				else
				if (n3x1 > 4000 && n3x2 > 4000)
				{
					cout << "\n Move backward";
				}
			}
			nf++;

			imshow("bw", modify2);

		}if (waitKey(33) == 'q')
			break;
	}

	return 0;
}
