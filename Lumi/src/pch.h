#pragma once

// STL
// ------
// io
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
// memory
#include <memory>
// algorithm
#include <algorithm>
#include <functional>
// data struct
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
// debug
#include <chrono>
// thread
#include <thread>

// log and profile
#include "Lumi/Core/Core.h"
#include "Lumi/Core/Log.h"
#include "Lumi/Debug/Instrumentor.h"

#ifdef LM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // _LM_WINDOWS_
