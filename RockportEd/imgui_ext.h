#pragma once
#include "imgui\imgui.h"

inline ImVec2 operator-(const ImVec2& l, const ImVec2& r) {
   return{ l.x - r.x, l.y - r.y };
}
inline ImVec2 operator+(const ImVec2& l, const ImVec2& r) {
   return{ l.x + r.x, l.y + r.y };
}
inline ImVec2 operator>>(const ImVec2& vec, const size_t minusY) {
   return{ vec.x, vec.y - minusY };
}
inline ImVec2 operator<<(const ImVec2& vec, const size_t minusX) {
   return{ vec.x - minusX, vec.y };
}
inline ImVec2 operator/(const ImVec2& vec, const size_t div) {
   return{ vec.x / div, vec.y / div };
}