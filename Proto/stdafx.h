#pragma once
//
// Ԥ����ͷ�ļ�, ���ڰ���ϵͳ���������ȶ���ͷ�ļ�
//
//#include "vld.h"	// vldͷ�ļ�, �����ڴ�й©���, ������ߵĽ�������_CrtSetDbgFlag��ϸ, �ⲿ���й©Ҳ�ܹ���λ

// ʹ�ý��涯̬����
#define  GXWE_GENERATEMODE_FRAME

// ʹ��Crash Dumpģ��
#define CRASHDUMP_USING

// ���ý�ɫ�����ٶȵ��ڹ���
//#define FIND_SPRITE_SPEED

// ָ�������ƶ�ģ��İ汾
#define SPRITE_MOVE_VERSION_0X 0
#define SPRITE_MOVE_VERSION_1X 1
#define SPRITE_MOVE_VERSION SPRITE_MOVE_VERSION_1X

// ������־����
#define OPEN_LOGGER

#include <assert.h>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <fstream>
#include <deque>
#include <locale>

#if (defined WIN7_32) || (defined WINAPI_FAMILY && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#include "../include/cauthc.h"
#endif

#include "nuiengine.h"
#include "nuienv.h"
#include "nuiapp.h"

#if (defined WIN7_32) || (defined WINAPI_FAMILY && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)

#include "log/CoreLog.h"
#include "Singleton.hpp"
#else
#include "../../../common/platform/log/CoreLog.h"
#include "../../../common/platform/Singleton.hpp"

#include "NetConnection.h"

#endif

#include "common/nuworldlogiccoord.h"
#include "common/nulog.h"
#include "renderer/nurenderer.h"
#include "particlesystem/nuparticlemanager.h"
#include "renderer/nucocos2d_render.h"
#include "common/nuxptypes.h"
#include "common/nuutil.h"
#include "common/nuxbuffer.h"
#ifdef WIN7_32
#include "octets.h"
#include "marshal.h"
#endif
#include "../../../common/ljfm/code/include/ljfm.h"
#include "UICommonHeader.h"
#define mynew DEBUG_NEW


namespace Nuclear
{
	inline int distance(Nuclear::NuclearLocation& pt1, Nuclear::NuclearLocation& pt2)
	{
		return abs(static_cast<int>(pt1.x - pt2.x)) > abs(static_cast<int>(pt1.y - pt2.y)) ? abs(static_cast<int>(pt1.x - pt2.x)) : abs(static_cast<int>(pt1.y - pt2.y));
	}
}
const float PI = 3.14159265f;
