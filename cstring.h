#ifndef __CSTR_H__
#define __CSTR_H__

/*
    数据结构
    [00000000]cccccccc...
      count  |  chars 
*/

char * cstring(char * source);
/*
    长度包含0x00,即\0的存储位置也计算在内
*/
long cstringlength(char * source);
void cstringdescribe(char * cstring, long flag);
char * cstringcopy(char * source);

#endif