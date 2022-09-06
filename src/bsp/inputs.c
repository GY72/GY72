#include "..\include_s.h"


void update_all_inputs(void)
{
     Get_TK_States();//调用中颖库获得的键值
     scan_key=sino_key_value;//将调用中颖库获得的键值付给key_scan函数使用
     key_board_scan(&kb);//键信息处理
}