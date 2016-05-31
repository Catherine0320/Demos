#pragma once

#ifdef ADD_IMP
#define CLASS_DECL __declspec(dllexport)
#else
#define CLASS_DECL __declspec(dllimport)
#endif

double CLASS_DECL Add(double a, double b);
