#pragma once

struct BTWArchive
{
	int empty1[2];//8 null bytes
	char wad[4];//contains "WAD!"
	int unk1;//Always = 4
	unsigned char unk2[6];//Always = D3 07 0B 04 03 0C
	unsigned char unk3[2];
	char archiveName [128];//null-terminated string - all zeros until byte 0x98 - I assume it's a 128 byte string
	
	unsigned int unk6DataChunkStart;
	unsigned int unk6DataChunkSize;
	
	unsigned int unk7;//it's a low number (count of smth?)
	unsigned int unk8;//in all .btw files is stored the same address as in unk6DataChunkStart
	unsigned int unk9;//in all .btw files = 0
	unsigned int unk10;

	unsigned int unk11DataChunkStart;
	unsigned int unk11DataChunkSize;
	unsigned int unk12DataChunkStart;
	unsigned int unk12DataChunkSize;

	unsigned int usedFileTypesStringStart;
	unsigned int usedFileTypesStringSize;//Number or actual types of file

	unsigned int unk5DataChunkStart;
	unsigned int unk5DataChunkSize;//Size in "4 bytes" (number of bytes: unk5DataChunkSize*4)

	unsigned int namesEntryStart;//At the pointed address start a string with (probably) names of files contained in the archive
	unsigned int namesEntrySize;//size of the long string (in bytes)
	//first file start
};

/*
	From template:

	struct Date
	{
	    u16 year;
	    u8 month;
	    u8 day;
	    u8 hour;
	    u8 minutes;
	};
	
	struct BtwHeader
	{
	    u32 empty1[2];//8 null bytes
	    char wad[4];//contains "WAD!"
	    u32 four;//Always = 4
	    Date date;//Always = D3 07 0B 04 03 0C
	    char unk0[2];
	    char archiveName [128];//null-terminated string - all zeros until byte 0x98 - I assume it's a 128 byte string
	
	    u32 mainSectionStart;
		u32 mainSectionSize;
		
		u32 subSection1Count;
		u32 subSection1Start;
		
		u32 unk9;//in all .btw files = 0
		
		u32 assetsCount;
		u32 assetsStart;
		
		u32 subSection2Count;
		u32 subSection2Start;
		
		u32 unk2;
		
		u32 fileTypesStringStart;
		u32 fileTypesStringSize;//Number or actual types of file
		
		u32 subSection3Start;
		u32 subSection3Count;//Size in "4 bytes" (number of bytes: unk5DataChunkSize*4)
		
		u32 namesEntryStart;//At the pointed address start a string with (probably) names of files contained in the archive
		u32 namesEntrySize;//size of the long string (in bytes)
	};
	
	
	BtwHeader header @ 0x0;
	
	struct File
	{
	    u32 size;
	    u32 start;
	};
	
	struct Item1
	{
	    u32 a;
	    u32 b;
	};
	
	struct Item2
	{
	    u32 a;
	};
	
	struct FileType
	{
	    char name[4];
	};
	
	struct Item3
	{
	    u32 a;
	};
	
	//u8 mainSection[header.mainSectionSize] @ header.mainSectionStart;
	u8 mainSection @ header.mainSectionStart;
	
	Item1 subSection1[header.subSection1Count] @ header.subSection1Start;
	
	File filesInfoSection[header.assetsCount] @ header.assetsStart;
	
	Item2 subSection2[header.subSection2Count] @ header.subSection2Start;
	
	FileType fileTypesSection[header.fileTypesStringSize] @ header.fileTypesStringStart;
	
	Item3 subSection3[header.subSection3Count] @ header.subSection3Start;
	
	u8 namesSection[header.namesEntrySize] @ header.namesEntryStart;

*/
