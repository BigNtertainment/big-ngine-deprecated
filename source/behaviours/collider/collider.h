#include "types/behaviour/behaviour.h"

#include <functional>

namespace BigNgine {
    class ColliderBehaviour : public Behaviour {
        using CollisionCallback = std::function<void(ColliderBehaviour*)>;
    public:
        void Start() override;
        void Update(int deltaTime) override;
        
        void SetCollisionCallback(CollisionCallback callback);

        bool CollidesWith(Vector2 point);

    private:
        CollisionCallback collisionCallback;
    };
}