#include "stdafx.h"
#include <Windows.h>
HANDLE OpenDisk(LPCSTR FileName);
BOOL GetDiskGeometry(HANDLE hDisk, PDISK_GEOMETRY lpGeometry);
BOOL Format(HANDLE hDisk, PDISK_GEOMETRY pGeometry, DWORD StartCylinder, DWORD CylinderNumber);

typedef struct Stack
{
	PVOID StackBasePointer;
	PVOID StackTopPointer;
	DWORD StackSize;
};


int main()
{
	//Cylinder     柱面数
	//MediaType 介质类型
	//TracksPerCylinder 每柱面的磁道数
	//SectorsPerTrack    每磁道的扇区数
	//BytesPerSector      每扇区的字节数
	DISK_GEOMETRY DiskGeo = { 0 };
	ULONGLONG DiskSize;
	HANDLE DiskHandle = OpenDisk("//./C:");
	printf("Handle : 0x%08X \n", DiskHandle);
	GetDiskGeometry(DiskHandle, &DiskGeo);



	DiskSize = DiskGeo.Cylinders.QuadPart*DiskGeo.TracksPerCylinder*DiskGeo.SectorsPerTrack*DiskGeo.BytesPerSector;
	//磁盘容量=柱面数×每个柱面的磁道数×每个磁道的扇区数×每个扇区可以存储的字节数

	/*磁道: 当磁盘旋转时,磁头若保持在一个位置上,则每个磁头都会在磁盘表面划出一个圆形轨迹,这些圆形轨迹就叫做磁道.
	这些磁道用肉眼是根本看不到的,因为它们仅是盘面上以特殊方式磁化了的一些磁化区,磁盘上的信息便是沿着这样的轨道存放的.
	相邻磁道之间并不是紧挨着的,这是因为磁化单元相隔太近时磁性会相互产生影响,同时也为磁头的读写带来困难.

     扇区：磁盘上的每个磁道被等分为若干个弧段,这些弧段便是磁盘的扇区.

     柱面：硬盘通常由重叠的一组盘片构成,每个盘面都被划分为数目相等的磁道,并从外缘的"0"开始编号,具有相同编号的磁道形成一个圆柱,称之为磁盘的柱面.

      簇:"簇"是 DOS 进行分配的最小单位.当创建一个很小的文件时,如是一个字节,则它在磁盘上并不是只占一个字节的空间,而是占有整个一簇.
	  DOS 视不同的存储介质(如软盘,硬盘),不同容量的硬盘,簇的大小也不一样.簇的大小可在称为磁盘参数块(BPB)中获取.簇的概念仅适用于数据区.
	 */

	printf("BytesPerSector : 0x%08X \n", DiskGeo.BytesPerSector);
	printf("Cylinders : 0x%08X \n", DiskGeo.Cylinders);
	printf("Cylinders.QuadPart : 0x%08X \n", DiskGeo.Cylinders.QuadPart);
	printf("MediaType : 0x%08X \n", DiskGeo.MediaType);
	printf("SectorsPerTrack : 0x%08X \n", DiskGeo.SectorsPerTrack);
	printf("TracksPerCylinder : 0x%08X \n", DiskGeo.TracksPerCylinder);
	printf("Disk size = %I64d (Bytes) = %I64d (MB)\n", DiskSize, DiskSize / (1024 * 1024));

	//Format(DiskHandle, &DiskGeo, 0, DiskGeo.Cylinders.QuadPart);


	system("pause");
	return 0;
}
HANDLE OpenDisk(LPCSTR FileName)
{
	return CreateFileA(FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
}
BOOL GetDiskGeometry(HANDLE hDisk, PDISK_GEOMETRY lpGeometry)
{
	DWORD OutBytes;
	BOOL Result;
	Result = DeviceIoControl(hDisk, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, lpGeometry, sizeof(DISK_GEOMETRY), &OutBytes, 0);
	return Result;
}
BOOL Format(HANDLE hDisk, PDISK_GEOMETRY pGeometry, DWORD StartCylinder, DWORD CylinderNumber)
{
	FORMAT_PARAMETERS FormatParam;
	ZeroMemory(&FormatParam, sizeof(FORMAT_PARAMETERS));
	PBAD_TRACK_NUMBER pBadTrack;
	DWORD OutBytes;
	DWORD BuffSize;
	BOOL Result;

	FormatParam.MediaType = pGeometry->MediaType;
	FormatParam.StartCylinderNumber = StartCylinder;
	FormatParam.EndCylinderNumber = StartCylinder + CylinderNumber - 1;
	FormatParam.StartHeadNumber = 0;
	FormatParam.EndHeadNumber = pGeometry->TracksPerCylinder - 1;

	BuffSize = pGeometry->TracksPerCylinder * sizeof(BAD_TRACK_NUMBER);

	
	pBadTrack = (PBAD_TRACK_NUMBER)new BYTE[BuffSize];



	Result = DeviceIoControl(hDisk, IOCTL_DISK_FORMAT_TRACKS, &FormatParam, sizeof(FormatParam), pBadTrack, BuffSize, &OutBytes, 0);



	return Result;

}


