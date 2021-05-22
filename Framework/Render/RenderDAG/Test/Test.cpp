
#include "../DAG.hpp"
int main()
{
    FlyEngine::DAG::DirectedAcyclicGraph dag;
    auto                                 gbuffer0 = dag.AddResourceNode("GBuffer0");
    auto                                 gbuffer1 = dag.AddResourceNode("GBuffer1");
    auto                                 gbuffer2 = dag.AddResourceNode("GBuffer2");
    auto                                 deferLightedRT = dag.AddResourceNode("Defer Lighted");
    auto                                 deferLightingPass = dag.AddPassNode(
        "Defer Lighting",
        {gbuffer0, gbuffer1, gbuffer2},
        {deferLightedRT});
    auto gbPass = dag.AddPassNode(
        "GBuffer Pass",
        {},
        {gbuffer0, gbuffer1, gbuffer2});
    FlyEngine::DAG::DAGCompiler compiler;
    compiler.Compiler(dag);
    return 1;
}