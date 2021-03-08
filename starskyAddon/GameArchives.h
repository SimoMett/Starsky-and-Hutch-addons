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
	Notes:
	- Files seem to be concatenated
*/
