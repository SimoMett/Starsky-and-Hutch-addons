#pragma once

struct BTWArchive
{
	int empty1[2];//8 null bytes
	char wad[4];//contains "WAD!"
	int unk1;//Always = 4
	unsigned char unk2[6];//Always = D3 07 0B 04 03 0C
	unsigned char unk3[2];
	char archiveName [128];//null-terminated string - all zeros until byte 0x98 - I assume it's a 128 byte string
	unsigned int sizeOfSomething;//The value stored here is almost the size of the file
};

/*
	Notes:
	- At the address of "sizeOfSomething" apparently begins another chunk of data.
	- The string "‰PNG" always occupies a multiple of 4 position (maybe it's useless)
*/