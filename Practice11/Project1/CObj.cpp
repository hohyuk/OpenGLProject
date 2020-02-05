#include "CObj.h"

CObj::CObj()
{

}

CObj::~CObj()
{

}

//GLubyte * CObj::LoadDIBitMap(const char * filename, BITMAPINFO ** info)
//{
//	FILE* fp;
//
//	GLubyte* bits;
//	int bitsize, infosize;
//	BITMAPFILEHEADER header;
//
//	if ((fp = fopen(filename, "rb")) == NULL)
//		return NULL;
//
//	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
//	{
//		fclose(fp);
//		return NULL;
//	}
//
//	if (header.bfType != 'MB')
//	{
//		fclose(fp);
//		return NULL;
//	}
//
//	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
//	
//	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL)
//	{
//		fclose(fp);
//		exit(0);
//		return NULL;
//	}
//
//	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
//	{
//		free (*info);
//		fclose(fp);
//		return NULL;
//	}
//
//	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
//		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8 * abs((*info)->bmiHeader.biHeight);
//
//	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) 
//	{
//		free(*info);
//		fclose(fp);
//		return NULL;
//	}
//	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
//	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
//	{
//		free(*info); free(bits);
//		fclose(fp);
//		return NULL;
//	}
//
//	fclose(fp);
//	return bits;
//}
