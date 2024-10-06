#ifndef __CSTRING_H__
#define __CSTRING_H__

/*
    数据结构
     -----------------------0++++++++++++
    [---long---][---long---][char.......]
     volume      length       chars
     容量(0-...)  数量(0-...)  存储位置
*/

char * cstring(char * str);

// 长度包含0x00,即\0的存储位置也计算在内
long    cstringlength(char * cstr);
long    cstringvolume(char * cstr);
void    cstringdescribe(char * cstr, long flag);
char *  cstringcopy(char * cstr);
void    cstringfree(char * cstr);
bool    cstringcompare(char * cstr, char * data);

#endif