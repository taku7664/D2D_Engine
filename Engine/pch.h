#ifndef PCH_H
#define PCH_H

#include <stdlib.h>
#include <Windows.h>
#include <assert.h>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>
#include <algorithm>

//Direct2D
#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include <d2d1_1helper.h>
#include <wincodec.h>
#include <comdef.h>

// Fmod
#include "Library/FMOD/Include/fmod.hpp"
#include "Library/FMOD/Include/fmod_studio.hpp"
#include "Library/FMOD/Include/fmod_common.h"
#include "Library/FMOD/Include/fmod_codec.h"
//#pragma comment (lib, "Library/FMOD/Include/fmod_vc.lib")

#include "Helper/CommonEnum.h"
#include "Helper/Math/MathF.h"
#include "Helper/DataType/Vector2.h"
#include "Helper/ReferenceCounter.h"
#include "Helper/Utillity.h"
#include "Helper/Debug.h"
#include "Helper/Time/Time.h"
#include "Helper/Input/Input.h"
#endif //PCH_H
