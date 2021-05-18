
#include "../SceneDefines.hpp"

int main()
{
    FlyEngine::SCENE::Scene scene;

    auto gameObject1 = scene.AddGameObject("gameObject1");
    auto gameObject2 = scene.AddGameObject("gameObject2");
    auto gameObject3 = scene.AddGameObject("gameObject3");
    auto gameObject4 = scene.AddGameObject("gameObject4");

    auto gameObject5 = scene.AddGameObject(gameObject1, "gameObject5");
    auto gameObject6 = scene.AddGameObject(gameObject2, "gameObject6");
    auto gameObject7 = scene.AddGameObject(gameObject3, "gameObject7");
    auto gameObject8 = scene.AddGameObject(gameObject3, "gameObject8");
    auto gameObject9 = scene.AddGameObject(gameObject1, "gameObject9");

    auto gameObject10 = scene.AddGameObject(gameObject8, "gameObject10");

    FlyEngine::SCENE::SceneCompiler compiler;
    compiler.Compiler(scene);
    return 1;
}