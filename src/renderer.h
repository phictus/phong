#pragma once

typedef struct { float x, y, w, h; } Rect;
typedef enum { Yellow, Red, Blue } Color;

void phInitRenderer();
void phDestroyRenderer();
void phRenderRect(const Rect* rect, Color color);
