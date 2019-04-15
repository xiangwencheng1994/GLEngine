#include <assimp/Importer.hpp>

_declspec(dllexport) void a()
{
    Assimp::Importer    p;
    p.ReadFile("C", 0);
}
