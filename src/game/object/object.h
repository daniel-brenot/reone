#pragma once

#include "../../render/modelinstance.h"
#include "../../render/walkmesh.h"
#include "../../resources/gfffile.h"

#include "../types.h"

namespace reone {

namespace game {

class Object {
public:
    virtual void animate(const std::string &anim, int flags = 0);
    virtual void update(const UpdateContext &ctx);
    virtual void initGL();
    virtual void saveTo(AreaState &state) const;
    virtual void loadState(const AreaState &state);

    float distanceTo(const glm::vec3 &point) const;
    bool contains(const glm::vec3 &point) const;

    // Setters
    void setPosition(const glm::vec3 &position);
    void setHeading(float heading);
    void setSynchronize(bool synchronize);

    // Getters
    uint32_t id() const;
    ObjectType type() const;
    const std::string &tag() const;
    const glm::vec3 &position() const;
    float heading() const;
    const glm::mat4 &transform() const;
    std::shared_ptr<render::ModelInstance> model() const;
    std::shared_ptr<render::Walkmesh> walkmesh() const;

protected:
    uint32_t _id { 0 };
    ObjectType _type { ObjectType::None };
    float _drawDistance { 1024.0f };
    float _fadeDistance { 256.0f };
    std::string _tag;
    glm::vec3 _position { 0.0f };
    float _heading { 0.0f };
    glm::mat4 _transform { 1.0f };
    std::shared_ptr<render::ModelInstance> _model;
    std::shared_ptr<render::Walkmesh> _walkmesh;
    bool _synchronize { true };

    Object(uint32_t id);
    Object(Object &&) = default;

    Object &operator=(Object &&) = default;

    virtual void updateTransform();

private:
    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;
};

} // namespace game

} // namespace reone
