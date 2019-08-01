#include "cocos2d.h"
#include "Help.h"
#include "Singleton.h"

Help::Help():
	text
	{
		"오른쪽의 신발버튼을 누르면 점프할 수 있습니다.\n사다리근처로가면 매달리기로 바뀝니다",
		"돌은 밟고 밀 수 있습니다.\n성냥을 줍고 나무근처에서 사용할 수 있습니다.",
		"중앙의 버튼은 과거로 이동할 수 있습니다.\n돌을 발판위에 올리면 벽이 움직입니다.",
		"1-4",
		"1-5",
		"경험했던 것을 모두 쓰세요",
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
