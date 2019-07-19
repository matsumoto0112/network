#pragma once

#include "Utility/Math/Primitive2D.h"

namespace Utility {

class Collision2D {
public:
    static bool point_aabb(const Math::Vector2& point, const Math::AABB2D& aabb);
    static bool circle_segment(const Math::Circle2D& circle, const Math::Segment2D& segment);
    static bool circle_circle(const Math::Circle2D& circle1, const Math::Circle2D& circle2);
    static bool circle_aabb(const Math::Circle2D& circle, const Math::AABB2D& aabb);
    static bool circle_obb(const Math::Circle2D& circle, const Math::OBB2D& obb);
    static bool aabb_aabb(const Math::AABB2D& aabb1, const Math::AABB2D& aabb2);
    static bool obb_obb(const Math::OBB2D& obb1, const Math::OBB2D& obb2);
};

} //Utility 