#include "cocos2d.h"
#include "Help.h"
#include "Singleton.h"

Help::Help():
	text
	{
		"�������� �Ź߹�ư�� ������ ������ �� �ֽ��ϴ�.\n��ٸ���ó�ΰ��� �Ŵ޸���� �ٲ�ϴ�",
		"���� ��� �� �� �ֽ��ϴ�.\n������ �ݰ� ������ó���� ����� �� �ֽ��ϴ�.",
		"�߾��� ��ư�� ���ŷ� �̵��� �� �ֽ��ϴ�.\n���� �������� �ø��� ���� �����Դϴ�.",
		"1-4",
		"1-5",
		"�����ߴ� ���� ��� ������",
		"2-2",
		"2-3",
		"2-4",
		"2-5"
	}
{
}

const char* Help::Return()
{
	Chaptor = Singleton::getInstance()->IsChapter();
	Stage = Singleton::getInstance()->IsLevel();
	select = ((Chaptor - 1) * 5) + Stage;
	return text[select - 1].c_str();
}
