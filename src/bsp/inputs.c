#include "..\include_s.h"


void update_all_inputs(void)
{
     Get_TK_States();//������ӱ���õļ�ֵ
     scan_key=sino_key_value;//��������ӱ���õļ�ֵ����key_scan����ʹ��
     key_board_scan(&kb);//����Ϣ����
}