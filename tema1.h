#pragma once

#include "components/simple_scene.h"
#include <string>
#include <core/engine.h>


namespace m1
{

    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct Obstacle 
        {
            float x;
            float y;
            float width;
            float height;
            char name[10];
            bool collision;
        };

        struct Enemy 
        {
            float x;
            float y;
            float length;
            float lengthL;
            float lengthR;
            float speed;
            char name[10];
            char nameEyeLeft[10];
            char nameEyeRight[10];
            bool alive;
            int direction;
            float angle_enemy;
        };
    
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        float clamp(float value, float min, float max) {
            return std::max(min, std::min(max, value));
        }

    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

        bool CollisionPlayer(float posXNew_player, float posYNew_player);
        void CreateNewEnemy();
        void GenerateNewEnemy(float deltaTimeSeconds);
        bool CollisionProjectileAndEnemy(float posXNew_enemy, float posYNew_enemy, float posX_pr, float posY_pr);
        bool CollisionProjectile(float posXNew_projectile, float posYNew_projectile);

        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;

        float widthMap;
        float heightMap;

        Obstacle obstacle[10];
        int nrObst;

        Enemy enemy[50];
        int nrEnemy;
        float enemyLength = 50;
        float seconds = 0;

        float nrOfTr;
        float radius1;
        float radius2;
        float posX_player;
        float posY_player;
        float angle_player;

        float widthHB;
        float heightHB;
        float posX_HB;
        float posY_HB;
        float score;
        float display_score;
        float health;
        float scaleHB;

        float lenghtPr;
        float posX_pr;
        float posY_pr;
        float distanceMovingPr;
        float projectileMoving;
        float angle_pr;
        float prSpeed;
        float prFireRate;
        float distPlayerProjectil;
        
        bool collEnemy = false;

    };
}