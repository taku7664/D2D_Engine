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

#include <d2d1.h>
#include <dwrite.h>
#include <d2d1_1helper.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#include <wincodec.h>
#include <comdef.h>

#include "Helper/CommonEnum.h"
#include "Helper/Math/MathF.h"
#include "Helper/DataType/Vector2.h"
#include "Helper/ReferenceCounter.h"
#include "Helper/Utillity.h"
#include "Helper/Debug.h"
#include "Helper/Time/Time.h"
#include "Helper/Input/Input.h"
#endif //PCH_H
