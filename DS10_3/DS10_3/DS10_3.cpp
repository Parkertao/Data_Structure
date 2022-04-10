// test hash table class
#include <iostream>
#include "hashChains.h"
#include <iostream>
#include <fstream>

using namespace std;
/*
int t_main()
{
	hashChains<int, int> z(11);
	pair<int, int> p;

	// test insert
	p.first = 2; p.second = 10;
	z.insert(p);
	p.first = 10; p.second = 50;
	z.insert(p);
	p.first = 24; p.second = 120;
	z.insert(p);
	p.first = 32; p.second = 160;
	z.insert(p);
	p.first = 3; p.second = 15;
	z.insert(p);
	p.first = 12; p.second = 60;
	z.insert(p);
	cout << "The dictionary is " << endl << z << endl;
	cout << "Its siz is " << z.siz() << endl;

	// test find
	cout << "Element associated with 2 is " << z.find(2)->second << endl;
	cout << "Element associated with 10 is " << z.find(10)->second << endl;
	cout << "Element associated with 12 is " << z.find(12)->second << endl;
	return 0;
}

*/

//LZW压缩
/*
const int	DIVISOR = 4099,
			MAX_CODES = 4096,
			BYTE_SIZE = 8,
			EXCESS = 4,
			ALPHA = 256,
			MASK1 = 255,
			MASK2 = 15;

typedef pair<const long, int> pairType;

int leftOver;
bool bitsLeftOver = false;
ifstream in;
ofstream out;

void setFiles(int argc, char* argv[]);
void output(long pcode);
void compress();

int main(int argc, char* argv[])
{
	setFiles(argc, argv);
	compress();
}

void setFiles(int argc, char* argv[])
{
	char outputFile[50], inputFile[54];
	if (argc >= 2)
		strcpy_s(inputFile, argv[1]);
	else
	{
		cout << "Enter name of file to compress" << endl;
		cin >> inputFile;
	}
	in.open(inputFile, ios::binary);
	if (in.fail()) {
		cerr << "Cannot open " << inputFile << endl;
		exit(1);
	}
	strcpy_s(outputFile, inputFile);
	strcat_s(outputFile, ".zzz");
	out.open(outputFile, ios::binary);
}

void output(long pcode)
{
	int c, d;
	if (bitsLeftOver)
	{
		d = int(pcode & MASK1);//截取pcode后8位
		c = int((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
		//pcode右移8位后剩下前4位，与上一次输出时剩下的4位leftOver相加（leftOver左移4位后再|效果等同于相加）
		//保持顺序
		out.put(c);
		out.put(d);
		bitsLeftOver = false;
	}
	else
	{
		leftOver = pcode & MASK2;//截取pcode后4位
		c = int(pcode >> EXCESS);//pcode右移4位，剩下前8位先输出
		out.put(c);
		bitsLeftOver = true;
	}
}

void compress()
{
	hashChains<long, int>h(DIVISOR);
	for (int i = 0;i < ALPHA;i++)
		h.insert(pairType(i, i));//初始化hash表，256个ASCII码以及其对应的value
	int codeUsed = ALPHA;//使用了256个码，最大码数为2^12=4096

	int c = in.get();
	if (c != EOF)
	{
		long pcode = c;//第一个字符，一定在hash表中
		while ((c = in.get()) != EOF)//读取下一个c，开始处理
		{
			long theKey = (pcode << BYTE_SIZE) + c;//pcode左移8位形成前缀，再加上c，得到键值
			pairType* thePair = h.find(theKey);//查找该键值
			if (thePair == NULL)//如果hash表中没有该键值，则需要插入该键值
			{
				output(pcode);//将键值输出到文件中？？不对劲
				if (codeUsed < MAX_CODES)//如果还有码数可以使用，则可以插入该新键值以及其对应value即codeUsed值
					h.insert(pairType((pcode << BYTE_SIZE) | c, codeUsed++));
				pcode = c;
			}
			else pcode = thePair->second;//把键值更新为代码
		}
		output(pcode);
		if (bitsLeftOver)
			out.put(leftOver << EXCESS);
	}
	out.close();
	in.close();
}
*/


// constants
const int MAX_CODES = 4096,    // 2^12
BYTE_SIZE = 8,
EXCESS = 4,          // 12 - BYTE_SIZE
ALPHA = 256,         // 2^BYTE_SIZE
MASK = 15;           // 2^EXCESS - 1

typedef pair<int, char> pairType;

// globals
pairType ht[MAX_CODES];        // dictionary
char s[MAX_CODES];             // used to reconstruct text
int siz = 0;                      // siz of reconstructed text
int leftOver;                  // code bits yet to be output
bool bitsLeftOver = false;     // false means no bits in leftOver
ifstream in;                   // input file
ofstream out;                  // output file

void setFiles(int argc, char* argv[])
{// Determine file name.
	char outputFile[50], inputFile[54];

	// see if file name provided
	if (argc == 2)
		strcpy_s(outputFile, argv[1]);
	else
	{// name not provided, ask for it
		cout << "Enter name of file to decompress"
			<< endl;
		cout << "Omit the extension .zzz" << endl;
		cin >> outputFile;
	}

	strcpy_s(inputFile, outputFile);
	strcat_s(inputFile, ".zzz");

	// open files in binary mode
	in.open(inputFile, ios::binary);
	if (in.fail())
	{
		cerr << "Cannot open " << inputFile << endl;
		exit(1);
	}
	out.open(outputFile, ios::binary);
}

bool getCode(int& code);
void output(int code);

void decompress()
{// Decompress a compressed file.
	int codesUsed = ALPHA; // codes codesUsed so far

	// input and decompress
	int pcode,  // previous code
		ccode;  // current code
	if (getCode(pcode))
	{// file is not empty
		s[0] = pcode;   // character for pcode 
		out.put(s[0]);  // output string for pcode
		siz = 0; // s[siz] is first character of
				  // last string output

		while (getCode(ccode))
		{// there is another code
			if (ccode < codesUsed)
			{// ccode is defined
				output(ccode);
				if (codesUsed < MAX_CODES)
				{// create new code
					ht[codesUsed].first = pcode;
					ht[codesUsed++].second = s[siz];
				}
			}
			else
			{// special case, undefined code
				ht[codesUsed].first = pcode;
				ht[codesUsed++].second = s[siz];
				output(ccode);
			}
			pcode = ccode;
		}
	}

	out.close();
	in.close();
}

bool getCode(int& code)
{// Put next code in compressed file into code.
 // Return false if no more codes.
	int c, d;
	if ((c = in.get()) == EOF)
		return false;  // no more codes

	 // see if any left over bits from before
	 // if yes, concatenate with left over 4 bits
	if (bitsLeftOver)
		code = (leftOver << BYTE_SIZE) | c;
	else
	{// no left over bits, need four more bits
	 // to complete code
		d = in.get();  // another 8 bits
		code = (c << EXCESS) | (d >> EXCESS);
		leftOver = d & MASK;  // save 4 bits
	}
	bitsLeftOver = !bitsLeftOver;
	return true;
}

void output(int code)
{// Output string corresponding to code.
	siz = -1;
	while (code >= ALPHA)
	{// suffix in dictionary
		s[++siz] = ht[code].second;
		code = ht[code].first;
	}
	s[++siz] = code;  // code < ALPHA

	// decompressed string is s[siz] ... s[0]
	for (int i = siz; i >= 0; i--)
		out.put(s[i]);
}

int main(int argc, char* argv[])
{
	setFiles(argc, argv);
	decompress();
	return 0;
}
