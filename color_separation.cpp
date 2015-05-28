#include "highgui.h"
#include <cv.h>

void separation(IplImage *src, IplImage *dst){
  //陣列方式宣告
	//unsigned char** R = new unsigned char *[src->height];	
	//unsigned char** G = new unsigned char *[src->height];
	//unsigned char** B = new unsigned char *[src->height];
	//for( int i = 0 ; i < src->height ; i++ ){
	//	R[i] = new unsigned char[src->width];
	//	G[i] = new unsigned char[src->width];
	//	B[i] = new unsigned char[src->width];
	//}
//指標方式宣告
	IplImage *R = cvCreateImage(cvGetSize(src),8,1);
	IplImage *G = cvCreateImage(cvGetSize(src),8,1);
	IplImage *B = cvCreateImage(cvGetSize(src),8,1);
	for( int i=0 ; i<src->height ; i++ ){
		int countR=0,countG=0,countB=0;
		for ( int j=0; j<src->widthStep ; j++ ){
			if	( j%3==2 ){
				R->imageData[i*R->width+countR]= src->imageData[i*src->widthStep+j];
				countR++;
			}
			if ( j%3==1 ){
				G->imageData[i*G->width+countG]= src->imageData[i*src->widthStep+j];
				countG++;
			}
			if ( j%3==0 ){
				B->imageData[i*B->width+countB]= src->imageData[i*src->widthStep+j];
				countB++;
			}
		}
	}
//RGB矩陣測試
	//for( int i=0 ; i<src->height ; i++ ){
	//	for(int j=0 ; j<src->width ; j++){
	//		unsigned char temp=B->imageData[i*B->width+j];
	//		int t = temp;
	//		std::cout<<t<<std::endl; 
	//	}
	//}
	for( int i=0 ; i<dst->height ; i++ ){
		for( int j=0 ; j< dst->width ; j++ ){
			unsigned char temp=B->imageData[i*B->width+j];
			unsigned char temp1=G->imageData[i*G->width+j];
			unsigned char temp2=R->imageData[i*R->width+j];
			int t=temp;
			int t1=temp1;
			int t2=temp2;
			if ( temp == 0 && temp1 == 255 && temp2 == 255  ){
				for(int k=0 ; k<3 ; k++)
				dst->imageData[ i*dst->widthStep+j*3+k ] = src->imageData[ i*src->widthStep+j*3+k ];
			}
			else if( temp + temp1 + temp2 >=255 ){ 
				for( int k=0 ; k<3 ;k++)
				dst->imageData[ i*dst->widthStep+j*3+k ] = 255;
			}

		}
	}
}
int main()
{
IplImage *Img; 
IplImage *dst;
Img = cvLoadImage("rgb2.bmp",1); 

int i, j, IW, IL;
IW = Img->height;
IL = Img->width;
dst= cvCreateImage( cvSize(IL ,IW) , 8, 3 );

separation( Img , dst);

//顯示影像
cvNamedWindow("Picture",1); 
cvShowImage("Picture",Img);
cvNamedWindow("Picture1",1); //建立視窗(視窗名稱,參數) 
cvShowImage("Picture1",dst); //顯示影像(視窗名稱,影像檔案) 
cvWaitKey(0); //按下任意按鍵可將圖片關閉
return 0;
}
