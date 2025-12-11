#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "HidTable.h"
#include <time.h>
#include <stdio.h>
#include "math.h"


namespace kmboxnew {
	int kmNet_init(char* ip, char* port, char* mac);//ok
	int kmNet_mouse_move(short x, short y);			//ok
	int kmNet_mouse_left(int isdown);				//ok
	int kmNet_mouse_right(int isdown);				//ok
	int kmNet_mouse_middle(int isdown);				//ok
	int kmNet_mouse_wheel(int wheel);				//ok
	int kmNet_mouse_all(int button, int x, int y, int wheel);//ok
	int kmNet_mouse_move_auto(int x, int y, int time_ms);	//ok
	int kmNet_mouse_move_beizer(int x, int y, int ms, int x1, int y1, int x2, int y2);//��������

	//���̺���
	int kmNet_keydown(int vkey);// ok
	int kmNet_keyup(int vkey);  // ok

	//���ϵ��
	int kmNet_monitor(short port);			//����ر����������
	int kmNet_monitor_mouse_left();			//��ѯ����������״̬
	int kmNet_monitor_mouse_middle();		//��ѯ����м�״̬
	int kmNet_monitor_mouse_right();		//��ѯ����Ҽ�״̬
	int kmNet_monitor_mouse_side1();		//��ѯ�����1״̬
	int kmNet_monitor_mouse_side2();		//��ѯ�����2״̬ 
	int kmNet_monitor_keyboard(short  vk_key);//��ѯ����ָ������״̬
	//�����������ϵ��
	int kmNet_mask_mouse_left(int enable);	//���������� 
	int kmNet_mask_mouse_right(int enable);	//��������Ҽ� 
	int kmNet_mask_mouse_middle(int enable);//��������м� 
	int kmNet_mask_mouse_side1(int enable);	//�����������1 
	int kmNet_mask_mouse_side2(int enable);	//�����������2
	int kmNet_mask_mouse_x(int enable);		//�������X������
	int kmNet_mask_mouse_y(int enable);		//�������y������
	int kmNet_mask_mouse_wheel(int enable);	//����������
	int kmNet_mask_keyboard(short vkey);	//���μ���ָ������
	int kmNet_unmask_keyboard(short vkey);	//�������ָ������
	int kmNet_unmask_all();					//������������Ѿ����õ���������


	//�����ຯ��
	int kmNet_reboot(void);									  //�������
	int kmNet_setconfig(char* ip, unsigned short port);		  //���ú���IP��ַ
	int kmNet_setvidpid(unsigned short vid, unsigned short pid);//���ú���VIDPID ���ú���Ҫ������ӡ��´��ϵ������Ч
	int kmNet_debug(short port, char enable);				  //����ʹ��
	int kmNet_lcd_color(unsigned short rgb565);				  //������LCD��Ļ��ָ����ɫ��䡣 ���������ú�ɫ
	int kmNet_lcd_picture_bottom(unsigned char* buff_128_80); //�°벿����ʾ128x80ͼƬ
	int kmNet_lcd_picture(unsigned char* buff_128_160);		  //������ʾ128x160ͼƬ
}