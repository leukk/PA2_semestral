#include "SceneObject.h"

SceneObject::SceneObject(OBJECT_TYPE objectType, string tags) :
    position(Vec2::Zero()), size(Vec2::Zero()), m_objectType(objectType), m_tags(std::move(tags)) {
}

SceneObject::SceneObject(Vec2 pos, Vec2 size, OBJECT_TYPE objectType, string tags) :
    position(pos), size(size), m_objectType(objectType), m_tags(std::move(tags)){
}


