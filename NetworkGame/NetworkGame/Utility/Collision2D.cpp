#include "Collision2D.h"
#include "Utility/Math/MathUtility.h"
#include <vector>

namespace {
//�~���������AABB�ɕϊ�����
Math::AABB2D circleToAABB(const Math::Circle2D& circle) {
    Math::AABB2D result(circle.center, Math::Vector2(circle.radius, circle.radius));
    return result;
}

//�~�Ɛ����̋����̓��
float lengthCircleSegment2(const Math::Circle2D& circle, const Math::Segment2D& segment) {
    const Math::Vector2 v1 = circle.center - segment.position;
    const Math::Vector2 v = segment.direction;
    //�W��t�𒲂ׂĐ����ɑ΂��ĉ~���ǂ̈ʒu�ɂ��邩���ׂ�
    float t = dot(v, v1) / dot(v, v);
    //�����̎n�_�̊O��
    if (t < 0) {
        return v1.lengthSq();
    }
    //�����̏I�_�̊O��
    else if (t > 1) {
        return (circle.center - segment.getEndPosition()).lengthSq();
    }
    //�����̊�
    return (v1 - v * t).lengthSq();
}

}

namespace Utility {

bool Collision2D::point_aabb(const Math::Vector2& point, const Math::AABB2D& aabb) {
    if (point.x < aabb.left())return false;
    if (point.x > aabb.right())return false;
    if (point.y < aabb.top())return false;
    if (point.y > aabb.bottom())return false;
    return true;
}

bool Collision2D::circle_circle(const Math::Circle2D& circle1, const Math::Circle2D& circle2) {
    float len2 = (circle1.center - circle2.center).lengthSq();
    return len2 < (circle1.radius * circle1.radius + circle2.radius * circle2.radius);
}

bool Collision2D::circle_segment(const Math::Circle2D& circle, const Math::Segment2D& segment) {
    //�����Ɖ~�̋��������a��菬���������瓖�����Ă���
    return lengthCircleSegment2(circle, segment) < (circle.radius * circle.radius);
}

bool Collision2D::circle_aabb(const Math::Circle2D& circle, const Math::AABB2D& aabb) {
    //�܂��ȒP��AABB���m�Ŕ��肵�A�������Ă��Ȃ�������I������    
    if (!aabb_aabb(circleToAABB(circle), aabb))return false;
    //�~�̒��S����`�̓����ɂ������瓖�����Ă���
    if (point_aabb(circle.center, aabb)) {
        return true;
    }
    //��`���\���������
    std::vector<Math::Segment2D> rectSegments
    {
        Math::Segment2D(Math::Vector2(aabb.left(),aabb.top()),Math::Vector2(aabb.left(),aabb.bottom())),
        Math::Segment2D(Math::Vector2(aabb.left(),aabb.bottom()),Math::Vector2(aabb.right(),aabb.bottom())),
        Math::Segment2D(Math::Vector2(aabb.right(),aabb.bottom()),Math::Vector2(aabb.right(),aabb.top())),
        Math::Segment2D(Math::Vector2(aabb.right(),aabb.top()),Math::Vector2(aabb.left(),aabb.top()))
    };
    //�����ꂩ�̋�`�̐����̂Ɖ~���Փ˂��Ă��邩
    for (int i = 0; i < 4; i++) {
        if (circle_segment(circle, rectSegments[i])) {
            return true;
        }
    }

    return false;
}

bool Collision2D::circle_obb(const Math::Circle2D& circle, const Math::OBB2D& obb) {
    //��]�����Ă��Ȃ�������AABB�Ƃ��ĉ~�Ɣ��肷��
    if (fabs(obb.rotate) < 0.001f) {
        return circle_aabb(circle, Math::OBB2D::toAABB2DIgnoreRotate(obb));
    }
    //AABB���m�Ŕ��肵�ē������Ă��Ȃ������烊�^�[������
    if (!aabb_aabb(circleToAABB(circle), Math::OBB2D::toAABB2D(obb))) {
        return false;
    }

    //OBB���`������������擾
    std::array<Math::Vector2, 4> v = obb.getVertices();
    std::vector<Math::Segment2D> segments(4);
    for (int i = 0; i < 4; i++) {
        segments[i] = Math::Segment2D(v[i], v[(i + 1) % 4]);
    }

    //�����Ɖ~���Փ˂��Ă��邩
    for (int i = 0; i < 4; i++) {
        if (circle_segment(circle, segments[i])) {
            return true;
        }
    }
    return false;
}


bool Collision2D::aabb_aabb(const Math::AABB2D & aabb1, const Math::AABB2D & aabb2) {
    if (aabb1.left() > aabb2.right())return false;
    if (aabb1.right() < aabb2.left())return false;
    if (aabb1.top() > aabb2.bottom())return false;
    if (aabb1.bottom() < aabb2.top())return false;
    return true;
}

bool Collision2D::obb_obb(const Math::OBB2D& obb1, const Math::OBB2D& obb2) {
    //��]���Ă��Ȃ����AABB�ɕϊ����Ĕ��肷��
    if (fabs(obb1.rotate) < 0.1f && fabs(obb2.rotate) < 0.1f) {
        return aabb_aabb(Math::OBB2D::toAABB2DIgnoreRotate(obb1), Math::OBB2D::toAABB2DIgnoreRotate(obb2));
    }
    //�܂�AABB�ɓ��e���Ĕ��肵�������Ă��Ȃ���΃��^�[������
    if (!aabb_aabb(Math::OBB2D::toAABB2D(obb1), Math::OBB2D::toAABB2D(obb2))) {
        return false;
    }

    //OBB���m�̕����������ƂɏՓ˔���
    std::array<Math::Vector2, 4> va = obb1.getVertices();
    std::array<Math::Vector2, 4> vb = obb2.getVertices();
    const Math::Vector2 ea1 = (va[2] - va[1]) * 0.5f;
    const Math::Vector2 ea2 = (va[0] - va[1]) * 0.5f;
    const Math::Vector2 eb1 = (vb[2] - vb[1]) * 0.5f;
    const Math::Vector2 eb2 = (vb[0] - vb[1]) * 0.5f;
    const Math::Vector2 v = obb1.position - obb2.position;
    Math::Vector2 L = ea1.getNormal();
    float ra = ea1.length();
    float rb = Math::MathUtility::abs(dot(eb1, L)) + Math::MathUtility::abs(dot(eb2, L));
    float len = Math::MathUtility::abs(dot(v, L));
    if (len >= ra + rb)return false;

    L = ea2.getNormal();
    ra = ea2.length();
    rb = Math::MathUtility::abs(dot(eb1, L)) + Math::MathUtility::abs(dot(eb2, L));
    len = Math::MathUtility::abs(dot(v, L));
    if (len >= ra + rb)return false;

    L = eb1.getNormal();
    ra = Math::MathUtility::abs(dot(ea1, L)) + Math::MathUtility::abs(dot(ea2, L));
    rb = eb1.length();
    len = Math::MathUtility::abs(dot(v, L));
    if (len >= ra + rb)return false;

    L = eb2.getNormal();
    ra = Math::MathUtility::abs(dot(ea1, L)) + Math::MathUtility::abs(dot(ea2, L));
    rb = eb2.length();
    len = Math::MathUtility::abs(dot(v, L));
    if (len >= ra + rb)return false;
    return true;
}

} //Utility 
