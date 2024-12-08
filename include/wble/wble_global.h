#pragma once

#include <QtCore/qglobal.h>

#if defined(WBLE_LIBRARY)
#define WBLE_EXPORT Q_DECL_EXPORT
#else
#define WBLE_EXPORT Q_DECL_IMPORT
#endif
