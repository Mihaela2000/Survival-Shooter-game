#include "lab_m1/tema1/tema1.h"
#include "lab_m1/tema1/tema1Transform2D.h"
#include "lab_m1/tema1/tema1Object2D.h"

#include <vector>
#include <iostream>


using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = -200;       // logic x
    logicSpace.y = -200;       // logic y
    logicSpace.width = 400;   // logic width
    logicSpace.height = 400;  // logic height

    glm::vec3 corner = glm::vec3(0, 0, 0);

    widthMap = 800;
    heightMap = 500;

    nrObst = 0;

    obstacle[nrObst].width = 30;
    obstacle[nrObst].height = 200;
    obstacle[nrObst].x = -300;
    obstacle[nrObst].y = -100;
    strcpy(obstacle[nrObst].name, "obst11");
    nrObst++;
    
    obstacle[nrObst].width = 100;
    obstacle[nrObst].height = 30;
    obstacle[nrObst].x = -235;
    obstacle[nrObst].y = -185;
    strcpy(obstacle[nrObst].name, "obst12");
    nrObst++;

    obstacle[nrObst].width = 100;
    obstacle[nrObst].height = 100;
    obstacle[nrObst].x = 180;
    obstacle[nrObst].y = -130;
    strcpy(obstacle[nrObst].name, "obst2");
    nrObst++;

    obstacle[nrObst].width = 70;
    obstacle[nrObst].height = 70;
    obstacle[nrObst].x = 260;
    obstacle[nrObst].y = 90;
    strcpy(obstacle[nrObst].name, "obst3");
    nrObst++;

    obstacle[nrObst].width = 150;
    obstacle[nrObst].height = 125;
    obstacle[nrObst].x = -50;
    obstacle[nrObst].y = 125;
    strcpy(obstacle[nrObst].name, "obst4");
    nrObst++;

    obstacle[nrObst].width = 70;
    obstacle[nrObst].height = 70;
    obstacle[nrObst].x = -200;
    obstacle[nrObst].y = 100;
    strcpy(obstacle[nrObst].name, "obst5");
    nrObst++;

    nrOfTr = 100;
    radius1 = 20;
    radius2 = 8;
    posX_player = 0;
    posY_player = 0;
    angle_player = 0;

    nrEnemy = 0;
    seconds = 0;

    widthHB = 100;
    heightHB = 20;
    posX_HB = 300;
    posY_HB = 170;
    health = 5;
    score = 0;
    display_score = 0.0f;
    scaleHB = 1;

    lenghtPr = 8;
    posX_pr = posX_player;
    posY_pr = posY_player;
    angle_pr = 0;
    distanceMovingPr = 250;
    projectileMoving = false;
    prSpeed = 0;
    prFireRate = 0;

    cout << "Score: " << score << endl;
    
    // mapa
    Mesh* map = tema1Object2D::CreateRectangle("map", corner, widthMap, heightMap, glm::vec3(0.2f, 0.2f, 0.2f), true);
    AddMeshToList(map);

    // obstacole
    for (int i = 0; i < nrObst; i++) {
        Mesh* obst = tema1Object2D::CreateRectangle(obstacle[i].name, corner, obstacle[i].width, obstacle[i].height, glm::vec3(0, 0.3f, 0), true);
        AddMeshToList(obst);
    }
    
    // jucator
    Mesh* circle1 = tema1Object2D::CreateCircle("circle1", radius1, nrOfTr, glm::vec3(0.8f, 0.8f, 0));
    AddMeshToList(circle1);
    Mesh* circle2 = tema1Object2D::CreateCircle("circle2", radius2, nrOfTr, glm::vec3(0.3f, 0.3f, 0.1f));
    AddMeshToList(circle2);
    Mesh* circle3 = tema1Object2D::CreateCircle("circle3", radius2, nrOfTr, glm::vec3(0.3f, 0.3f, 0.1f));
    AddMeshToList(circle3);

    // bara de viata
    Mesh* rectangle1 = tema1Object2D::CreateRectangle("rectangle1", corner, widthHB, heightHB, glm::vec3(0, 0, 0), false);
    AddMeshToList(rectangle1);
    Mesh* rectangle2 = tema1Object2D::CreateRectangle("rectangle2", corner, widthHB - 2.5f, heightHB - 2.5f, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle2);

    // proiectil
    Mesh* rectangle = tema1Object2D::CreateRectangle("rectangle", corner, lenghtPr, lenghtPr, glm::vec3(0, 0, 0), true);
    AddMeshToList(rectangle);
}

// creaza un nou inamic
void Tema1::CreateNewEnemy()
{
    glm::vec3 corner = glm::vec3(0, 0, 0);
    
    enemy[nrEnemy].alive = true;
    enemy[nrEnemy].length = 50;
    enemy[nrEnemy].lengthL = 20;
    enemy[nrEnemy].lengthR = 20;
    enemy[nrEnemy].speed = rand() % 50 + 50;
    enemy[nrEnemy].x = rand() % 800 - 400;
    enemy[nrEnemy].y = rand() % 500 - 250;

    strcpy(enemy[nrEnemy].name, "enemy00");
    enemy[nrEnemy].name[5] = '0' + nrEnemy / 10;
    enemy[nrEnemy].name[6] = '0' + nrEnemy % 10;

    strcpy(enemy[nrEnemy].nameEyeLeft, "enemy00L");
    enemy[nrEnemy].name[5] = '0' + nrEnemy / 10;
    enemy[nrEnemy].name[6] = '0' + nrEnemy % 10;

    strcpy(enemy[nrEnemy].nameEyeRight, "enemy00R");
    enemy[nrEnemy].name[5] = '0' + nrEnemy / 10;
    enemy[nrEnemy].name[6] = '0' + nrEnemy % 10;

    enemy[nrEnemy].direction = rand() % 4;
    if (enemy[nrEnemy].direction == 0)
        enemy[nrEnemy].y = -heightMap / 2;
    if (enemy[nrEnemy].direction == 1)
        enemy[nrEnemy].y = heightMap / 2;
    if (enemy[nrEnemy].direction == 2)
        enemy[nrEnemy].x = -widthMap / 2;
    if (enemy[nrEnemy].direction == 3)
        enemy[nrEnemy].x = widthMap / 2;

    Mesh* square1 = tema1Object2D::CreateRectangle(enemy[nrEnemy].nameEyeLeft, corner, enemy[nrEnemy].lengthL, enemy[nrEnemy].lengthL, glm::vec3(1, 0.3f, 0.1f), true);
    AddMeshToList(square1);
    Mesh* square2 = tema1Object2D::CreateRectangle(enemy[nrEnemy].nameEyeRight, corner, enemy[nrEnemy].lengthR, enemy[nrEnemy].lengthR, glm::vec3(1, 0.3f, 0.1f), true);
    AddMeshToList(square2);
    Mesh* square3 = tema1Object2D::CreateRectangle(enemy[nrEnemy].name, corner, enemy[nrEnemy].length, enemy[nrEnemy].length, glm::vec3(1, 0, 0), true);
    AddMeshToList(square3);

    nrEnemy++;
}

// pentru a nu crea incontinuu inamici, in momentul in care moare un inamic, acesta isi reface random pozitia
// daca nu am nici un inamic mort, se va apela functia de creare
void Tema1::GenerateNewEnemy(float deltaTimeSeconds)
{
    seconds += 3 * deltaTimeSeconds;

    if (seconds >= 6.0f && nrEnemy < 50) {
        if (nrEnemy > 0)
            for (int i = 0; i < nrEnemy; i++)
                if (enemy[i].alive == false) {
                    enemy[i].speed = rand() % 50 + 50;
                    enemy[i].x = rand() % 800 - 400;
                    enemy[i].y = rand() % 500 - 250;
                    enemy[i].alive = true;
                    enemy[i].direction = rand() % 4;
                    if (enemy[i].direction == 0)
                        enemy[i].y = -heightMap / 2;
                    if (enemy[i].direction == 1)
                        enemy[i].y = heightMap / 2;
                    if (enemy[i].direction == 2)
                        enemy[i].x = -widthMap / 2;
                    if (enemy[i].direction == 3)
                        enemy[i].x = widthMap / 2;
                    seconds = 0;
                    return;
                }

        CreateNewEnemy();
        //cout << "nr enemy: " << nrEnemy << endl;

        seconds = 0;
    }
}


glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);


    // bara viata
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    modelMatrix = visMatrix * tema1Transform2D::Translate(posX_HB, posY_HB);
    RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    modelMatrix = visMatrix * tema1Transform2D::Translate(posX_HB + 0.20f, posY_HB + 0.2f);
    if (health == 5) {
        scaleHB = 1;
    }
    if (health == 4) {
        scaleHB = 0.80f;
    }
    if (health == 3) {
        scaleHB = 0.60f;
    }
    if (health == 2) {
        scaleHB = 0.40f;
    }
    if (health == 1) {
        scaleHB = 0.20f;
    }
    if (health == 0) {
        scaleHB = 0;
    }
    modelMatrix *= tema1Transform2D::Scale(scaleHB, 1);
    RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);


    // inamici
    GenerateNewEnemy(deltaTimeSeconds);

    for (int i = 0; i < nrEnemy; i++) {
        if (enemy[i].alive == false) continue;
        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
        modelMatrix = visMatrix * tema1Transform2D::Translate(enemy[i].x + sin(enemy[i].angle_enemy + M_PI * 0.75f) * enemy[i].length / 2, enemy[i].y - cos(enemy[i].angle_enemy + M_PI * 0.75f) * enemy[i].length / 2);
        modelMatrix *= tema1Transform2D::Rotate(enemy[i].angle_enemy);
        RenderMesh2D(meshes[enemy[i].nameEyeLeft], shaders["VertexColor"], modelMatrix);

        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
        modelMatrix = visMatrix * tema1Transform2D::Translate(enemy[i].x + sin(enemy[i].angle_enemy + M_PI / 4) * enemy[i].length / 2, enemy[i].y - cos(enemy[i].angle_enemy + M_PI / 4) * enemy[i].length / 2);
        modelMatrix *= tema1Transform2D::Rotate(enemy[i].angle_enemy);
        RenderMesh2D(meshes[enemy[i].nameEyeRight], shaders["VertexColor"], modelMatrix);

        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
        modelMatrix = visMatrix * tema1Transform2D::Translate(enemy[i].x, enemy[i].y);
        modelMatrix *= tema1Transform2D::Rotate(enemy[i].angle_enemy);
        RenderMesh2D(meshes[enemy[i].name], shaders["VertexColor"], modelMatrix);
    }


    // jucator
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    modelMatrix = visMatrix * tema1Transform2D::Translate(posX_player + sin(angle_player + M_PI / 6) * 0.8f * radius1, posY_player - cos(angle_player + M_PI / 6) * 0.8f * radius1);
    RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    modelMatrix = visMatrix * tema1Transform2D::Translate(posX_player + sin(angle_player - M_PI / 6) * 0.8f * radius1, posY_player - cos(angle_player - M_PI / 6) * 0.8f * radius1);
    RenderMesh2D(meshes["circle3"], shaders["VertexColor"], modelMatrix);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    modelMatrix = visMatrix * tema1Transform2D::Translate(posX_player, posY_player);
    modelMatrix *= tema1Transform2D::Rotate(angle_player);
    RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);


    // proiectil
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    modelMatrix = visMatrix * tema1Transform2D::Translate(posX_pr, posY_pr);
    modelMatrix *= tema1Transform2D::Rotate(angle_player);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);


    // obstacole
    for (int i = 0; i < nrObst; i++) {
        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
        modelMatrix = visMatrix * tema1Transform2D::Translate(obstacle[i].x, obstacle[i].y);
        RenderMesh2D(meshes[obstacle[i].name], shaders["VertexColor"], modelMatrix);
    }


    //harta
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    modelMatrix = visMatrix * tema1Transform2D::Translate(0,0);
    RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}


bool Tema1::CollisionProjectileAndEnemy(float posXNew_enemy, float posYNew_enemy, float posXNew_pr, float posYNew_pr)
{

    // jucator - inamic
    glm::vec2 centerCircle = { posX_player, posY_player };
    glm::vec2 centerRectangle = { posXNew_enemy, posYNew_enemy };
    glm::vec2 difference;
    glm::vec2 clamped;
    glm::vec2 closest;
    glm::vec2 halfExtendsRectangle;

    halfExtendsRectangle = { enemyLength / 2.0f, enemyLength / 2.0f };

    difference = centerCircle - centerRectangle;

    clamped = glm::clamp(difference, -halfExtendsRectangle, halfExtendsRectangle);

    closest = centerRectangle + clamped;

    difference = closest - centerCircle;

    
    if (glm::length(difference) < radius1) {
        collEnemy = true;
        return true;
    }


    // proiectil - inamic
    if (posXNew_pr <= posXNew_enemy + enemyLength * 0.75f &&
        posXNew_pr >= posXNew_enemy - enemyLength * 0.75f &&
        posYNew_pr <= posYNew_enemy + enemyLength * 0.75f &&
        posYNew_pr >= posYNew_enemy - enemyLength * 0.75f) {
        return true;
    }
        
    return false;
}


bool Tema1::CollisionPlayer(float posXNew_player, float posYNew_player)
{
    // jucator - harta
    // margine stanga-dreapta harta
    if (posXNew_player - radius1 <= -widthMap / 2 || posXNew_player + radius1 >= widthMap / 2)
        return true;

    // margine sus-jos harta
    if (posYNew_player - radius1 <= -heightMap / 2 || posYNew_player + radius1 >= heightMap / 2)
        return true;


    // jucator - obstacole

    glm::vec2 centerCircle = { posXNew_player, posYNew_player };
    glm::vec2 centerRectangle;
    glm::vec2 difference;
    glm::vec2 clamped;
    glm::vec2 closest;
    glm::vec2 halfExtendsRectangle;


    for (int i = 0; i < nrObst; i++) {

        centerRectangle = { obstacle[i].x , obstacle[i].y };

        halfExtendsRectangle = { obstacle[i].width / 2.0f, obstacle[i].height / 2.0f };

        difference = centerCircle - centerRectangle;

        clamped = glm::clamp(difference, -halfExtendsRectangle, halfExtendsRectangle);

        closest = centerRectangle + clamped;

        difference = closest - centerCircle;

        if (glm::length(difference) < radius1) {
            return true;
        }
    }

    return false;
}


bool Tema1::CollisionProjectile(float posXNew_pr, float posYNew_pr)
{
    // proiectil - harta
    // margine stanga-dreapta harta
    if (posXNew_pr <= -widthMap / 2 || posXNew_pr >= widthMap / 2)
        return true;

    // margine sus-jos harta
    if (posYNew_pr <= -heightMap / 2 || posYNew_pr >= heightMap / 2)
        return true;

    for (int i = 0; i < nrObst; i++) {
        if (posXNew_pr <= obstacle[i].x + obstacle[i].width / 2 &&
            posXNew_pr >= obstacle[i].x - obstacle[i].width / 2 &&
            posYNew_pr <= obstacle[i].y + obstacle[i].height / 2 &&
            posYNew_pr >= obstacle[i].y - obstacle[i].height / 2) {
            return true;
        }
    }
    return false;
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    float posXNewDeltaPlayer = 0;
    float posYNewDeltaPlayer = 0;
    float posXNewDeltaEnemy = 0;
    float posYNewDeltaEnemy = 0;
    float posXNewDeltaPr = 0;
    float posYNewDeltaPr = 0 ;


    if (deltaTime < 0 || isinf(deltaTime)) return;

    if (window->KeyHold(GLFW_KEY_W)) {
        posYNewDeltaPlayer += 200 * deltaTime;

    }

    if (window->KeyHold(GLFW_KEY_A)) {
        posXNewDeltaPlayer -= 200 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        posYNewDeltaPlayer -= 200 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        posXNewDeltaPlayer += 200 * deltaTime;
    }


    if (!CollisionPlayer(posX_player + posXNewDeltaPlayer, posY_player + posYNewDeltaPlayer)) {
        logicSpace.x += posXNewDeltaPlayer;
        posX_player += posXNewDeltaPlayer;
        posX_HB += posXNewDeltaPlayer;

        logicSpace.y += posYNewDeltaPlayer;
        posY_player += posYNewDeltaPlayer;
        posY_HB += posYNewDeltaPlayer;
    }

    display_score += deltaTime;
    for (int i = 0; i < nrEnemy; i++) {
        if (enemy[i].alive == false) continue;
        enemy[i].angle_enemy = atan2(posY_player - enemy[i].y, posX_player - enemy[i].x);
        posXNewDeltaEnemy += cos(enemy[i].angle_enemy) * enemy[i].speed * deltaTime;
        posYNewDeltaEnemy += sin(enemy[i].angle_enemy) * enemy[i].speed * deltaTime;


        if ((CollisionProjectileAndEnemy(enemy[i].x + posXNewDeltaEnemy, enemy[i].y + posYNewDeltaEnemy, posX_pr, posY_pr))) {
            
            if (collEnemy) {
                health--;
                collEnemy = false;
            }
            else {
                score++;
                if (display_score > 9.0f) {
                    cout << "Score: " << score << endl;
                    display_score = 0;
                }
            }
            
            enemy[i].alive = false;
            posX_pr = posX_player;
            posY_pr = posY_player;
            angle_pr = angle_player;
            projectileMoving = false;
            prSpeed = 0;
            prFireRate = 0;
            continue;
        }

        enemy[i].x += cos(enemy[i].angle_enemy) * enemy[i].speed * deltaTime;
        enemy[i].y += sin(enemy[i].angle_enemy) * enemy[i].speed * deltaTime;
    }

    // update proiectile
    prFireRate += 5 * deltaTime;

    if (prFireRate >= 0.2f) {
        
        
        if (!projectileMoving) {
            posX_pr = posX_player;
            posY_pr = posY_player;
            angle_pr = angle_player;
            prFireRate = 0;

        }
        else {
            posX_pr += sin(angle_pr) * prSpeed * deltaTime;
            posY_pr -= cos(angle_pr) * prSpeed * deltaTime;

            distPlayerProjectil = sqrt((posX_pr - posX_player) * (posX_pr - posX_player) + (posY_pr - posY_player) * (posY_pr - posY_player));
            if (distPlayerProjectil > distanceMovingPr) {
                posX_pr = posX_player;
                posY_pr = posY_player;
                angle_pr = angle_player;
                projectileMoving = false;
                prSpeed = 0;
                prFireRate = 0;
            }
        }
    }

    if (health <= 0) {

        cout << "FINAL SCORE: " << score << endl << endl;
        cout << "   _____          __  __ ______      ______      ________ _____" << endl;
        cout << "  / ____|   /\\   |  \\\/  |  ____|    / __ \\ \\    / /  ____|  __ \\ " << endl;
        cout << " | |  __   /  \\  | \\  / | |__      | |  | \\ \\  / /| |__  | |__) | " << endl;
        cout << " | | |_ | / /\\ \\ | |\\/| |  __|     | |  | |\\ \\/ / |  __| |  _  /" << endl;
        cout << " | |__| |/ ____ \\| |  | | |____    | |__| | \\  /  | |____| | \\ \\ " << endl;
        cout << "  \\_____/_/    \\_\\_|  |_|______|    \\____/   \\/   |______|_|  \\_\\ " << endl << endl;

        exit(0);
    }

    if (score >= 30) {

        cout << "FINAL SCORE: " << score << endl << endl;
        cout << "$$\\     $$\\  $$$$$$\\  $$\\   $$\\              $$\\      $$\\ $$$$$$\\ $$\\   $$\\" << endl;
        cout << "\\$$\\   $$  |$$  __$$\\ $$ |  $$ |             $$ | $\\  $$ |\\_$$  _|$$$\\  $$ |" << endl;
        cout << " \\$$\\ $$  / $$ /  $$ |$$ |  $$ |             $$ |$$$\\ $$ |  $$ |  $$$$\\ $$ |" << endl;
        cout << "  \\$$$$  /  $$ |  $$ |$$ |  $$ |             $$ $$ $$\\$$ |  $$ |  $$ $$\\$$ |" << endl;
        cout << "   \\$$  /   $$ |  $$ |$$ |  $$ |             $$$$  _$$$$ |  $$ |  $$ \\$$$$ |" << endl;
        cout << "    $$ |    $$ |  $$ |$$ |  $$ |             $$$  / \\$$$ |  $$ |  $$ |\\$$$ |" << endl;
        cout << "    $$ |     $$$$$$  |\\$$$$$$  |             $$  /   \\$$ |$$$$$$\\ $$ | \\$$ |" << endl;
        cout << "    \\__|     \\______/  \\______/              \\__/     \\__|\\______|\\__|  \\__|" << endl;

        exit(0);
    }

}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    glm::ivec2 resolution = window->GetResolution();
    float distance_x;
    float distance_y;
    distance_x = mouseX - resolution.x / 2;
    distance_y = mouseY - resolution.y / 2;
    angle_player = atan2(distance_x, distance_y);
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        prSpeed += 500;
        prFireRate = 0;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        projectileMoving = true;
    }
}
