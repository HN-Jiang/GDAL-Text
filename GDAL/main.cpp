#include "gdal_priv.h"
#include<iostream>
#include "string"
#include "complex"

using namespace std;
int main()
{
	string file_path = "‪E:\\bzar_unit_test\\radar\\s1\\S1A_IW_SLC__1SDV_20160229T010636_20160229T010704_010154_00EFA8_BFA7.SAFE\\measurement\\s1a-iw1-slc-vh-20160229t010636-20160229t010704-010154-00efa8-001.tiff";
	GDALAllRegister();
	auto dataset = static_cast<GDALDataset*>(GDALOpen(file_path.c_str(), GA_ReadOnly));
	if (dataset == nullptr)
	{
		cout << "Error opening file" << endl;
		return 1;
	}

	auto band = dataset->GetRasterBand(1);
	if (band == nullptr)
	{
		cout << "Error opening band" << endl;
		return 1;
	}

	int width = band->GetXSize();
	int ysize = band->GetYSize();
	//申请储存空间，为一行的大小
	//complex<float>* line_buffer = (complex<float>*) CPLMalloc(sizeof(complex<float> * width));
	//dynamic area
	vector<complex<float>> line_buffer(width);
	//shared_ptr<vector<complex<float>>> line;

	/*第一个参数指定是读取还是写入，23代表读取或写入的起始坐标（0，0），45代表读取或写入图像窗口大小（先宽度，后高度）
	第六个是指针，读取或写入存到哪里，78指定缓冲区大小，6的大小应该为7*8，9存储类型，1011一般用0*/

	band->RasterIO(GF_Read, 0, 0, width, 1, line_buffer.data(), width, 1, GDT_CFloat32, 0, 0);
	//band->RasterIO(GF_Read, 0, 0, width, 1, line.get(), width, 1, GDT_CFloat32, 0, 0);

	//提取幅度和相位
	auto pix = line_buffer[1000];
	
	float amplitude = std::abs(pix);
	float phase = std::arg(pix);
	cout << "Amplitude" << amplitude << endl << "phase" << phase << endl;
	

	
	//CPLFree(line_buffer);
	GDALClose(dataset);

	return 0;

}
